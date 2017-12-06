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

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace mcu
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SPIMasterConfigurationInterface
{

public:

  typedef enum
  {
    MODE_0,   /* CPOL = 0, CPHA = 0 */
    MODE_1,   /* CPOL = 0, CPHA = 1 */
    MODE_2,   /* CPOL = 1, CPHA = 0 */
    MODE_3    /* CPOL = 1, CPHA = 1 */
  } eSPIMode;

           SPIMasterConfigurationInterface() { }
  virtual ~SPIMasterConfigurationInterface() { }

  virtual void setSpiMode (eSPIMode const spi_mode    ) = 0;
  virtual void setSpiClock(uint32_t const spi_clock_hz) = 0;

  
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface*/

} /* mcu */

} /* spectre */

