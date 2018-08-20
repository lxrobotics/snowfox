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

#ifndef INCLUDE_SPECTRE_MCU_AVR_ATXXXX_I2CMASTER_BASE_H_
#define INCLUDE_SPECTRE_MCU_AVR_ATXXXX_I2CMASTER_BASE_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/interface/i2c/I2cMaster.h>
#include <spectre/hal/interface/i2c/I2cMasterConfiguration.h>

#include <spectre/hal/avr/common/ATxxxx/i2c/interface/I2cMasterMcu.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class I2cMasterBase : public hal::interface::I2cMaster,
                      public hal::interface::I2cMasterConfiguration
{

public:

           I2cMasterBase(interface::I2cMasterMcu & i2c_master_mcu);
  virtual ~I2cMasterBase();


  /* I2C Master Interface */

  virtual bool begin      (uint8_t const address, bool const is_read_access               ) override;
  virtual void end        (                                                               ) override;
  virtual bool write      (uint8_t const data                                             ) override;
  virtual bool requestFrom(uint8_t const address, uint8_t * data, uint16_t const num_bytes) override;


  /* I2C Master Configuration Interface */

  virtual void setI2cClock(hal::interface::I2cClock const i2c_clock) override;


private:

  interface::I2cMasterMcu & _i2c_master_mcu;

  static uint8_t convertI2CAddress(uint8_t const address, bool is_read_access);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */

#endif /* INCLUDE_SPECTRE_MCU_AVR_ATXXXX_I2CMASTER_BASE_H_ */
