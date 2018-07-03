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

#include <spectre/hal/avr/common/ATMEGA640_1280_2560/InterruptController.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA640_1280_2560
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

/* PCICR */
#define PCIE0_bm  (1<<0)
#define PCIE1_bm  (1<<1)
#define PCIE2_bm  (1<<2)

/* WDTCSR */
#define WDIE_bm   (1<<6)

/* TIMSK2 */
#define OCIE2B_bm (1<<2)
#define OCIE2A_bm (1<<1)
#define TOIE2_bm  (1<<0)

/* TIMSK1 */
#define ICIE1_bm  (1<<5)
#define OCIE1C_bm (1<<3)
#define OCIE1B_bm (1<<2)
#define OCIE1A_bm (1<<1)
#define TOIE1_bm  (1<<0)

/* TIMSK0 */
#define OCIE0B_bm (1<<2)
#define OCIE0A_bm (1<<1)
#define TOIE0_bm  (1<<0)

/* SPCR */
#define SPIE_bm   (1<<7)

/* UCSR0B */
#define RXCIE0_bm (1<<7)
#define TXCIE0_bm (1<<6)
#define UDRIE0_bm (1<<5)

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
#define RXCIE1_bm (1<<7)
#define TXCIE1_bm (1<<6)
#define UDRIE1_bm (1<<5)

/* TIMSK4 */
#define ICIE4_bm  (1<<5)
#define OCIE4C_bm (1<<3)
#define OCIE4B_bm (1<<2)
#define OCIE4A_bm (1<<1)
#define TOIE4_bm  (1<<0)

/* TIMSK5 */
#define ICIE5_bm  (1<<5)
#define OCIE5C_bm (1<<3)
#define OCIE5B_bm (1<<2)
#define OCIE5A_bm (1<<1)
#define TOIE5_bm  (1<<0)

/* UCSR2B */
#define RXCIE2_bm (1<<7)
#define TXCIE2_bm (1<<6)
#define UDRIE2_bm (1<<5)

/* UCSR3B */
#define RXCIE3_bm (1<<7)
#define TXCIE3_bm (1<<6)
#define UDRIE3_bm (1<<5)

/* TWCR */
#define TWIE_bm   (1<<0)

/* SPMCSR */
#define SPMIE_bm  (1<<7)

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

static interface::InterruptCallback * isr_external_int0                   = 0,
                                    * isr_external_int1                   = 0,
                                    * isr_external_int2                   = 0,
                                    * isr_external_int3                   = 0,
                                    * isr_external_int4                   = 0,
                                    * isr_external_int5                   = 0,
                                    * isr_external_int6                   = 0,
                                    * isr_external_int7                   = 0,
                                    * isr_pin_change_int0                 = 0,
                                    * isr_pin_change_int1                 = 0,
                                    * isr_pin_change_int2                 = 0,
                                    * isr_watchdog_timer                  = 0,
                                    * isr_timer2_compare_a                = 0,
                                    * isr_timer2_compare_b                = 0,
                                    * isr_timer2_overflow                 = 0,
                                    * isr_timer1_capture                  = 0,
                                    * isr_timer1_compare_a                = 0,
                                    * isr_timer1_compare_b                = 0,
                                    * isr_timer1_compare_c                = 0,
                                    * isr_timer1_overflow                 = 0,
                                    * isr_timer0_compare_a                = 0,
                                    * isr_timer0_compare_b                = 0,
                                    * isr_timer0_overflow                 = 0,
                                    * isr_spi_serial_transfer_complete    = 0,
                                    * isr_usart0_receive_complete         = 0,
                                    * isr_usart0_uart_data_register_empty = 0,
                                    * isr_usart0_transmit_complete        = 0,
                                    * isr_analog_comparator               = 0,
                                    * isr_analog_digital_converter        = 0,
                                    * isr_eeprom_ready                    = 0,
                                    * isr_timer3_capture                  = 0,
                                    * isr_timer3_compare_a                = 0,
                                    * isr_timer3_compare_b                = 0,
                                    * isr_timer3_compare_c                = 0,
                                    * isr_timer3_overflow                 = 0,
                                    * isr_usart1_receive_complete         = 0,
                                    * isr_usart1_uart_data_register_empty = 0,
                                    * isr_usart1_transmit_complete        = 0,
                                    * isr_two_wire_int                    = 0,
                                    * isr_spm_ready                       = 0,
                                    * isr_timer4_capture                  = 0,
                                    * isr_timer4_compare_a                = 0,
                                    * isr_timer4_compare_b                = 0,
                                    * isr_timer4_compare_c                = 0,
                                    * isr_timer4_overflow                 = 0,
                                    * isr_timer5_capture                  = 0,
                                    * isr_timer5_compare_a                = 0,
                                    * isr_timer5_compare_b                = 0,
                                    * isr_timer5_compare_c                = 0,
                                    * isr_timer5_overflow                 = 0,
                                    * isr_usart2_receive_complete         = 0,
                                    * isr_usart2_uart_data_register_empty = 0,
                                    * isr_usart2_transmit_complete        = 0,
                                    * isr_usart3_receive_complete         = 0,
                                    * isr_usart3_uart_data_register_empty = 0,
                                    * isr_usart3_transmit_complete        = 0;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

InterruptController::InterruptController(volatile uint8_t * eimsk,
                                         volatile uint8_t * pcicr,
                                         volatile uint8_t * wdtcsr,
                                         volatile uint8_t * timsk2,
                                         volatile uint8_t * timsk1,
                                         volatile uint8_t * timsk0,
                                         volatile uint8_t * spcr,
                                         volatile uint8_t * ucsr0b,
                                         volatile uint8_t * acsr,
                                         volatile uint8_t * adcsra,
                                         volatile uint8_t * eecr,
                                         volatile uint8_t * timsk3,
                                         volatile uint8_t * ucsr1b,
                                         volatile uint8_t * twcr,
                                         volatile uint8_t * spmcsr,
                                         volatile uint8_t * timsk4,
                                         volatile uint8_t * timsk5,
                                         volatile uint8_t * ucsr2b,
                                         volatile uint8_t * ucsr3b)
: _EIMSK (eimsk ),
  _PCICR (pcicr ),
  _WDTCSR(wdtcsr),
  _TIMSK2(timsk2),
  _TIMSK1(timsk1),
  _TIMSK0(timsk0),
  _SPCR  (spcr  ),
  _UCSR0B(ucsr0b),
  _ACSR  (acsr  ),
  _ADCSRA(adcsra),
  _EECR  (eecr  ),
  _TIMSK3(timsk3),
  _UCSR1B(ucsr1b),
  _TWCR  (twcr  ),
  _SPMCSR(spmcsr),
  _TIMSK4(timsk4),
  _TIMSK5(timsk5),
  _UCSR2B(ucsr2b),
  _UCSR3B(ucsr3b)
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
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): *_EIMSK   |= INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): *_EIMSK   |= INT1_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): *_EIMSK   |= INT2_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): *_EIMSK   |= INT3_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): *_EIMSK   |= INT4_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): *_EIMSK   |= INT5_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): *_EIMSK   |= INT6_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): *_EIMSK   |= INT7_bm;   break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): *_PCICR   |= PCIE0_bm;  break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): *_PCICR   |= PCIE1_bm;  break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): *_PCICR   |= PCIE2_bm;  break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): *_WDTCSR  |= WDIE_bm;   break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): *_TIMSK2  |= OCIE2A_bm; break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): *_TIMSK2  |= OCIE2B_bm; break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): *_TIMSK2  |= TOIE2_bm;  break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): *_TIMSK1  |= ICIE1_bm;  break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): *_TIMSK1  |= OCIE1A_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): *_TIMSK1  |= OCIE1B_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): *_TIMSK1  |= OCIE1C_bm; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): *_TIMSK1  |= TOIE1_bm;  break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): *_TIMSK0  |= OCIE0A_bm; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): *_TIMSK0  |= OCIE0B_bm; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): *_TIMSK0  |= TOIE0_bm;  break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): *_SPCR    |= SPIE_bm;   break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): *_UCSR0B  |= RXCIE0_bm; break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): *_UCSR0B  |= UDRIE0_bm; break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): *_UCSR0B  |= TXCIE0_bm; break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): *_ACSR    |= ACIE_bm;   break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): *_ADCSRA  |= ADIE_bm;   break;
  case toIntNum(Interrupt::EEPROM_READY                   ): *_EECR    |= EERIE_bm;  break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): *_TIMSK3  |= ICIE3_bm;  break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): *_TIMSK3  |= OCIE3A_bm; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): *_TIMSK3  |= OCIE3B_bm; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): *_TIMSK3  |= OCIE3C_bm; break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): *_TIMSK3  |= TOIE3_bm;  break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): *_UCSR1B  |= RXCIE1_bm; break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): *_UCSR1B  |= UDRIE1_bm; break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): *_UCSR1B  |= TXCIE1_bm; break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): *_TWCR    |= TWIE_bm;   break;
  case toIntNum(Interrupt::SPM_READY                      ): *_SPMCSR  |= SPMIE_bm;  break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): *_TIMSK4  |= ICIE4_bm;  break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): *_TIMSK4  |= OCIE4A_bm; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): *_TIMSK4  |= OCIE4B_bm; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): *_TIMSK4  |= OCIE4C_bm; break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): *_TIMSK4  |= TOIE4_bm;  break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): *_TIMSK5  |= ICIE5_bm;  break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): *_TIMSK5  |= OCIE5A_bm; break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): *_TIMSK5  |= OCIE5B_bm; break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): *_TIMSK5  |= OCIE5C_bm; break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): *_TIMSK5  |= TOIE5_bm;  break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): *_UCSR2B  |= RXCIE2_bm; break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): *_UCSR2B  |= UDRIE2_bm; break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): *_UCSR2B  |= TXCIE2_bm; break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): *_UCSR3B  |= RXCIE3_bm; break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): *_UCSR3B  |= UDRIE3_bm; break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): *_UCSR3B  |= TXCIE3_bm; break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("sei");    break;
#endif
  case toIntNum(Interrupt::INVALID                        ): /* DO NOTHING */        break;
  }
}

void InterruptController::disableInterrupt(uint8_t const int_num)
{
  switch(int_num)
  {
  case toIntNum(Interrupt::EXTERNAL_INT0                  ): *_EIMSK   &= ~INT0_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT1                  ): *_EIMSK   &= ~INT1_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT2                  ): *_EIMSK   &= ~INT2_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT3                  ): *_EIMSK   &= ~INT3_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT4                  ): *_EIMSK   &= ~INT4_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT5                  ): *_EIMSK   &= ~INT5_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT6                  ): *_EIMSK   &= ~INT6_bm;   break;
  case toIntNum(Interrupt::EXTERNAL_INT7                  ): *_EIMSK   &= ~INT7_bm;   break;
  case toIntNum(Interrupt::PIN_CHANGE_INT0                ): *_PCICR   &= ~PCIE0_bm;  break;
  case toIntNum(Interrupt::PIN_CHANGE_INT1                ): *_PCICR   &= ~PCIE1_bm;  break;
  case toIntNum(Interrupt::PIN_CHANGE_INT2                ): *_PCICR   &= ~PCIE2_bm;  break;
  case toIntNum(Interrupt::WATCHDOG_TIMER                 ): *_WDTCSR  &= ~WDIE_bm;   break;
  case toIntNum(Interrupt::TIMER2_COMPARE_A               ): *_TIMSK2  &= ~OCIE2A_bm; break;
  case toIntNum(Interrupt::TIMER2_COMPARE_B               ): *_TIMSK2  &= ~OCIE2B_bm; break;
  case toIntNum(Interrupt::TIMER2_OVERFLOW                ): *_TIMSK2  &= ~TOIE2_bm;  break;
  case toIntNum(Interrupt::TIMER1_CAPTURE                 ): *_TIMSK1  &= ~ICIE1_bm;  break;
  case toIntNum(Interrupt::TIMER1_COMPARE_A               ): *_TIMSK1  &= ~OCIE1A_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_B               ): *_TIMSK1  &= ~OCIE1B_bm; break;
  case toIntNum(Interrupt::TIMER1_COMPARE_C               ): *_TIMSK1  &= ~OCIE1C_bm; break;
  case toIntNum(Interrupt::TIMER1_OVERFLOW                ): *_TIMSK1  &= ~TOIE1_bm;  break;
  case toIntNum(Interrupt::TIMER0_COMPARE_A               ): *_TIMSK0  &= ~OCIE0A_bm; break;
  case toIntNum(Interrupt::TIMER0_COMPARE_B               ): *_TIMSK0  &= ~OCIE0B_bm; break;
  case toIntNum(Interrupt::TIMER0_OVERFLOW                ): *_TIMSK0  &= ~TOIE0_bm;  break;
  case toIntNum(Interrupt::SPI_SERIAL_TRANSFER_COMPLETE   ): *_SPCR    &= ~SPIE_bm;   break;
  case toIntNum(Interrupt::USART0_RECEIVE_COMPLETE        ): *_UCSR0B  &= ~RXCIE0_bm; break;
  case toIntNum(Interrupt::USART0_UART_DATA_REGISTER_EMPTY): *_UCSR0B  &= ~UDRIE0_bm; break;
  case toIntNum(Interrupt::USART0_TRANSMIT_COMPLETE       ): *_UCSR0B  &= ~TXCIE0_bm; break;
  case toIntNum(Interrupt::ANALOG_COMPARATOR              ): *_ACSR    &= ~ACIE_bm;   break;
  case toIntNum(Interrupt::ANALOG_DIGITAL_CONVERTER       ): *_ADCSRA  &= ~ADIE_bm;   break;
  case toIntNum(Interrupt::EEPROM_READY                   ): *_EECR    &= ~EERIE_bm;  break;
  case toIntNum(Interrupt::TIMER3_CAPTURE                 ): *_TIMSK3  &= ~ICIE3_bm;  break;
  case toIntNum(Interrupt::TIMER3_COMPARE_A               ): *_TIMSK3  &= ~OCIE3A_bm; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_B               ): *_TIMSK3  &= ~OCIE3B_bm; break;
  case toIntNum(Interrupt::TIMER3_COMPARE_C               ): *_TIMSK3  &= ~OCIE3C_bm; break;
  case toIntNum(Interrupt::TIMER3_OVERFLOW                ): *_TIMSK3  &= ~TOIE3_bm;  break;
  case toIntNum(Interrupt::USART1_RECEIVE_COMPLETE        ): *_UCSR1B  &= ~RXCIE1_bm; break;
  case toIntNum(Interrupt::USART1_UART_DATA_REGISTER_EMPTY): *_UCSR1B  &= ~UDRIE1_bm; break;
  case toIntNum(Interrupt::USART1_TRANSMIT_COMPLETE       ): *_UCSR1B  &= ~TXCIE1_bm; break;
  case toIntNum(Interrupt::TWO_WIRE_INT                   ): *_TWCR    &= ~TWIE_bm;   break;
  case toIntNum(Interrupt::SPM_READY                      ): *_SPMCSR  &= ~SPMIE_bm;  break;
  case toIntNum(Interrupt::TIMER4_CAPTURE                 ): *_TIMSK4  &= ~ICIE4_bm;  break;
  case toIntNum(Interrupt::TIMER4_COMPARE_A               ): *_TIMSK4  &= ~OCIE4A_bm; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_B               ): *_TIMSK4  &= ~OCIE4B_bm; break;
  case toIntNum(Interrupt::TIMER4_COMPARE_C               ): *_TIMSK4  &= ~OCIE4C_bm; break;
  case toIntNum(Interrupt::TIMER4_OVERFLOW                ): *_TIMSK4  &= ~TOIE4_bm;  break;
  case toIntNum(Interrupt::TIMER5_CAPTURE                 ): *_TIMSK5  &= ~ICIE5_bm;  break;
  case toIntNum(Interrupt::TIMER5_COMPARE_A               ): *_TIMSK5  &= ~OCIE5A_bm; break;
  case toIntNum(Interrupt::TIMER5_COMPARE_B               ): *_TIMSK5  &= ~OCIE5B_bm; break;
  case toIntNum(Interrupt::TIMER5_COMPARE_C               ): *_TIMSK5  &= ~OCIE5C_bm; break;
  case toIntNum(Interrupt::TIMER5_OVERFLOW                ): *_TIMSK5  &= ~TOIE5_bm;  break;
  case toIntNum(Interrupt::USART2_RECEIVE_COMPLETE        ): *_UCSR2B  &= ~RXCIE2_bm; break;
  case toIntNum(Interrupt::USART2_UART_DATA_REGISTER_EMPTY): *_UCSR2B  &= ~UDRIE2_bm; break;
  case toIntNum(Interrupt::USART2_TRANSMIT_COMPLETE       ): *_UCSR2B  &= ~TXCIE2_bm; break;
  case toIntNum(Interrupt::USART3_RECEIVE_COMPLETE        ): *_UCSR3B  &= ~RXCIE3_bm; break;
  case toIntNum(Interrupt::USART3_UART_DATA_REGISTER_EMPTY): *_UCSR3B  &= ~UDRIE3_bm; break;
  case toIntNum(Interrupt::USART3_TRANSMIT_COMPLETE       ): *_UCSR3B  &= ~TXCIE3_bm; break;
#if defined(MCU_ARCH_avr)
  case toIntNum(Interrupt::GLOBAL                         ): asm volatile("cli");     break;
#endif
  }
}

void InterruptController::registerInterruptCallback(uint8_t const isr_num, interface::InterruptCallback * interrupt_callback)
{
  switch(isr_num)
  {
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT0                  ): isr_external_int0                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT1                  ): isr_external_int1                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT2                  ): isr_external_int2                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT3                  ): isr_external_int3                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT4                  ): isr_external_int4                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT5                  ): isr_external_int5                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT6                  ): isr_external_int6                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EXTERNAL_INT7                  ): isr_external_int7                   = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT0                ): isr_pin_change_int0                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT1                ): isr_pin_change_int1                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::PIN_CHANGE_INT2                ): isr_pin_change_int2                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::WATCHDOG_TIMER                 ): isr_watchdog_timer                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_COMPARE_A               ): isr_timer2_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_COMPARE_B               ): isr_timer2_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER2_OVERFLOW                ): isr_timer2_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_CAPTURE                 ): isr_timer1_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_A               ): isr_timer1_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_B               ): isr_timer1_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_COMPARE_C               ): isr_timer1_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER1_OVERFLOW                ): isr_timer1_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE_A               ): isr_timer0_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_COMPARE_B               ): isr_timer0_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER0_OVERFLOW                ): isr_timer0_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPI_SERIAL_TRANSFER_COMPLETE   ): isr_spi_serial_transfer_complete    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_RECEIVE_COMPLETE        ): isr_usart0_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_UART_DATA_REGISTER_EMPTY): isr_usart0_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART0_TRANSMIT_COMPLETE       ): isr_usart0_transmit_complete        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_COMPARATOR              ): isr_analog_comparator               = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::ANALOG_DIGITAL_CONVERTER       ): isr_analog_digital_converter        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::EEPROM_READY                   ): isr_eeprom_ready                    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_CAPTURE                 ): isr_timer3_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_A               ): isr_timer3_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_B               ): isr_timer3_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_COMPARE_C               ): isr_timer3_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER3_OVERFLOW                ): isr_timer3_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_RECEIVE_COMPLETE        ): isr_usart1_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_UART_DATA_REGISTER_EMPTY): isr_usart1_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART1_TRANSMIT_COMPLETE       ): isr_usart1_transmit_complete        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TWO_WIRE_INT                   ): isr_two_wire_int                    = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::SPM_READY                      ): isr_spm_ready                       = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_CAPTURE                 ): isr_timer4_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_A               ): isr_timer4_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_B               ): isr_timer4_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_COMPARE_C               ): isr_timer4_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER4_OVERFLOW                ): isr_timer4_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_CAPTURE                 ): isr_timer5_capture                  = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_COMPARE_A               ): isr_timer5_compare_a                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_COMPARE_B               ): isr_timer5_compare_b                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_COMPARE_C               ): isr_timer5_compare_c                = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::TIMER5_OVERFLOW                ): isr_timer5_overflow                 = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART2_RECEIVE_COMPLETE        ): isr_usart2_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART2_UART_DATA_REGISTER_EMPTY): isr_usart2_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART2_TRANSMIT_COMPLETE       ): isr_usart2_transmit_complete        = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART3_RECEIVE_COMPLETE        ): isr_usart3_receive_complete         = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART3_UART_DATA_REGISTER_EMPTY): isr_usart3_uart_data_register_empty = interrupt_callback; break;
  case toIsrNum(InterruptServiceRoutine::USART3_TRANSMIT_COMPLETE       ): isr_usart3_transmit_complete        = interrupt_callback; break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA640_1280_2560 */

} /* hal */

} /* spectre */

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

#if defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640) )

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre::hal::ATMEGA640_1280_2560;

/**************************************************************************************
 * INTERRUPT SERVICE ROUTINES
 **************************************************************************************/

ISR(INT0_vect)
{
  if(isr_external_int0) isr_external_int0->interruptServiceRoutine();
}

ISR(INT1_vect)
{
  if(isr_external_int1) isr_external_int1->interruptServiceRoutine();
}

ISR(INT2_vect)
{
  if(isr_external_int2) isr_external_int2->interruptServiceRoutine();
}

ISR(INT3_vect)
{
  if(isr_external_int3) isr_external_int3->interruptServiceRoutine();
}

ISR(INT4_vect)
{
  if(isr_external_int4) isr_external_int4->interruptServiceRoutine();
}

ISR(INT5_vect)
{
  if(isr_external_int5) isr_external_int5->interruptServiceRoutine();
}

ISR(INT6_vect)
{
  if(isr_external_int6) isr_external_int6->interruptServiceRoutine();
}

ISR(INT7_vect)
{
  if(isr_external_int7) isr_external_int7->interruptServiceRoutine();
}

ISR(PCINT0_vect)
{
  if(isr_pin_change_int0) isr_pin_change_int0->interruptServiceRoutine();
}

ISR(PCINT1_vect)
{
  if(isr_pin_change_int1) isr_pin_change_int1->interruptServiceRoutine();
}

ISR(PCINT2_vect)
{
  if(isr_pin_change_int2) isr_pin_change_int2->interruptServiceRoutine();
}

ISR(WDT_vect)
{
  if(isr_watchdog_timer) isr_watchdog_timer->interruptServiceRoutine();
}

ISR(TIMER2_COMPA_vect)
{
  if(isr_timer2_compare_a) isr_timer2_compare_a->interruptServiceRoutine();
}

ISR(TIMER2_COMPB_vect)
{
  if(isr_timer2_compare_b) isr_timer2_compare_b->interruptServiceRoutine();
}

ISR(TIMER2_OVF_vect)
{
  if(isr_timer2_overflow) isr_timer2_overflow->interruptServiceRoutine();
}

ISR(TIMER1_CAPT_vect)
{
  if(isr_timer1_capture) isr_timer1_capture->interruptServiceRoutine();
}

ISR(TIMER1_COMPA_vect)
{
  if(isr_timer1_compare_a) isr_timer1_compare_a->interruptServiceRoutine();
}

ISR(TIMER1_COMPB_vect)
{
  if(isr_timer1_compare_b) isr_timer1_compare_b->interruptServiceRoutine();
}

ISR(TIMER1_COMPC_vect)
{
  if(isr_timer1_compare_c) isr_timer1_compare_c->interruptServiceRoutine();
}

ISR(TIMER1_OVF_vect)
{
  if(isr_timer1_overflow) isr_timer1_overflow->interruptServiceRoutine();
}

ISR(TIMER0_COMPA_vect)
{
  if(isr_timer0_compare_a) isr_timer0_compare_a->interruptServiceRoutine();
}

ISR(TIMER0_COMPB_vect)
{
  if(isr_timer0_compare_b) isr_timer0_compare_b->interruptServiceRoutine();
}

ISR(TIMER0_OVF_vect)
{
  if(isr_timer0_overflow) isr_timer0_overflow->interruptServiceRoutine();
}

ISR(SPI_STC_vect)
{
  if(isr_spi_serial_transfer_complete) isr_spi_serial_transfer_complete->interruptServiceRoutine();
}

ISR(USART0_RX_vect)
{
  if(isr_usart0_receive_complete) isr_usart0_receive_complete->interruptServiceRoutine();
}

ISR(USART0_UDRE_vect)
{
  if(isr_usart0_uart_data_register_empty) isr_usart0_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART0_TX_vect)
{
  if(isr_usart0_transmit_complete) isr_usart0_transmit_complete->interruptServiceRoutine();
}

ISR(ANALOG_COMP_vect)
{
  if(isr_analog_comparator) isr_analog_comparator->interruptServiceRoutine();
}

ISR(ADC_vect)
{
  if(isr_analog_digital_converter) isr_analog_digital_converter->interruptServiceRoutine();
}

ISR(EE_READY_vect)
{
  if(isr_eeprom_ready) isr_eeprom_ready->interruptServiceRoutine();
}

ISR(TIMER3_CAPT_vect)
{
  if(isr_timer3_capture) isr_timer3_capture->interruptServiceRoutine();
}

ISR(TIMER3_COMPA_vect)
{
  if(isr_timer3_compare_a) isr_timer3_compare_a->interruptServiceRoutine();
}

ISR(TIMER3_COMPB_vect)
{
  if(isr_timer3_compare_b) isr_timer3_compare_b->interruptServiceRoutine();
}

ISR(TIMER3_COMPC_vect)
{
  if(isr_timer3_compare_c) isr_timer3_compare_c->interruptServiceRoutine();
}

ISR(TIMER3_OVF_vect)
{
  if(isr_timer3_overflow) isr_timer3_overflow->interruptServiceRoutine();
}

ISR(USART1_RX_vect)
{
  if(isr_usart1_receive_complete) isr_usart1_receive_complete->interruptServiceRoutine();
}

ISR(USART1_UDRE_vect)
{
  if(isr_usart1_uart_data_register_empty) isr_usart1_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART1_TX_vect)
{
  if(isr_usart1_transmit_complete) isr_usart1_transmit_complete->interruptServiceRoutine();
}

ISR(TWI_vect)
{
  if(isr_two_wire_int) isr_two_wire_int->interruptServiceRoutine();
}

ISR(SPM_READY_vect)
{
  if(isr_spm_ready) isr_spm_ready->interruptServiceRoutine();
}

ISR(TIMER4_CAPT_vect)
{
  if(isr_timer4_capture) isr_timer4_capture->interruptServiceRoutine();
}

ISR(TIMER4_COMPA_vect)
{
  if(isr_timer4_compare_a) isr_timer4_compare_a->interruptServiceRoutine();
}

ISR(TIMER4_COMPB_vect)
{
  if(isr_timer4_compare_b) isr_timer4_compare_b->interruptServiceRoutine();
}

ISR(TIMER4_COMPC_vect)
{
  if(isr_timer4_compare_c) isr_timer4_compare_c->interruptServiceRoutine();
}

ISR(TIMER4_OVF_vect)
{
  if(isr_timer4_overflow) isr_timer4_overflow->interruptServiceRoutine();
}

ISR(TIMER5_CAPT_vect)
{
  if(isr_timer5_capture) isr_timer5_capture->interruptServiceRoutine();
}

ISR(TIMER5_COMPA_vect)
{
  if(isr_timer5_compare_a) isr_timer5_compare_a->interruptServiceRoutine();
}

ISR(TIMER5_COMPB_vect)
{
  if(isr_timer5_compare_b) isr_timer5_compare_b->interruptServiceRoutine();
}

ISR(TIMER5_COMPC_vect)
{
  if(isr_timer5_compare_c) isr_timer5_compare_c->interruptServiceRoutine();
}

ISR(TIMER5_OVF_vect)
{
  if(isr_timer5_overflow) isr_timer5_overflow->interruptServiceRoutine();
}

ISR(USART2_RX_vect)
{
  if(isr_usart2_receive_complete) isr_usart2_receive_complete->interruptServiceRoutine();
}

ISR(USART2_UDRE_vect)
{
  if(isr_usart2_uart_data_register_empty) isr_usart2_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART2_TX_vect)
{
  if(isr_usart2_transmit_complete) isr_usart2_transmit_complete->interruptServiceRoutine();
}

ISR(USART3_RX_vect)
{
  if(isr_usart3_receive_complete) isr_usart3_receive_complete->interruptServiceRoutine();
}

ISR(USART3_UDRE_vect)
{
  if(isr_usart3_uart_data_register_empty) isr_usart3_uart_data_register_empty->interruptServiceRoutine();
}

ISR(USART3_TX_vect)
{
  if(isr_usart3_transmit_complete) isr_usart3_transmit_complete->interruptServiceRoutine();
}

#endif /* defined(MCU_ARCH_avr) && ( defined(MCU_TYPE_atmega2560) || defined(MCU_TYPE_atmega1280) || defined(MCU_TYPE_atmega640) ) */
