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

#ifndef INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_INTERFACE_RA6963_IO_INTERFACE_H_
#define INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_INTERFACE_RA6963_IO_INTERFACE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::glcd::RA6963::interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RA6963_Io
{

public:

           RA6963_Io() { }
  virtual ~RA6963_Io() { }


  virtual void    reset       (                      ) = 0;
  virtual uint8_t readStatus  (                      ) = 0;
  virtual uint8_t readData    (                      ) = 0;
  virtual void    writeData   (uint8_t const data_val) = 0;
  virtual void    writeCommand(uint8_t const cmd_val ) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::glcd::RA6963::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_GLCD_RA6963_INTERFACE_RA6963_IO_INTERFACE_H_ */
