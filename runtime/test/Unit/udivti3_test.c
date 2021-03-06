//===-- udivti3_test.c - Test __udivti3 -----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file tests __udivti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#if __x86_64

#include "int_lib.h"
#include <stdio.h>

// Returns: a / b

tu_int __udivti3(tu_int a, tu_int b);

int test__udivti3(tu_int a, tu_int b, tu_int expected_q)
{
    tu_int q = __udivti3(a, b);
    if (q != expected_q)
    {
        utwords at;
        at.all = a;
        utwords bt;
        bt.all = b;
        utwords qt;
        qt.all = q;
        utwords expected_qt;
        expected_qt.all = expected_q;
        printf("error in __udivti3: 0x%llX%.16llX / 0x%llX%.16llX = "
               "0x%llX%.16llX, expected 0x%llX%.16llX\n",
               at.s.high, at.s.low, bt.s.high, bt.s.low, qt.s.high, qt.s.low,
               expected_qt.s.high, expected_qt.s.low);
    }
    return q != expected_q;
}

#endif

int main()
{
#if __x86_64
    if (test__udivti3(0, 1, 0))
        return 1;
    if (test__udivti3(2, 1, 2))
        return 1;
    if (test__udivti3(make_tu(0x8000000000000000uLL, 0), 1,
                      make_tu(0x8000000000000000uLL, 0)))
        return 1;
    if (test__udivti3(make_tu(0x8000000000000000uLL, 0), 2,
                      make_tu(0x4000000000000000uLL, 0)))
        return 1;
    if (test__udivti3(make_tu(0xFFFFFFFFFFFFFFFFuLL, 0xFFFFFFFFFFFFFFFFuLL), 2,
                      make_tu(0x7FFFFFFFFFFFFFFFuLL, 0xFFFFFFFFFFFFFFFFuLL)))
        return 1;

#endif
    return 0;
}
