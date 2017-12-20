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

#include <spectre/hal/avr/ATMEGA328P/I2CMaster.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA328P
{

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

/* TWCR */
#define TWIE_bm     (1<<0)
#define TWEN_bm     (1<<2)
#define TWWC_bm     (1<<3)
#define TWSTO_bm    (1<<4)
#define TWSTA_bm    (1<<5)
#define TWEA_bm     (1<<6)
#define TWINT_bm    (1<<7)

/* TWSR */
#define TWPS0_bm    (1<<0)
#define TWPS1_bm    (1<<1)

/* TWI STATUS DEFINITIONS */

#define TW_START                  0x08
#define TW_REP_START              0x10
#define TW_MT_SLA_ACK             0x18
#define TW_MT_SLA_NACK            0x20
#define TW_MT_DATA_ACK            0x28
#define TW_MT_DATA_NACK           0x30
#define TW_MT_ARB_LOST            0x38
#define TW_MR_ARB_LOST            0x38
#define TW_MR_SLA_ACK             0x40
#define TW_MR_SLA_NACK            0x48
#define TW_MR_DATA_ACK            0x50
#define TW_MR_DATA_NACK           0x58
#define TW_ST_SLA_ACK             0xA8
#define TW_ST_ARB_LOST_SLA_ACK    0xB0
#define TW_ST_DATA_ACK            0xB8
#define TW_ST_DATA_NACK           0xC0
#define TW_ST_LAST_DATA           0xC8
#define TW_SR_SLA_ACK             0x60
#define TW_SR_ARB_LOST_SLA_ACK    0x68
#define TW_SR_GCALL_ACK           0x70
#define TW_SR_ARB_LOST_GCALL_ACK  0x78
#define TW_SR_DATA_ACK            0x80
#define TW_SR_DATA_NACK           0x88
#define TW_SR_GCALL_DATA_ACK      0x90
#define TW_SR_GCALL_DATA_NACK     0x98
#define TW_SR_STOP                0xA0
#define TW_NO_INFO                0xF8
#define TW_BUS_ERROR              0x00

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

I2CMaster::I2CMaster(volatile uint8_t * TWCR, volatile uint8_t * TWDR, volatile uint8_t * TWSR, volatile uint8_t * TWBR)
: _TWCR(TWCR),
  _TWDR(TWDR),
  _TWSR(TWSR),
  _TWBR(TWBR)
{

}

I2CMaster::~I2CMaster()
{

}

/**************************************************************************************
 * PROTECTED MEMBER FUNCTIONS
 **************************************************************************************/

bool I2CMaster::start(uint8_t const address)
{
  /* Transmit START condition */
  *_TWCR = TWINT_bm | TWSTA_bm | TWEN_bm;

  /* Wait for end of transmission */
  while( !(*_TWCR & TWINT_bm) );

  /* Check if the start condition was successfully transmitted */
  uint8_t twst = *_TWSR & 0xF8;
  if((twst != TW_START) && (twst != TW_REP_START)) return false;

  /* Load slave address into data register */
  *_TWDR = address;

  /* Start transmission of address */
  *_TWCR = TWINT_bm | TWEN_bm;

  /* Wait for end of transmission */
  while( !(*_TWCR & TWINT_bm) );

  /* Check if the device has acknowledged the READ / WRITE mode */
  twst = *_TWSR & 0xF8;
  if  ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return false;
  else                                                      return true;
}

bool I2CMaster::transmitByte(uint8_t const data)
{
  /* Load data into data register */
  *_TWDR = data;

  /* Start transmission of data */
  *_TWCR = TWINT_bm | TWEN_bm;

  /* Wait for end of transmission */
  while( !(*_TWCR & TWINT_bm) );

  if  ((*_TWSR & 0xF8) != TW_MT_DATA_ACK ) return false;
  else                                     return true;
}

void I2CMaster::receiveByteAndSendACK(uint8_t * data)
{
  /* Start TWI module and acknowledge data after reception */
  *_TWCR = TWINT_bm | TWEN_bm | TWEA_bm;

  /* Wait for end of transmission */
  while( !(*_TWCR & TWINT_bm) );

  /* Read received data from TWDR */
  *data = *_TWDR;
}

void I2CMaster::receiveByteAndSendNACK(uint8_t * data)
{
  /* Start receiving without acknowledging reception */
  *_TWCR = TWINT_bm | TWEN_bm;

  /* Wait for end of transmission */
  while( !(*_TWCR & TWINT_bm) );

  /* Read received data from TWDR */
  *data = *_TWDR;
}

void I2CMaster::stop()
{
  /* Transmit STOP condition */
  *_TWCR = TWINT_bm | TWEN_bm | TWSTO_bm;
}

void I2CMaster::setTWIPrescaler(uint32_t const prescaler)
{
  *_TWSR &= ~(TWPS1_bm | TWPS0_bm);

  switch(prescaler)
  {
  case 1  : *_TWSR |= 0;                    break;
  case 4  : *_TWSR |= TWPS0_bm;             break;
  case 16 : *_TWSR |= TWPS1_bm;             break;
  case 64 : *_TWSR |= TWPS1_bm | TWPS0_bm;  break;
  default: break;
  }
}

void I2CMaster::setTWBR(uint32_t const i2c_speed_Hz, uint32_t const i2c_prescaler)
{
  uint32_t const twbr_val = (((static_cast<uint32_t>(F_CPU) / i2c_speed_Hz) / i2c_prescaler) - 16) / 2;

  *_TWBR = static_cast<uint8_t>(twbr_val);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* ATMEGA328P */

} /* hal */

} /* spectre */
