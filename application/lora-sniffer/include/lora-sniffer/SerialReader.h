/**
 * lora-sniffer is a LoRa packet sniffer based on the HopeRF RF95.
 * Copyright (C) 2018 Alexander Entinger / LXRobotics GmbH
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

#ifndef APPLICATION_LORA_SNIFFER_INCLUDE_LORA_SNIFFER_SERIALREADER_H_
#define APPLICATION_LORA_SNIFFER_INCLUDE_LORA_SNIFFER_SERIALREADER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/driver/serial/Serial.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace application
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SerialReader
{

public:

  SerialReader(spectre::driver::interface::Driver & serial);


  bool readUntil(char const key, char * msg_buf, uint16_t const num_bytes);


private:

  spectre::driver::interface::Driver & _serial;

  bool readByte(char & byte);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* application */

#endif /* APPLICATION_LORA_SNIFFER_INCLUDE_LORA_SNIFFER_SERIALREADER_H_ */
