/*
Arduino_MAX17043.h - MAX17043 class
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

#pragma once
#include <stdint.h>

enum MAX17043_regs {
  VCELL = 0x02,		// R/O
  SOC,			// R/O
  MODE,			// W/O
  VERSION,		// R/O
  CONFIG = 0x0c,	// R/W
  COMMAND = 0xfe,	// W/O
};

class Arduino_MAX17043 {
private:
  uint8_t _addr;
  bool _error;

  uint16_t read_reg(uint8_t reg);
  void write_reg(uint8_t reg, uint16_t val);

public:
  Arduino_MAX17043() :
    _addr(0x36)
  {}

  bool error(void) const { return _error; }

  uint16_t raw_Vcell(void) { return read_reg(VCELL); }
  uint16_t raw_SoC(void) { return read_reg(SOC); }

  // Cell voltage in volts
  float Vcell(void) {
    return (float)(read_reg(VCELL) >> 4) * 0.00125;
  }

  // State of charge in percent
  float SoC(void) {
    return (float)read_reg(SOC) * 0.00390625;
  }

  uint16_t version(void) {
    return read_reg(VERSION);
  }

  void reset(void) {
    write_reg(COMMAND, 0x5400);
  }

  void quickStart(void) {
    write_reg(MODE, 0x4000);
  }

};
