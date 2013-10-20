// Copyright (c) 2013 Shaun Crampton.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdint.h>

static uint16_t lfsr_state;
uint8_t rand_byte()
{
    if (!lfsr_state)
    {
        // Can't allow LFSR to be all 0, it won't recover.
        lfsr_state = 0xDEAD;
    }
    for (uint8_t i = 8; i>0; i--)
    {
        uint8_t new_bit = 0;
        if (lfsr_state & (1 << 15)) {
            new_bit = !new_bit;
        }
        if (lfsr_state & (1 << 13)) {
            new_bit = !new_bit;
        }
        if (lfsr_state & (1 << 12)) {
            new_bit = !new_bit;
        }
        if (lfsr_state & (1 << 10)) {
            new_bit = !new_bit;
        }
        lfsr_state <<= 1;
        lfsr_state |= new_bit;
    }
    return (uint8_t)lfsr_state;
}

void mix_rand(uint8_t x)
{
    if (x & 1) {
        uint8_t tmp = (lfsr_state & (1 << 15)) >> 15;
        uint8_t tmp2 = (lfsr_state & (1 << 3)) >> 3;
        if (tmp != tmp2)
        {
            lfsr_state ^= 1 << 3;
            lfsr_state ^= 1 << 15;
        }
    }
}
