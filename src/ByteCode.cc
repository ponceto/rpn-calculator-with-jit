/*
 * ByteCode.cc - Copyright (c) 2023 - Olivier Poncet
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
#include <unistd.h>
#include <sys/mman.h>
#include <algorithm>
#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "ByteCode.h"

// ---------------------------------------------------------------------------
// rpn::ByteCode
// ---------------------------------------------------------------------------

namespace rpn {

ByteCode::ByteCode()
    : Buffer()
{
    Allocator::allocate(*this);
}

ByteCode::~ByteCode()
{
    Allocator::deallocate(*this);
}

void ByteCode::reset()
{
    Buffer::reset(OP_NOP);
}

void ByteCode::emit_byte(const uint8_t value)
{
    Buffer::write(static_cast<uint8_t>((value >>  0) & 0xff));
}

void ByteCode::emit_word(const uint16_t value)
{
    Buffer::write(static_cast<uint8_t>((value >>  0) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >>  8) & 0xff));
}

void ByteCode::emit_long(const uint32_t value)
{
    Buffer::write(static_cast<uint8_t>((value >>  0) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >>  8) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 16) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 24) & 0xff));
}

void ByteCode::emit_quad(const uint64_t value)
{
    Buffer::write(static_cast<uint8_t>((value >>  0) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >>  8) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 16) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 24) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 32) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 40) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 48) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 56) & 0xff));
}

void ByteCode::emit_nop()
{
    emit_byte(OP_NOP);
}

void ByteCode::emit_i64(const int64_t operand)
{
    emit_byte(OP_I64);
    emit_quad(operand);
}

void ByteCode::emit_top()
{
    emit_byte(OP_TOP);
}

void ByteCode::emit_pop()
{
    emit_byte(OP_POP);
}

void ByteCode::emit_clr()
{
    emit_byte(OP_CLR);
}

void ByteCode::emit_dup()
{
    emit_byte(OP_DUP);
}

void ByteCode::emit_xch()
{
    emit_byte(OP_XCH);
}

void ByteCode::emit_sto()
{
    emit_byte(OP_STO);
}

void ByteCode::emit_rcl()
{
    emit_byte(OP_RCL);
}

void ByteCode::emit_abs()
{
    emit_byte(OP_ABS);
}

void ByteCode::emit_neg()
{
    emit_byte(OP_NEG);
}

void ByteCode::emit_add()
{
    emit_byte(OP_ADD);
}

void ByteCode::emit_sub()
{
    emit_byte(OP_SUB);
}

void ByteCode::emit_mul()
{
    emit_byte(OP_MUL);
}

void ByteCode::emit_div()
{
    emit_byte(OP_DIV);
}

void ByteCode::emit_mod()
{
    emit_byte(OP_MOD);
}

void ByteCode::emit_cpl()
{
    emit_byte(OP_CPL);
}

void ByteCode::emit_and()
{
    emit_byte(OP_AND);
}

void ByteCode::emit_ior()
{
    emit_byte(OP_IOR);
}

void ByteCode::emit_xor()
{
    emit_byte(OP_XOR);
}

void ByteCode::emit_shl()
{
    emit_byte(OP_SHL);
}

void ByteCode::emit_shr()
{
    emit_byte(OP_SHR);
}

void ByteCode::emit_inc()
{
    emit_byte(OP_INC);
}

void ByteCode::emit_dec()
{
    emit_byte(OP_DEC);
}

}

// ---------------------------------------------------------------------------
// rpn::ByteCode::Allocator
// ---------------------------------------------------------------------------

namespace rpn {

void ByteCode::Allocator::allocate(ByteCode& bytecode)
{
    auto& _buffer(bytecode._buffer);
    auto& _bufptr(bytecode._bufptr);
    auto& _buflen(bytecode._buflen);

    if(_buflen == 0) {
        _buflen = 1024;
    }
    if(_buffer == nullptr) {
        _buffer = _bufptr = new uint8_t[_buflen];
    }
    bytecode.reset();
}

void ByteCode::Allocator::deallocate(ByteCode& bytecode)
{
    auto& _buffer(bytecode._buffer);
    auto& _bufptr(bytecode._bufptr);
    auto& _buflen(bytecode._buflen);

    if(_buffer != nullptr) {
        _buffer = _bufptr = (delete[] _buffer, nullptr);
    }
    if(_buflen != 0) {
        _buflen = 0;
    }
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
