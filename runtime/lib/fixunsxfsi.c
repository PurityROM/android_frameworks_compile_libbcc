/* ===-- fixunsxfsi.c - Implement __fixunsxfsi -----------------------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is distributed under the University of Illinois Open Source
 * License. See LICENSE.TXT for details.
 *
 * ===----------------------------------------------------------------------===
 *
 * This file implements __fixunsxfsi for the compiler_rt library.
 *
 * ===----------------------------------------------------------------------===
 */

#if !_ARCH_PPC

#include "int_lib.h"

/* Returns: convert a to a unsigned int, rounding toward zero.
 *          Negative values all become zero.
 */

/* Assumption: long double is an intel 80 bit floating point type padded with 6 bytes
 *             su_int is a 32 bit integral type
 *             value in long double is representable in su_int or is negative 
 *                 (no range checking performed)
 */

/* gggg gggg gggg gggg gggg gggg gggg gggg | gggg gggg gggg gggg seee eeee eeee eeee |
 * 1mmm mmmm mmmm mmmm mmmm mmmm mmmm mmmm | mmmm mmmm mmmm mmmm mmmm mmmm mmmm mmmm
 */

su_int
__fixunsxfsi(long double a)
{
    long_double_bits fb;
    fb.f = a;
    int e = (fb.u.high.s.low & 0x00007FFF) - 16383;
    if (e < 0 || (fb.u.high.s.low & 0x00008000))
        return 0;
    return fb.u.low.s.high >> (31 - e);
}

#endif /* !_ARCH_PPC */
