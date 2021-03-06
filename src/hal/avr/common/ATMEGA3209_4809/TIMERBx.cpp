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

#include <snowfox/hal/avr/common/ATMEGA3209_4809/TIMERBx.h>

#include <snowfox/util/BitUtil.h>

#include <snowfox/cpu/avr/io/common/ATMEGA3209_4809.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATMEGA3209_4809
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Prescaler : uint8_t
{
  P1      = 0,
  P2      =                 TCBx_CLKSEL0_bm,
  CLK_TCA = TCBx_CLKSEL1_bm,
};

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

TIMERBx::TIMERBx(volatile uint8_t  * tcb_ctrla,
                 volatile uint16_t * tcb_cnt)
: _TCBx_CTRLA(tcb_ctrla),
  _TCBx_CNT  (tcb_cnt  )
{

}

TIMERBx::~TIMERBx()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void TIMERBx::start()
{
  util::setBit(_TCBx_CTRLA, TCBx_ENABLE_bp);
}

void TIMERBx::stop()
{
  util::clrBit(_TCBx_CTRLA, TCBx_ENABLE_bp);
}

void TIMERBx::set(uint16_t const val)
{
  *_TCBx_CNT = val;
}

uint16_t TIMERBx::get()
{
  return *_TCBx_CNT;
}

void TIMERBx::setCompareRegister(uint8_t const /* reg_sel */, uint16_t const /* reg_val */)
{
  /* TIMERB has no compare register */
}

void TIMERBx::setPrescaler(uint32_t const prescaler)
{
  *_TCBx_CTRLA &= ~(TCBx_CLKSEL1_bm | TCBx_CLKSEL0_bm);

  switch(prescaler)
  {
  case 1   : *_TCBx_CTRLA |= static_cast<uint8_t>(Prescaler::P1     ); break;
  case 2   : *_TCBx_CTRLA |= static_cast<uint8_t>(Prescaler::P2     ); break;
  case 3   : *_TCBx_CTRLA |= static_cast<uint8_t>(Prescaler::CLK_TCA); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATMEGA3209_4809 */
