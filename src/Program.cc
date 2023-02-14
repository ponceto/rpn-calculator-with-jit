/*
 * Program.cc - Copyright (c) 2023 - Olivier Poncet
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
#include "Program.h"

// ---------------------------------------------------------------------------
// rpn::Program
// ---------------------------------------------------------------------------

namespace rpn {

Program::Program(ArgList& arglist, Console& console)
    : Runnable()
    , _arglist(arglist)
    , _console(console)
    , _calculator(console)
{
}

void Program::run()
{
    std::string expression;

    auto opt_help = [&](const std::string& argument) -> bool
    {
        if(argument == "--help") {
            return true;
        }
        return false;
    };

    auto opt_verbose = [&](const std::string& argument) -> bool
    {
        if(argument == "--verbose") {
            _console.set_debug(true);
            _console.set_trace(true);
            _console.set_print(true);
            _console.set_alert(true);
            _console.set_error(true);
            return true;
        }
        if(argument == "--quiet") {
            _console.set_debug(false);
            _console.set_trace(false);
            _console.set_print(false);
            _console.set_alert(false);
            _console.set_error(false);
            return true;
        }
        return false;
    };

    auto opt_debug = [&](const std::string& argument) -> bool
    {
        if(argument == "--debug") {
            _console.set_debug(true);
            return true;
        }
        if(argument == "--no-debug") {
            _console.set_debug(false);
            return true;
        }
        return false;
    };

    auto opt_trace = [&](const std::string& argument) -> bool
    {
        if(argument == "--trace") {
            _console.set_trace(true);
            return true;
        }
        if(argument == "--no-trace") {
            _console.set_trace(false);
            return true;
        }
        return false;
    };

    auto opt_print = [&](const std::string& argument) -> bool
    {
        if(argument == "--print") {
            _console.set_print(true);
            return true;
        }
        if(argument == "--no-print") {
            _console.set_print(false);
            return true;
        }
        return false;
    };

    auto opt_alert = [&](const std::string& argument) -> bool
    {
        if(argument == "--alert") {
            _console.set_alert(true);
            return true;
        }
        if(argument == "--no-alert") {
            _console.set_alert(false);
            return true;
        }
        return false;
    };

    auto opt_error = [&](const std::string& argument) -> bool
    {
        if(argument == "--error") {
            _console.set_error(true);
            return true;
        }
        if(argument == "--no-error") {
            _console.set_error(false);
            return true;
        }
        return false;
    };

    auto arg_execute = [&](const std::string& argument) -> bool
    {
        if(argument == "execute") {
            _calculator.execute(expression);
            return true;
        }
        return false;
    };

    auto arg_compile = [&](const std::string& argument) -> bool
    {
        if(argument == "compile") {
            _calculator.compile(expression);
            return true;
        }
        return false;
    };

    auto arg_run = [&](const std::string& argument) -> bool
    {
        if(argument == "run") {
            _calculator.run();
            return true;
        }
        return false;
    };

    auto arg_clear = [&](const std::string& argument) -> bool
    {
        if(argument == "clear") {
            _calculator.clear();
            return true;
        }
        return false;
    };

    auto set_expression = [&](const std::string& argument) -> void
    {
        expression = argument;
    };

    auto has_help = [&]() -> bool
    {
        int argi = -1;
        for(auto& argument : _arglist) {
            if(++argi == 0) {
                continue;
            }
            else if(opt_help(argument)) {
                return true;
            }
        }
        return false;
    };

    auto do_usage = [&]() -> void
    {
        usage();
    };

    auto do_parse = [&]() -> void
    {
        int argi = -1;
        for(auto& argument : _arglist) {
            if(++argi == 0) {
                continue;
            }
            else if(opt_help(argument)) {
                continue;
            }
            else if(opt_verbose(argument)) {
                continue;
            }
            else if(opt_debug(argument)) {
                continue;
            }
            else if(opt_trace(argument)) {
                continue;
            }
            else if(opt_print(argument)) {
                continue;
            }
            else if(opt_alert(argument)) {
                continue;
            }
            else if(opt_error(argument)) {
                continue;
            }
            else if(arg_execute(argument)) {
                continue;
            }
            else if(arg_compile(argument)) {
                continue;
            }
            else if(arg_run(argument)) {
                continue;
            }
            else if(arg_clear(argument)) {
                continue;
            }
            else {
                set_expression(argument);
            }
        }
    };

    if(has_help()) {
        return do_usage();
    }
    return do_parse();
}

void Program::usage()
{
    auto do_usage = [&](std::ostream& stream) -> void
    {
        stream << "Usage:" << ' ' << _arglist[0] << ' ' << "[OPTIONS...] [EXPR [VERB]]..." << std::endl;
        stream << ""                                                                       << std::endl;
        stream << "Options:"                                                               << std::endl;
        stream << ""                                                                       << std::endl;
        stream << "    --help, -h                   display this help and exit"            << std::endl;
        stream << ""                                                                       << std::endl;
        stream << "    --verbose, --quiet           enable/disable all log messages"       << std::endl;
        stream << "    --debug, --no-debug          enable/disable debug log level"        << std::endl;
        stream << "    --trace, --no-trace          enable/disable trace log level"        << std::endl;
        stream << "    --print, --no-print          enable/disable print log level"        << std::endl;
        stream << "    --alert, --no-alert          enable/disable alert log level"        << std::endl;
        stream << "    --error, --no-error          enable/disable error log level"        << std::endl;
        stream << ""                                                                       << std::endl;
        stream << "Expr:"                                                                  << std::endl;
        stream << ""                                                                       << std::endl;
        stream << "    a valid RPN expression"                                             << std::endl;
        stream << ""                                                                       << std::endl;
        stream << "Verb:"                                                                  << std::endl;
        stream << ""                                                                       << std::endl;
        stream << "    execute                     execute an RPN expression"              << std::endl;
        stream << "    compile                     compile an RPN expression"              << std::endl;
        stream << "    run                         run the compiled expression"            << std::endl;
        stream << "    clear                       clear the stack"                        << std::endl;
        stream << ""                                                                       << std::endl;
    };
    return do_usage(_console.error_stream());
}

void Program::log_debug(const std::string& message)
{
    _console.log_debug(message);
}

void Program::log_trace(const std::string& message)
{
    _console.log_trace(message);
}

void Program::log_print(const std::string& message)
{
    _console.log_print(message);
}

void Program::log_alert(const std::string& message)
{
    _console.log_alert(message);
}

void Program::log_error(const std::string& message)
{
    _console.log_error(message);
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
