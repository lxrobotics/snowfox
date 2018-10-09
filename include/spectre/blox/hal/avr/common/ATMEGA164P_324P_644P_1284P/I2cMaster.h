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

#ifndef INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_I2CMASTER_H_
#define INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_I2CMASTER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/blox/hal/avr/common/ATxxxx/I2cMaster.hpp>

#include <spectre/hal/avr/common/ATMEGA164P_324P_644P_1284P/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef ATxxxx::I2cMaster<hal::ATMEGA164P_324P_644P_1284P::toIntNum(hal::ATMEGA164P_324P_644P_1284P::Interrupt::TWO_WIRE_INT)> I2cMaster;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA164P_324P_644P_1284P */

} /* blox */

} /* spectre */

#endif /* INCLUDE_SPECTRE_BLOX_HAL_AVR_COMMON_ATMEGA164P_324P_644P_1284P_I2CMASTER_H_ */