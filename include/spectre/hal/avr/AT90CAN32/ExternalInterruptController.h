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

#ifndef INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_EXTERNALINTERRUPTCONTROLLER_H_
#define INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_EXTERNALINTERRUPTCONTROLLER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/AT90CAN32_64_128/ExternalInterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN32
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef AT90CAN32_64_128::ExternalInterrupt                    ExternalInterrupt;
typedef AT90CAN32_64_128::ExternalInterruptController          ExternalInterruptController;
typedef AT90CAN32_64_128::EINT0_ExternalInterruptEventCallback EINT0_ExternalInterruptEventCallback;
typedef AT90CAN32_64_128::EINT1_ExternalInterruptEventCallback EINT1_ExternalInterruptEventCallback;
typedef AT90CAN32_64_128::EINT2_ExternalInterruptEventCallback EINT2_ExternalInterruptEventCallback;
typedef AT90CAN32_64_128::EINT3_ExternalInterruptEventCallback EINT3_ExternalInterruptEventCallback;
typedef AT90CAN32_64_128::EINT4_ExternalInterruptEventCallback EINT4_ExternalInterruptEventCallback;
typedef AT90CAN32_64_128::EINT5_ExternalInterruptEventCallback EINT5_ExternalInterruptEventCallback;
typedef AT90CAN32_64_128::EINT6_ExternalInterruptEventCallback EINT6_ExternalInterruptEventCallback;
typedef AT90CAN32_64_128::EINT7_ExternalInterruptEventCallback EINT7_ExternalInterruptEventCallback;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN32 */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_HAL_AVR_AT90CAN32_EXTERNALINTERRUPTCONTROLLER_H_ */