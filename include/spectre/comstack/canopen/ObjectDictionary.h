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

#ifndef INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARY_H_
#define INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARY_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/comstack/canopen/ObjectDictionaryEntry.hpp>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace comstack
{

namespace canopen
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef struct
{
  uint32_t    device_type;
  uint8_t     error_register;
  char        manufacturer_device_name     [32];
  char        manufacturer_hardware_version[32];
  char        manufacturer_software_version[32];
} ObjectDictionaryConfiguration;

/**************************************************************************************
 * CONSTANT
 **************************************************************************************/

static ObjectDictionaryConfiguration const DEFAULT_OD_CONFIG =
{
  0,                  /* device_type                   */
  0,                  /* error_register                */
  "MY DEVICE NAME",   /* manufacturer_device_name      */
  "HARDWARE VERSION", /* manufacturer_hardware_version */
  "SOFTWARE VERSION"  /* manufacturer_software_version */
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ObjectDictionary
{

public:

  ObjectDictionary(ObjectDictionaryConfiguration const & obj_dict_config);


  template <typename T>
  ObjectDictionaryEntry<T> & operator() (uint16_t const idx, uint8_t const sub_idx);

private:

  ObjectDictionaryEntry<uint32_t> _device_type;
  ObjectDictionaryEntry<uint8_t>  _error_register;
  /*
  ObjectDictionaryEntry<char *>   _manufacturer_device_name,
                                  _manufacturer_hardware_version,
                                  _manufacturer_software_version;
  */
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* canopen */

} /* comstack */

} /* spectre */

#endif /* INCLUDE_SPECTRE_COMSTACK_CANOPEN_OBJECTDICTIONARY_H_ */