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

#include <snowfox/hal/avr/common/ATMEGA640_1280_2560/ExternalInterruptController.h>

#include <snowfox/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>
#include <snowfox/hal/avr/common/ATxxxx/util/ExternalInterruptUtil.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::hal::ATMEGA640_1280_2560
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

ExternalInterruptController::ExternalInterruptController(volatile uint8_t               * eicra,
                                                         volatile uint8_t               * eicrb,
                                                         interface::InterruptController & int_ctrl)
: _EICRA   (eicra   ),
  _EICRB   (eicrb   ),
  _int_ctrl(int_ctrl)
{

}

ExternalInterruptController::~ExternalInterruptController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void ExternalInterruptController::setTriggerMode(uint8_t const ext_int_num, interface::TriggerMode const trigger_mode)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0): ATxxxx::setTriggerModeEint0(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1): ATxxxx::setTriggerModeEint1(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2): ATxxxx::setTriggerModeEint2(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT3): ATxxxx::setTriggerModeEint3(trigger_mode, _EICRA); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT4): ATxxxx::setTriggerModeEint4(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT5): ATxxxx::setTriggerModeEint5(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT6): ATxxxx::setTriggerModeEint6(trigger_mode, _EICRB); break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT7): ATxxxx::setTriggerModeEint7(trigger_mode, _EICRB); break;
  default                                           : /* PCINT trigger mode is Any */                    break;
  }
}

void ExternalInterruptController::enable(uint8_t const ext_int_num)
{
  uint8_t const int_num = converToIntNum(ext_int_num);
  if(int_num != interface::InterruptController::INVALID_INT_NUM)
  {
    _int_ctrl.enableInterrupt(int_num);
  }
}

void ExternalInterruptController::disable(uint8_t const ext_int_num)
{
  uint8_t const int_num = converToIntNum(ext_int_num);
  if(int_num != interface::InterruptController::INVALID_INT_NUM)
  {
    _int_ctrl.disableInterrupt(int_num);
  }
}

void ExternalInterruptController::registerInterruptCallback(uint8_t const ext_int_num, interface::ExternalInterruptCallback * external_interrupt_callback)
{
  uint8_t const int_num = converToIntNum(ext_int_num);
  if(int_num != interface::InterruptController::INVALID_INT_NUM)
  {
    _int_ctrl.registerInterruptCallback(int_num, external_interrupt_callback);
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t ExternalInterruptController::converToIntNum(uint8_t const ext_int_num)
{
  switch(ext_int_num)
  {
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT0   ): return toIntNum(Interrupt::EXTERNAL_INT0   );           break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT1   ): return toIntNum(Interrupt::EXTERNAL_INT1   );           break;
  case toExtIntNum(ExternalInterrupt::EXTERNAL_INT2   ): return toIntNum(Interrupt::EXTERNAL_INT2   );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT0 ): return toIntNum(Interrupt::PIN_CHANGE_INT0 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT1 ): return toIntNum(Interrupt::PIN_CHANGE_INT1 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT2 ): return toIntNum(Interrupt::PIN_CHANGE_INT2 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT3 ): return toIntNum(Interrupt::PIN_CHANGE_INT3 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT4 ): return toIntNum(Interrupt::PIN_CHANGE_INT4 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT5 ): return toIntNum(Interrupt::PIN_CHANGE_INT5 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT6 ): return toIntNum(Interrupt::PIN_CHANGE_INT6 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT7 ): return toIntNum(Interrupt::PIN_CHANGE_INT7 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT8 ): return toIntNum(Interrupt::PIN_CHANGE_INT8 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT9 ): return toIntNum(Interrupt::PIN_CHANGE_INT9 );           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT10): return toIntNum(Interrupt::PIN_CHANGE_INT10);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT11): return toIntNum(Interrupt::PIN_CHANGE_INT11);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT12): return toIntNum(Interrupt::PIN_CHANGE_INT12);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT13): return toIntNum(Interrupt::PIN_CHANGE_INT13);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT14): return toIntNum(Interrupt::PIN_CHANGE_INT14);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT15): return toIntNum(Interrupt::PIN_CHANGE_INT15);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT16): return toIntNum(Interrupt::PIN_CHANGE_INT16);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT17): return toIntNum(Interrupt::PIN_CHANGE_INT17);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT18): return toIntNum(Interrupt::PIN_CHANGE_INT18);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT19): return toIntNum(Interrupt::PIN_CHANGE_INT19);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT20): return toIntNum(Interrupt::PIN_CHANGE_INT20);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT21): return toIntNum(Interrupt::PIN_CHANGE_INT21);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT22): return toIntNum(Interrupt::PIN_CHANGE_INT22);           break;
  case toExtIntNum(ExternalInterrupt::PIN_CHANGE_INT23): return toIntNum(Interrupt::PIN_CHANGE_INT23);           break;
  default                                              : return interface::InterruptController::INVALID_INT_NUM; break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::hal::ATMEGA640_1280_2560 */
