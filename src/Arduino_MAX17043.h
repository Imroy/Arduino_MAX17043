/*
Arduino_MAX17043.h - MAX17043 class
Copyright (C) 2015-2017 Ian Tester

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

class Arduino_MAX17043 {
private:
  // Note: actual register values have to be doubled before sending
  enum class Register : uint8_t {
    VCELL = 1,		// R/O
    SOC,		// R/O
    MODE,		// W/O
    VERSION,		// R/O
    __REG5,
    CONFIG,		// R/W

    COMMAND = 127,	// W/O
  };

  uint8_t _addr;
  bool _error;

  uint16_t read_reg(Register reg);
  void write_reg(Register reg, uint16_t val);

public:
  Arduino_MAX17043() :
    _addr(0x36)
  {}

  bool error(void) const { return _error; }

  uint16_t raw_Vcell(void) { return read_reg(Register::VCELL); }
  uint16_t raw_SoC(void) { return read_reg(Register::SOC); }

  // Cell voltage in volts
  float Vcell(void) {
    return static_cast<float>(read_reg(Register::VCELL) >> 4) * 0.00125;
  }

  // State of charge in percent
  float SoC(void) {
    return static_cast<float>(read_reg(Register::SOC)) * 0.00390625;
  }

  uint16_t version(void) {
    return read_reg(Register::VERSION);
  }

  void reset(void) {
    write_reg(Register::COMMAND, 0x5400);
  }

  void quickStart(void) {
    write_reg(Register::MODE, 0x4000);
  }

};
