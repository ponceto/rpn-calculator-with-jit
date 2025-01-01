/*
 * Parser.cc - Copyright (c) 2023-2025 - Olivier Poncet
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
#include <map>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Parser.h"

// ---------------------------------------------------------------------------
// <anonymous>::Token
// ---------------------------------------------------------------------------

namespace {

enum Token
{
    TK_ERR =  0,
    TK_NOP =  1,
    TK_I64 =  2,
    TK_TOP =  3,
    TK_POP =  4,
    TK_CLR =  5,
    TK_DUP =  6,
    TK_XCH =  7,
    TK_STO =  8,
    TK_ST0 =  9,
    TK_ST1 = 10,
    TK_ST2 = 11,
    TK_ST3 = 12,
    TK_ST4 = 13,
    TK_ST5 = 14,
    TK_ST6 = 15,
    TK_ST7 = 16,
    TK_ST8 = 17,
    TK_ST9 = 18,
    TK_RCL = 19,
    TK_RC0 = 20,
    TK_RC1 = 21,
    TK_RC2 = 22,
    TK_RC3 = 23,
    TK_RC4 = 24,
    TK_RC5 = 25,
    TK_RC6 = 26,
    TK_RC7 = 27,
    TK_RC8 = 28,
    TK_RC9 = 29,
    TK_ABS = 30,
    TK_NEG = 31,
    TK_ADD = 32,
    TK_SUB = 33,
    TK_MUL = 34,
    TK_DIV = 35,
    TK_MOD = 36,
    TK_CPL = 37,
    TK_AND = 38,
    TK_IOR = 39,
    TK_XOR = 40,
    TK_SHL = 41,
    TK_SHR = 42,
    TK_INC = 43,
    TK_DEC = 44,
    TK_HLT = 45,
    TK_RND = 46,
    TK_NOW = 47,
    TK_FIB = 48,
    TK_RUN = 49,
};

}

// ---------------------------------------------------------------------------
// rpn::Parser
// ---------------------------------------------------------------------------

namespace rpn {

Parser::Parser(Listener& listener)
    : _listener(listener)
{
}

void Parser::parse(std::istream& stream)
{
    const std::map<std::string, Token> map = {
        { "nop", TK_NOP },
    //  { "i64", TK_I64 },
        { "top", TK_TOP },
        { "pop", TK_POP },
        { "clr", TK_CLR },
        { "dup", TK_DUP },
        { "xch", TK_XCH },
        { "sto", TK_STO },
        { "st0", TK_ST0 },
        { "st1", TK_ST1 },
        { "st2", TK_ST2 },
        { "st3", TK_ST3 },
        { "st4", TK_ST4 },
        { "st5", TK_ST5 },
        { "st6", TK_ST6 },
        { "st7", TK_ST7 },
        { "st8", TK_ST8 },
        { "st9", TK_ST9 },
        { "rcl", TK_RCL },
        { "rc0", TK_RC0 },
        { "rc1", TK_RC1 },
        { "rc2", TK_RC2 },
        { "rc3", TK_RC3 },
        { "rc4", TK_RC4 },
        { "rc5", TK_RC5 },
        { "rc6", TK_RC6 },
        { "rc7", TK_RC7 },
        { "rc8", TK_RC8 },
        { "rc9", TK_RC9 },
        { "abs", TK_ABS },
        { "neg", TK_NEG },
        { "add", TK_ADD },
        { "sub", TK_SUB },
        { "mul", TK_MUL },
        { "div", TK_DIV },
        { "mod", TK_MOD },
        { "cpl", TK_CPL },
        { "and", TK_AND },
        { "ior", TK_IOR },
        { "xor", TK_XOR },
        { "shl", TK_SHL },
        { "shr", TK_SHR },
        { "inc", TK_INC },
        { "dec", TK_DEC },
        { "hlt", TK_HLT },
        { "rnd", TK_RND },
        { "now", TK_NOW },
        { "fib", TK_FIB },
        { "run", TK_RUN },
        { "+"  , TK_ADD },
        { "-"  , TK_SUB },
        { "*"  , TK_MUL },
        { "/"  , TK_DIV },
        { "%"  , TK_MOD },
        { "~"  , TK_CPL },
        { "&"  , TK_AND },
        { "|"  , TK_IOR },
        { "^"  , TK_XOR },
        { "<<" , TK_SHL },
        { ">>" , TK_SHR },
        { "++" , TK_INC },
        { "--" , TK_DEC },
    };

    auto empty = [&](const std::string& token) -> bool
    {
        return token.empty();
    };

    auto tk_i64 = [&](const std::string& token, int64_t& value) -> bool
    {
        char* endptr = nullptr;
        const int64_t result = ::strtoll(token.c_str(), &endptr, 10);
        if((endptr != nullptr) && (*endptr == '\0')) {
            value = result;
            return true;
        }
        return false;
    };

    auto lookup = [&](const std::string& token, int64_t& value) -> Token
    {
        const auto found(map.find(token));
        if(found != map.end()) {
            return found->second;
        }
        else if(tk_i64(token, value)) {
            return TK_I64;
        }
        return TK_ERR;
    };

    auto dispatch = [&](const std::string& token) -> bool
    {
        int64_t value = 0;

        switch(lookup(token, value)) {
            case TK_NOP:
                _listener.op_nop();
                break;
            case TK_I64:
                _listener.op_i64(value);
                break;
            case TK_TOP:
                _listener.op_top();
                break;
            case TK_POP:
                _listener.op_pop();
                break;
            case TK_CLR:
                _listener.op_clr();
                break;
            case TK_DUP:
                _listener.op_dup();
                break;
            case TK_XCH:
                _listener.op_xch();
                break;
            case TK_STO:
                _listener.op_sto();
                break;
            case TK_ST0:
                _listener.op_st0();
                break;
            case TK_ST1:
                _listener.op_st1();
                break;
            case TK_ST2:
                _listener.op_st2();
                break;
            case TK_ST3:
                _listener.op_st3();
                break;
            case TK_ST4:
                _listener.op_st4();
                break;
            case TK_ST5:
                _listener.op_st5();
                break;
            case TK_ST6:
                _listener.op_st6();
                break;
            case TK_ST7:
                _listener.op_st7();
                break;
            case TK_ST8:
                _listener.op_st8();
                break;
            case TK_ST9:
                _listener.op_st9();
                break;
            case TK_RCL:
                _listener.op_rcl();
                break;
            case TK_RC0:
                _listener.op_rc0();
                break;
            case TK_RC1:
                _listener.op_rc1();
                break;
            case TK_RC2:
                _listener.op_rc2();
                break;
            case TK_RC3:
                _listener.op_rc3();
                break;
            case TK_RC4:
                _listener.op_rc4();
                break;
            case TK_RC5:
                _listener.op_rc5();
                break;
            case TK_RC6:
                _listener.op_rc6();
                break;
            case TK_RC7:
                _listener.op_rc7();
                break;
            case TK_RC8:
                _listener.op_rc8();
                break;
            case TK_RC9:
                _listener.op_rc9();
                break;
            case TK_ABS:
                _listener.op_abs();
                break;
            case TK_NEG:
                _listener.op_neg();
                break;
            case TK_ADD:
                _listener.op_add();
                break;
            case TK_SUB:
                _listener.op_sub();
                break;
            case TK_MUL:
                _listener.op_mul();
                break;
            case TK_DIV:
                _listener.op_div();
                break;
            case TK_MOD:
                _listener.op_mod();
                break;
            case TK_CPL:
                _listener.op_cpl();
                break;
            case TK_AND:
                _listener.op_and();
                break;
            case TK_IOR:
                _listener.op_ior();
                break;
            case TK_XOR:
                _listener.op_xor();
                break;
            case TK_SHL:
                _listener.op_shl();
                break;
            case TK_SHR:
                _listener.op_shr();
                break;
            case TK_INC:
                _listener.op_inc();
                break;
            case TK_DEC:
                _listener.op_dec();
                break;
            case TK_HLT:
                _listener.op_hlt();
                break;
            case TK_RND:
                _listener.op_rnd();
                break;
            case TK_NOW:
                _listener.op_now();
                break;
            case TK_FIB:
                _listener.op_fib();
                break;
            case TK_RUN:
                _listener.op_run();
                break;
            default:
                return false;
        }
        return true;
    };

    auto do_parse = [&]() -> void
    {
        while(stream.good()) {
            std::string token;
            stream >> token;
            if(empty(token)) {
                continue;
            }
            else if(dispatch(token)) {
                continue;
            }
            else {
                throw std::runtime_error(std::string("unexpected token") + ' ' + '<' + token + '>');
            }
        }
    };

    return do_parse();
}

void Parser::parse(const std::string& string)
{
    std::istringstream stream(string);

    return parse(stream);
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
