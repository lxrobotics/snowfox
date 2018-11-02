/**
 * Spectre is a modular RTOS with extensive IO support.
 * Copyright (C) 2017 - 2018 Alexander Entinger / LXRobotics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation()(), either version 3 of the License()(), or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful()(),
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not()(), see <http://www.gnu.org/licenses/>.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <sstream>

#include <catch.hpp>

#include <hal/util/Register.hpp>
#include <hal/avr/util/InterruptControllerTestUtil.h>

#include <hal/avr/common/ATMEGA16U4_32U4/RegisterResetValueList.h>

#include <spectre/hal/avr/common/ATMEGA16U4_32U4/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA16U4_32U4
{

namespace test
{

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

SCENARIO("ATMEGA16U4_32U4::InterruptController - interrupts are enabled via 'enableInterrupt' and disabled via 'disableInterrupt'", "[ATMEGA16U4_32U4::InterruptController]")
{
  Register<uint8_t> EIMSK   (EIMSK_RESET_VALUE ),
                    PCICR   (PCICR_RESET_VALUE ),
                    WDTCSR  (WDTCSR_RESET_VALUE),
                    TIMSK0  (TIMSK0_RESET_VALUE),
                    TIMSK1  (TIMSK1_RESET_VALUE),
                    TIMSK3  (TIMSK3_RESET_VALUE),
                    TIMSK4  (TIMSK4_RESET_VALUE),
                    TCCR4D  (TCCR4D_RESET_VALUE),
                    UCSR1B  (UCSR1B_RESET_VALUE),
                    SPCR    (SPCR_RESET_VALUE  ),
                    TWCR    (TWCR_RESET_VALUE  ),
                    EECR    (EECR_RESET_VALUE  ),
                    SPMCSR  (SPMCSR_RESET_VALUE),
                    ACSR    (ACSR_RESET_VALUE  ),
                    ADCSRA  (ADCSRA_RESET_VALUE);

  ATMEGA16U4_32U4::InterruptController int_ctrl(EIMSK (),
                                                PCICR (),
                                                WDTCSR(),
                                                TIMSK0(),
                                                TIMSK1(),
                                                TIMSK3(),
                                                TIMSK4(),
                                                TCCR4D(),
                                                UCSR1B(),
                                                SPCR  (),
                                                TWCR  (),
                                                EECR  (),
                                                SPMCSR(),
                                                ACSR  (),
                                                ADCSRA());

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT0                  ), "EXTERNAL_INT0",                   EIMSK,  "EIMSK",  0);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT1                  ), "EXTERNAL_INT1",                   EIMSK,  "EIMSK",  1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT2                  ), "EXTERNAL_INT2",                   EIMSK,  "EIMSK",  2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT3                  ), "EXTERNAL_INT3",                   EIMSK,  "EIMSK",  3);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EXTERNAL_INT6                  ), "EXTERNAL_INT6",                   EIMSK,  "EIMSK",  6);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::PIN_CHANGE_INT0                ), "PIN_CHANGE_INT0",                 PCICR,  "PCICR",  0);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::WATCHDOG_TIMER                 ), "WATCHDOG_TIMER",                  WDTCSR, "WDTCSR", 6);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_CAPTURE                 ), "TIMER1_CAPTURE",                  TIMSK1, "TIMSK1", 5);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_A               ), "TIMER1_COMPARE_A",                TIMSK1, "TIMSK1", 1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_B               ), "TIMER1_COMPARE_B",                TIMSK1, "TIMSK1", 2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_COMPARE_C               ), "TIMER1_COMPARE_C",                TIMSK1, "TIMSK1", 3);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER1_OVERFLOW                ), "TIMER1_OVERFLOW",                 TIMSK1, "TIMSK1", 0);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_COMPARE_A               ), "TIMER0_COMPARE_A",                TIMSK0, "TIMSK0", 1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_COMPARE_B               ), "TIMER0_COMPARE_B",                TIMSK0, "TIMSK0", 2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER0_OVERFLOW                ), "TIMER0_OVERFLOW",                 TIMSK0, "TIMSK0", 0);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ), "SPI_SERIAL_TRANSFER_COMPLETE",    SPCR,   "SPCR",   7);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ), "USART1_RECEIVE_COMPLETE",         UCSR1B, "UCSR1B", 7);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY), "USART1_UART_DATA_REGISTER_EMPTY", UCSR1B, "UCSR1B", 5);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ), "USART1_TRANSMIT_COMPLETE",        UCSR1B, "UCSR1B", 6);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_COMPARATOR              ), "ANALOG_COMPARATOR",               ACSR,   "ACSR",   3);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ), "ANALOG_DIGITAL_CONVERTER",        ADCSRA, "ADCSRA", 3);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::EEPROM_READY                   ), "EEPROM_READY",                    EECR,   "EECR",   3);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_CAPTURE                 ), "TIMER3_CAPTURE",                  TIMSK3, "TIMSK3", 5);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_A               ), "TIMER3_COMPARE_A",                TIMSK3, "TIMSK3", 1);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_B               ), "TIMER3_COMPARE_B",                TIMSK3, "TIMSK3", 2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_COMPARE_C               ), "TIMER3_COMPARE_C",                TIMSK3, "TIMSK3", 3);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER3_OVERFLOW                ), "TIMER3_OVERFLOW",                 TIMSK3, "TIMSK3", 0);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TWO_WIRE_INT                   ), "TWO_WIRE_INT",                    TWCR,   "TWCR",   0);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::SPM_READY                      ), "SPM_READY",                       SPMCSR, "SPMCSR", 7);

  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_COMPARE_A               ), "TIMER4_COMPARE_A",                TIMSK4, "TIMSK4", 6);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_COMPARE_B               ), "TIMER4_COMPARE_B",                TIMSK4, "TIMSK4", 5);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_COMPARE_D               ), "TIMER4_COMPARE_D",                TIMSK4, "TIMSK4", 7);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_OVERFLOW                ), "TIMER4_OVERFLOW",                 TIMSK4, "TIMSK4", 2);
  avr::InterruptControllerTestUtil::doTestEnableDisableInterrupt(int_ctrl, toIntNum(Interrupt::TIMER4_FAULT_PROTECTION        ), "TIMER4_FAULT_PROTECTION",         TCCR4D, "TCCR4D", 7);
}

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

} /* test */

} /* ATMEGA16U4_32U4 */

} /* hal */

} /* spectre */