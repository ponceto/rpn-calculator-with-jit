/*
 * Console.cc - Copyright (c) 2023-2025 - Olivier Poncet
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
#include "Console.h"

// ---------------------------------------------------------------------------
// <anonymous>::LOG
// ---------------------------------------------------------------------------

namespace {

const std::string LOG_DEBUG("🟣");
const std::string LOG_TRACE("🔵");
const std::string LOG_PRINT("🟢");
const std::string LOG_ALERT("🟡");
const std::string LOG_ERROR("🔴");

}

// ---------------------------------------------------------------------------
// <anonymous>::Flags
// ---------------------------------------------------------------------------

namespace {

struct Flags
{
    static constexpr unsigned int FL_ALL   = (~0);
    static constexpr unsigned int FL_NONE  = 0x00;
    static constexpr unsigned int FL_DEBUG = 0x01;
    static constexpr unsigned int FL_TRACE = 0x02;
    static constexpr unsigned int FL_PRINT = 0x04;
    static constexpr unsigned int FL_ALERT = 0x08;
    static constexpr unsigned int FL_ERROR = 0x10;
};

}

// ---------------------------------------------------------------------------
// rpn::Console
// ---------------------------------------------------------------------------

namespace rpn {

Console::Console(std::istream& cin, std::ostream& cout, std::ostream& cerr)
    : Logger()
    , _logger_flags(Flags::FL_ALL)
    , _input_stream(cin)
    , _print_stream(cout)
    , _error_stream(cerr)
{
}

bool Console::inputln(std::string& message)
{
    std::istream& stream(_input_stream);

    if(stream.good()) {
        static_cast<void>(std::getline(stream, message));
        return true;
    }
    return false;
}

void Console::println(const std::string& message)
{
    std::ostream& stream(_print_stream);

    if(stream.good()) {
        stream << message << std::endl;
    }
}

void Console::errorln(const std::string& message)
{
    std::ostream& stream(_error_stream);

    if(stream.good()) {
        stream << message << std::endl;
    }
}

void Console::log_debug(const std::string& message)
{
    std::ostream& stream(_print_stream);

    if(stream.good() && (_logger_flags & Flags::FL_DEBUG)) {
        stream << LOG_DEBUG << ' ' << message << std::endl;
    }
}

void Console::log_trace(const std::string& message)
{
    std::ostream& stream(_print_stream);

    if(stream.good() && (_logger_flags & Flags::FL_TRACE)) {
        stream << LOG_TRACE << ' ' << message << std::endl;
    }
}

void Console::log_print(const std::string& message)
{
    std::ostream& stream(_print_stream);

    if(stream.good() && (_logger_flags & Flags::FL_PRINT)) {
        stream << LOG_PRINT << ' ' << message << std::endl;
    }
}

void Console::log_alert(const std::string& message)
{
    std::ostream& stream(_error_stream);

    if(stream.good() && (_logger_flags & Flags::FL_ALERT)) {
        stream << LOG_ALERT << ' ' << message << std::endl;
    }
}

void Console::log_error(const std::string& message)
{
    std::ostream& stream(_error_stream);

    if(stream.good() && (_logger_flags & Flags::FL_ERROR)) {
        stream << LOG_ERROR << ' ' << message << std::endl;
    }
}

void Console::set_debug(const bool enabled)
{
    if(enabled != false) {
        _logger_flags |= Flags::FL_DEBUG;
    }
    else {
        _logger_flags &= ~Flags::FL_DEBUG;
    }
}

void Console::set_trace(const bool enabled)
{
    if(enabled != false) {
        _logger_flags |= Flags::FL_TRACE;
    }
    else {
        _logger_flags &= ~Flags::FL_TRACE;
    }
}

void Console::set_print(const bool enabled)
{
    if(enabled != false) {
        _logger_flags |= Flags::FL_PRINT;
    }
    else {
        _logger_flags &= ~Flags::FL_PRINT;
    }
}

void Console::set_alert(const bool enabled)
{
    if(enabled != false) {
        _logger_flags |= Flags::FL_ALERT;
    }
    else {
        _logger_flags &= ~Flags::FL_ALERT;
    }
}

void Console::set_error(const bool enabled)
{
    if(enabled != false) {
        _logger_flags |= Flags::FL_ERROR;
    }
    else {
        _logger_flags &= ~Flags::FL_ERROR;
    }
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
