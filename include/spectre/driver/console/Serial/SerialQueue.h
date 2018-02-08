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

#ifndef INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_SERIALRXBUFFER_H_
#define INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_SERIALRXBUFFER_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <spectre/memory/container/Queue.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace driver
{

namespace console
{

namespace Serial
{

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef memory::container::Queue<uint8_t> SerialQueue;

/**************************************************************************************
 * PROTOTYPES
 **************************************************************************************/

bool isEmpty(SerialQueue const & queue);
bool isFull (SerialQueue const & queue);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* Serial */

} /* console */

} /* driver */

} /* spectre */

#endif /* INCLUDE_SPECTRE_DRIVER_CONSOLE_SERIAL_SERIALRXBUFFER_H_ */