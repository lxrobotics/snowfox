/**
 * Snowfox is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2020 Alexander Entinger / LXRobotics GmbH
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

#include <snowfox/hal/avr/common/ATxxxx/UART0.h>

#include <snowfox/hal/avr/common/ATxxxx/util/UartUtil.h>

#if   defined(MCU_TYPE_atmega328p)
  #include <snowfox/hal/avr/ATMEGA328P/InterruptController.h>
#elif defined(MCU_TYPE_at90can32)
  #include <snowfox/hal/avr/AT90CAN32/InterruptController.h>
#elif defined(MCU_TYPE_at90can64)
  #include <snowfox/hal/avr/AT90CAN64/InterruptController.h>
#elif defined(MCU_TYPE_at90can128)
  #include <snowfox/hal/avr/AT90CAN128/InterruptController.h>
#elif defined(MCU_TYPE_atmega164p)
  #include <snowfox/hal/avr/ATMEGA164P/InterruptController.h>
#elif defined(MCU_TYPE_atmega324p)
  #include <snowfox/hal/avr/ATMEGA324P/InterruptController.h>
#elif defined(MCU_TYPE_atmega644p)
  #include <snowfox/hal/avr/ATMEGA644P/InterruptController.h>
#elif defined(MCU_TYPE_atmega1284p)
  #include <snowfox/hal/avr/ATMEGA1284P/InterruptController.h>
#elif defined(MCU_TYPE_atmega640)
  #include <snowfox/hal/avr/ATMEGA640/InterruptController.h>
#elif defined(MCU_TYPE_atmega1280)
  #include <snowfox/hal/avr/ATMEGA1280/InterruptController.h>
#elif defined(MCU_TYPE_atmega2560)
  #include <snowfox/hal/avr/ATMEGA2560/InterruptController.h>
#elif defined(MCU_TYPE_atmega16u4)
  #include <snowfox/hal/avr/ATMEGA16U4/InterruptController.h>
#elif defined(MCU_TYPE_atmega32u4)
  #include <snowfox/hal/avr/ATMEGA32U4/InterruptController.h>
#else
  #include <snowfox/hal/interface/interrupt/InterruptController.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATxxxx
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* UCSR0A */
#define RXC0_bm     (1<<7)
#define TXC0_bm     (1<<6)
#define UDRE0_bm    (1<<5)
#define FE0_bm      (1<<4)
#define DOR0_bm     (1<<3)
#define UPE0_bm     (1<<2)
#define U2X0_bm     (1<<1)
#define MPCM0_bm    (1<<0)

/* UCSR0B */
#define RXCIE0_bm   (1<<7)
#define TXCIE0_bm   (1<<6)
#define UDRIE0_bm   (1<<5)
#define RXEN0_bm    (1<<4)
#define TXEN0_bm    (1<<3)
#define UCSZ02_bm   (1<<2)
#define RXB80_bm    (1<<1)
#define TXB80_bm    (1<<0)

/* UCSR0C */
#define UMSEL01_bm  (1<<7)
#define UMSEL00_bm  (1<<6)
#define UPM01_bm    (1<<5)
#define UPM00_bm    (1<<4)
#define USBS0_bm    (1<<3)
#define UCSZ01_bm   (1<<2)
#define UCSZ00_bm   (1<<1)
#define UCPOL0_bm   (1<<0)

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

#if   defined(MCU_TYPE_atmega328p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA328P::toIntNum                 (ATMEGA328P::Interrupt::USART_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA328P::toIntNum                 (ATMEGA328P::Interrupt::USART_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_at90can32)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = AT90CAN32_64_128::toIntNum           (AT90CAN32::Interrupt::USART0_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = AT90CAN32_64_128::toIntNum           (AT90CAN32::Interrupt::USART0_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_at90can64)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = AT90CAN32_64_128::toIntNum           (AT90CAN64::Interrupt::USART0_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = AT90CAN32_64_128::toIntNum           (AT90CAN64::Interrupt::USART0_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_at90can128)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = AT90CAN32_64_128::toIntNum           (AT90CAN128::Interrupt::USART0_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = AT90CAN32_64_128::toIntNum           (AT90CAN128::Interrupt::USART0_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega164p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA164P::Interrupt::USART0_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA164P::Interrupt::USART0_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega324p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA324P::Interrupt::USART0_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA324P::Interrupt::USART0_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega644p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA644P::Interrupt::USART0_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA644P::Interrupt::USART0_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega1284p)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA1284P::Interrupt::USART0_UART_DATA_REGISTER_EMPTY);
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA164P_324P_644P_1284P::toIntNum (ATMEGA1284P::Interrupt::USART0_RECEIVE_COMPLETE        );
#elif defined(MCU_TYPE_atmega640)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum        (ATMEGA640::Interrupt::USART0_UART_DATA_REGISTER_EMPTY  );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum        (ATMEGA640::Interrupt::USART0_RECEIVE_COMPLETE          );
#elif defined(MCU_TYPE_atmega1280)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum        (ATMEGA1280::Interrupt::USART0_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum        (ATMEGA1280::Interrupt::USART0_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega2560)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = ATMEGA640_1280_2560::toIntNum        (ATMEGA2560::Interrupt::USART0_UART_DATA_REGISTER_EMPTY );
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = ATMEGA640_1280_2560::toIntNum        (ATMEGA2560::Interrupt::USART0_RECEIVE_COMPLETE         );
#elif defined(MCU_TYPE_atmega16u4)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#elif defined(MCU_TYPE_atmega32u4)
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#else
  static uint8_t const INT_NUM_UART_DATA_REGISTER_EMPTY = interface::InterruptController::INVALID_INT_NUM;
  static uint8_t const INT_NUM_RECEIVE_COMPLETE         = interface::InterruptController::INVALID_INT_NUM;
#endif

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART0::UART0(volatile uint8_t * udr0, volatile uint8_t * ucsr0a, volatile uint8_t * ucsr0b, volatile uint8_t * ucsr0c, volatile uint16_t * ubrr0, interface::InterruptController & int_ctrl, uint32_t const f_cpu)
: _UDR0               (udr0    ),
  _UCSR0A             (ucsr0a  ),
  _UCSR0B             (ucsr0b  ),
  _UCSR0C             (ucsr0c  ),
  _UBRR0              (ubrr0   ),
  _int_ctrl           (int_ctrl),
  _f_cpu              (f_cpu   ),
  _on_rx_done_callback(0       ),
  _on_tx_done_callback(0       )
{

}

UART0::~UART0()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART0::transmit(uint8_t const data)
{
  *_UDR0 = data;
}

void UART0::receive(uint8_t & data)
{
  data = *_UDR0;
}

void UART0::enableTx()
{
  *_UCSR0B |= TXEN0_bm;
  _int_ctrl.enableInterrupt(INT_NUM_UART_DATA_REGISTER_EMPTY);
}

void UART0::enableRx()
{
  _int_ctrl.enableInterrupt(INT_NUM_RECEIVE_COMPLETE);
  *_UCSR0B |= RXEN0_bm;
}

void UART0::disableTx()
{
  _int_ctrl.disableInterrupt(INT_NUM_UART_DATA_REGISTER_EMPTY);
  *_UCSR0B &= ~TXEN0_bm;
}

bool UART0::setBaudRate(interface::UartBaudRate const baud_rate)
{
  *_UCSR0A |= U2X0_bm;

  switch(baud_rate)
  {
  case interface::UartBaudRate::B115200: *_UBRR0 = calcUartBaudRate(_f_cpu, 115200); return true;  break;
  default:                                                                           return false; break;
  }
}

bool UART0::setParity(interface::UartParity const parity)
{
  *_UCSR0C &= ~(UPM01_bm | UPM00_bm);

  switch(parity)
  {
  case interface::UartParity::None:                                  return true;  break;
  case interface::UartParity::Even: *_UCSR0C |= UPM01_bm;            return true;  break;
  case interface::UartParity::Odd:  *_UCSR0C |= UPM01_bm | UPM00_bm; return true;  break;
  default:                                                           return false; break;
  }
}

bool UART0::setStopBit(interface::UartStopBit const stop_bit)
{
  *_UCSR0C &= ~USBS0_bm;

  switch(stop_bit)
  {
  case interface::UartStopBit::_1:                       return true;  break;
  case interface::UartStopBit::_2: *_UCSR0C |= USBS0_bm; return true;  break;
  default:                                               return false; break;
  }
}

void UART0::register_onRxDoneCallback(interface::UART_onRxDoneCallback * on_rx_done_callback)
{
  _on_rx_done_callback = on_rx_done_callback;
}

void UART0::register_onTxDoneCallback(interface::UART_onTxDoneCallback * on_tx_done_callback)
{
  _on_tx_done_callback = on_tx_done_callback;
}

void UART0::ISR_onTransmitRegisterEmpty()
{
  if(_on_tx_done_callback) _on_tx_done_callback->onTxDone();
}

void UART0::ISR_onReceiveComplete()
{
  if(_on_rx_done_callback) _on_rx_done_callback->onRxDone();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATxxxx */
