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

#ifndef INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_H_
#define INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/sensor/BMG160/interface/BMG160_Control.h>

#include <snowfox/driver/sensor/BMG160/interface/BMG160_Io.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::sensor::BMG160
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class BMG160_Control final : public interface::BMG160_Control
{

public:

           BMG160_Control(interface::BMG160_Io & io);
  virtual ~BMG160_Control();


  /* BMG160 Interface */

  virtual bool readXYZAxis    (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) override;
  virtual bool readXAxis      (int16_t * raw_x                                  ) override;
  virtual bool readYAxis      (int16_t * raw_y                                  ) override;
  virtual bool readZAxis      (int16_t * raw_z                                  ) override;
  virtual bool readTemperature(int8_t  * raw_temp                               ) override;


  /* BMG160 Configuration Interface */

  virtual bool setOutputDataRateAndBandwith (interface::OutputDataRateAndBandwith const output_data_rate_and_bandwidth) override;
  virtual bool setFullScaleRange            (interface::FullScaleRange            const full_scale_range              ) override;


private:

  interface::BMG160_Io & _io;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::sensor::BMG160 */

#endif /* INCLUDE_SNOWFOX_DRIVER_SENSOR_BMG160_H_ */
