/*
 * HostCode.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_HostCode_h__
#define __RPN_HostCode_h__

#include "Buffer.h"

// ---------------------------------------------------------------------------
// rpn::HostCode
// ---------------------------------------------------------------------------

namespace rpn {

class HostCode final
    : public Buffer
{
public: // public interface
    HostCode();

    HostCode(const HostCode&) = delete;

    HostCode& operator=(const HostCode&) = delete;

    virtual ~HostCode();

    void reset();

    void emit_byte(const uint8_t value);

    void emit_word(const uint16_t value);

    void emit_long(const uint32_t value);

    void emit_quad(const uint64_t value);

    void nop();

    void push_rbp();

    void mov_rbp_rsp();

    void sub_rsp_imm08(const uint8_t imm08);

    void mov_rsp_rbp();

    void pop_rbp();

    void ret();

    void mov_rax_imm64(const uint64_t imm64);

    void mov_rdi_imm64(const uint64_t imm64);

    void mov_rsi_imm64(const uint64_t imm64);

    void call_rax();

private: // private interface
    void allocate();

    void deallocate();
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_HostCode_h__ */
