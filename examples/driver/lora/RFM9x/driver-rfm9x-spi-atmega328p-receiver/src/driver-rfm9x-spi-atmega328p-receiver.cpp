/**
 * lora-sniffer is a LoRa packet sniffer based on the HopeRF RF95.
 * Copyright (C) 2018 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <string.h>

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/EINT0.h>
#include <spectre/hal/avr/ATMEGA328P/UART0.h>
#include <spectre/hal/avr/ATMEGA328P/Flash.h>
#include <spectre/hal/avr/ATMEGA328P/SpiMaster.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/driver/serial/Serial.h>
#include <spectre/driver/serial/UART/UART_ReceiveBuffer.h>
#include <spectre/driver/serial/UART/UART_TransmitBuffer.h>
#include <spectre/driver/serial/UART/UART_CallbackHandler.h>
#include <spectre/driver/serial/UART/UART_SerialController.h>

#include <spectre/driver/lora/RFM9x/RFM9x.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Debug.h>
#include <spectre/driver/lora/RFM9x/RFM9x_IoSpi.h>
#include <spectre/driver/lora/RFM9x/RFM9x_Control.h>
#include <spectre/driver/lora/RFM9x/RFM9x_FifoControl.h>
#include <spectre/driver/lora/RFM9x/RFM9x_InterruptControl.h>
#include <spectre/driver/lora/RFM9x/packet_mode/RFM9x_Dio0EventCallback.h>
#include <spectre/driver/lora/RFM9x/packet_mode/RFM9x_onPacketSentCallback.h>
#include <spectre/driver/lora/RFM9x/packet_mode/RFM9x_onPayloadReadyCallback.h>

#include <lora-sniffer/SerialReader.h>
#include <lora-sniffer/SerialWriter.h>
#include <lora-sniffer/CommandParser.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;
using namespace application;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint16_t                    const RX_BUFFER_SIZE         = 16;
static uint16_t                    const TX_BUFFER_SIZE         = 128;

static hal::interface::SpiMode     const RFM9x_SPI_MODE         = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const RFM9x_SPI_BIT_ORDER    = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const RFM9x_SPI_PRESCALER    = 16;       /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz */

static uint32_t                    const RFM9x_F_XOSC_Hz        = 32000000; /* 32 MHz                                      */
static hal::interface::TriggerMode const RFM9x_INT_TRIGGER_MODE = hal::interface::TriggerMode::RisingEdge;


/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /************************************************************************************
   * HAL
   ************************************************************************************/

  ATMEGA328P::Flash                               flash;
  ATMEGA328P::InterruptController                 int_ctrl                               (&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ADCSRA, &EECR, &ACSR, &TWCR, &SPMCSR);
  ATMEGA328P::CriticalSection                     crit_sec                               (&SREG);

  /* UART0 ****************************************************************************/
  ATMEGA328P::UART0                               uart0                                  (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);
  ATMEGA328P::UART0_TransmitRegisterEmptyCallback uart0_uart_data_register_empty_callback(uart0);
  ATMEGA328P::UART0_ReceiveCompleteCallback       uart0_receive_complete_callback        (uart0);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::USART_UART_DATA_REGISTER_EMPTY), &uart0_uart_data_register_empty_callback);
  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::USART_RECEIVE_COMPLETE        ), &uart0_receive_complete_callback        );

  /* SPI/CS for RFM95 *****************************************************************/
  /* As the datasheet state: 'If SS is configured as an input and is driven low
   * while MSTR is set, MSTR will be cleared.'. This means that in this special
   * case where the CS pin is equal with SS pin we need to set it before configuring
   * the SPI interface.
   */
  ATMEGA328P::DigitalOutPin rfm9x_cs  (&DDRB, &PORTB,        2);     /* CS   = D10 = PB2 */
  ATMEGA328P::DigitalOutPin rfm9x_sck (&DDRB, &PORTB,        5);     /* SCK  = D13 = PB5 */
  ATMEGA328P::DigitalInPin  rfm9x_miso(&DDRB, &PORTB, &PINB, 4);     /* MOSI = D12 = PB4 */
  ATMEGA328P::DigitalOutPin rfm9x_mosi(&DDRB, &PORTB,        3);     /* MOSI = D11 = PB3 */

  rfm9x_cs.set();
  rfm9x_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  ATMEGA328P::SpiMaster     spi_master(&SPCR, &SPSR, &SPDR);

  spi_master.setSpiMode     (RFM9x_SPI_MODE     );
  spi_master.setSpiBitOrder (RFM9x_SPI_BIT_ORDER);
  spi_master.setSpiPrescaler(RFM9x_SPI_PRESCALER);

  /* EXT INT #0 for notifications by RFM9x ********************************************/
  ATMEGA328P::DigitalInPin                          rfm9x_dio0_int_pin        (&DDRD, &PORTD, &PIND, 2); /* D2 = PD2 = INT0 */
  ATMEGA328P::EINT0                                 rfm9x_dio0_eint0          (&EICRA, int_ctrl);
  ATMEGA328P::EINT0_ExternalInterruptEventCallback  rfm9x_dio0_eint0_callback (rfm9x_dio0_eint0);

  rfm9x_dio0_int_pin.setPullUpMode (hal::interface::PullUpMode::PULL_UP);

  rfm9x_dio0_eint0.setTriggerMode  (RFM9x_INT_TRIGGER_MODE);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::EXTERNAL_INT0), &rfm9x_dio0_eint0_callback);



  /***********************************************************************************
   * DRIVER
   ***********************************************************************************/

  /* SERIAL **************************************************************************/
  serial::UART::UART_TransmitBuffer   serial_tx_buffer  (TX_BUFFER_SIZE, crit_sec, uart0);
  serial::UART::UART_ReceiveBuffer    serial_rx_buffer  (RX_BUFFER_SIZE, crit_sec, uart0);
  serial::UART::UART_CallbackHandler  serial_callback   (serial_tx_buffer, serial_rx_buffer);
  serial::UART::UART_SerialController serial_ctrl       (uart0);
  serial::Serial                      serial            (serial_ctrl, serial_tx_buffer, serial_rx_buffer);

  uart0.registerUARTCallback(&serial_callback);

  uint8_t baud_rate = static_cast<uint8_t>(serial::interface::SerialBaudRate::B115200);
  uint8_t parity    = static_cast<uint8_t>(serial::interface::SerialParity::None     );
  uint8_t stop_bit  = static_cast<uint8_t>(serial::interface::SerialStopBit::_1      );

  serial.open();
  serial.ioctl(serial::IOCTL_SET_BAUDRATE, static_cast<void *>(&baud_rate));
  serial.ioctl(serial::IOCTL_SET_PARITY,   static_cast<void *>(&parity   ));
  serial.ioctl(serial::IOCTL_SET_STOPBIT,  static_cast<void *>(&stop_bit ));

  /* RFM95********* *******************************************************************/
  lora::RFM9x::RFM9x_IoSpi                    rfm9x_spi                           (spi_master, rfm9x_cs      );
  lora::RFM9x::RFM9x_Control                  rfm9x_control                       (rfm9x_spi, RFM9x_F_XOSC_Hz);
  lora::RFM9x::RFM9x_InterruptControl         rfm9x_int_control                   (rfm9x_spi                 );
  lora::RFM9x::RFM9x_FifoControl              rfm9x_fifo_control                  (rfm9x_spi                 );

  lora::RFM9x::RFM9x_onPacketSentCallback     rfm9x_on_packet_sent_callback;
  lora::RFM9x::RFM9x_onPayloadReadyCallback   rfm9x_on_payload_ready_callback;

  lora::RFM9x::RFM9x_Dio0EventCallback        rfm9x_di0_event_callback            (rfm9x_int_control, rfm9x_on_packet_sent_callback, rfm9x_on_payload_ready_callback);

  lora::RFM9x::RFM9x                          rfm9x                               (rfm9x_control             );


  rfm9x_dio0_eint0.registerExternalInterruptCallback(&rfm9x_di0_event_callback);


  rfm9x.open();

  /* ALL ******************************************************************************/
  int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::GLOBAL));



  /* APPLICATION **********************************************************************/

  /* COMMANDS
   * 'DB\r'                 Print all registers of the RFM95 chip
   * 'MD [LORA|FSK_OOK]\r'  Set LoRa mode
   * 'FR 433000000\r'       Set frequency of module
   */

  SerialReader serial_reader(serial);
  SerialWriter serial_writer(serial);

  for(;;)
  {
    char cmd_str[16];

    if(serial_reader.readUntil('\r', cmd_str, 16))
    {
      if(CommandParser::isDebugCommand(cmd_str))
      {
        lora::RFM9x::RFM9x_Debug::debug_dumpAllRegs(serial_writer, flash, rfm9x_spi);
      }
    }
  }


  /* CLEANUP **************************************************************************/

  serial.close();
  rfm9x.close ();

  return 0;
}
