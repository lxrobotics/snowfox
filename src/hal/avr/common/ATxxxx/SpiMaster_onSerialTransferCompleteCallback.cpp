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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/avr/common/ATxxxx/SpiMaster_onSerialTransferCompleteCallback.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATxxxx
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

SpiMaster_onSerialTransferCompleteCallback::SpiMaster_onSerialTransferCompleteCallback(os::interface::EventProducer & spi_transfer_complete_event)
: _spi_transfer_complete_event(spi_transfer_complete_event)
{

}

SpiMaster_onSerialTransferCompleteCallback::~SpiMaster_onSerialTransferCompleteCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void SpiMaster_onSerialTransferCompleteCallback::onInterrupt()
{
  _spi_transfer_complete_event.set();
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATxxxx */
