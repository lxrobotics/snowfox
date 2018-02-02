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
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/Delay.h>
#include <spectre/hal/avr/ATMEGA328P/I2CMaster.h>
#include <spectre/hal/avr/ATxxxx/i2c/I2CMasterBase.h>

#include <spectre/driver/haptic/DRV2605/DRV2605.h>
#include <spectre/driver/haptic/DRV2605/DRV2605_IoI2C.h>
#include <spectre/driver/haptic/DRV2605/DRV2605_Control.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static uint8_t  const DRV2605_I2C_ADDR = (0x5A << 1);
static uint32_t const LOOP_DELAY_ms    = 1000; /* 1 s */

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::I2CMaster i2c_master_atmega328p(&TWCR, &TWDR, &TWSR, &TWBR);
  ATxxxx::I2CMasterBase i2c_master           (i2c_master_atmega328p);

  i2c_master.setI2CClock(hal::interface::I2CMasterConfiguration::F_100_kHz);

  ATMEGA328P::Delay     delay;

  /* DRIVER ***************************************************************************/

  haptic::DRV2605::DRV2605_IoI2C    drv2605_io_i2c(DRV2605_I2C_ADDR, i2c_master);
  haptic::DRV2605::DRV2605_Control  drv2605_ctrl  (drv2605_io_i2c, delay       );
  haptic::DRV2605::DRV2605          drv2605       (drv2605_ctrl                );

  uint8_t mode         = static_cast<uint8_t>(haptic::DRV2605::interface::INTERNAL_TRIGGER);
  uint8_t actuator     = static_cast<uint8_t>(haptic::DRV2605::interface::LRA             );
  uint8_t waveform_lib = static_cast<uint8_t>(haptic::DRV2605::interface::LIB_LRA         );

  /* APPLICATION **********************************************************************/

  drv2605.open();
  drv2605.ioctl(haptic::DRV2605::IOCTL_SET_MODE,             static_cast<void *>(&mode        ));
  drv2605.ioctl(haptic::DRV2605::IOCTL_SET_ACTUATOR,         static_cast<void *>(&actuator    ));
  drv2605.ioctl(haptic::DRV2605::IOCTL_SET_WAVEFORM_LIBRARY, static_cast<void *>(&waveform_lib));

  uint8_t  const DRV2605_MIN_LRA_LIB_WAVEFORM_NUM = 1;
  uint8_t  const DRV2605_MAX_LRA_LIB_WAVEFORM_NUM = 127;

  for(uint8_t w = DRV2605_MIN_LRA_LIB_WAVEFORM_NUM; ; w++)
  {
    haptic::DRV2605::IoctlSetWaveFormArg waveform_arg;

    waveform_arg.waveform_sequencer_select = haptic::DRV2605::interface::WAVEFORM_SEQUENCER_1;
    waveform_arg.waveform                  = w;

    drv2605.ioctl(haptic::DRV2605::IOCTL_SET_WAVEFORM, static_cast<void *>(&waveform_arg));
    drv2605.ioctl(haptic::DRV2605::IOCTL_SET_GO,       0                                 );

    if(w == DRV2605_MAX_LRA_LIB_WAVEFORM_NUM) w = DRV2605_MIN_LRA_LIB_WAVEFORM_NUM;

    delay.delay_ms(LOOP_DELAY_ms);
  }

  drv2605.close();

  return 0;
}