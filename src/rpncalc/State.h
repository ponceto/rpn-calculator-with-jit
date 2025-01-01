/*
 * State.h - Copyright (c) 2023-2025 - Olivier Poncet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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
#ifndef __RPN_State_h__
#define __RPN_State_h__

#include <stack>
#include <array>

// ---------------------------------------------------------------------------
// rpn::Operands
// ---------------------------------------------------------------------------

namespace rpn {

struct Operands
{
    std::stack<int64_t>     stack;
    std::array<int64_t, 32> array;
};

}

// ---------------------------------------------------------------------------
// rpn::Operators
// ---------------------------------------------------------------------------

namespace rpn {

struct Operators
{
    static int64_t op_nop(Operands& operands);

    static int64_t op_i64(Operands& operands, const int64_t operand);

    static int64_t op_top(Operands& operands);

    static int64_t op_pop(Operands& operands);

    static int64_t op_clr(Operands& operands);

    static int64_t op_dup(Operands& operands);

    static int64_t op_xch(Operands& operands);

    static int64_t op_sto(Operands& operands);

    static int64_t op_rcl(Operands& operands);

    static int64_t op_abs(Operands& operands);

    static int64_t op_neg(Operands& operands);

    static int64_t op_add(Operands& operands);

    static int64_t op_sub(Operands& operands);

    static int64_t op_mul(Operands& operands);

    static int64_t op_div(Operands& operands);

    static int64_t op_mod(Operands& operands);

    static int64_t op_cpl(Operands& operands);

    static int64_t op_and(Operands& operands);

    static int64_t op_ior(Operands& operands);

    static int64_t op_xor(Operands& operands);

    static int64_t op_shl(Operands& operands);

    static int64_t op_shr(Operands& operands);

    static int64_t op_inc(Operands& operands);

    static int64_t op_dec(Operands& operands);

    static int64_t op_hlt(Operands& operands);
};

}

// ---------------------------------------------------------------------------
// rpn::Registers
// ---------------------------------------------------------------------------

namespace rpn {

struct Registers
{
    static constexpr int R00 =  0;
    static constexpr int R01 =  1;
    static constexpr int R02 =  2;
    static constexpr int R03 =  3;
    static constexpr int R04 =  4;
    static constexpr int R05 =  5;
    static constexpr int R06 =  6;
    static constexpr int R07 =  7;
    static constexpr int R08 =  8;
    static constexpr int R09 =  9;
    static constexpr int R10 = 10;
    static constexpr int R11 = 11;
    static constexpr int R12 = 12;
    static constexpr int R13 = 13;
    static constexpr int R14 = 14;
    static constexpr int R15 = 15;
    static constexpr int R16 = 16;
    static constexpr int R17 = 17;
    static constexpr int R18 = 18;
    static constexpr int R19 = 19;
    static constexpr int R20 = 20;
    static constexpr int R21 = 21;
    static constexpr int R22 = 22;
    static constexpr int R23 = 23;
    static constexpr int R24 = 24;
    static constexpr int R25 = 25;
    static constexpr int R26 = 26;
    static constexpr int R27 = 27;
    static constexpr int R28 = 28;
    static constexpr int R29 = 29;
    static constexpr int R30 = 30;
    static constexpr int R31 = 31;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_State_h__ */
