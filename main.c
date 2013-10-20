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

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "rand.h"

#define STRINGIFY(s) XSTRINGIFY(s)
#define XSTRINGIFY(s) #s

#define NUM_SAMPLES 150
const uint8_t PATTERN[NUM_SAMPLES] PROGMEM =
{
      0,
     64, 128, 200, 255, 255, 255, 255, 200, 128,  40,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
     64, 170, 200, 220, 235, 245, 250, 255, 255, 255,
    254, 253, 252, 251, 250, 249, 248, 247, 246, 245,
    244, 243, 242, 241, 240, 239, 238, 237, 236, 235,

    234, 233, 232, 231, 230, 229, 228, 227, 226, 225,
    223, 223, 222, 221, 220, 219, 218, 217, 216, 215,
    214, 213, 212, 211, 210, 209, 208, 207, 206, 205,
    204, 203, 202, 201, 200, 199, 198, 197, 196, 195,

    194, 193, 192, 191, 190, 185, 180, 175, 170, 165,
    160, 155, 150, 145, 140, 135, 130, 125, 120, 115,
    110, 105, 100,  95,  90,  85,  80,  75,  70,  65,
     60,  55,  50,  45,  40,  35,  30,  25,  20,  15,
     20,  10,   5,   0,   0,   0,   0,   0,   0
};


int main(void)
{
  uint16_t start_delay[4];
  uint8_t position[4] = { 0, 0, 0, 0 };
  uint8_t i;

  /* PWM PINS as outputs.., */
  DDRA |= _BV(DD7) | _BV(DD6) | _BV(DD5);
  DDRB |= _BV(DD2);
  PORTA = 0;

  /* Timer 0, on, PWM with both PWM outputs. */
  TCCR0A |= _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);
  TCCR0B |= _BV(CS01); /* CLK/8 */

  /* Timer 1, on, 8-bit, PWM with both PWM outputs. */
  TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
  TCCR1B |= _BV(CS11); /* CLK/8 */

  for (i = 0; i < 4; i++)
  {
    start_delay[i] = rand_byte();
  }

  while (1)
  {
    OCR0A = pgm_read_byte(&(PATTERN[position[0]]));
    OCR0B = pgm_read_byte(&(PATTERN[position[1]]));
    OCR1A = pgm_read_byte(&(PATTERN[position[2]]));
    OCR1B = pgm_read_byte(&(PATTERN[position[3]]));

    for (i = 0; i < 4; i++) {
      if (start_delay[i] > 0) {
        start_delay[i]--;
      } else if (position[i] < NUM_SAMPLES-1) {
        position[i]++;
      } else {
        position[i] = 0;
        start_delay[i] = rand_byte();
        start_delay[i] += rand_byte();
      }
    }
    _delay_ms(25);
  }
}
