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

#ifndef INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CANCONTROL_H_
#define INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CANCONTROL_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/driver/can/interface/CanControl.h>

#include <snowfox/driver/can/interface/CanFrameBuffer.h>

#include <snowfox/driver/can/MCP2515/interface/control/MCP2515_TransmitControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::can::MCP2515
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_CanControl final : public can::interface::CanControl
{

public:

           MCP2515_CanControl(can::interface::CanFrameBuffer     & can_tx_buf,
                              can::interface::CanFrameBuffer     & can_rx_buf,
                              interface::MCP2515_TransmitControl & ctrl);
  virtual ~MCP2515_CanControl();


  virtual bool transmit(util::type::CanFrame const & frame) override;
  virtual bool receive (util::type::CanFrame       * frame) override;


private:

  can::interface::CanFrameBuffer     & _can_tx_buf,
                                     & _can_rx_buf;
  interface::MCP2515_TransmitControl & _ctrl;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::can::MCP2515 */

#endif /* INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_MCP2515_CANCONTROL_H_ */
