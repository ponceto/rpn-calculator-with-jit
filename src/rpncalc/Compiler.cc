/*
 * Compiler.cc - Copyright (c) 2023 - Olivier Poncet
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
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Parser.h"
#include "Compiler.h"

// ---------------------------------------------------------------------------
// rpn::Compiler
// ---------------------------------------------------------------------------

namespace rpn {

Compiler::Compiler(ByteCode& bytecode, HostCode& hostcode, Function& function)
    : Listener()
    , _bytecode(bytecode)
    , _hostcode(hostcode)
    , _function(function)
{
    _bytecode.clear();
    _hostcode.clear();
    _function.clear();
}

void Compiler::compile(std::istream& stream)
{
    Parser parser(*this);

    return parser.parse(stream);
}

void Compiler::compile(const std::string& string)
{
    std::istringstream stream(string);

    return compile(stream);
}

void Compiler::op_nop()
{
    _bytecode.emit_nop();
}

void Compiler::op_i64(const int64_t operand)
{
    _bytecode.emit_i64(operand);
}

void Compiler::op_top()
{
    _bytecode.emit_top();
}

void Compiler::op_pop()
{
    _bytecode.emit_pop();
}

void Compiler::op_clr()
{
    _bytecode.emit_clr();
}

void Compiler::op_dup()
{
    _bytecode.emit_dup();
}

void Compiler::op_xch()
{
    _bytecode.emit_xch();
}

void Compiler::op_sto()
{
    _bytecode.emit_sto();
}

void Compiler::op_rcl()
{
    _bytecode.emit_rcl();
}

void Compiler::op_abs()
{
    _bytecode.emit_abs();
}

void Compiler::op_neg()
{
    _bytecode.emit_neg();
}

void Compiler::op_add()
{
    _bytecode.emit_add();
}

void Compiler::op_sub()
{
    _bytecode.emit_sub();
}

void Compiler::op_mul()
{
    _bytecode.emit_mul();
}

void Compiler::op_div()
{
    _bytecode.emit_div();
}

void Compiler::op_mod()
{
    _bytecode.emit_mod();
}

void Compiler::op_cpl()
{
    _bytecode.emit_cpl();
}

void Compiler::op_and()
{
    _bytecode.emit_and();
}

void Compiler::op_ior()
{
    _bytecode.emit_ior();
}

void Compiler::op_xor()
{
    _bytecode.emit_xor();
}

void Compiler::op_shl()
{
    _bytecode.emit_shl();
}

void Compiler::op_shr()
{
    _bytecode.emit_shr();
}

void Compiler::op_inc()
{
    _bytecode.emit_inc();
}

void Compiler::op_dec()
{
    _bytecode.emit_dec();
}

void Compiler::op_run()
{
    throw std::runtime_error("the <run> instruction cannot be compiled");
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
