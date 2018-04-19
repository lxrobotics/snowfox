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
 * This example programm is tailored for usage with Arduino Uno
 * and Seedstudio CAN Bus Shield V2.0
 **************************************************************************************/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <avr/io.h>

#include <spectre/hal/avr/ATMEGA328P/EINT0.h>
#include <spectre/hal/avr/ATMEGA328P/SpiMaster.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalInPin.h>
#include <spectre/hal/avr/ATMEGA328P/DigitalOutPin.h>
#include <spectre/hal/avr/ATMEGA328P/InterruptController.h>

#include <spectre/driver/can/Can.h>

#include <spectre/driver/can/MCP2515/MCP2515_IoSpi.h>
#include <spectre/driver/can/MCP2515/MCP2515_Control.h>
#include <spectre/driver/can/MCP2515/MCP2515_Callback.h>
#include <spectre/driver/can/MCP2515/MCP2515_CanController.h>
#include <spectre/driver/can/MCP2515/MCP2515_CanReceiveBuffer.h>
#include <spectre/driver/can/MCP2515/MCP2515_CanTransmitBuffer.h>

/**************************************************************************************
 * NAMESPACES
 **************************************************************************************/

using namespace spectre;
using namespace spectre::hal;
using namespace spectre::driver;

/**************************************************************************************
 * GLOBAL CONSTANTS
 **************************************************************************************/

static hal::interface::SpiMode     const MCP2515_SPI_MODE         = hal::interface::SpiMode::MODE_0;
static hal::interface::SpiBitOrder const MCP2515_SPI_BIT_ORDER    = hal::interface::SpiBitOrder::MSB_FIRST;
static uint32_t                    const MCP2515_SPI_PRESCALER    = 16; /* Arduino Uno Clk = 16 MHz -> SPI Clk = 1 MHz                     */
static hal::interface::TriggerMode const MCP2515_INT_TRIGGER_MODE = hal::interface::TriggerMode::FallingEdge;

static uint8_t                     const F_MCP2515_MHz            = 16; /* Seedstudio CAN Bus Shield V2.0 is clocked with a 16 MHz crystal */
static uint16_t                    const CAN_RX_BUFFER_SIZE       = 8;
static uint16_t                    const CAN_TX_BUFFER_SIZE       = 8;

/**************************************************************************************
 * MAIN
 **************************************************************************************/

int main()
{
  /* HAL ******************************************************************************/

  ATMEGA328P::InterruptController                   int_ctrl               (&EIMSK, &PCICR, &WDTCSR, &TIMSK2, &TIMSK1, &TIMSK0, &SPCR, &UCSR0B, &ADCSRA, &EECR, &ACSR, &TWCR, &SPMCSR);
  ATMEGA328P::SpiMaster                             spi_master             (&SPCR, &SPSR, &SPDR);
  ATMEGA328P::DigitalOutPin                         mcp2515_cs             (&DDRB, &PORTB, 1);        /* D9 = PB1        */
  ATMEGA328P::DigitalInPin                          mcp2515_int_pin        (&DDRD, &PORTD, &PIND, 2); /* D2 = PD2 = INT0 */
  ATMEGA328P::EINT0                                 mcp2515_eint0          (&EICRA, int_ctrl);
  ATMEGA328P::EINT0_ExternalInterruptEventCallback  mcp2515_eint0_callback (mcp2515_eint0);

  spi_master.setSpiMode         (MCP2515_SPI_MODE     );
  spi_master.setSpiBitOrder     (MCP2515_SPI_BIT_ORDER);
  spi_master.setSpiPrescaler    (MCP2515_SPI_PRESCALER);

  mcp2515_int_pin.setPullUpMode (hal::interface::PullUpMode::PULL_UP);

  mcp2515_eint0.setTriggerMode  (MCP2515_INT_TRIGGER_MODE);

  int_ctrl.registerInterruptCallback(ATMEGA328P::toIsrNum(ATMEGA328P::InterruptServiceRoutine::EXTERNAL_INT0), &mcp2515_eint0_callback);

  /* DRIVER ***************************************************************************/

  can::MCP2515::MCP2515_IoSpi             mcp2515_io_spi    (spi_master, mcp2515_cs);
  can::MCP2515::MCP2515_Control           mcp2515_control   (mcp2515_io_spi);
  can::MCP2515::MCP2515_CanController     mcp2515_can_ctrl  (mcp2515_control, F_MCP2515_MHz);
  can::MCP2515::MCP2515_CanReceiveBuffer  mcp2515_can_rx_buf(CAN_RX_BUFFER_SIZE);
  can::MCP2515::MCP2515_CanTransmitBuffer mcp2515_can_tx_buf(CAN_TX_BUFFER_SIZE);
  can::MCP2515::MCP2515_Callback          mcp2515_callback;

  can::Can                                can               (mcp2515_can_ctrl, mcp2515_can_tx_buf, mcp2515_can_rx_buf);

  mcp2515_eint0.registerExternalInterruptCallback(&mcp2515_callback);

  /* APPLICATION **********************************************************************/

  uint8_t bitrate = static_cast<uint8_t>(can::MCP2515::interface::CanBitRate::BR_250kBPS);

  can.open();
  can.ioctl(can::IOCTL_SET_BITRATE, static_cast<void *>(&bitrate));

  for(;;) { }

  can.close();

  return 0;
}