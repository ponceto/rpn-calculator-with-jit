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
// rpn::Calculator
// ---------------------------------------------------------------------------

namespace rpn {

Calculator::Calculator(Console& console)
    : Listener()
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
        Parser parser(*this);
        parser.parse(expression);
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
        Compiler compiler(_bytecode, _hostcode);
        compiler.compile(expression);
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
        op_run();
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
    BasicBlock basic_block(_hostcode.begin(), _hostcode.end());

    auto exec_nop = [&]() -> void
    {
        log_debug("exec <nop>");

        return op_nop();
    };

    auto exec_i64 = [&](const int64_t operand) -> void
    {
        log_debug("exec <i64>");

        return op_i64(operand);
    };

    auto exec_top = [&]() -> void
    {
        log_debug("exec <top>");

        return op_top();
    };

    auto exec_pop = [&]() -> void
    {
        log_debug("exec <pop>");

        return op_pop();
    };

    auto exec_clr = [&]() -> void
    {
        log_debug("exec <clr>");

        return op_clr();
    };

    auto exec_dup = [&]() -> void
    {
        log_debug("exec <dup>");

        return op_dup();
    };

    auto exec_xch = [&]() -> void
    {
        log_debug("exec <xch>");

        return op_xch();
    };

    auto exec_sto = [&]() -> void
    {
        log_debug("exec <sto>");

        return op_sto();
    };

    auto exec_rcl = [&]() -> void
    {
        log_debug("exec <rcl>");

        return op_rcl();
    };

    auto exec_abs = [&]() -> void
    {
        log_debug("exec <abs>");

        return op_abs();
    };

    auto exec_neg = [&]() -> void
    {
        log_debug("exec <neg>");

        return op_neg();
    };

    auto exec_add = [&]() -> void
    {
        log_debug("exec <add>");

        return op_add();
    };

    auto exec_sub = [&]() -> void
    {
        log_debug("exec <sub>");

        return op_sub();
    };

    auto exec_mul = [&]() -> void
    {
        log_debug("exec <mul>");

        return op_mul();
    };

    auto exec_div = [&]() -> void
    {
        log_debug("exec <div>");

        return op_div();
    };

    auto exec_mod = [&]() -> void
    {
        log_debug("exec <mod>");

        return op_mod();
    };

    auto exec_cpl = [&]() -> void
    {
        log_debug("exec <cpl>");

        return op_cpl();
    };

    auto exec_and = [&]() -> void
    {
        log_debug("exec <and>");

        return op_and();
    };

    auto exec_ior = [&]() -> void
    {
        log_debug("exec <ior>");

        return op_ior();
    };

    auto exec_xor = [&]() -> void
    {
        log_debug("exec <xor>");

        return op_xor();
    };

    auto exec_shl = [&]() -> void
    {
        log_debug("exec <shl>");

        return op_shl();
    };

    auto exec_shr = [&]() -> void
    {
        log_debug("exec <shr>");

        return op_shr();
    };

    auto exec_inc = [&]() -> void
    {
        log_debug("exec <inc>");

        return op_inc();
    };

    auto exec_dec = [&]() -> void
    {
        log_debug("exec <dec>");

        return op_dec();
    };

    auto emit_prolog = [&]() -> void
    {
        log_debug("emit <function prolog>");

        _hostcode.push_rbp();
        _hostcode.mov_rbp_rsp();
    };

    auto emit_epilog = [&]() -> void
    {
        log_debug("emit <function epilog>");

        _hostcode.mov_rsp_rbp();
        _hostcode.pop_rbp();
        _hostcode.ret();
    };

    auto emit_nop = [&]() -> void
    {
        log_debug("emit <nop>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_nop));
        _hostcode.call_rax();
    };

    auto emit_i64 = [&](const int64_t operand) -> void
    {
        log_debug("emit <i64>");

        _hostcode.mov_rsi_imm64(operand);
        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_i64));
        _hostcode.call_rax();
    };

    auto emit_top = [&]() -> void
    {
        log_debug("emit <top>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_top));
        _hostcode.call_rax();
    };

    auto emit_pop = [&]() -> void
    {
        log_debug("emit <pop>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_pop));
        _hostcode.call_rax();
    };

    auto emit_clr = [&]() -> void
    {
        log_debug("emit <clr>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_clr));
        _hostcode.call_rax();
    };

    auto emit_dup = [&]() -> void
    {
        log_debug("emit <dup>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_dup));
        _hostcode.call_rax();
    };

    auto emit_xch = [&]() -> void
    {
        log_debug("emit <xch>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_xch));
        _hostcode.call_rax();
    };

    auto emit_sto = [&]() -> void
    {
        log_debug("emit <sto>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_sto));
        _hostcode.call_rax();
    };

    auto emit_rcl = [&]() -> void
    {
        log_debug("emit <rcl>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_rcl));
        _hostcode.call_rax();
    };

    auto emit_abs = [&]() -> void
    {
        log_debug("emit <abs>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_abs));
        _hostcode.call_rax();
    };

    auto emit_neg = [&]() -> void
    {
        log_debug("emit <neg>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_neg));
        _hostcode.call_rax();
    };

    auto emit_add = [&]() -> void
    {
        log_debug("emit <add>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_add));
        _hostcode.call_rax();
    };

    auto emit_sub = [&]() -> void
    {
        log_debug("emit <sub>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_sub));
        _hostcode.call_rax();
    };

    auto emit_mul = [&]() -> void
    {
        log_debug("emit <mul>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_mul));
        _hostcode.call_rax();
    };

    auto emit_div = [&]() -> void
    {
        log_debug("emit <div>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_div));
        _hostcode.call_rax();
    };

    auto emit_mod = [&]() -> void
    {
        log_debug("emit <mod>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_mod));
        _hostcode.call_rax();
    };

    auto emit_cpl = [&]() -> void
    {
        log_debug("emit <cpl>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_cpl));
        _hostcode.call_rax();
    };

    auto emit_and = [&]() -> void
    {
        log_debug("emit <and>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_and));
        _hostcode.call_rax();
    };

    auto emit_ior = [&]() -> void
    {
        log_debug("emit <ior>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_ior));
        _hostcode.call_rax();
    };

    auto emit_xor = [&]() -> void
    {
        log_debug("emit <xor>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_xor));
        _hostcode.call_rax();
    };

    auto emit_shl = [&]() -> void
    {
        log_debug("emit <shl>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_shl));
        _hostcode.call_rax();
    };

    auto emit_shr = [&]() -> void
    {
        log_debug("emit <shr>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_shr));
        _hostcode.call_rax();
    };

    auto emit_inc = [&]() -> void
    {
        log_debug("emit <inc>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_inc));
        _hostcode.call_rax();
    };

    auto emit_dec = [&]() -> void
    {
        log_debug("emit <dec>");

        _hostcode.mov_rdi_imm64(reinterpret_cast<uintptr_t>(&_operands));
        _hostcode.mov_rax_imm64(reinterpret_cast<uintptr_t>(&Operators::op_dec));
        _hostcode.call_rax();
    };

    auto prolog = [&]() -> void
    {
        emit_prolog();
    };

    auto epilog = [&]() -> void
    {
        emit_epilog();
    };

    auto do_nop = [&](const uint8_t& opcode) -> int
    {
        exec_nop();
        emit_nop();
        return 0;
    };

    auto do_i64 = [&](const uint8_t& opcode) -> int
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

    auto do_top = [&](const uint8_t& opcode) -> int
    {
        exec_top();
        emit_top();
        return 0;
    };

    auto do_pop = [&](const uint8_t& opcode) -> int
    {
        exec_pop();
        emit_pop();
        return 0;
    };

    auto do_clr = [&](const uint8_t& opcode) -> int
    {
        exec_clr();
        emit_clr();
        return 0;
    };

    auto do_dup = [&](const uint8_t& opcode) -> int
    {
        exec_dup();
        emit_dup();
        return 0;
    };

    auto do_xch = [&](const uint8_t& opcode) -> int
    {
        exec_xch();
        emit_xch();
        return 0;
    };

    auto do_sto = [&](const uint8_t& opcode) -> int
    {
        exec_sto();
        emit_sto();
        return 0;
    };

    auto do_rcl = [&](const uint8_t& opcode) -> int
    {
        exec_rcl();
        emit_rcl();
        return 0;
    };

    auto do_abs = [&](const uint8_t& opcode) -> int
    {
        exec_abs();
        emit_abs();
        return 0;
    };

    auto do_add = [&](const uint8_t& opcode) -> int
    {
        exec_add();
        emit_add();
        return 0;
    };

    auto do_sub = [&](const uint8_t& opcode) -> int
    {
        exec_sub();
        emit_sub();
        return 0;
    };

    auto do_mul = [&](const uint8_t& opcode) -> int
    {
        exec_mul();
        emit_mul();
        return 0;
    };

    auto do_div = [&](const uint8_t& opcode) -> int
    {
        exec_div();
        emit_div();
        return 0;
    };

    auto do_mod = [&](const uint8_t& opcode) -> int
    {
        exec_mod();
        emit_mod();
        return 0;
    };

    auto do_cpl = [&](const uint8_t& opcode) -> int
    {
        exec_cpl();
        emit_cpl();
        return 0;
    };

    auto do_and = [&](const uint8_t& opcode) -> int
    {
        exec_and();
        emit_and();
        return 0;
    };

    auto do_ior = [&](const uint8_t& opcode) -> int
    {
        exec_ior();
        emit_ior();
        return 0;
    };

    auto do_xor = [&](const uint8_t& opcode) -> int
    {
        exec_xor();
        emit_xor();
        return 0;
    };

    auto do_shl = [&](const uint8_t& opcode) -> int
    {
        exec_shl();
        emit_shl();
        return 0;
    };

    auto do_shr = [&](const uint8_t& opcode) -> int
    {
        exec_shr();
        emit_shr();
        return 0;
    };

    auto do_inc = [&](const uint8_t& opcode) -> int
    {
        exec_inc();
        emit_inc();
        return 0;
    };

    auto do_dec = [&](const uint8_t& opcode) -> int
    {
        exec_dec();
        emit_dec();
        return 0;
    };

    auto do_neg = [&](const uint8_t& opcode) -> int
    {
        exec_neg();
        emit_neg();
        return 0;
    };

    auto translate = [&]() -> void
    {
        prolog();
        int skip = 0;
        for(const uint8_t& opcode : _bytecode) {
            if(skip > 0) {
                --skip;
            }
            else switch(opcode) {
                case ByteCode::OP_NOP:
                    skip = do_nop(opcode);
                    break;
                case ByteCode::OP_I64:
                    skip = do_i64(opcode);
                    break;
                case ByteCode::OP_TOP:
                    skip = do_top(opcode);
                    break;
                case ByteCode::OP_POP:
                    skip = do_pop(opcode);
                    break;
                case ByteCode::OP_CLR:
                    skip = do_clr(opcode);
                    break;
                case ByteCode::OP_DUP:
                    skip = do_dup(opcode);
                    break;
                case ByteCode::OP_XCH:
                    skip = do_xch(opcode);
                    break;
                case ByteCode::OP_STO:
                    skip = do_sto(opcode);
                    break;
                case ByteCode::OP_RCL:
                    skip = do_rcl(opcode);
                    break;
                case ByteCode::OP_ABS:
                    skip = do_abs(opcode);
                    break;
                case ByteCode::OP_NEG:
                    skip = do_neg(opcode);
                    break;
                case ByteCode::OP_ADD:
                    skip = do_add(opcode);
                    break;
                case ByteCode::OP_SUB:
                    skip = do_sub(opcode);
                    break;
                case ByteCode::OP_MUL:
                    skip = do_mul(opcode);
                    break;
                case ByteCode::OP_DIV:
                    skip = do_div(opcode);
                    break;
                case ByteCode::OP_MOD:
                    skip = do_mod(opcode);
                    break;
                case ByteCode::OP_CPL:
                    skip = do_cpl(opcode);
                    break;
                case ByteCode::OP_AND:
                    skip = do_and(opcode);
                    break;
                case ByteCode::OP_IOR:
                    skip = do_ior(opcode);
                    break;
                case ByteCode::OP_XOR:
                    skip = do_xor(opcode);
                    break;
                case ByteCode::OP_SHL:
                    skip = do_shl(opcode);
                    break;
                case ByteCode::OP_SHR:
                    skip = do_shr(opcode);
                    break;
                case ByteCode::OP_INC:
                    skip = do_inc(opcode);
                    break;
                case ByteCode::OP_DEC:
                    skip = do_dec(opcode);
                    break;
                default:
                    throw std::runtime_error("unexpected bytecode");
            }
        }
        epilog();
    };

    auto execute = [&]() -> void
    {
        if(basic_block.valid()) {
            log_trace("the bytecode has already been translated, executing the generated machine code...");
            basic_block.execute();
        }
        else {
            log_trace("the bytecode has never been translated, executing bytecode and translating to machine code...");
            translate();
        }
    };

    return execute();
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
// End-Of-File
// ---------------------------------------------------------------------------
