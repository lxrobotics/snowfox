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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONTROL_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/BMG160/interface/BMG160_Interface.h>
#include <spectre/driver/sensor/BMG160/interface/BMG160_Configuration.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace BMG160
{

namespace interface
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMG160_Control : public BMG160_Interface,
                       public BMG160_Configuration
{

public:

           BMG160_Control() { }
  virtual ~BMG160_Control() { }


  /* BMG160 Interface */

  virtual bool readXYZAxis    (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) = 0;
  virtual bool readXAxis      (int16_t * raw_x                                  ) = 0;
  virtual bool readYAxis      (int16_t * raw_y                                  ) = 0;
  virtual bool readZAxis      (int16_t * raw_z                                  ) = 0;
  virtual bool readTemperature(int8_t  * raw_temp                               ) = 0;


  /* BMG160 Configuration Interface */

  virtual bool setOutputDataRateAndBandwith (OutputDataRateAndBandwithSelect const sel) = 0;
  virtual bool setFullScale                 (FullScaleSelect                 const sel) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* interface */

} /* BMG160 */

} /* sensor */

} /* driver */

} /* spectre */



#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_BMG160_INTERFACE_BMG160_CONTROL_H_ */