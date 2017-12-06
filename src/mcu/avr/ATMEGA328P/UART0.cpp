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
 * INCLUDES
 **************************************************************************************/

#include <spectre/mcu/avr/ATMEGA328P/UART0.h>

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace mcu
{

namespace ATMEGA328P
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef void(*onTransmitCompleteCallback)(UART0 * _this);
typedef void(*onReceiveCompleteCallback )(UART0 * _this);

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

static UART0 * _this = 0;

static onTransmitCompleteCallback on_transmit_complete = 0;
static onReceiveCompleteCallback  on_receive_complete  = 0;

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* UXSR0C */
#define U2X0_bm     (1<<U2X0)

/* UXSR0B */
#define RXCIE0_bm   (1<<RXCIE0)
#define UDRIE0_bm   (1<<UDRIE0)
#define RXEN0_bm    (1<<RXEN0)
#define TXEN0_bm    (1<<TXEN0)

/* UCSR0C */
#define UPM01_bm    (1<<UPM01)
#define UPM00_bm    (1<<UPM00)
#define USBS0_bm    (1<<USBS0)

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART0::UART0()
: _uart_callback_interface(0)
{
  _this = this;

  on_transmit_complete = &UART0::onTransmitCompleteFunc;
  on_receive_complete  = &UART0::onReceiveCompleteFunc;
}

UART0::~UART0()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void UART0::transmit(uint8_t const data)
{
  UDR0 = data;
}

void UART0::receive(uint8_t & data)
{
  data = UDR0;
}

void UART0::setBaudRate(eBaudRate const baud_rate)
{
  UCSR0A |= U2X0_bm;

  switch(baud_rate)
  {
  case B115200: UBRR0 = calcBaudRate(F_CPU, 115200);  break;
  default:                                            break;
  }
}

void UART0::setParity(eParity const parity)
{
  UCSR0C &= ~(UPM01_bm | UPM00_bm);

  switch(parity)
  {
  case None:                                  break;
  case Even:  UCSR0C |= UPM01_bm;             break;
  case Odd:   UCSR0C |= UPM01_bm | UPM00_bm;  break;
  default:                                    break;
  }
}

void UART0::setStopBit(eStopBit const stop_bit)
{
  UCSR0C &= ~USBS0_bm;

  switch(stop_bit)
  {
  case _1:                      break;
  case _2: UCSR0C |= USBS0_bm;  break;
  default:                      break;
  }
}

void UART0::registerUARTCallbackInterface(interface::UARTCallback * uart_callback_interface)
{
  _uart_callback_interface = uart_callback_interface;
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

uint16_t UART0::calcBaudRate(uint32_t const f_cpu, uint32_t const baud_rate)
{
  return (static_cast<uint16_t>(f_cpu/(8*baud_rate)) - 1);
}

void UART0::onTransmitCompleteFunc(UART0 * _this)
{
  _this->_uart_callback_interface->onTransmitCompleteCallback();
}

void UART0::onReceiveCompleteFunc(UART0 * _this)
{
  _this->_uart_callback_interface->onReceiveCompleteCallback();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* mcu */

} /* spectre */

/**************************************************************************************
 * ISR
 **************************************************************************************/

using namespace spectre::mcu::ATMEGA328P;

ISR(USART_UDRE_vect)
{
  if(on_transmit_complete && _this) on_transmit_complete(_this);
}

ISR(USART_RX_vect)
{
  if(on_receive_complete && _this) on_receive_complete(_this);
}
