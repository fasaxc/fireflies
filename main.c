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

#define STRINGIFY(s) XSTRINGIFY(s)
#define XSTRINGIFY(s) #s

int main(void) {
    /* PWM PINS as outputs.., */
    DDRA |= _BV(DD7) | _BV(DD6) | _BV(DD5);
    DDRB |= _BV(DD2);
    PORTA = 0;

    /* Timer 0, on, fast PWM with both PWM outputs. */
    TCCR0A |= _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |= _BV(CS01); /* CLK/8 */

    /* Timer 1, on, 8-bit, fast PWM with both PWM outputs. */
    TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
    TCCR1B |= _BV(CS11) | _BV(WGM12); /* CLK/8 */

    while (1) {

    }
}
