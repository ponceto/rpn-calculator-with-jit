/*
 * ByteCode.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_ByteCode_h__
#define __RPN_ByteCode_h__

#include "Buffer.h"

// ---------------------------------------------------------------------------
// rpn::ByteCode
// ---------------------------------------------------------------------------

namespace rpn {

class ByteCode final
    : public Buffer
{
public: // public interface
    ByteCode();

    ByteCode(ByteCode&&) = delete;

    ByteCode& operator=(ByteCode&&) = delete;

    ByteCode(const ByteCode&) = delete;

    ByteCode& operator=(const ByteCode&) = delete;

    virtual ~ByteCode();

    void reset();

    void emit_byte(const uint8_t value);

    void emit_word(const uint16_t value);

    void emit_long(const uint32_t value);

    void emit_quad(const uint64_t value);

    void emit_nop();

    void emit_i64(const int64_t operand);

    void emit_top();

    void emit_pop();

    void emit_clr();

    void emit_dup();

    void emit_xch();

    void emit_sto();

    void emit_rcl();

    void emit_abs();

    void emit_neg();

    void emit_add();

    void emit_sub();

    void emit_mul();

    void emit_div();

    void emit_mod();

    void emit_and();

    void emit_ior();

    void emit_xor();

    void emit_shl();

    void emit_shr();

    void emit_cpl();

    void emit_inc();

    void emit_dec();

public: // public static data
    static constexpr uint8_t OP_NOP = 0x00;
    static constexpr uint8_t OP_I64 = 0x01;
    static constexpr uint8_t OP_TOP = 0x02;
    static constexpr uint8_t OP_POP = 0x03;
    static constexpr uint8_t OP_CLR = 0x04;
    static constexpr uint8_t OP_DUP = 0x05;
    static constexpr uint8_t OP_XCH = 0x06;
    static constexpr uint8_t OP_STO = 0x07;
    static constexpr uint8_t OP_RCL = 0x08;
    static constexpr uint8_t OP_ABS = 0x09;
    static constexpr uint8_t OP_NEG = 0x0a;
    static constexpr uint8_t OP_ADD = 0x0b;
    static constexpr uint8_t OP_SUB = 0x0c;
    static constexpr uint8_t OP_MUL = 0x0d;
    static constexpr uint8_t OP_DIV = 0x0e;
    static constexpr uint8_t OP_MOD = 0x0f;
    static constexpr uint8_t OP_CPL = 0x10;
    static constexpr uint8_t OP_AND = 0x11;
    static constexpr uint8_t OP_IOR = 0x12;
    static constexpr uint8_t OP_XOR = 0x13;
    static constexpr uint8_t OP_SHL = 0x14;
    static constexpr uint8_t OP_SHR = 0x15;
    static constexpr uint8_t OP_INC = 0x16;
    static constexpr uint8_t OP_DEC = 0x17;

private: // private interface
    struct Allocator
    {
        static void allocate(ByteCode&);

        static void deallocate(ByteCode&);
    };
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_ByteCode_h__ */
