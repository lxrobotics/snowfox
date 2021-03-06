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

#include <snowfox/hal/riscv64/FE310/UART0.h>

#include <snowfox/hal/riscv64/FE310/RegisterBits.h>

#include <snowfox/util/BitUtil.h>
#include <snowfox/util/EnumClassConv.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::FE310
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UART0::UART0(volatile uint32_t * uart0_txdata,
             volatile uint32_t * uart0_rxdata,
             volatile uint32_t * uart0_txctrl,
             volatile uint32_t * uart0_rxctrl,
             volatile uint32_t * uart0_div,
             uint32_t const      tlclk_Hz,
             volatile uint32_t * gpio_iof_en,
             volatile uint32_t * gpio_iof_sel)
: UARTx(uart0_txdata,
        uart0_rxdata,
        uart0_txctrl,
        uart0_rxctrl,
        uart0_div,
        tlclk_Hz)
{
  enableGpioAccess(gpio_iof_en, gpio_iof_sel);
}

UART0::~UART0()
{

}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void UART0::enableGpioAccess(volatile uint32_t * gpio_iof_en, volatile uint32_t * gpio_iof_sel)
{
  util::clrBit(gpio_iof_sel, util::bp(GPIO0_IOF_SEL::UART0_RX));
  util::clrBit(gpio_iof_sel, util::bp(GPIO0_IOF_SEL::UART0_TX));
  util::setBit(gpio_iof_en,  util::bp(GPIO0_IOF_EN::UART0_RX ));
  util::setBit(gpio_iof_en,  util::bp(GPIO0_IOF_EN::UART0_TX ));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::FE310 */
