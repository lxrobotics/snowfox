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

#include <snowfox/driver/ioexpander/PCA9547/PCA9547.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::ioexpander::PCA9547
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

PCA9547::PCA9547(interface::PCA9547_Control & ctrl)
: _ctrl(ctrl)
{

}

PCA9547::~PCA9547()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool PCA9547::open()
{
  return true;
}

ssize_t PCA9547::read(uint8_t * /* buffer */, ssize_t const /* num_bytes */)
{
  return -1; /* Not supported by this driver */
}

ssize_t PCA9547::write(uint8_t const * /* buffer */, ssize_t const /* num_bytes */)
{
  return -1; /* Not supported by this driver */
}

bool PCA9547::ioctl(uint32_t const cmd, void * arg)
{
  switch(cmd)
  {
  /* SET_CHANNEL **********************************************************************/
  case IOCTL_SET_CHANNEL:
  {
    uint8_t               const * arg_ptr     = static_cast<uint8_t *>            (arg     );
    interface::I2cChannel const   i2c_channel = static_cast<interface::I2cChannel>(*arg_ptr);
    return _ctrl.setChannel(i2c_channel);
  }
  break;
  /* GET_CHANNEL **********************************************************************/
  case IOCTL_GET_CHANNEL:
  {
    interface::I2cChannel i2c_channel = interface::I2cChannel::NO_CHANNEL;
    bool const success = _ctrl.getChannel(&i2c_channel);
    uint8_t i2c_channel_val = static_cast<uint8_t>(i2c_channel);
    arg = &i2c_channel_val;
    return success;
  }
  break;
  }

  return false;
}

void PCA9547::close()
{

}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::ioexpander::PCA9547 */
