/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 Alexander Entinger / LXRobotics GmbH
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

#include <avr/io.h>

#include <spectre/hal/avr/AT90CAN128/UART1.h>
#include <spectre/hal/avr/AT90CAN128/CriticalSection.h>
#include <spectre/hal/avr/AT90CAN128/InterruptController.h>

#include <spectre/driver/serial/Serial.h>
#include <spectre/driver/serial/SerialQueue.h>
#include <spectre/driver/serial/UART/UART_CallbackHandler.h>
#include <spectre/driver/serial/UART/UART_SerialController.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint16_t const RX_QUEUE_SIZE = 16;
static uint16_t const TX_QUEUE_SIZE = 16;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  AT90CAN128::InterruptController int_ctrl  (&EIMSK, &TIMSK2, &TIMSK1, &TIMSK0, &CANGIE, &SPCR, &UCSR0B, &ACSR, &ADCSRA, &EECR, &TIMSK3, &UCSR1B, &TWCR, &SPMCSR);
  AT90CAN128::CriticalSection     crit_sec  (&SREG);
  AT90CAN128::UART1               uart1     (&UDR1, &UCSR1A, &UCSR1B, &UCSR1C, &UBRR1, int_ctrl, F_CPU);

  int_ctrl.registerISR(AT90CAN128::USART1_UART_DATA_REGISTER_EMPTY, AT90CAN128::UART1::ISR_onTransmitComplete, &uart1);
  int_ctrl.registerISR(AT90CAN128::USART1_RECEIVE_COMPLETE,         AT90CAN128::UART1::ISR_onReceiveComplete,  &uart1);

  /* DRIVER ***************************************************************************/

  serial::SerialQueue                 rx_queue        (RX_QUEUE_SIZE),
                                      tx_queue        (TX_QUEUE_SIZE);
  serial::UART::UART_SerialController serial_ctrl     (uart1, uart1, crit_sec, rx_queue, tx_queue);
  serial::UART::UART_CallbackHandler  serial_callback (serial_ctrl);
  serial::Serial                      serial          (serial_ctrl);

  uart1.registerUARTCallbackInterface (&serial_callback);

  int_ctrl.enableInterrupt            (AT90CAN128::GLOBAL);

  /* APPLICATION **********************************************************************/

  uint8_t baud_rate = static_cast<uint8_t>(serial::interface::SerialBaudRate::B115200);
  uint8_t parity    = static_cast<uint8_t>(serial::interface::SerialParity::None     );
  uint8_t stop_bit  = static_cast<uint8_t>(serial::interface::SerialStopBit::_1      );

  serial.open();
  serial.ioctl(serial::IOCTL_SET_BAUDRATE, static_cast<void *>(&baud_rate));
  serial.ioctl(serial::IOCTL_SET_PARITY,   static_cast<void *>(&parity   ));
  serial.ioctl(serial::IOCTL_SET_STOPBIT,  static_cast<void *>(&stop_bit ));

  uint8_t buf[5] = {0};
  for(;;)
  {
    ssize_t const bytes_received = serial.read(buf, 5);

    for(ssize_t bytes_written = 0; bytes_written != bytes_received; )
    {
      bytes_written += serial.write(buf + bytes_written, bytes_received - bytes_written);
    }
  }

  serial.close();

  return 0;
}