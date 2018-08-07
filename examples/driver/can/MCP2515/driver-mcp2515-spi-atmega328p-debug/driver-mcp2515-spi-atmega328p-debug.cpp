/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
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
 * This example programm is tailored for usage with Arduino Uno
 * and Seedstudio CAN Bus Shield V2.0
 *
 * Electrical interface:
 *   CS   = D10 = PB2
 *   SCK  = D13 = PB5
 *   MISO = D12 = PB4
 *   MOSI = D11 = PB3
 *   INT  = D2  = PD2 = INT0
 *
 * Upload via avrdude
 *   avrdude -p atmega328p -c avrisp2 -e -U flash:w:bin/driver-mcp2515-spi-atmega328p-debug
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/Flash.h>
#include <spectre/hal/avr/ATMEGA328P/SpiMaster.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA328P/CriticalSection.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/blox/hal/avr/ATMEGA328P/UART0.h>

#include <spectre/blox/driver/serial/SerialUart.h>

#include <spectre/driver/can/MCP2515/MCP2515_IoSpi.h>
#include <spectre/driver/can/MCP2515/MCP2515_Debug.h>

#include <spectre/debug/serial/DebugSerial.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint16_t                    const UART_RX_BUFFER_SIZE      = 0;
static uint16_t                    const UART_TX_BUFFER_SIZE      = 16;

static hal::interface::SpiMode     const MCP2515_SPI_MODE         = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const MCP2515_SPI_BIT_ORDER    = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const MCP2515_SPI_PRESCALER    = 16; /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz                     */

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /************************************************************************************
   * HAL
   ************************************************************************************/

  ATMEGA328P::Flash               flash;
  ATMEGA328P::InterruptController int_ctrl(&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ADCSRA, &EECR, &ACSR, &TWCR, &SPMCSR);
  ATMEGA328P::CriticalSection     crit_sec(&SREG);
  blox::ATMEGA328P::UART0         uart0   (&UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0, int_ctrl, F_CPU);

  /* SPI/CS for MCP2515 ***************************************************************/
  ATMEGA328P::DigitalOutPin mcp2515_cs  (&DDRB, &PORTB,        2); /* CS   = D10 = PB2 */
  ATMEGA328P::DigitalOutPin mcp2515_sck (&DDRB, &PORTB,        5); /* SCK  = D13 = PB5 */
  ATMEGA328P::DigitalInPin  mcp2515_miso(&DDRB, &PORTB, &PINB, 4); /* MISO = D12 = PB4 */
  ATMEGA328P::DigitalOutPin mcp2515_mosi(&DDRB, &PORTB,        3); /* MOSI = D11 = PB3 */

  mcp2515_cs.set();
  mcp2515_miso.setPullUpMode(hal::interface::PullUpMode::PULL_UP);

  ATMEGA328P::SpiMaster     spi_master(&SPCR, &SPSR, &SPDR);

  spi_master.setSpiMode     (MCP2515_SPI_MODE     );
  spi_master.setSpiBitOrder (MCP2515_SPI_BIT_ORDER);
  spi_master.setSpiPrescaler(MCP2515_SPI_PRESCALER);


  /************************************************************************************
   * DRIVER
   ************************************************************************************/

  /* SERIAL ***************************************************************************/
  blox::SerialUart   serial(crit_sec,
                            uart0(),
                            UART_RX_BUFFER_SIZE,
                            UART_TX_BUFFER_SIZE,
                            serial::interface::SerialBaudRate::B115200,
                            serial::interface::SerialParity::None,
                            serial::interface::SerialStopBit::_1);

  debug::DebugSerial debug_serial(serial());

  /* MCP2515 **************************************************************************/
  can::MCP2515::MCP2515_IoSpi mcp2515_io_spi(spi_master, mcp2515_cs);

  /* GLOBAL INTERRUPT *****************************************************************/
  int_ctrl.enableInterrupt(ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::GLOBAL));


  /************************************************************************************
   * APPLICATION
   ************************************************************************************/

  can::MCP2515::MCP2515_Debug::debug_dumpAllRegs(debug_serial, flash, mcp2515_io_spi);

  for(;;)
  {
  }

  return 0;
}