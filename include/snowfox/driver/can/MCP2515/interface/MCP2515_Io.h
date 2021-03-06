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

#ifndef INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_IO_H_
#define INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_IO_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace snowfox::driver::can::MCP2515::interface
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  RXF0SIDH = 0x00,
  RXF0SIDL = 0x01,
  RXF0EID8 = 0x02,
  RXF0EID0 = 0x03,
  RXF1SIDH = 0x04,
  RXF1SIDL = 0x05,
  RXF1EID8 = 0x06,
  RXF1EID0 = 0x07,
  RXF2SIDH = 0x08,
  RXF2SIDL = 0x09,
  RXF2EID8 = 0x0A,
  RXF2EID0 = 0x0B,
  CANSTAT  = 0x0E,
  CANCTRL  = 0x0F,
  RXF3SIDH = 0x10,
  RXF3SIDL = 0x11,
  RXF3EID8 = 0x12,
  RXF3EID0 = 0x13,
  RXF4SIDH = 0x14,
  RXF4SIDL = 0x15,
  RXF4EID8 = 0x16,
  RXF4EID0 = 0x17,
  RXF5SIDH = 0x18,
  RXF5SIDL = 0x19,
  RXF5EID8 = 0x1A,
  RXF5EID0 = 0x1B,
  TEC      = 0x1C,
  REC      = 0x1D,
  RXM0SIDH = 0x20,
  RXM0SIDL = 0x21,
  RXM0EID8 = 0x22,
  RXM0EID0 = 0x23,
  RXM1SIDH = 0x24,
  RXM1SIDL = 0x25,
  RXM1EID8 = 0x26,
  RXM1EID0 = 0x27,
  CNF3     = 0x28,
  CNF2     = 0x29,
  CNF1     = 0x2A,
  CANINTE  = 0x2B,
  CANINTF  = 0x2C,
  EFLG     = 0x2D,
  TXB0CTRL = 0x30,
  TXB0SIDH = 0x31,
  TXB0SIDL = 0x32,
  TXB0EID8 = 0x33,
  TXB0EID0 = 0x34,
  TXB0DLC  = 0x35,
  TXB0DATA = 0x36,
  TXB1CTRL = 0x40,
  TXB1SIDH = 0x41,
  TXB1SIDL = 0x42,
  TXB1EID8 = 0x43,
  TXB1EID0 = 0x44,
  TXB1DLC  = 0x45,
  TXB1DATA = 0x46,
  TXB2CTRL = 0x50,
  TXB2SIDH = 0x51,
  TXB2SIDL = 0x52,
  TXB2EID8 = 0x53,
  TXB2EID0 = 0x54,
  TXB2DLC  = 0x55,
  TXB2DATA = 0x56,
  RXB0CTRL = 0x60,
  RXB0SIDH = 0x61,
  RXB0SIDL = 0x62,
  RXB0EID8 = 0x63,
  RXB0EID0 = 0x64,
  RXB0DLC  = 0x65,
  RXB0DATA = 0x66,
  RXB1CTRL = 0x70,
  RXB1SIDH = 0x71,
  RXB1SIDL = 0x72,
  RXB1EID8 = 0x73,
  RXB1EID0 = 0x74,
  RXB1DLC  = 0x75,
  RXB1DATA = 0x76
};

enum class Instruction : uint8_t
{
  WRITE       = 0x02,
  READ        = 0x03,
  BITMOD      = 0x05,
  LOAD_TX0    = 0x40,
  LOAD_TX1    = 0x42,
  LOAD_TX2    = 0x44,
  RTS_TX0     = 0x81,
  RTS_TX1     = 0x82,
  RTS_TX2     = 0x84,
  RTS_ALL     = 0x87,
  READ_RX0    = 0x90,
  READ_RX1    = 0x94,
  READ_STATUS = 0xA0,
  RX_STATUS   = 0xB0,
  RESET       = 0xC0
};

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class MCP2515_Io
{

public:

           MCP2515_Io() { }
  virtual ~MCP2515_Io() { }


  virtual void    reset   () = 0;
  virtual uint8_t status  () = 0;


  static uint8_t constexpr TX_BUF_MAX_SIZE = 5 + 8;
  static uint8_t constexpr RX_BUF_MAX_SIZE = 5 + 8;


  virtual void    loadTx0 (uint8_t const * tx_buf) = 0; /* tx_buf = {SIDH, SIDL, EID8, EID0, DLC, DATA[0-8 Byte] } */
  virtual void    loadTx1 (uint8_t const * tx_buf) = 0;
  virtual void    loadTx2 (uint8_t const * tx_buf) = 0;
  virtual void    readRx0 (uint8_t       * rx_buf) = 0; /* rx_buf = {SIDH, SIDL, EID8, EID0, DLC, DATA[0-8 Byte] } */
  virtual void    readRx1 (uint8_t       * rx_buf) = 0;

  virtual void    requestToTransmitTx0() = 0;
  virtual void    requestToTransmitTx1() = 0;
  virtual void    requestToTransmitTx2() = 0;

  virtual void    readRegister  (Register const reg, uint8_t       * data                    ) = 0;
  virtual void    writeRegister (Register const reg, uint8_t const   data                    ) = 0;
  virtual void    modifyRegister(Register const reg, uint8_t const   data, uint8_t const mask) = 0;

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* snowfox::driver::can::MCP2515::interface */

#endif /* INCLUDE_SNOWFOX_DRIVER_CAN_MCP2515_INTERFACE_MCP2515_IO_H_ */
