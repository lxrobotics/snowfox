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
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::blox::ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <uint8_t UART_DATA_REGISTER_EMPTY_INTERRUPT_NUMBER,
          uint8_t UART_RECEIVE_COMPLETE_INTERRUPT_NUMBER>
UART0<UART_DATA_REGISTER_EMPTY_INTERRUPT_NUMBER, UART_RECEIVE_COMPLETE_INTERRUPT_NUMBER>::UART0(
             volatile uint8_t                                  * udr0,
             volatile uint8_t                                  * ucsr0a,
             volatile uint8_t                                  * ucsr0b,
             volatile uint8_t                                  * ucsr0c,
             volatile uint16_t                                 * ubrr0,
             hal::interface::InterruptController               & int_ctrl,
             uint32_t                                    const   f_cpu)
: _uart0                                  (udr0, ucsr0a, ucsr0b, ucsr0c, ubrr0, int_ctrl, f_cpu),
  _uart0_uart_data_register_empty_callback(_uart0),
  _uart0_receive_complete_callback        (_uart0)
{
  int_ctrl.registerInterruptCallback(UART_DATA_REGISTER_EMPTY_INTERRUPT_NUMBER, &_uart0_uart_data_register_empty_callback);
  int_ctrl.registerInterruptCallback(UART_RECEIVE_COMPLETE_INTERRUPT_NUMBER,    &_uart0_receive_complete_callback        );
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::blox::ATxxxx */
