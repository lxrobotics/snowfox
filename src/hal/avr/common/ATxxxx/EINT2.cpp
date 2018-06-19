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

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <spectre/hal/avr/common/ATxxxx/EINT2.h>

#if   defined(MCU_TYPE_atmega328p)
  #include <spectre/hal/avr/ATMEGA328P/InterruptController.h>
#elif defined(MCU_TYPE_at90can32)
  #include <spectre/hal/avr/AT90CAN32/InterruptController.h>
#elif defined(MCU_TYPE_at90can64)
  #include <spectre/hal/avr/AT90CAN64/InterruptController.h>
#elif defined(MCU_TYPE_at90can128)
  #include <spectre/hal/avr/AT90CAN128/InterruptController.h>
#elif defined(MCU_TYPE_atmega640)
  #include <spectre/hal/avr/AT90CAN640/InterruptController.h>
#elif defined(MCU_TYPE_atmega1280)
  #include <spectre/hal/avr/AT90CAN1280/InterruptController.h>
#elif defined(MCU_TYPE_atmega2560)
  #include <spectre/hal/avr/AT90CAN2560/InterruptController.h>
#else
  #include <spectre/hal/interface/interrupt/InterruptController.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATxxxx
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EICRA */
#define ISC21_bm (1<<5)
#define ISC20_bm (1<<4)

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

#if   defined(MCU_TYPE_atmega328p)
  static uint8_t const INT_NUM = ATMEGA328P::toIntNum(ATMEGA328P::Interrupt::EXTERNAL_INT7);
#elif defined(MCU_TYPE_at90can32)
  static uint8_t const INT_NUM = AT90CAN32::toIntNum(AT90CAN32::Interrupt::EXTERNAL_INT7);
#elif defined(MCU_TYPE_at90can64)
  static uint8_t const INT_NUM = AT90CAN64::toIntNum(AT90CAN64::Interrupt::EXTERNAL_INT7);
#elif defined(MCU_TYPE_at90can128)
  static uint8_t const INT_NUM = AT90CAN128::toIntNum(AT90CAN128::Interrupt::EXTERNAL_INT7);
#elif defined(MCU_TYPE_atmega640)
  static uint8_t const INT_NUM = ATMEGA640::toIntNum(ATMEGA640::Interrupt::EXTERNAL_INT7);
#elif defined(MCU_TYPE_atmega1280)
  static uint8_t const INT_NUM = ATMEGA1280::toIntNum(ATMEGA1280::Interrupt::EXTERNAL_INT7);
#elif defined(MCU_TYPE_atmega2560)
  static uint8_t const INT_NUM = ATMEGA2560::toIntNum(ATMEG2560::Interrupt::EXTERNAL_INT7);
#else
  static uint8_t const INT_NUM = interface::InterruptController::INVALID_INT_NUM;
#endif

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

EINT2::EINT2(volatile uint8_t * eicra, interface::InterruptController & int_ctrl)
: _EICRA                      (eicra   ),
  _int_ctrl                   (int_ctrl),
  _external_interrupt_callback(0       )
{

}

EINT2::~EINT2()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void EINT2::setTriggerMode(interface::TriggerMode const trigger_mode)
{
  *_EICRA &= ~(ISC21_bm | ISC20_bm);

  switch(trigger_mode)
  {
  case interface::TriggerMode::Any        : *_EICRA |=            ISC20_bm; break;
  case interface::TriggerMode::Low        : *_EICRA |= 0;                   break;
  case interface::TriggerMode::High       : /* Not supported */             break;
  case interface::TriggerMode::RisingEdge : *_EICRA |= ISC21_bm | ISC20_bm; break;
  case interface::TriggerMode::FallingEdge: *_EICRA |= ISC21_bm;            break;
  }
}

void EINT2::enable()
{
  _int_ctrl.enableInterrupt(INT_NUM);
}

void EINT2::disable()
{
  _int_ctrl.disableInterrupt(INT_NUM);
}

void EINT2::registerExternalInterruptCallback(interface::ExternalInterruptCallback * external_interrupt_callback)
{
  _external_interrupt_callback = external_interrupt_callback;
}

void EINT2::ISR_onExternalInterruptEvent()
{
  if(_external_interrupt_callback)
  {
    _external_interrupt_callback->onExternalEventCallback();
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATxxxx */

} /* hal */

} /* spectre */
