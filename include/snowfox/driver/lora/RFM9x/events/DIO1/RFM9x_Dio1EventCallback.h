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

#ifndef INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_DIO1_RFM9X_DIO1EVENTCALLBACK_H_
#define INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_DIO1_RFM9X_DIO1EVENTCALLBACK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/hal/interface/extint/ExternalInterruptCallback.h>

#include <snowfox/driver/lora/RFM9x/interface/events/DIO1/RFM9x_onRxTimeoutCallback.h>
#include <snowfox/driver/lora/RFM9x/interface/events/DIO1/RFM9x_onCadDetectedCallback.h>
#include <snowfox/driver/lora/RFM9x/interface/events/DIO1/RFM9x_onFhssChangeChannelCallback.h>

#include <snowfox/driver/lora/RFM9x/interface/control/RFM9x_EventControl.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::lora::RFM9x
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/* For information in DIO mapping in LoRa mode check out
 * Table 63. There are three events which can be mapped
 * on DIO1: RxTimeout, FhssChangeChannel, CadDetected
 */

class RFM9x_Dio1EventCallback final : public hal::interface::ExternalInterruptCallback
{

public:

           RFM9x_Dio1EventCallback(interface::RFM9x_EventControl                & event_ctrl,
                                   interface::RFM9x_onRxTimeoutCallback         & on_rx_timeout_callback,
                                   interface::RFM9x_onFhssChangeChannelCallback & on_fhss_change_channel_callback,
                                   interface::RFM9x_onCadDetectedCallback       & on_cad_detected_callback);
  virtual ~RFM9x_Dio1EventCallback();


  virtual void onExternalInterrupt() override;


private:

  interface::RFM9x_EventControl                & _event_ctrl;
  interface::RFM9x_onRxTimeoutCallback         & _on_rx_timeout_callback;
  interface::RFM9x_onFhssChangeChannelCallback & _on_fhss_change_channel_callback;
  interface::RFM9x_onCadDetectedCallback       & _on_cad_detected_callback;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::lora::RFM9x */

#endif /* INCLUDE_SNOWFOX_DRIVER_LORA_RFM9X_DIO1_RFM9X_DIO1EVENTCALLBACK_H_ */
