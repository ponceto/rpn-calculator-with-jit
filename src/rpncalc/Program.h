/*
 * Program.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_Program_h__
#define __RPN_Program_h__

#include "Logger.h"
#include "Console.h"
#include "Runnable.h"
#include "Calculator.h"

// ---------------------------------------------------------------------------
// rpn::ArgList
// ---------------------------------------------------------------------------

namespace rpn {

using ArgList = std::vector<std::string>;

}

// ---------------------------------------------------------------------------
// rpn::Program
// ---------------------------------------------------------------------------

namespace rpn {

class Program final
    : public Runnable
    , public Logger
{
public: // public interface
    Program(ArgList&, Console&);

    Program(Program&&) = delete;

    Program& operator=(Program&&) = delete;

    Program(const Program&) = delete;

    Program& operator=(const Program&) = delete;

    virtual ~Program() = default;

public: // runnable interface
    virtual void run() override;

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

private: // private data
    ArgList    _arglist;
    Console&   _console;
    Calculator _calculator;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_Program_h__ */
