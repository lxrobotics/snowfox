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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART0_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART0_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/interface/uart/UART.h>
#include <spectre/hal/interface/uart/UARTAssembly.h>
#include <spectre/hal/interface/uart/UARTCallback.h>
#include <spectre/hal/interface/uart/UARTConfiguration.h>

#include <spectre/hal/interface/interrupt/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UART0 : public interface::UART,
              public interface::UARTConfiguration,
              public interface::UARTAssembly
{

public:


           UART0(volatile uint8_t * udr0, volatile uint8_t * ucsr0a, volatile uint8_t * ucsr0b, volatile uint8_t * ucsr0c, volatile uint16_t * ubrr0, interface::InterruptController & int_ctrl, uint32_t const f_cpu);
  virtual ~UART0();


  /* UART Interface */

  virtual void transmit         (uint8_t  const    data) override;
  virtual void receive          (uint8_t         & data) override;


  /* UART Configuration Interface */

  virtual void setBaudRate      (interface::UartBaudRate const   baud_rate) override;
  virtual void setParity        (interface::UartParity   const   parity   ) override;
  virtual void setStopBit       (interface::UartStopBit  const   stop_bit ) override;
  virtual void enableInterrupt  (interface::UartInt      const   uart_int ) override;
  virtual void disableInterrupt (interface::UartInt      const   uart_int ) override;


  /* UART Assembly */

  virtual void registerUARTCallbackInterface(interface::UARTCallback * uart_callback_interface) override;


  /* Functions to be called upon execution of a interrupt service routine */

  static void ISR_onTransmitComplete(void * arg);
  static void ISR_onReceiveComplete (void * arg);


private:

  volatile uint8_t  * _UDR0,
                    * _UCSR0A,
                    * _UCSR0B,
                    * _UCSR0C;
  volatile uint16_t * _UBRR0;

  interface::InterruptController       & _int_ctrl;
  interface::UARTCallback              * _uart_callback_interface;
  uint32_t                       const   _f_cpu;

  /* Member functions */

  void enableTransmit        ();
  void enableReceive         ();
  void ISR_onTransmitComplete();
  void ISR_onReceiveComplete ();

  static uint16_t calcBaudRate(uint32_t const f_cpu, uint32_t const baud_rate);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN128_UART0_H_ */