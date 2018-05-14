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

#include <spectre/driver/lora/RFM9x/DIO0/RFM9x_Dio0EventCallback.h>

#include <spectre/driver/lora/RFM9x/RFM9x_InterruptControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace lora
{

namespace RFM9x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

RFM9x_Dio0EventCallback::RFM9x_Dio0EventCallback(interface::RFM9x_InterruptControl       & int_ctrl,
                                                 interface::RFM9x_onPacketSentCallback   & on_packet_sent_callback,
                                                 interface::RFM9x_onPayloadReadyCallback & on_payload_ready_callback,
                                                 interface::RFM9x_onCadDoneCallback      & on_cad_done_callback)
: _int_ctrl                 (int_ctrl                 ),
  _on_packet_sent_callback  (on_packet_sent_callback  ),
  _on_payload_ready_callback(on_payload_ready_callback),
  _on_cad_done_callback     (on_cad_done_callback     )
{

}

RFM9x_Dio0EventCallback::~RFM9x_Dio0EventCallback()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RFM9x_Dio0EventCallback::onExternalEventCallback()
{
  uint8_t irq_req_flags = 0;

  _int_ctrl.getIntReqFlags(&irq_req_flags);

  if(RFM9x_InterruptControl::isRxDone(irq_req_flags))
  {
    _on_payload_ready_callback.onPayloadReady();
    _int_ctrl.clearIntReqFlag(interface::InterruptRequest::RxDone);
  }
  if(RFM9x_InterruptControl::isTxDone(irq_req_flags))
  {
    _on_packet_sent_callback.onPacketSent();
    _int_ctrl.clearIntReqFlag(interface::InterruptRequest::TxDone);
  }
  if(RFM9x_InterruptControl::isCadDone(irq_req_flags))
  {
    _on_cad_done_callback.onCadDone();
    _int_ctrl.clearIntReqFlag(interface::InterruptRequest::CadDone);
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */