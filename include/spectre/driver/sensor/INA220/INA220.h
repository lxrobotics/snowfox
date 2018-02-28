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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INA220_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INA220_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/INA220/interface/INA220_Control.h>

#include <spectre/driver/interface/Driver.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace INA220
{

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_BUS_VOLTAGE_RANGE    = 0; /* Arg: interface::BusVoltageRangeSelect *    -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_SHUNT_PGA_GAIN       = 1; /* Arg: interface::ShuntPGAGainSelect *       -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_BUS_ADC_RESOLUTION   = 2; /* Arg: interface::BusADCResolutionSelect *   -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_SHUNT_ADC_RESOLUTION = 3; /* Arg: interface::ShuntADCResolutionSelect * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_OPERATING_MODE       = 4; /* Arg: interface::OperatingModeSelect *      -> uint8_t *  */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class INA220 : public driver::interface::Driver
{

public:

           INA220(interface::INA220_Control & ctrl);
  virtual ~INA220();


  virtual bool    open (                                                  ) override;
  virtual ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  virtual ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  virtual bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  virtual void    close(                                                  ) override;

private:

  interface::INA220_Control & _ctrl;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* INA220 */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_INA220_INA220_H_ */