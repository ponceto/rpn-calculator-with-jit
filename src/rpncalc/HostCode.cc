/*
 * HostCode.cc - Copyright (c) 2023 - Olivier Poncet
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
#include "HostCode.h"

// ---------------------------------------------------------------------------
// rpn::HostCode
// ---------------------------------------------------------------------------

namespace rpn {

HostCode::HostCode()
    : Buffer()
{
    Allocator::allocate(*this);
}

HostCode::~HostCode()
{
    Allocator::deallocate(*this);
}

void HostCode::clear()
{
    Buffer::clear(0xc3);
}

void HostCode::emit_byte(const uint8_t value)
{
    Buffer::write(static_cast<uint8_t>((value >>  0) & 0xff));
}

void HostCode::emit_word(const uint16_t value)
{
    Buffer::write(static_cast<uint8_t>((value >>  0) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >>  8) & 0xff));
}

void HostCode::emit_long(const uint32_t value)
{
    Buffer::write(static_cast<uint8_t>((value >>  0) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >>  8) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 16) & 0xff));
    Buffer::write(static_cast<uint8_t>((value >> 24) & 0xff));
}

void HostCode::emit_quad(const uint64_t value)
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

void HostCode::nop()
{
    emit_byte(0x90);
}

void HostCode::push_rbp()
{
    emit_byte(0x55);
}

void HostCode::mov_rbp_rsp()
{
    emit_byte(0x48);
    emit_byte(0x89);
    emit_byte(0xe5);
}

void HostCode::sub_rsp_imm08(const uint8_t imm08)
{
    emit_byte(0x48);
    emit_byte(0x83);
    emit_byte(0xec);
    emit_byte(imm08);
}

void HostCode::mov_rsp_rbp()
{
    emit_byte(0x48);
    emit_byte(0x89);
    emit_byte(0xec);
}

void HostCode::pop_rbp()
{
    emit_byte(0x5d);
}

void HostCode::ret()
{
    emit_byte(0xc3);
}

void HostCode::mov_rax_imm64(const uint64_t imm64)
{
    emit_byte(0x48);
    emit_byte(0xb8);
    emit_quad(imm64);
}

void HostCode::mov_rdi_imm64(const uint64_t imm64)
{
    emit_byte(0x48);
    emit_byte(0xbf);
    emit_quad(imm64);
}

void HostCode::mov_rsi_imm64(const uint64_t imm64)
{
    emit_byte(0x48);
    emit_byte(0xbe);
    emit_quad(imm64);
}

void HostCode::call_rax()
{
    emit_byte(0xff);
    emit_byte(0xd0);
}

}

// ---------------------------------------------------------------------------
// rpn::HostCode::Allocator
// ---------------------------------------------------------------------------

namespace rpn {

void HostCode::Allocator::allocate(HostCode& hostcode)
{
    auto& _buffer(hostcode._buffer);
    auto& _bufptr(hostcode._bufptr);
    auto& _buflen(hostcode._buflen);

    if(_buflen == 0) {
        const long buflen = ::sysconf(_SC_PAGESIZE);
        if(buflen > 0) {
            _buflen = buflen;
        }
        else {
            throw std::runtime_error("sysconf() has failed");
        }
    }
    if(_buffer == nullptr) {
        const int prot   = (PROT_READ | PROT_WRITE | PROT_EXEC);
        const int flags  = (MAP_PRIVATE | MAP_ANONYMOUS);
        void*     buffer = ::mmap(nullptr, _buflen, prot, flags, -1, 0);
        if(buffer != MAP_FAILED) {
            _buffer = _bufptr = reinterpret_cast<uint8_t*>(buffer);
        }
        else {
            throw std::runtime_error("mmap() has failed");
        }
    }
    hostcode.clear();
}

void HostCode::Allocator::deallocate(HostCode& hostcode)
{
    auto& _buffer(hostcode._buffer);
    auto& _bufptr(hostcode._bufptr);
    auto& _buflen(hostcode._buflen);

    if(_buffer != nullptr) {
        const int rc = ::munmap(_buffer, _buflen);
        if(rc == 0) {
            _buffer = _bufptr = nullptr;
        }
        else {
            throw std::runtime_error("munmap() has failed");
        }
    }
    if(_buflen != 0) {
        _buflen = 0;
    }
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
