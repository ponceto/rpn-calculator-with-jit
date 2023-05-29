/*
 * Calculator.cc - Copyright (c) 2023 - Olivier Poncet
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
#include "BasicBlock.h"
#include "Calculator.h"

// ---------------------------------------------------------------------------
// rpn::VirtualMachine
// ---------------------------------------------------------------------------

namespace rpn {

struct VirtualMachine
{
    static void execute(Calculator&, Operands&, ByteCode&, HostCode&, const std::string& expression);

    static void compile(Calculator&, Operands&, ByteCode&, HostCode&, const std::string& expression);

    static void run(Calculator&, Operands&, ByteCode&, HostCode&);
};

}

// ---------------------------------------------------------------------------
// rpn::Calculator
// ---------------------------------------------------------------------------

namespace rpn {

Calculator::Calculator(Console& console)
    : Listener()
    , Logger()
    , _console(console)
    , _operands()
    , _bytecode()
    , _hostcode()
{
}

void Calculator::execute(const std::string& expression)
{
    log_print(std::string("executing expression") + ' ' + '<' + expression + '>');
    try {
        VirtualMachine::execute(*this, _operands, _bytecode, _hostcode, expression);
    }
    catch(const std::runtime_error& e) {
        log_error("error while executing!");
        throw;
    }
    log_result();
}

void Calculator::compile(const std::string& expression)
{
    log_print(std::string("compiling expression") + ' ' + '<' + expression + '>');
    try {
        VirtualMachine::compile(*this, _operands, _bytecode, _hostcode, expression);
    }
    catch(const std::runtime_error& e) {
        log_error("error while compiling!");
        throw;
    }
    log_result();
}

void Calculator::run()
{
    log_print("running the compiled expression...");
    try {
        VirtualMachine::run(*this, _operands, _bytecode, _hostcode);
    }
    catch(const std::runtime_error& e) {
        log_error("error while running!");
        throw;
    }
    log_result();
}

void Calculator::clear()
{
    log_print("clearing the stack ...");
    try {
        op_clr();
    }
    catch(const std::runtime_error& e) {
        log_error("error while clearing!");
        throw;
    }
    log_result();
}

int64_t Calculator::result()
{
    return Operators::op_top(_operands);
}

void Calculator::op_nop()
{
    static_cast<void>(Operators::op_nop(_operands));
}

void Calculator::op_i64(const int64_t operand)
{
    static_cast<void>(Operators::op_i64(_operands, operand));
}

void Calculator::op_top()
{
    static_cast<void>(Operators::op_top(_operands));
}

void Calculator::op_pop()
{
    static_cast<void>(Operators::op_pop(_operands));
}

void Calculator::op_clr()
{
    static_cast<void>(Operators::op_clr(_operands));
}

void Calculator::op_dup()
{
    static_cast<void>(Operators::op_dup(_operands));
}

void Calculator::op_xch()
{
    static_cast<void>(Operators::op_xch(_operands));
}

void Calculator::op_sto()
{
    static_cast<void>(Operators::op_sto(_operands));
}

void Calculator::op_rcl()
{
    static_cast<void>(Operators::op_rcl(_operands));
}

void Calculator::op_abs()
{
    static_cast<void>(Operators::op_abs(_operands));
}

void Calculator::op_neg()
{
    static_cast<void>(Operators::op_neg(_operands));
}

void Calculator::op_add()
{
    static_cast<void>(Operators::op_add(_operands));
}

void Calculator::op_sub()
{
    static_cast<void>(Operators::op_sub(_operands));
}

void Calculator::op_mul()
{
    static_cast<void>(Operators::op_mul(_operands));
}

void Calculator::op_div()
{
    static_cast<void>(Operators::op_div(_operands));
}

void Calculator::op_mod()
{
    static_cast<void>(Operators::op_mod(_operands));
}

void Calculator::op_cpl()
{
    static_cast<void>(Operators::op_cpl(_operands));
}

void Calculator::op_and()
{
    static_cast<void>(Operators::op_and(_operands));
}

void Calculator::op_ior()
{
    static_cast<void>(Operators::op_ior(_operands));
}

void Calculator::op_xor()
{
    static_cast<void>(Operators::op_xor(_operands));
}

void Calculator::op_shl()
{
    static_cast<void>(Operators::op_shl(_operands));
}

void Calculator::op_shr()
{
    static_cast<void>(Operators::op_shr(_operands));
}

void Calculator::op_inc()
{
    static_cast<void>(Operators::op_inc(_operands));
}

void Calculator::op_dec()
{
    static_cast<void>(Operators::op_dec(_operands));
}

void Calculator::op_run()
{
    VirtualMachine::run(*this, _operands, _bytecode, _hostcode);
}

void Calculator::log_debug(const std::string& message)
{
    _console.log_debug(message);
}

void Calculator::log_trace(const std::string& message)
{
    _console.log_trace(message);
}

void Calculator::log_print(const std::string& message)
{
    _console.log_print(message);
}

void Calculator::log_alert(const std::string& message)
{
    _console.log_alert(message);
}

void Calculator::log_error(const std::string& message)
{
    _console.log_error(message);
}

void Calculator::set_debug(const bool enabled)
{
    _console.set_debug(enabled);
}

void Calculator::set_trace(const bool enabled)
{
    _console.set_trace(enabled);
}

void Calculator::set_print(const bool enabled)
{
    _console.set_print(enabled);
}

void Calculator::set_alert(const bool enabled)
{
    _console.set_alert(enabled);
}

void Calculator::set_error(const bool enabled)
{
    _console.set_error(enabled);
}

void Calculator::log_result()
{
    try {
        _console.log_print(std::string("result is") + ' ' + std::to_string(result()));
    }
    catch(...) {
        _console.log_print(std::string("no result") + ' ' + "<empty stack>");
    }
}

}

// ---------------------------------------------------------------------------
// rpn::VirtualMachine
// ---------------------------------------------------------------------------

namespace rpn {

void VirtualMachine::execute(Calculator& calculator, Operands& operands, ByteCode& bytecode, HostCode& hostcode, const std::string& expression)
{
    Parser parser(calculator);

    parser.parse(expression);
}

void VirtualMachine::compile(Calculator& calculator, Operands& operands, ByteCode& bytecode, HostCode& hostcode, const std::string& expression)
{
    Compiler compiler(bytecode, hostcode);

    compiler.compile(expression);
}

void VirtualMachine::run(Calculator& calculator, Operands& operands, ByteCode& bytecode, HostCode& hostcode)
{
    auto exec_nop = [&]() -> void
    {
        calculator.log_debug("exec <nop>");
        calculator.op_nop();
    };

    auto exec_i64 = [&](const int64_t operand) -> void
    {
        calculator.log_debug("exec <i64>");
        calculator.op_i64(operand);
    };

    auto exec_top = [&]() -> void
    {
        calculator.log_debug("exec <top>");
        calculator.op_top();
    };

    auto exec_pop = [&]() -> void
    {
        calculator.log_debug("exec <pop>");
        calculator.op_pop();
    };

    auto exec_clr = [&]() -> void
    {
        calculator.log_debug("exec <clr>");
        calculator.op_clr();
    };

    auto exec_dup = [&]() -> void
    {
        calculator.log_debug("exec <dup>");
        calculator.op_dup();
    };

    auto exec_xch = [&]() -> void
    {
        calculator.log_debug("exec <xch>");
        calculator.op_xch();
    };

    auto exec_sto = [&]() -> void
    {
        calculator.log_debug("exec <sto>");
        calculator.op_sto();
    };

    auto exec_rcl = [&]() -> void
    {
        calculator.log_debug("exec <rcl>");
        calculator.op_rcl();
    };

    auto exec_abs = [&]() -> void
    {
        calculator.log_debug("exec <abs>");
        calculator.op_abs();
    };

    auto exec_neg = [&]() -> void
    {
        calculator.log_debug("exec <neg>");
        calculator.op_neg();
    };

    auto exec_add = [&]() -> void
    {
        calculator.log_debug("exec <add>");
        calculator.op_add();
    };

    auto exec_sub = [&]() -> void
    {
        calculator.log_debug("exec <sub>");
        calculator.op_sub();
    };

    auto exec_mul = [&]() -> void
    {
        calculator.log_debug("exec <mul>");
        calculator.op_mul();
    };

    auto exec_div = [&]() -> void
    {
        calculator.log_debug("exec <div>");
        calculator.op_div();
    };

    auto exec_mod = [&]() -> void
    {
        calculator.log_debug("exec <mod>");
        calculator.op_mod();
    };

    auto exec_cpl = [&]() -> void
    {
        calculator.log_debug("exec <cpl>");
        calculator.op_cpl();
    };

    auto exec_and = [&]() -> void
    {
        calculator.log_debug("exec <and>");
        calculator.op_and();
    };

    auto exec_ior = [&]() -> void
    {
        calculator.log_debug("exec <ior>");
        calculator.op_ior();
    };

    auto exec_xor = [&]() -> void
    {
        calculator.log_debug("exec <xor>");
        calculator.op_xor();
    };

    auto exec_shl = [&]() -> void
    {
        calculator.log_debug("exec <shl>");
        calculator.op_shl();
    };

    auto exec_shr = [&]() -> void
    {
        calculator.log_debug("exec <shr>");
        calculator.op_shr();
    };

    auto exec_inc = [&]() -> void
    {
        calculator.log_debug("exec <inc>");
        calculator.op_inc();
    };

    auto exec_dec = [&]() -> void
    {
        calculator.log_debug("exec <dec>");
        calculator.op_dec();
    };

    auto emit_prolog = [&]() -> void
    {
        calculator.log_debug("emit <function prolog>");
        hostcode.push_rbp();
        hostcode.mov_rbp_rsp();
    };

    auto emit_epilog = [&]() -> void
    {
        calculator.log_debug("emit <function epilog>");
        hostcode.mov_rsp_rbp();
        hostcode.pop_rbp();
        hostcode.ret();
    };

    auto emit_nop = [&]() -> void
    {
        calculator.log_debug("emit <nop>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_nop));
        hostcode.call_rax();
    };

    auto emit_i64 = [&](const int64_t operand) -> void
    {
        calculator.log_debug("emit <i64>");
        hostcode.mov_rsi_imm64(operand);
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_i64));
        hostcode.call_rax();
    };

    auto emit_top = [&]() -> void
    {
        calculator.log_debug("emit <top>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_top));
        hostcode.call_rax();
    };

    auto emit_pop = [&]() -> void
    {
        calculator.log_debug("emit <pop>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_pop));
        hostcode.call_rax();
    };

    auto emit_clr = [&]() -> void
    {
        calculator.log_debug("emit <clr>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_clr));
        hostcode.call_rax();
    };

    auto emit_dup = [&]() -> void
    {
        calculator.log_debug("emit <dup>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_dup));
        hostcode.call_rax();
    };

    auto emit_xch = [&]() -> void
    {
        calculator.log_debug("emit <xch>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_xch));
        hostcode.call_rax();
    };

    auto emit_sto = [&]() -> void
    {
        calculator.log_debug("emit <sto>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_sto));
        hostcode.call_rax();
    };

    auto emit_rcl = [&]() -> void
    {
        calculator.log_debug("emit <rcl>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_rcl));
        hostcode.call_rax();
    };

    auto emit_abs = [&]() -> void
    {
        calculator.log_debug("emit <abs>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_abs));
        hostcode.call_rax();
    };

    auto emit_neg = [&]() -> void
    {
        calculator.log_debug("emit <neg>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_neg));
        hostcode.call_rax();
    };

    auto emit_add = [&]() -> void
    {
        calculator.log_debug("emit <add>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_add));
        hostcode.call_rax();
    };

    auto emit_sub = [&]() -> void
    {
        calculator.log_debug("emit <sub>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_sub));
        hostcode.call_rax();
    };

    auto emit_mul = [&]() -> void
    {
        calculator.log_debug("emit <mul>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_mul));
        hostcode.call_rax();
    };

    auto emit_div = [&]() -> void
    {
        calculator.log_debug("emit <div>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_div));
        hostcode.call_rax();
    };

    auto emit_mod = [&]() -> void
    {
        calculator.log_debug("emit <mod>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_mod));
        hostcode.call_rax();
    };

    auto emit_cpl = [&]() -> void
    {
        calculator.log_debug("emit <cpl>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_cpl));
        hostcode.call_rax();
    };

    auto emit_and = [&]() -> void
    {
        calculator.log_debug("emit <and>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_and));
        hostcode.call_rax();
    };

    auto emit_ior = [&]() -> void
    {
        calculator.log_debug("emit <ior>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_ior));
        hostcode.call_rax();
    };

    auto emit_xor = [&]() -> void
    {
        calculator.log_debug("emit <xor>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_xor));
        hostcode.call_rax();
    };

    auto emit_shl = [&]() -> void
    {
        calculator.log_debug("emit <shl>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_shl));
        hostcode.call_rax();
    };

    auto emit_shr = [&]() -> void
    {
        calculator.log_debug("emit <shr>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_shr));
        hostcode.call_rax();
    };

    auto emit_inc = [&]() -> void
    {
        calculator.log_debug("emit <inc>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_inc));
        hostcode.call_rax();
    };

    auto emit_dec = [&]() -> void
    {
        calculator.log_debug("emit <dec>");
        hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&operands));
        hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_dec));
        hostcode.call_rax();
    };

    auto prolog = [&]() -> void
    {
        emit_prolog();
    };

    auto epilog = [&]() -> void
    {
        emit_epilog();
    };

    auto op_nop = [&](const uint8_t& opcode) -> int
    {
        exec_nop();
        emit_nop();
        return 0;
    };

    auto op_i64 = [&](const uint8_t& opcode) -> int
    {
        int64_t operand = 0;
        operand = ((operand << 8) | (&opcode)[8]);
        operand = ((operand << 8) | (&opcode)[7]);
        operand = ((operand << 8) | (&opcode)[6]);
        operand = ((operand << 8) | (&opcode)[5]);
        operand = ((operand << 8) | (&opcode)[4]);
        operand = ((operand << 8) | (&opcode)[3]);
        operand = ((operand << 8) | (&opcode)[2]);
        operand = ((operand << 8) | (&opcode)[1]);
        exec_i64(operand);
        emit_i64(operand);
        return 8;
    };

    auto op_top = [&](const uint8_t& opcode) -> int
    {
        exec_top();
        emit_top();
        return 0;
    };

    auto op_pop = [&](const uint8_t& opcode) -> int
    {
        exec_pop();
        emit_pop();
        return 0;
    };

    auto op_clr = [&](const uint8_t& opcode) -> int
    {
        exec_clr();
        emit_clr();
        return 0;
    };

    auto op_dup = [&](const uint8_t& opcode) -> int
    {
        exec_dup();
        emit_dup();
        return 0;
    };

    auto op_xch = [&](const uint8_t& opcode) -> int
    {
        exec_xch();
        emit_xch();
        return 0;
    };

    auto op_sto = [&](const uint8_t& opcode) -> int
    {
        exec_sto();
        emit_sto();
        return 0;
    };

    auto op_rcl = [&](const uint8_t& opcode) -> int
    {
        exec_rcl();
        emit_rcl();
        return 0;
    };

    auto op_abs = [&](const uint8_t& opcode) -> int
    {
        exec_abs();
        emit_abs();
        return 0;
    };

    auto op_neg = [&](const uint8_t& opcode) -> int
    {
        exec_neg();
        emit_neg();
        return 0;
    };

    auto op_add = [&](const uint8_t& opcode) -> int
    {
        exec_add();
        emit_add();
        return 0;
    };

    auto op_sub = [&](const uint8_t& opcode) -> int
    {
        exec_sub();
        emit_sub();
        return 0;
    };

    auto op_mul = [&](const uint8_t& opcode) -> int
    {
        exec_mul();
        emit_mul();
        return 0;
    };

    auto op_div = [&](const uint8_t& opcode) -> int
    {
        exec_div();
        emit_div();
        return 0;
    };

    auto op_mod = [&](const uint8_t& opcode) -> int
    {
        exec_mod();
        emit_mod();
        return 0;
    };

    auto op_cpl = [&](const uint8_t& opcode) -> int
    {
        exec_cpl();
        emit_cpl();
        return 0;
    };

    auto op_and = [&](const uint8_t& opcode) -> int
    {
        exec_and();
        emit_and();
        return 0;
    };

    auto op_ior = [&](const uint8_t& opcode) -> int
    {
        exec_ior();
        emit_ior();
        return 0;
    };

    auto op_xor = [&](const uint8_t& opcode) -> int
    {
        exec_xor();
        emit_xor();
        return 0;
    };

    auto op_shl = [&](const uint8_t& opcode) -> int
    {
        exec_shl();
        emit_shl();
        return 0;
    };

    auto op_shr = [&](const uint8_t& opcode) -> int
    {
        exec_shr();
        emit_shr();
        return 0;
    };

    auto op_inc = [&](const uint8_t& opcode) -> int
    {
        exec_inc();
        emit_inc();
        return 0;
    };

    auto op_dec = [&](const uint8_t& opcode) -> int
    {
        exec_dec();
        emit_dec();
        return 0;
    };

    auto translate = [&]() -> void
    {
        prolog();
        int skip = 0;
        for(const uint8_t& opcode : bytecode) {
            if(skip > 0) {
                --skip;
            }
            else switch(opcode) {
                case ByteCode::OP_NOP:
                    skip = op_nop(opcode);
                    break;
                case ByteCode::OP_I64:
                    skip = op_i64(opcode);
                    break;
                case ByteCode::OP_TOP:
                    skip = op_top(opcode);
                    break;
                case ByteCode::OP_POP:
                    skip = op_pop(opcode);
                    break;
                case ByteCode::OP_CLR:
                    skip = op_clr(opcode);
                    break;
                case ByteCode::OP_DUP:
                    skip = op_dup(opcode);
                    break;
                case ByteCode::OP_XCH:
                    skip = op_xch(opcode);
                    break;
                case ByteCode::OP_STO:
                    skip = op_sto(opcode);
                    break;
                case ByteCode::OP_RCL:
                    skip = op_rcl(opcode);
                    break;
                case ByteCode::OP_ABS:
                    skip = op_abs(opcode);
                    break;
                case ByteCode::OP_NEG:
                    skip = op_neg(opcode);
                    break;
                case ByteCode::OP_ADD:
                    skip = op_add(opcode);
                    break;
                case ByteCode::OP_SUB:
                    skip = op_sub(opcode);
                    break;
                case ByteCode::OP_MUL:
                    skip = op_mul(opcode);
                    break;
                case ByteCode::OP_DIV:
                    skip = op_div(opcode);
                    break;
                case ByteCode::OP_MOD:
                    skip = op_mod(opcode);
                    break;
                case ByteCode::OP_CPL:
                    skip = op_cpl(opcode);
                    break;
                case ByteCode::OP_AND:
                    skip = op_and(opcode);
                    break;
                case ByteCode::OP_IOR:
                    skip = op_ior(opcode);
                    break;
                case ByteCode::OP_XOR:
                    skip = op_xor(opcode);
                    break;
                case ByteCode::OP_SHL:
                    skip = op_shl(opcode);
                    break;
                case ByteCode::OP_SHR:
                    skip = op_shr(opcode);
                    break;
                case ByteCode::OP_INC:
                    skip = op_inc(opcode);
                    break;
                case ByteCode::OP_DEC:
                    skip = op_dec(opcode);
                    break;
                default:
                    throw std::runtime_error("unexpected opcode");
            }
        }
        epilog();
    };

    auto execute = [&]() -> void
    {
        BasicBlock basic_block(hostcode.begin(), hostcode.end());

        if(basic_block.valid()) {
            calculator.log_trace("the bytecode has already been translated, executing the generated machine code...");
            basic_block.execute();
        }
        else {
            calculator.log_trace("the bytecode has never been translated, executing bytecode and translating to machine code...");
            translate();
        }
    };

    return execute();
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
