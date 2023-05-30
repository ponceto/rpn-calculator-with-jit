/*
 * Calculator.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_Calculator_h__
#define __RPN_Calculator_h__

#include "Logger.h"
#include "Console.h"
#include "Parser.h"
#include "Compiler.h"
#include "State.h"

// ---------------------------------------------------------------------------
// rpn::Calculator
// ---------------------------------------------------------------------------

namespace rpn {

class Calculator final
    : public Listener
    , public Logger
{
public: // public interface
    Calculator(Console&);

    Calculator(Calculator&&) = delete;

    Calculator(const Calculator&) = delete;

    Calculator& operator=(const Calculator&) = delete;

    virtual ~Calculator() = default;

    void execute(const std::string& expression);

    void compile(const std::string& expression);

    void run();

    void clear();

    int64_t result();

public: // listener interface
    virtual void op_nop() override;

    virtual void op_i64(const int64_t operand) override;

    virtual void op_top() override;

    virtual void op_pop() override;

    virtual void op_clr() override;

    virtual void op_dup() override;

    virtual void op_xch() override;

    virtual void op_sto() override;

    virtual void op_rcl() override;

    virtual void op_abs() override;

    virtual void op_neg() override;

    virtual void op_add() override;

    virtual void op_sub() override;

    virtual void op_mul() override;

    virtual void op_div() override;

    virtual void op_mod() override;

    virtual void op_cpl() override;

    virtual void op_and() override;

    virtual void op_ior() override;

    virtual void op_xor() override;

    virtual void op_shl() override;

    virtual void op_shr() override;

    virtual void op_inc() override;

    virtual void op_dec() override;

    virtual void op_run() override;

public: // logger interface
    virtual void log_debug(const std::string& message) override;

    virtual void log_trace(const std::string& message) override;

    virtual void log_print(const std::string& message) override;

    virtual void log_alert(const std::string& message) override;

    virtual void log_error(const std::string& message) override;

    virtual void set_debug(const bool enabled) override;

    virtual void set_trace(const bool enabled) override;

    virtual void set_print(const bool enabled) override;

    virtual void set_alert(const bool enabled) override;

    virtual void set_error(const bool enabled) override;

    void log_result();

private: // private data
    Console& _console;
    Operands _operands;
    ByteCode _bytecode;
    HostCode _hostcode;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_Calculator_h__ */
