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

#ifndef INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_DEBUG_H_
#define INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_DEBUG_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <snowfox/NoInstance.h>

#include <snowfox/driver/memory/N25Q256A/interface/N25Q256A_Io.h>

#include <snowfox/trace/Trace.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::memory::N25Q256A
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class N25Q256A_Debug final : public NoInstance
{

public:

  static void debug_dumpAllRegs(trace::Trace & trace, interface::N25Q256A_Io & io);

private:

  static void debug_dumpStatusReg    (trace::Trace & trace, interface::N25Q256A_Io & io);
  static void debug_dumpFlagStatusReg(trace::Trace & trace, interface::N25Q256A_Io & io);
  static void debug_dumpNVConfigReg  (trace::Trace & trace, interface::N25Q256A_Io & io);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::memory::N25Q256A */

#endif /* INCLUDE_SNOWFOX_DRIVER_MEMORY_N25Q256A_N25Q256A_DEBUG_H_ */
