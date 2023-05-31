/*
 * State.cc - Copyright (c) 2023 - Olivier Poncet
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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>
#include <algorithm>
#include <chrono>
#include <thread>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "State.h"

// ---------------------------------------------------------------------------
// <anonymous>::Stack
// ---------------------------------------------------------------------------

namespace {

struct Stack
{
    static int64_t push(rpn::Operands& operands, const int64_t operand)
    {
        operands.stack.push(operand);

        return operand;
    }

    static int64_t top(rpn::Operands& operands)
    {
        int64_t operand = 0;

        if(operands.stack.empty()) {
            throw std::runtime_error("stack underflow");
        }
        else {
            operand = operands.stack.top();
        }
        return operand;
    }

    static int64_t pop(rpn::Operands& operands)
    {
        int64_t operand = 0;

        if(operands.stack.empty()) {
            throw std::runtime_error("stack underflow");
        }
        else {
            operand = operands.stack.top();
            operands.stack.pop();
        }
        return operand;
    }

    static int64_t clear(rpn::Operands& operands)
    {
        int64_t operand = 0;

        while(operands.stack.size() > 0) {
            operand = operands.stack.top();
            operands.stack.pop();
        }
        return operand;
    }
};

}

// ---------------------------------------------------------------------------
// <anonymous>::Array
// ---------------------------------------------------------------------------

namespace {

struct Array
{
    static int64_t set(rpn::Operands& operands, const int64_t index, const int64_t value)
    {
        return operands.array.at(index) = value;
    }

    static int64_t get(rpn::Operands& operands, const int64_t index)
    {
        switch(index) {
            case rpn::Registers::R30:
                {
                    const auto prev_value    = operands.array.at(index);
                    const auto next_value    = prev_value * 1103515245 + 12345;
                    operands.array.at(index) = next_value;
                }
                break;
            case rpn::Registers::R31:
                {
                    const auto now              = std::chrono::system_clock::now();
                    const auto time_since_epoch = now.time_since_epoch();
                    const auto msec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch).count();
                    operands.array.at(index)    = msec_since_epoch;
                }
                break;
            default:
                break;
        }
        return operands.array.at(index);
    }
};

}

// ---------------------------------------------------------------------------
// rpn::Operands
// ---------------------------------------------------------------------------

namespace rpn {

}

// ---------------------------------------------------------------------------
// rpn::Operators
// ---------------------------------------------------------------------------

namespace rpn {

int64_t Operators::op_nop(Operands& operands)
{
    return 0;
}

int64_t Operators::op_i64(Operands& operands, const int64_t operand)
{
    return Stack::push(operands, operand);
}

int64_t Operators::op_top(Operands& operands)
{
    return Stack::top(operands);
}

int64_t Operators::op_pop(Operands& operands)
{
    return Stack::pop(operands);
}

int64_t Operators::op_clr(Operands& operands)
{
    return Stack::clear(operands);
}

int64_t Operators::op_dup(Operands& operands)
{
    const int64_t res = Stack::pop(operands);

    static_cast<void>(Stack::push(operands, res));
    static_cast<void>(Stack::push(operands, res));

    return res;
}

int64_t Operators::op_xch(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    int64_t       res = 0;

    res = Stack::push(operands, op2);
    res = Stack::push(operands, op1);

    return res;
}

int64_t Operators::op_sto(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Array::set(operands, op2, op1);

    return res;
}

int64_t Operators::op_rcl(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Array::get(operands, op2);
    const int64_t res = Stack::push(operands, op1);

    return res;
}

int64_t Operators::op_abs(Operands& operands)
{
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 < 0 ? -op1 : op1));

    return res;
}

int64_t Operators::op_neg(Operands& operands)
{
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (-op1));

    return res;
}

int64_t Operators::op_add(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 + op2));

    return res;
}

int64_t Operators::op_sub(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 - op2));

    return res;
}

int64_t Operators::op_mul(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 * op2));

    return res;
}

int64_t Operators::op_div(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 / op2));

    return res;
}

int64_t Operators::op_mod(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 % op2));

    return res;
}

int64_t Operators::op_cpl(Operands& operands)
{
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (~op1));

    return res;
}

int64_t Operators::op_and(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 & op2));

    return res;
}

int64_t Operators::op_ior(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 | op2));

    return res;
}

int64_t Operators::op_xor(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 ^ op2));

    return res;
}

int64_t Operators::op_shl(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 << op2));

    return res;
}

int64_t Operators::op_shr(Operands& operands)
{
    const int64_t op2 = Stack::pop(operands);
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 >> op2));

    return res;
}

int64_t Operators::op_inc(Operands& operands)
{
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 + 1));

    return res;
}

int64_t Operators::op_dec(Operands& operands)
{
    const int64_t op1 = Stack::pop(operands);
    const int64_t res = Stack::push(operands, (op1 - 1));

    return res;
}

int64_t Operators::op_hlt(Operands& operands)
{
    const int64_t op1 = Stack::pop(operands);

    std::this_thread::sleep_for(std::chrono::milliseconds(op1));

    return op1;
}

}

// ---------------------------------------------------------------------------
// rpn::Registers
// ---------------------------------------------------------------------------

namespace rpn {

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
