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

#ifndef INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER4_H_
#define INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER4_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/TIMER4.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA1280
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class TIMER4 : public ATMEGA640_1280_2560::TIMER4
{

public:

           TIMER4(volatile uint16_t * tcnt4,
                  volatile uint8_t  * tccr4b,
                  volatile uint16_t * ocr4a,
                  volatile uint16_t * ocr4b,
                  volatile uint16_t * ocr4c) : ATMEGA640_1280_2560::TIMER4(tcnt4, tccr4b, ocr4a, ocr4b, ocr4c) { }
  virtual ~TIMER4() { }

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA1280 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_ATMEGA1280_TIMER4_H_ */