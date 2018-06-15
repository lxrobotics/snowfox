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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER0_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER0_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/TIMER0.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA16U4
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TIMER0 : public ATMEGA16U4_32U4::TIMER0
{

public:

           TIMER0(volatile uint8_t * tcnt0,
                  volatile uint8_t * tccr0b,
                  volatile uint8_t * ocr0a,
                  volatile uint8_t * ocr0b) : ATMEGA16U4_32U4::TIMER0(tcnt0, tccr0b, ocr0a, ocr0b) { }
  virtual ~TIMER0() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA16U4 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA16U4_TIMER0_H_ */
