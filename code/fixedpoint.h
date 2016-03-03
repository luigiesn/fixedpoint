/*
 * Fixed point arithimetics - Optimized for 8 bits uP
 * Copyright (C) 2016 - Luigi E. Sica Nery
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FIXEDPOINT_H_
#define	_FIXEDPOINT_H_

#define FP_TOTAL_LENGTH 16
#define FP_INTEGER_LENGTH 0
#define FP_SIGNED 1

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed long int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

#if FP_SIGNED == 1
#if FP_TOTAL_LENGTH == 8
typedef int8_t fixed;
typedef int16_t lfixed;
#define FIXED_MAX  ((fixed)0xff)
#define FIXED_MIN  ((fixed)0x80)

#elif FP_TOTAL_LENGTH == 16
typedef int16_t fixed;
typedef int32_t lfixed;
#define FIXED_MAX  ((fixed)0xffff)
#define FIXED_MIN  ((fixed)0x8000)
#endif

#elif FP_SIGNED == 0
#if FP_TOTAL_LENGTH == 8
typedef uint8_t fixed;
typedef uint16_t lfixed;
#define FIXED_MAX  0xff
#define FIXED_MIN  0x00

#elif FP_TOTAL_LENGTH == 16
typedef uint16_t fixed;
typedef uint32_t lfixed;
#define FIXED_MAX  0xffff
#define FIXED_MIN  0x0000
#endif

#endif

#define FP_FRACTIONAL_LENGTH (FP_TOTAL_LENGTH - FP_INTEGER_LENGTH - FP_SIGNED)

#if (FP_SIGNED == 1)
#if FP_FRACTIONAL_LENGTH > (FP_TOTAL_LENGTH-1)
#error FP_FRACTIONAL_LENGTH must be less to FP_TOTAL_LENGTH if fixed point is signed
#endif /* FP_FRACTIONAL_LENGTH >= FP_TOTAL_LENGTH */
#elif (FP_SIGNED == 0)
#if FP_FRACTIONAL_LENGTH > (FP_TOTAL_LENGTH)
#error FP_FRACTIONAL_LENGTH must be less or equal to FP_TOTAL_LENGTH if fixed point is unsigned
#endif /* FP_FRACTIONAL_LENGTH >= FP_TOTAL_LENGTH */
#else
#error FP_SIGNED must be 1 or 0
#endif /* FP_SIGNED */


#define fixed_toint(fxp) (((fixed)fxp) << FP_FRACTIONAL_LENGTH)
#define fixed_fromint(intgr) (intgr >> FP_FRACTIONAL_LENGTH)

#define fixed_abs(fxp) (fxp < 0 ? -fxp : fxp)
#define fixed_constround(c) ((fixed)((c) * (((lfixed)0b1 << FP_FRACTIONAL_LENGTH) + ((c) >= 0 ? 0.5 : -0.5))))

inline static fixed fixed_sum(fixed a, fixed b) {
    lfixed sum = (lfixed) a + (lfixed) b;

    /* Check for overflow and saturate if necessary */
    return sum > FIXED_MAX ? FIXED_MAX : (fixed) sum;
}

inline static fixed fixed_sub(fixed a, fixed b) {
    lfixed sub = (lfixed) a - (lfixed) b;

    /* Check for underflow and saturate if necessary */
    return sub < FIXED_MIN ? FIXED_MIN : (fixed) sub;
}

inline static fixed fixed_mult(fixed a, fixed b) {
    return (fixed) (((lfixed) a * (lfixed) b) >> FP_FRACTIONAL_LENGTH);
}

inline static fixed fixed_div(fixed a, fixed b) {
    return (fixed) (((lfixed) a << FP_FRACTIONAL_LENGTH) / (lfixed) b);
}

#endif	/* _FIXEDPOINT_H_ */

