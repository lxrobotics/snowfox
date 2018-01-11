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

#include <spectre/driver/sensor/LIS3DSH/LIS3DSH.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace sensor
{

namespace LIS3DSH
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LIS3DSH::LIS3DSH(LIS3DSH_IO_Interface & io)
: _io(io)
{
  enableBlockDataUpdate();
}

LIS3DSH::~LIS3DSH()
{

}

/**************************************************************************************
 * PUBLIC FUNCTIONS
 **************************************************************************************/

bool LIS3DSH::setOutputDataRate(OutputDataRateSelect const sel)
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content &= ~(LIS3DSH_CTRL_REG_4_ODR_3_bm | LIS3DSH_CTRL_REG_4_ODR_2_bm | LIS3DSH_CTRL_REG_4_ODR_1_bm | LIS3DSH_CTRL_REG_4_ODR_0_bm);
  ctrl_reg4_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH::setFullScaleRange(FullScaleRangeSelect const sel)
{
  uint8_t ctrl_reg5_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content &= ~(LIS3DSH_CTRL_REG_5_FSCALE_2_bm | LIS3DSH_CTRL_REG_5_FSCALE_1_bm | LIS3DSH_CTRL_REG_5_FSCALE_0_bm);
  ctrl_reg5_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG_5, ctrl_reg5_content)) return false;

  return true;
}

bool LIS3DSH::setFilterBandwidth(FilterBandwidth const sel)
{
  uint8_t ctrl_reg5_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_5, &ctrl_reg5_content)) return false;

  ctrl_reg5_content &= ~(LIS3DSH_CTRL_REG_5_BW_2_bm | LIS3DSH_CTRL_REG_5_BW_1_bm);
  ctrl_reg5_content |= static_cast<uint8_t>(sel);

  if(!writeSingleRegister(REG_CTRL_REG_5, ctrl_reg5_content)) return false;

  return true;
}

bool LIS3DSH::enableFIFO()
{
  uint8_t ctrl_reg6_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_6, &ctrl_reg6_content)) return false;

  ctrl_reg6_content |= LIS3DSH_CTRL_REG_6_FIFO_EN_bm;

  if(!writeSingleRegister(REG_CTRL_REG_6, ctrl_reg6_content)) return false;

  return true;
}

bool LIS3DSH::disableFIFO()
{
  uint8_t ctrl_reg6_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_6, &ctrl_reg6_content)) return false;

  ctrl_reg6_content &= ~LIS3DSH_CTRL_REG_6_FIFO_EN_bm;

  if(!writeSingleRegister(REG_CTRL_REG_6, ctrl_reg6_content)) return false;

  return true;
}

bool LIS3DSH::enableBlockDataUpdate()
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= LIS3DSH_CTRL_REG_4_BDU_bm;

  if(!writeSingleRegister(REG_CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH::enableXYZAxis()
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS3DSH_CTRL_REG_4_ZEN_bm | LIS3DSH_CTRL_REG_4_YEN_bm | LIS3DSH_CTRL_REG_4_XEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH::enableXAxis()
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS3DSH_CTRL_REG_4_XEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH::enableYAxis()
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS3DSH_CTRL_REG_4_YEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH::enableZAxis()
{
  uint8_t ctrl_reg4_content = 0;

  if(!readSingleRegister(REG_CTRL_REG_4, &ctrl_reg4_content)) return false;

  ctrl_reg4_content |= (LIS3DSH_CTRL_REG_4_ZEN_bm);

  if(!writeSingleRegister(REG_CTRL_REG_4, ctrl_reg4_content)) return false;

  return true;
}

bool LIS3DSH::checkIfNewDataIsAvailable_XYZ(bool * is_new_data_available_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_new_data_available_xyz = (status_reg_content & LIS3DSH_STATUS_REG_ZYXDA_bm) != 0;

  return true;
}

bool LIS3DSH::checkIfNewDataIsAvailable_X(bool * is_new_data_available_x)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_new_data_available_x = (status_reg_content & LIS3DSH_STATUS_REG_XDA_bm) != 0;

  return true;
}

bool LIS3DSH::checkIfNewDataIsAvailable_Y(bool * is_new_data_available_y)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_new_data_available_y = (status_reg_content & LIS3DSH_STATUS_REG_YDA_bm) != 0;

  return true;
}

bool LIS3DSH::checkIfNewDataIsAvailable_Z(bool * is_new_data_available_z)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_new_data_available_z = (status_reg_content & LIS3DSH_STATUS_REG_ZDA_bm) != 0;

  return true;
}

bool LIS3DSH::checkIfDataOverrun_XYZ(bool * is_data_overrun_xyz)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_data_overrun_xyz = (status_reg_content & LIS3DSH_STATUS_REG_ZYXOR_bm) != 0;

  return true;
}

bool LIS3DSH::checkIfDataOverrun_X(bool * is_data_overrun_x)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_data_overrun_x = (status_reg_content & LIS3DSH_STATUS_REG_XOR_bm) != 0;

  return true;
}

bool LIS3DSH::checkIfDataOverrun_Y(bool * is_data_overrun_y)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_data_overrun_y = (status_reg_content & LIS3DSH_STATUS_REG_YOR_bm) != 0;

  return true;
}

bool LIS3DSH::checkIfDataOverrun_Z(bool * is_data_overrun_z)
{
  uint8_t status_reg_content  = 0;

  if(!readSingleRegister(REG_STATUS, &status_reg_content)) return false;

  *is_data_overrun_z = (status_reg_content & LIS3DSH_STATUS_REG_ZOR_bm) != 0;

  return true;
}

bool LIS3DSH::readXYZAxis(int16_t * raw_x, int16_t * raw_y, int16_t * raw_z)
{
  uint8_t raw_xyz_data[6];

  if(!_io.readMultipleRegister(static_cast<RegisterSelect>(0x80 | REG_OUT_X_L), raw_xyz_data, 6)) return false;

  uint8_t const x_l = raw_xyz_data[0];
  uint8_t const x_h = raw_xyz_data[1];
  uint8_t const y_l = raw_xyz_data[2];
  uint8_t const y_h = raw_xyz_data[3];
  uint8_t const z_l = raw_xyz_data[4];
  uint8_t const z_h = raw_xyz_data[5];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));
  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));
  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool LIS3DSH::readXAxis(int16_t * raw_x)
{
  uint8_t raw_x_data[2];

  if(!_io.readMultipleRegister(static_cast<RegisterSelect>(REG_OUT_X_L), raw_x_data, 2)) return false;

  uint8_t const x_l = raw_x_data[0];
  uint8_t const x_h = raw_x_data[1];

  *raw_x = static_cast<int16_t>((static_cast<uint16_t>(x_h) << 8) + (static_cast<uint16_t>(x_l)));

  return true;
}

bool LIS3DSH::readYAxis(int16_t * raw_y)
{
  uint8_t raw_y_data[2];

  if(!_io.readMultipleRegister(static_cast<RegisterSelect>(0x80 | REG_OUT_Y_L), raw_y_data, 2)) return false;

  uint8_t const y_l = raw_y_data[0];
  uint8_t const y_h = raw_y_data[1];

  *raw_y = static_cast<int16_t>((static_cast<uint16_t>(y_h) << 8) + (static_cast<uint16_t>(y_l)));

  return true;
}

bool LIS3DSH::readZAxis(int16_t * raw_z)
{
  uint8_t raw_z_data[2];

  if(!_io.readMultipleRegister(static_cast<RegisterSelect>(0x80 | REG_OUT_Z_L), raw_z_data, 2)) return false;

  uint8_t const z_l = raw_z_data[0];
  uint8_t const z_h = raw_z_data[1];

  *raw_z = static_cast<int16_t>((static_cast<uint16_t>(z_h) << 8) + (static_cast<uint16_t>(z_l)));

  return true;
}

bool LIS3DSH::readTemperature(int8_t * raw_temp)
{
  uint8_t temp_reg_content = 0;

  if(!readSingleRegister(REG_OUT_T, &temp_reg_content)) return false;

  *raw_temp = static_cast<int8_t>(temp_reg_content);

  return true;
}

void LIS3DSH::debug_dumpAllRegs(driver::interface::Debug & debug_interface)
{
  debug_dumpSingleReg(debug_interface, "REG_INFO_1 =      ", REG_INFO_1    );
  debug_dumpSingleReg(debug_interface, "REG_INFO_2 =      ", REG_INFO_2    );
  debug_dumpSingleReg(debug_interface, "REG_WHO_AM_I =    ", REG_WHO_AM_I  );

  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_1 =  ", REG_CTRL_REG_1);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_2 =  ", REG_CTRL_REG_2);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_3 =  ", REG_CTRL_REG_3);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_4 =  ", REG_CTRL_REG_4);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_5 =  ", REG_CTRL_REG_5);
  debug_dumpSingleReg(debug_interface, "REG_CTRL_REG_6 =  ", REG_CTRL_REG_6);

  debug_dumpSingleReg(debug_interface, "REG_STATUS =      ", REG_STATUS    );

  debug_dumpSingleReg(debug_interface, "REG_OUT_T =       ", REG_OUT_T     );

  debug_dumpSingleReg(debug_interface, "REG_OFF_X =       ", REG_OFF_X     );
  debug_dumpSingleReg(debug_interface, "REG_OFF_Y =       ", REG_OFF_Y     );
  debug_dumpSingleReg(debug_interface, "REG_OFF_Z =       ", REG_OFF_Z     );
  debug_dumpSingleReg(debug_interface, "REG_CS_X =        ", REG_CS_X      );
  debug_dumpSingleReg(debug_interface, "REG_CS_Y =        ", REG_CS_Y      );
  debug_dumpSingleReg(debug_interface, "REG_CS_Z =        ", REG_CS_Z      );

  debug_dumpSingleReg(debug_interface, "REG_OUT_X_L =     ", REG_OUT_X_L   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_X_H =     ", REG_OUT_X_H   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Y_L =     ", REG_OUT_Y_L   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Y_H =     ", REG_OUT_Y_H   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Z_L =     ", REG_OUT_Z_L   );
  debug_dumpSingleReg(debug_interface, "REG_OUT_Z_H =     ", REG_OUT_Z_H   );

  debug_dumpSingleReg(debug_interface, "REG_FIFO_CTRL =   ", REG_FIFO_CTRL );
  debug_dumpSingleReg(debug_interface, "REG_FIFO_SRC =    ", REG_FIFO_SRC  );
}

/**************************************************************************************
 * PRIVATE FUNCTIONS
 **************************************************************************************/

bool LIS3DSH::readSingleRegister(RegisterSelect const reg_sel, uint8_t * data)
{
  return _io.readMultipleRegister(reg_sel, data, 1);
}

bool LIS3DSH::writeSingleRegister(RegisterSelect const reg_sel, uint8_t const data)
{
  return _io.writeMultipleRegister(reg_sel, &data, 1);
}

void LIS3DSH::debug_dumpSingleReg(driver::interface::Debug & debug_interface, char const * msg, RegisterSelect const reg_sel)
{
  uint8_t reg_content = 0;

  readSingleRegister(reg_sel, &reg_content);

  debug_interface.print("%s%X\n", msg, reg_content);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* LIS3DSH */

} /* sensor */

} /* driver */

} /* spectre */