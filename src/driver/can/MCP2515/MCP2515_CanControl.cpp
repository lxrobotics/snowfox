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

#include <snowfox/driver/can/MCP2515/MCP2515_CanControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::can::MCP2515
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

MCP2515_CanControl::MCP2515_CanControl(can::interface::CanFrameBuffer     & can_tx_buf,
                                       can::interface::CanFrameBuffer     & can_rx_buf,
                                       interface::MCP2515_TransmitControl & ctrl)
: _can_tx_buf(can_tx_buf),
  _can_rx_buf(can_rx_buf),
  _ctrl      (ctrl      )
{

}

MCP2515_CanControl::~MCP2515_CanControl()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool MCP2515_CanControl::transmit(util::type::CanFrame const & frame)
{
  /* Check if there is a free transmit buffer to fill and if that
   * is the case fill the buffer and initiate transmission.
   */
  if(!_ctrl.isTransmitRequestPending(interface::TransmitBufferSelect::TB_0))
  {
    _ctrl.writeToTransmitBuffer(interface::TransmitBufferSelect::TB_0, frame);
    _ctrl.requestTransmit      (interface::TransmitBufferSelect::TB_0       );
    return true;
  }

  if(!_ctrl.isTransmitRequestPending(interface::TransmitBufferSelect::TB_1))
  {
    _ctrl.writeToTransmitBuffer(interface::TransmitBufferSelect::TB_1, frame);
    _ctrl.requestTransmit      (interface::TransmitBufferSelect::TB_1       );
    return true;
  }

  if(!_ctrl.isTransmitRequestPending(interface::TransmitBufferSelect::TB_2))
  {
    _ctrl.writeToTransmitBuffer(interface::TransmitBufferSelect::TB_2, frame);
    _ctrl.requestTransmit      (interface::TransmitBufferSelect::TB_2       );
    return true;
  }

  /* Otherwise slot the frame into the transmit buffer in
   * order to be transmitted at a later point in time.
   */

  if(!_can_tx_buf.isFull())
  {
    _can_tx_buf.push(frame);
    return true;
  }

  return false;
}

bool MCP2515_CanControl::receive(util::type::CanFrame * frame)
{
  if(_can_rx_buf.isEmpty()) return false;

  _can_rx_buf.pop(frame);
  return true;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::can::MCP2515 */
