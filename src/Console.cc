/*
 * Console.cc - Copyright (c) 2023 - Olivier Poncet
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
// <anonymous>::stuff
// ---------------------------------------------------------------------------

namespace {

const std::string LOG_DEBUG("🟣");
const std::string LOG_TRACE("🔵");
const std::string LOG_PRINT("🟢");
const std::string LOG_ALERT("🟡");
const std::string LOG_ERROR("🔴");

}

// ---------------------------------------------------------------------------
// rpn::Console
// ---------------------------------------------------------------------------

namespace rpn {

Console::Console(std::istream& cin, std::ostream& cout, std::ostream& cerr)
    : _flags(FL_ALL)
    , _input_stream(cin)
    , _print_stream(cout)
    , _error_stream(cerr)
{
}

void Console::log_debug(const std::string& message)
{
    if(_flags & FL_DEBUG) {
        _print_stream << LOG_DEBUG << ' ' << message << std::endl;
    }
}

void Console::log_trace(const std::string& message)
{
    if(_flags & FL_TRACE) {
        _print_stream << LOG_TRACE << ' ' << message << std::endl;
    }
}

void Console::log_print(const std::string& message)
{
    if(_flags & FL_PRINT) {
        _print_stream << LOG_PRINT << ' ' << message << std::endl;
    }
}

void Console::log_alert(const std::string& message)
{
    if(_flags & FL_ALERT) {
        _error_stream << LOG_ALERT << ' ' << message << std::endl;
    }
}

void Console::log_error(const std::string& message)
{
    if(_flags & FL_ERROR) {
        _error_stream << LOG_ERROR << ' ' << message << std::endl;
    }
}

void Console::set_debug(const bool enabled)
{
    if(enabled != false) {
        _flags |= FL_DEBUG;
    }
    else {
        _flags &= ~FL_DEBUG;
    }
}

void Console::set_trace(const bool enabled)
{
    if(enabled != false) {
        _flags |= FL_TRACE;
    }
    else {
        _flags &= ~FL_TRACE;
    }
}

void Console::set_print(const bool enabled)
{
    if(enabled != false) {
        _flags |= FL_PRINT;
    }
    else {
        _flags &= ~FL_PRINT;
    }
}

void Console::set_alert(const bool enabled)
{
    if(enabled != false) {
        _flags |= FL_ALERT;
    }
    else {
        _flags &= ~FL_ALERT;
    }
}

void Console::set_error(const bool enabled)
{
    if(enabled != false) {
        _flags |= FL_ERROR;
    }
    else {
        _flags &= ~FL_ERROR;
    }
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
