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

#include <catch.hpp>

#include <Register.h>

#include <spectre/hal/avr/ATMEGA328P/TIMER0.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

namespace hal
{

namespace ATMEGA328P
{

namespace test
{

/**************************************************************************************/

SCENARIO("A Timer 0 prescaler is configured", "[ATMEGA328P::TIMER0]")
{
  Register<uint8_t> TCNT0 (0b00000000),
                    TCCR0B(0b00000000);

  ATMEGA328P::TIMER0 timer0(TCNT0(), TCCR0B());

  WHEN("'setPrescaler' is called with the argument '0'")
  {
    timer0.setPrescaler(0);

    THEN("TCCR0B bits 2-0 == 0b000")
    {
      REQUIRE(TCCR0B.isBitClr(2));
      REQUIRE(TCCR0B.isBitClr(1));
      REQUIRE(TCCR0B.isBitClr(0));
    }
  }

  WHEN("'setPrescaler' is called with the argument '1'")
  {
    timer0.setPrescaler(1);

    THEN("TCCR0B bits 2-0 == 0b001")
    {
      REQUIRE(TCCR0B.isBitClr(2));
      REQUIRE(TCCR0B.isBitClr(1));
      REQUIRE(TCCR0B.isBitSet(0));
    }
  }

  WHEN("'setPrescaler' is called with the argument '8'")
  {
    timer0.setPrescaler(8);

    THEN("TCCR0B bits 2-0 == 0b010")
    {
      REQUIRE(TCCR0B.isBitClr(2));
      REQUIRE(TCCR0B.isBitSet(1));
      REQUIRE(TCCR0B.isBitClr(0));
    }
  }

  WHEN("'setPrescaler' is called with the argument '64'")
  {
    timer0.setPrescaler(64);

    THEN("TCCR0B bits 2-0 == 0b011")
    {
      REQUIRE(TCCR0B.isBitClr(2));
      REQUIRE(TCCR0B.isBitSet(1));
      REQUIRE(TCCR0B.isBitSet(0));
    }
  }

  WHEN("'setPrescaler' is called with the argument '256'")
  {
    timer0.setPrescaler(256);

    THEN("TCCR0B bits 2-0 == 0b100")
    {
      REQUIRE(TCCR0B.isBitSet(2));
      REQUIRE(TCCR0B.isBitClr(1));
      REQUIRE(TCCR0B.isBitClr(0));
    }
  }

  WHEN("'setPrescaler' is called with the argument '1024'")
  {
    timer0.setPrescaler(1024);

    THEN("TCCR0B bits 2-0 == 0b100")
    {
      REQUIRE(TCCR0B.isBitSet(2));
      REQUIRE(TCCR0B.isBitClr(1));
      REQUIRE(TCCR0B.isBitSet(0));
    }
  }

  WHEN("'setPrescaler' is called with the argument '2' (invalid value)")
  {
    timer0.setPrescaler(2);

    THEN("TCCR0B bits 2-0 == INITIAL = 0b000")
    {
      REQUIRE(TCCR0B.isBitClr(2));
      REQUIRE(TCCR0B.isBitClr(1));
      REQUIRE(TCCR0B.isBitClr(0));
    }
  }
}

/**************************************************************************************/

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

} /* test */

} /* ATMEGA328P */

} /* hal */

} /* spectre */