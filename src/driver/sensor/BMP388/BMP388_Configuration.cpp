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

#include <snowfox/driver/sensor/BMP388/BMP388_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox
{

namespace driver
{

namespace sensor
{

namespace BMP388
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

BMP388_Configuration::BMP388_Configuration(interface::BMP388_Io & io)
: _io{io}
{

}

BMP388_Configuration::~BMP388_Configuration()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void BMP388_Configuration::enableInterrupt(interface::Interrupt const interrupt)
{
  _io.setBit(interface::Register::INT_CTRL, util::to_integer(interrupt));
}

void BMP388_Configuration::disableInterrupt(interface::Interrupt const interrupt)
{
  _io.clrBit(interface::Register::INT_CTRL, util::to_integer(interrupt));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* BMP388 */

} /* sensor */

} /* driver */

} /* snowfox */
