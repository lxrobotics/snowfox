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

#include <spectre/hal/avr/AT90CAN128/InterruptController.h>

#include <assert.h>

/* Required for 'assert' which in turn needs 'abort' in avr-gcc */
#if defined(MCU_ARCH_avr)
  #include <stdlib.h>
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace AT90CAN128
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* EIMSK */
#define INT7_bm   (1<<7)
#define INT6_bm   (1<<6)
#define INT5_bm   (1<<5)
#define INT4_bm   (1<<4)
#define INT3_bm   (1<<3)
#define INT2_bm   (1<<2)
#define INT1_bm   (1<<1)
#define INT0_bm   (1<<0)

/* TIMSK2 */
#define OCIE2A_bm (1<<1)
#define TOIE2_bm  (1<<0)

/* TIMSK1 */
#define ICIE1_bm  (1<<5)
#define OCIE1C_bm (1<<3)
#define OCIE1B_bm (1<<2)
#define OCIE1A_bm (1<<1)
#define TOIE1_bm  (1<<0)

/* TIMSK0 */
#define OCIE0A_bm (1<<1)
#define TOIE0_bm  (1<<0)

/* CANGIE */
#define ENIT_bm   (1<<7)
#define ENBOFF_bm (1<<6)
#define ENRX_bm   (1<<5)
#define ENTX_bm   (1<<4)
#define ENERR_bm  (1<<3)
#define ENBX_bm   (1<<2)
#define ENERG_bm  (1<<1)
#define ENOVRT_bm (1<<0)

/* CANGIT */
#define CANIT_bm  (1<<7)
#define BOFFIT_bm (1<<6)
#define OVRTIM_bm (1<<5)
#define BXOK_bm   (1<<4)
#define SERG_bm   (1<<3)
#define CERG_bm   (1<<2)
#define FERG_bm   (1<<1)
#define AERG_bm   (1<<0)

/* CANSTMOB */
#define DLCW_bm   (1<<7)
#define TXOK_bm   (1<<6)
#define RXOK_bm   (1<<5)
#define BERR_bm   (1<<4)
#define SERR_bm   (1<<3)
#define CERR_bm   (1<<2)
#define FERR_bm   (1<<1)
#define AERR_bm   (1<<0)

/* SPCR */
#define SPIE_bm   (1<<7)

/* UCSR0B */
#define UDRIE0_bm (1<<5)
#define TXCIE0_bm (1<<6)
#define RXCIE0_bm (1<<7)

/* ACSR */
#define ACIE_bm   (1<<3)

/* ADCSRA */
#define ADIE_bm   (1<<3)

/* EECR */
#define EERIE_bm  (1<<3)

/* TIMSK3 */
#define ICIE3_bm  (1<<5)
#define OCIE3C_bm (1<<3)
#define OCIE3B_bm (1<<2)
#define OCIE3A_bm (1<<1)
#define TOIE3_bm  (1<<0)

/* UCSR1B */
#define UDRIE1_bm (1<<5)
#define TXCIE1_bm (1<<6)
#define RXCIE1_bm (1<<7)

/* TWCR */
#define TWIE_bm   (1<<0)

/* SPMCSR */
#define SPMIE_bm  (1<<7)

/* INTERRUPT NUMBERS */
#define INT_EXTERNAL_INT0                    0
#define INT_EXTERNAL_INT1                    1
#define INT_EXTERNAL_INT2                    2
#define INT_EXTERNAL_INT3                    3
#define INT_EXTERNAL_INT4                    4
#define INT_EXTERNAL_INT5                    5
#define INT_EXTERNAL_INT6                    6
#define INT_EXTERNAL_INT7                    7
#define INT_TIMER2_COMPARE                   8
#define INT_TIMER2_OVERFLOW                  9
#define INT_TIMER1_CAPTURE                   10
#define INT_TIMER1_COMPARE_A                 11
#define INT_TIMER1_COMPARE_B                 12
#define INT_TIMER1_COMPARE_C                 13
#define INT_TIMER1_OVERFLOW                  14
#define INT_TIMER0_COMPARE                   15
#define INT_TIMER0_OVERFLOW                  16
#define INT_CAN_ALL                          17
#define INT_CAN_BUS_OFF                      18
#define INT_CAN_RECEIVE                      19
#define INT_CAN_TRANSMIT                     20
#define INT_CAN_FRAME_BUFFER                 21
#define INT_CAN_GENERAL_ERROR                22
#define INT_CAN_TIMER_OVERRUN                23
#define INT_SPI_SERIAL_TRANSFER_COMPLETE     24
#define INT_USART0_RECEIVE_COMPLETE          25
#define INT_USART0_UART_DATA_REGISTER_EMPTY  26
#define INT_USART0_TRANSMIT_COMPLETE         27
#define INT_ANALOG_COMPARATOR                28
#define INT_ANALOG_DIGITAL_CONVERTER         29
#define INT_EEPROM_READY                     30
#define INT_TIMER3_CAPTURE                   31
#define INT_TIMER3_COMPARE_A                 32
#define INT_TIMER3_COMPARE_B                 33
#define INT_TIMER3_COMPARE_C                 34
#define INT_TIMER3_OVERFLOW                  35
#define INT_USART1_RECEIVE_COMPLETE          36
#define INT_USART1_UART_DATA_REGISTER_EMPTY  37
#define INT_USART1_TRANSMIT_COMPLETE         38
#define INT_TWO_WIRE_INT                     39
#define INT_SPM_READY                        40
#define INT_GLOBAL                           41
#define INT_INVALID                          255

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

/**************************************************************************************
 * GLOBAL FUNCTIONS
 **************************************************************************************/

uint8_t toIntNum(Interrupt const interrupt)
{
  switch(interrupt)
  {
  case Interrupt::EXTERNAL_INT0                   : return 0; break;
  case Interrupt::EXTERNAL_INT1                   : return 0; break;
  case Interrupt::EXTERNAL_INT2                   : return 0; break;
  case Interrupt::EXTERNAL_INT3                   : return 0; break;
  case Interrupt::EXTERNAL_INT4                   : return 0; break;
  case Interrupt::EXTERNAL_INT5                   : return 0; break;
  case Interrupt::EXTERNAL_INT6                   : return 0; break;
  case Interrupt::EXTERNAL_INT7                   : return 0; break;
  case Interrupt::TIMER2_COMPARE                  : return 0; break;
  case Interrupt::TIMER2_OVERFLOW                 : return 0; break;
  case Interrupt::TIMER1_CAPTURE                  : return 0; break;
  case Interrupt::TIMER1_COMPARE_A                : return 0; break;
  case Interrupt::TIMER1_COMPARE_B                : return 0; break;
  case Interrupt::TIMER1_COMPARE_C                : return 0; break;
  case Interrupt::TIMER1_OVERFLOW                 : return 0; break;
  case Interrupt::TIMER0_COMPARE                  : return 0; break;
  case Interrupt::TIMER0_OVERFLOW                 : return 0; break;
  case Interrupt::CAN_ALL                         : return 0; break;
  case Interrupt::CAN_BUS_OFF                     : return 0; break;
  case Interrupt::CAN_RECEIVE                     : return 0; break;
  case Interrupt::CAN_TRANSMIT                    : return 0; break;
  case Interrupt::CAN_FRAME_BUFFER                : return 0; break;
  case Interrupt::CAN_GENERAL_ERROR               : return 0; break;
  case Interrupt::CAN_TIMER_OVERRUN               : return 0; break;
  case Interrupt::SPI_SERIAL_TRANSFER_COMPLETE    : return 0; break;
  case Interrupt::USART0_RECEIVE_COMPLETE         : return 0; break;
  case Interrupt::USART0_UART_DATA_REGISTER_EMPTY : return 0;
  case Interrupt::USART0_TRANSMIT_COMPLETE        : return 0; break;
  case Interrupt::ANALOG_COMPARATOR               : return 0; break;
  case Interrupt::ANALOG_DIGITAL_CONVERTER        : return 0; break;
  case Interrupt::EEPROM_READY                    : return 0; break;
  case Interrupt::TIMER3_CAPTURE                  : return 0; break;
  case Interrupt::TIMER3_COMPARE_A                : return 0; break;
  case Interrupt::TIMER3_COMPARE_B                : return 0; break;
  case Interrupt::TIMER3_COMPARE_C                : return 0; break;
  case Interrupt::TIMER3_OVERFLOW                 : return 0; break;
  case Interrupt::USART1_RECEIVE_COMPLETE         : return 0; break;
  case Interrupt::USART1_UART_DATA_REGISTER_EMPTY : return 0; break;
  case Interrupt::USART1_TRANSMIT_COMPLETE        : return 0; break;
  case Interrupt::TWO_WIRE_INT                    : return 0; break;
  case Interrupt::SPM_READY                       : return 0; break;
  case Interrupt::GLOBAL                          : return 0; break;
  default                                         : return INT_INVALID; break;
  }
}

uint8_t toIsrNum(InterruptServiceRoutine const interrupt_service_routine)
{
  return 0;
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
                                         volatile uint8_t * timsk2,
                                         volatile uint8_t * timsk1,
                                         volatile uint8_t * timsk0,
                                         volatile uint8_t * cangie,
                                         volatile uint8_t * spcr,
                                         volatile uint8_t * ucsr0b,
                                         volatile uint8_t * acsr,
                                         volatile uint8_t * adcsra,
                                         volatile uint8_t * eecr,
                                         volatile uint8_t * timsk3,
                                         volatile uint8_t * ucsr1b,
                                         volatile uint8_t * twcr,
                                         volatile uint8_t * spmcsr)
: _EIMSK (eimsk ),
  _TIMSK2(timsk2),
  _TIMSK1(timsk1),
  _TIMSK0(timsk0),
  _CANGIE(cangie),
  _SPCR  (spcr  ),
  _UCSR0B(ucsr0b),
  _ACSR  (acsr  ),
  _ADCSRA(adcsra),
  _EECR  (eecr  ),
  _TIMSK3(timsk3),
  _UCSR1B(ucsr1b),
  _TWCR  (twcr  ),
  _SPMCSR(spmcsr)
{

}

InterruptController::~InterruptController()
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void InterruptController::enableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case INT_EXTERNAL_INT0                  : *_EIMSK   |= INT0_bm;   break;
  case INT_EXTERNAL_INT1                  : *_EIMSK   |= INT1_bm;   break;
  case INT_EXTERNAL_INT2                  : *_EIMSK   |= INT2_bm;   break;
  case INT_EXTERNAL_INT3                  : *_EIMSK   |= INT3_bm;   break;
  case INT_EXTERNAL_INT4                  : *_EIMSK   |= INT4_bm;   break;
  case INT_EXTERNAL_INT5                  : *_EIMSK   |= INT5_bm;   break;
  case INT_EXTERNAL_INT6                  : *_EIMSK   |= INT6_bm;   break;
  case INT_EXTERNAL_INT7                  : *_EIMSK   |= INT7_bm;   break;
  case INT_TIMER2_COMPARE                 : *_TIMSK2  |= OCIE2A_bm; break;
  case INT_TIMER2_OVERFLOW                : *_TIMSK2  |= TOIE2_bm;  break;
  case INT_TIMER1_CAPTURE                 : *_TIMSK1  |= ICIE1_bm;  break;
  case INT_TIMER1_COMPARE_A               : *_TIMSK1  |= OCIE1C_bm; break;
  case INT_TIMER1_COMPARE_B               : *_TIMSK1  |= OCIE1B_bm; break;
  case INT_TIMER1_COMPARE_C               : *_TIMSK1  |= OCIE1A_bm; break;
  case INT_TIMER1_OVERFLOW                : *_TIMSK1  |= TOIE1_bm;  break;
  case INT_TIMER0_COMPARE                 : *_TIMSK0  |= OCIE0A_bm; break;
  case INT_TIMER0_OVERFLOW                : *_TIMSK0  |= TOIE0_bm;  break;
  case INT_CAN_ALL                        : *_CANGIE  |= ENIT_bm;   break;
  case INT_CAN_BUS_OFF                    : *_CANGIE  |= ENBOFF_bm; break;
  case INT_CAN_RECEIVE                    : *_CANGIE  |= ENRX_bm;   break;
  case INT_CAN_TRANSMIT                   : *_CANGIE  |= ENTX_bm;   break;
  case INT_CAN_FRAME_BUFFER               : *_CANGIE  |= ENBX_bm;   break;
  case INT_CAN_GENERAL_ERROR              : *_CANGIE  |= ENERG_bm;  break;
  case INT_CAN_TIMER_OVERRUN              : *_CANGIE  |= ENOVRT_bm; break;
  case INT_SPI_SERIAL_TRANSFER_COMPLETE   : *_SPCR    |= SPIE_bm;   break;
  case INT_USART0_RECEIVE_COMPLETE        : *_UCSR0B  |= RXCIE0_bm; break;
  case INT_USART0_UART_DATA_REGISTER_EMPTY: *_UCSR0B  |= UDRIE0_bm; break;
  case INT_USART0_TRANSMIT_COMPLETE       : *_UCSR0B  |= TXCIE0_bm; break;
  case INT_ANALOG_COMPARATOR              : *_ACSR    |= ACIE_bm;   break;
  case INT_ANALOG_DIGITAL_CONVERTER       : *_ADCSRA  |= ADIE_bm;   break;
  case INT_EEPROM_READY                   : *_EECR    |= EERIE_bm;  break;
  case INT_TIMER3_CAPTURE                 : *_TIMSK3  |= ICIE3_bm;  break;
  case INT_TIMER3_COMPARE_A               : *_TIMSK3  |= OCIE3C_bm; break;
  case INT_TIMER3_COMPARE_B               : *_TIMSK3  |= OCIE3B_bm; break;
  case INT_TIMER3_COMPARE_C               : *_TIMSK3  |= OCIE3A_bm; break;
  case INT_TIMER3_OVERFLOW                : *_TIMSK3  |= TOIE3_bm;  break;
  case INT_USART1_RECEIVE_COMPLETE        : *_UCSR1B  |= RXCIE1_bm; break;
  case INT_USART1_UART_DATA_REGISTER_EMPTY: *_UCSR1B  |= UDRIE1_bm; break;
  case INT_USART1_TRANSMIT_COMPLETE       : *_UCSR1B  |= TXCIE1_bm; break;
  case INT_TWO_WIRE_INT                   : *_TWCR    |= TWIE_bm;   break;
  case INT_SPM_READY                      : *_SPMCSR  |= SPMIE_bm;  break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_at90can128)
  case INT_GLOBAL                         : asm volatile("sei");    break;
#endif
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case INT_EXTERNAL_INT0                  : *_EIMSK   &= ~INT0_bm;   break;
  case INT_EXTERNAL_INT1                  : *_EIMSK   &= ~INT1_bm;   break;
  case INT_EXTERNAL_INT2                  : *_EIMSK   &= ~INT2_bm;   break;
  case INT_EXTERNAL_INT3                  : *_EIMSK   &= ~INT3_bm;   break;
  case INT_EXTERNAL_INT4                  : *_EIMSK   &= ~INT4_bm;   break;
  case INT_EXTERNAL_INT5                  : *_EIMSK   &= ~INT5_bm;   break;
  case INT_EXTERNAL_INT6                  : *_EIMSK   &= ~INT6_bm;   break;
  case INT_EXTERNAL_INT7                  : *_EIMSK   &= ~INT7_bm;   break;
  case INT_TIMER2_COMPARE                 : *_TIMSK2  &= ~OCIE2A_bm; break;
  case INT_TIMER2_OVERFLOW                : *_TIMSK2  &= ~TOIE2_bm;  break;
  case INT_TIMER1_CAPTURE                 : *_TIMSK1  &= ~ICIE1_bm;  break;
  case INT_TIMER1_COMPARE_A               : *_TIMSK1  &= ~OCIE1C_bm; break;
  case INT_TIMER1_COMPARE_B               : *_TIMSK1  &= ~OCIE1B_bm; break;
  case INT_TIMER1_COMPARE_C               : *_TIMSK1  &= ~OCIE1A_bm; break;
  case INT_TIMER1_OVERFLOW                : *_TIMSK1  &= ~TOIE1_bm;  break;
  case INT_TIMER0_COMPARE                 : *_TIMSK0  &= ~OCIE0A_bm; break;
  case INT_TIMER0_OVERFLOW                : *_TIMSK0  &= ~TOIE0_bm;  break;
  case INT_CAN_ALL                        : *_CANGIE  &= ~ENIT_bm;   break;
  case INT_CAN_BUS_OFF                    : *_CANGIE  &= ~ENBOFF_bm; break;
  case INT_CAN_RECEIVE                    : *_CANGIE  &= ~ENRX_bm;   break;
  case INT_CAN_TRANSMIT                   : *_CANGIE  &= ~ENTX_bm;   break;
  case INT_CAN_FRAME_BUFFER               : *_CANGIE  &= ~ENBX_bm;   break;
  case INT_CAN_GENERAL_ERROR              : *_CANGIE  &= ~ENERG_bm;  break;
  case INT_CAN_TIMER_OVERRUN              : *_CANGIE  &= ~ENOVRT_bm; break;
  case INT_SPI_SERIAL_TRANSFER_COMPLETE   : *_SPCR    &= ~SPIE_bm;   break;
  case INT_USART0_RECEIVE_COMPLETE        : *_UCSR0B  &= ~RXCIE0_bm; break;
  case INT_USART0_UART_DATA_REGISTER_EMPTY: *_UCSR0B  &= ~UDRIE0_bm; break;
  case INT_USART0_TRANSMIT_COMPLETE       : *_UCSR0B  &= ~TXCIE0_bm; break;
  case INT_ANALOG_COMPARATOR              : *_ACSR    &= ~ACIE_bm;   break;
  case INT_ANALOG_DIGITAL_CONVERTER       : *_ADCSRA  &= ~ADIE_bm;   break;
  case INT_EEPROM_READY                   : *_EECR    &= ~EERIE_bm;  break;
  case INT_TIMER3_CAPTURE                 : *_TIMSK3  &= ~ICIE3_bm;  break;
  case INT_TIMER3_COMPARE_A               : *_TIMSK3  &= ~OCIE3C_bm; break;
  case INT_TIMER3_COMPARE_B               : *_TIMSK3  &= ~OCIE3B_bm; break;
  case INT_TIMER3_COMPARE_C               : *_TIMSK3  &= ~OCIE3A_bm; break;
  case INT_TIMER3_OVERFLOW                : *_TIMSK3  &= ~TOIE3_bm;  break;
  case INT_USART1_RECEIVE_COMPLETE        : *_UCSR1B  &= ~RXCIE1_bm; break;
  case INT_USART1_UART_DATA_REGISTER_EMPTY: *_UCSR1B  &= ~UDRIE1_bm; break;
  case INT_USART1_TRANSMIT_COMPLETE       : *_UCSR1B  &= ~TXCIE1_bm; break;
  case INT_TWO_WIRE_INT                   : *_TWCR    &= ~TWIE_bm;   break;
  case INT_SPM_READY                      : *_SPMCSR  &= ~SPMIE_bm;  break;
#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_at90can128)
  case INT_GLOBAL                         : asm volatile("cli");     break;
#endif
  }
}

void InterruptController::registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback)
{
  /* TODO */
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AT90CAN128 */

} /* hal */

} /* spectre */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && defined(MCU_TYPE_at90can128)

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::AT90CAN128;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(INT0_vect)
{

}

/**************************************************************************************/

ISR(INT1_vect)
{

}

/**************************************************************************************/

ISR(INT2_vect)
{

}

/**************************************************************************************/

ISR(INT3_vect)
{

}

/**************************************************************************************/

ISR(INT4_vect)
{

}

/**************************************************************************************/

ISR(INT5_vect)
{

}

/**************************************************************************************/

ISR(INT6_vect)
{

}

/**************************************************************************************/

ISR(INT7_vect)
{

}

/**************************************************************************************/

ISR(TIMER2_COMP_vect)
{

}

/**************************************************************************************/

ISR(TIMER2_OVF_vect)
{

}

/**************************************************************************************/

ISR(TIMER1_CAPT_vect)
{

}

/**************************************************************************************/

ISR(TIMER1_COMPA_vect)
{

}

/**************************************************************************************/

ISR(TIMER1_COMPB_vect)
{

}

/**************************************************************************************/

ISR(TIMER1_COMPC_vect)
{

}

/**************************************************************************************/

ISR(TIMER1_OVF_vect)
{

}

/**************************************************************************************/

ISR(TIMER0_COMP_vect)
{

}

/**************************************************************************************/

ISR(TIMER0_OVF_vect)
{

}

/**************************************************************************************/

ISR(CANIT_vect)
{

}

/**************************************************************************************/

ISR(OVRIT_vect)
{

}

/**************************************************************************************/

ISR(SPI_STC_vect)
{

}

/**************************************************************************************/

ISR(USART0_RX_vect)
{

}

/**************************************************************************************/

ISR(USART0_UDRE_vect)
{

}

/**************************************************************************************/

ISR(USART0_TX_vect)
{

}

/**************************************************************************************/

ISR(ANALOG_COMP_vect)
{

}

/**************************************************************************************/

ISR(ADC_vect)
{

}

/**************************************************************************************/

ISR(EE_READY_vect)
{

}

/**************************************************************************************/

ISR(TIMER3_CAPT_vect)
{

}

/**************************************************************************************/

ISR(TIMER3_COMPA_vect)
{

}

/**************************************************************************************/

ISR(TIMER3_COMPB_vect)
{

}

/**************************************************************************************/

ISR(TIMER3_COMPC_vect)
{

}

/**************************************************************************************/

ISR(TIMER3_OVF_vect)
{

}

/**************************************************************************************/

ISR(USART1_RX_vect)
{

}

/**************************************************************************************/

ISR(USART1_UDRE_vect)
{

}

/**************************************************************************************/

ISR(USART1_TX_vect)
{

}

/**************************************************************************************/

ISR(TWI_vect)
{

}

/**************************************************************************************/

ISR(SPM_READY_vect)
{

}

/**************************************************************************************/

#endif /* defined(MCU_ARCH_avr) && defined(MCU_TYPE_at90can128) */
