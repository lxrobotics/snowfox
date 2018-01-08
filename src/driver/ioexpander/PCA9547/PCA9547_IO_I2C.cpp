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

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/driver/ioexpander/PCA9547/PCA9547_IO_I2C.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace ioexpander
{

namespace PCA9547
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

PCA9547_IO_I2C::PCA9547_IO_I2C(uint8_t const i2c_address, hal::interface::I2CMaster & i2c_master)
: _i2c_address(i2c_address),
  _i2c_master (i2c_master )
{

}

PCA9547_IO_I2C::~PCA9547_IO_I2C()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool PCA9547_IO_I2C::readControlRegister(uint8_t * data)
{
  return _i2c_master.requestFrom(_i2c_address, data, 1);
}

bool PCA9547_IO_I2C::writeControlRegister(uint8_t const data)
{
  if(!_i2c_master.begin(_i2c_address, false)) return false;
  if(!_i2c_master.write(data               )) return false;
      _i2c_master.end  (                   );

  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* PCA9547 */

} /* ioexpander */

} /* driver */

} /* spectre */
