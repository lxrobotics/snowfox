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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/blox/hal/avr/common/ATMEGA164P_324P_644P_1284P/SpiMaster.h>

#include <spectre/hal/avr/common/ATMEGA164P_324P_644P_1284P/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace blox
{

namespace ATMEGA164P_324P_644P_1284P
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SpiMaster::SpiMaster(volatile uint8_t                    * spcr,
                     volatile uint8_t                    * spsr,
                     volatile uint8_t                    * spdr,
                     hal::interface::CriticalSection     & crit_sec,
                     hal::interface::InterruptController & int_ctrl)
: _serial_transfer_complete_event                         (crit_sec                                         ),
  _spi_master                                             (spcr, spsr, spdr, _serial_transfer_complete_event),
  _spi_master_on_serial_transfer_complete_callback        (_serial_transfer_complete_event                  ),
  _spi_master_on_serial_transfer_complete_callback_adapter(_spi_master_on_serial_transfer_complete_callback )
{
  int_ctrl.registerInterruptCallback(hal::ATMEGA164P_324P_644P_1284P::toIntNum(hal::ATMEGA164P_324P_644P_1284P::Interrupt::SPI_SERIAL_TRANSFER_COMPLETE), &_spi_master_on_serial_transfer_complete_callback_adapter);
  int_ctrl.enableInterrupt          (hal::ATMEGA164P_324P_644P_1284P::toIntNum(hal::ATMEGA164P_324P_644P_1284P::Interrupt::SPI_SERIAL_TRANSFER_COMPLETE));
}

SpiMaster::SpiMaster(volatile uint8_t                          * spcr,
                     volatile uint8_t                          * spsr,
                     volatile uint8_t                          * spdr,
                     hal::interface::CriticalSection           & crit_sec,
                     hal::interface::InterruptController       & int_ctrl,
                     hal::interface::SpiMode             const   spi_mode,
                     hal::interface::SpiBitOrder         const   spi_bit_order,
                     uint32_t                            const   spi_prescaler)
: SpiMaster(spcr, spsr, spdr, crit_sec, int_ctrl)
{
  _spi_master.setSpiMode     (spi_mode     );
  _spi_master.setSpiBitOrder (spi_bit_order);
  _spi_master.setSpiPrescaler(spi_prescaler);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA164P_324P_644P_1284P */

} /* blox */

} /* spectre */
