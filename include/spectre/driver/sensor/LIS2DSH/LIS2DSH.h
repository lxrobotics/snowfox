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

#ifndef INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_H_
#define INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/sensor/LIS2DSH/interface/LIS2DSH_Interface.h>
#include <spectre/driver/sensor/LIS2DSH/interface/LIS2DSH_ConfigurationInterface.h>
#include <spectre/driver/sensor/LIS2DSH/interface/LIS2DSH_IO_Interface.h>

#include <spectre/driver/interface/Debug.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace LIS2DSH
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class LIS2DSH : public LIS2DSH_Interface,
                public LIS2DSH_ConfigurationInterface
{

public:

           LIS2DSH(LIS2DSH_IO_Interface & io);
  virtual ~LIS2DSH();


  /* LIS2DSH Interface */

  virtual bool checkIfNewDataIsAvailable_XYZ        (bool * is_new_data_available_xyz ) override;
  virtual bool checkIfNewDataIsAvailable_X          (bool * is_new_data_available_x   ) override;
  virtual bool checkIfNewDataIsAvailable_Y          (bool * is_new_data_available_y   ) override;
  virtual bool checkIfNewDataIsAvailable_Z          (bool * is_new_data_available_z   ) override;
  virtual bool checkIfNewDataIsAvailable_Temperature(bool * is_new_data_available_temp) override;

  virtual bool checkIfDataOverrun_XYZ               (bool * is_data_overrun_xyz       ) override;
  virtual bool checkIfDataOverrun_X                 (bool * is_data_overrun_x         ) override;
  virtual bool checkIfDataOverrun_Y                 (bool * is_data_overrun_y         ) override;
  virtual bool checkIfDataOverrun_Z                 (bool * is_data_overrun_z         ) override;
  virtual bool checkIfDataOverrun_Temperature       (bool * is_data_overrun_temp      ) override;

  virtual bool readXYZAxis                          (int16_t * raw_x, int16_t * raw_y, int16_t * raw_z) override;
  virtual bool readXAxis                            (int16_t * raw_x                                  ) override;
  virtual bool readYAxis                            (int16_t * raw_y                                  ) override;
  virtual bool readZAxis                            (int16_t * raw_z                                  ) override;
  virtual bool readTemperature                      (int16_t * raw_temp                               ) override;


  /* LIS2DSH Configuration Interface */

  virtual bool setOperatingMode       (OperatingModeSelect  const sel) override;
  virtual bool setOutputDataRate      (OutputDataRateSelect const sel) override;
  virtual bool setFullScaleRange      (FullScaleRangeSelect const sel) override;
  virtual bool setFIFOMode            (FIFOModeSelect       const sel) override;

  virtual bool enableFIFO             () override;
  virtual bool disableFIFO            () override;
  virtual bool enableBlockDataUpdate  () override;
  virtual bool enableTemperatureSensor() override;

  virtual bool enableXYZAxis          () override;
  virtual bool enableXAxis            () override;
  virtual bool enableYAxis            () override;
  virtual bool enableZAxis            () override;


          void debug_dumpAllRegs      (driver::interface::Debug & debug_interface);

private:

  LIS2DSH_IO_Interface & _io;

  bool readSingleRegister   (RegisterSelect const reg_sel, uint8_t       * data);
  bool writeSingleRegister  (RegisterSelect const reg_sel, uint8_t const   data);

  void debug_dumpSingleReg  (driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS2DSH */

} /* sensor */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_SENSOR_LIS2DSH_H_ */
