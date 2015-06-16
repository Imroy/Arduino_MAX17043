/*
Arduino_MAX17043.cpp - MAX17043 class
Copyright (C) 2015 Ian Tester

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include "Arduino_MAX17043.h"

uint16_t Arduino_MAX17043::read_reg(MAX17043_regs reg) {
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.endTransmission();

  _error = false;
  if (Wire.requestFrom(_addr, (size_t)2) != 2) {
    _error = true;
    return 0;
  }

  int high = Wire.read();
  if (high == -1) {
    _error = true;
    return 0;
  }

  int low = Wire.read();
  if (low == -1) {
    _error = true;
    return 0;
  }

  return (high << 8) | low;
}

void Arduino_MAX17043::write_reg(MAX17043_regs reg, uint16_t val) {
  _error = false;
  Wire.beginTransmission(_addr);
  if (Wire.write(reg) == 0) {
    _error = true;
    return;
  }
  if (Wire.write(val >> 8) == 0) {
    _error = true;
    return;
  }
  if (Wire.write(val & 0xff) == 0) {
    _error = true;
    return;
  }
  Wire.endTransmission();
}
