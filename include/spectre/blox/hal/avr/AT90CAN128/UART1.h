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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_AT90CAN128_UART1_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_AT90CAN128_UART1_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/AT90CAN128/UART1.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace AT90CAN128
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

class UART1
{

public:

  UART1(volatile uint8_t                          * udr1,
        volatile uint8_t                          * ucsr1a,
        volatile uint8_t                          * ucsr1b,
        volatile uint8_t                          * ucsr1c,
        volatile uint16_t                         * ubrr1,
        hal::interface::InterruptController       & int_ctrl,
        uint32_t                            const   f_cpu);

  hal::AT90CAN128::UART1 & operator () () { return _uart1; }

private:

  hal::AT90CAN128::UART1                               _uart1;
  hal::AT90CAN128::UART1_TransmitRegisterEmptyCallback _uart1_uart_data_register_empty_callback;
  hal::AT90CAN128::UART1_ReceiveCompleteCallback       _uart1_receive_complete_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_AT90CAN128_UART1_H_ */
