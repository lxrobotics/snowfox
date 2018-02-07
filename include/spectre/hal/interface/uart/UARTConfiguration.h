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

#ifndef INTERFACE_UART_CONFIGURATION_H_
#define INTERFACE_UART_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace interface
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

enum class UartBaudRate : uint8_t
{
  B115200
};

enum class UartParity : uint8_t
{
  None,
  Even,
  Odd
};

enum class UartStopBit : uint8_t
{
  _1,
  _2
};

enum class UartInt : uint8_t
{
  TxComplete,
  RxComplete
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UARTConfiguration
{

public:

           UARTConfiguration() { }
  virtual ~UARTConfiguration() { }


  virtual void setBaudRate      (UartBaudRate const baud_rate, uint32_t const f_cpu) = 0;
  virtual void setParity        (UartParity   const parity                         ) = 0;
  virtual void setStopBit       (UartStopBit  const stop_bit                       ) = 0;
  virtual void enableInterrupt  (UartInt      const uart_int                       ) = 0;
  virtual void disableInterrupt (UartInt      const uart_int                       ) = 0;
  
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface*/

} /* hal */

} /* spectre */

#endif /* INTERFACE_UART_CONFIGURATION_H_ */
