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

#ifndef INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_H_
#define INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/interface/Driver.h>

#include <spectre/driver/lora/RFM9x/interface/status/RFM9x_Status.h>
#include <spectre/driver/lora/RFM9x/interface/control/RFM9x_Control.h>
#include <spectre/driver/lora/RFM9x/interface/config/RFM9x_Configuration.h>

#include <spectre/os/event/Event.h>
#include <spectre/os/event/EventGroup.h>

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
 * TYPEDEF
 **************************************************************************************/

enum class RetCodeRead : ssize_t
{
  ParameterError       = -1,
  RxFifoSizeExceeded   = -2,
  ModemBusy_NotSleep   = -3,
  ModemBusy_NotStandby = -4,
  RxTimeout            = -5,
  UnkownError          = -6
};

enum class RetCodeWrite : ssize_t
{
  ParameterError       = -1,
  TxFifoSizeExceeded   = -2,
  ModemBusy_NotSleep   = -3,
  ModemBusy_NotStandby = -4
};

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint32_t constexpr IOCTL_SET_FREQUENCY_HZ      = 0; /* Arg: uint32_t *                                 */
static uint32_t constexpr IOCTL_SET_SIGNAL_BANDWIDTH  = 1; /* Arg: interface::SignalBandwidth * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_CODING_RATE       = 2; /* Arg: interface::CodingRate *      -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_SPREADING_FACTOR  = 3; /* Arg: interface::SpreadingFactor * -> uint8_t *  */
static uint32_t constexpr IOCTL_SET_PREAMBLE_LENGTH   = 4; /* Arg: uint16_t *                                 */
static uint32_t constexpr IOCTL_SET_TX_FIFO_SIZE      = 5; /* Arg: uint16_t *                                 */
static uint32_t constexpr IOCTL_SET_RX_FIFO_SIZE      = 6; /* Arg: uint16_t *                                 */
static uint32_t constexpr IOCTL_GET_CURRENT_RSSI      = 7; /* Arg: int16_t *                                  */
static uint32_t constexpr IOCTL_GET_LAST_PACKET_RSSI  = 8; /* Arg: int16_t *                                  */
static uint32_t constexpr IOCTL_GET_LAST_PACKET_SNR   = 9; /* Arg: int8_t *                                   */

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RFM9x : public driver::interface::Driver
{

public:

           RFM9x(interface::RFM9x_Configuration & config,
                 interface::RFM9x_Control       & control,
                 interface::RFM9x_Status        & status,
                 os::interface::EventConsumer   & rx_done_event,
                 os::interface::EventConsumer   & rx_timeout_event,
                 os::interface::EventConsumer   & tx_done_event);
  virtual ~RFM9x();


  bool    open (                                                  ) override;
  ssize_t read (uint8_t        * buffer, ssize_t const   num_bytes) override;
  ssize_t write(uint8_t  const * buffer, ssize_t const   num_bytes) override;
  bool    ioctl(uint32_t const   cmd,    void          * arg      ) override;
  void    close(                                                  ) override;


private:

  interface::RFM9x_Configuration & _config;
  interface::RFM9x_Control       & _control;
  interface::RFM9x_Status        & _status;
  os::interface::EventConsumer   & _rx_done_event,
                                 & _rx_timeout_event,
                                 & _tx_done_event;
  os::EventGroup                   _event_group_rx_done_rx_timeout;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* RFM9x */

} /* lora */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_LORA_RFM9X_RFM9X_H_ */
