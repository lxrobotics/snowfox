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

#ifndef INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_DRV2605_IO_I2C_H_
#define INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_DRV2605_IO_I2C_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/haptic/DRV2605/interface/DRV2605_Io.h>

#include <snowfox/hal/interface/i2c/I2cMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::haptic::DRV2605
{

/**************************************************************************************
 * CLASS DECLARATION DRV2605
 **************************************************************************************/

class DRV2605_IoI2C final : public interface::DRV2605_Io
{

public:

           DRV2605_IoI2C(uint8_t const i2c_address, hal::interface::I2cMaster & i2c_master);
  virtual ~DRV2605_IoI2C();


  virtual bool readRegister (interface::Register const reg, uint8_t       * data) override;
  virtual bool writeRegister(interface::Register const reg, uint8_t const   data) override;


private:

  uint8_t                     _i2c_address;
  hal::interface::I2cMaster & _i2c_master;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::haptic::DRV2605 */

#endif /* INCLUDE_SNOWFOX_DRIVER_HAPTIC_DRV2605_DRV2605_IO_I2C_H_ */
