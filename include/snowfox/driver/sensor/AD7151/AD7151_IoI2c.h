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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_AD7151_IO_I2C_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_AD7151_IO_I2C_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/AD7151/interface/AD7151_Io.h>

#include <snowfox/hal/interface/i2c/I2cMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::AD7151
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AD7151_IoI2c final : public interface::AD7151_Io
{

public:

           AD7151_IoI2c(uint8_t const i2c_address, hal::interface::I2cMaster & i2c_master);
  virtual ~AD7151_IoI2c();


  virtual bool readRegister (interface::Register const reg, uint8_t        * data, uint16_t const num_bytes) override;
  virtual bool readRegister (interface::Register const reg, uint8_t        * data                          ) override;
  virtual bool writeRegister(interface::Register const reg, uint8_t const  * data, uint16_t const num_bytes) override;
  virtual bool writeRegister(interface::Register const reg, uint8_t const    data                          ) override;

private:

  uint8_t                     _i2c_address;
  hal::interface::I2cMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::AD7151 */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_AD7151_AD7151_IO_I2C_H_ */
