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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_CONFIGURATION_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_CONFIGURATION_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/LSM6DSM/interface/LSM6DSM_Configuration.h>

#include <snowfox/driver/sensor/LSM6DSM/interface/LSM6DSM_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::LSM6DSM
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LSM6DSM_Configuration final : public interface::LSM6DSM_Configuration
{

public:

           LSM6DSM_Configuration(interface::LSM6DSM_Io & io);
  virtual ~LSM6DSM_Configuration();


  virtual bool enableRegAddrAutoIncrement() override;
  virtual bool enableBlockDataUpdate     () override;

private:

  interface::LSM6DSM_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::LSM6DSM */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_LSM6DSM_LSM6DSM_CONFIGURATION_H_ */