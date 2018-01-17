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
 * NAMESPACE
 **************************************************************************************/

namespace spectre
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

template <typename T>
Register<T>::Register(T const initial_reg_val)
: _reg_val(initial_reg_val)
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

template <typename T>
T * Register<T>::operator()()
{
  return &_reg_val;
}

template <typename T>
bool Register<T>::operator == (T const val) const
{
  return (_reg_val == val);
}

template <typename T>
void Register<T>::setBit(uint32_t const bit_pos)
{
  _reg_val |= (1<<bit_pos);
}

template <typename T>
void Register<T>::clrBit(uint32_t const bit_pos)
{
  _reg_val &= ~(1<<bit_pos);
}

template <typename T>
bool Register<T>::isBitSet(uint32_t const bit_pos)
{
  T const bit_mask = (1<<bit_pos);
  bool const is_bit_set = (_reg_val & bit_mask) == bit_mask;
  return is_bit_set;
}

template <typename T>
bool Register<T>::isBitClr(uint32_t const bit_pos)
{
  T const bit_mask = (1<<bit_pos);
  bool const is_bit_clr = (_reg_val & bit_mask) == 0;
  return is_bit_clr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* test */