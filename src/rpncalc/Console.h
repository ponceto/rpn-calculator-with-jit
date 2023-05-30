/*
 * Console.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_Console_h__
#define __RPN_Console_h__

#include "Logger.h"

// ---------------------------------------------------------------------------
// rpn::Console
// ---------------------------------------------------------------------------

namespace rpn {

class Console final
    : public Logger
{
public: // public interface
    Console(std::istream& cin, std::ostream& cout, std::ostream& cerr);

    Console(Console&&) = delete;

    Console& operator=(Console&&) = delete;

    Console(const Console&) = delete;

    Console& operator=(const Console&) = delete;

    virtual ~Console() = default;

    bool inputln(std::string& message);

    void println(const std::string& message);

    void errorln(const std::string& message);

    std::istream& input_stream() const
    {
        return _input_stream;
    }

    std::ostream& print_stream() const
    {
        return _print_stream;
    }

    std::ostream& error_stream() const
    {
        return _error_stream;
    }

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
    unsigned int  _logger_flags;
    std::istream& _input_stream;
    std::ostream& _print_stream;
    std::ostream& _error_stream;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_Console_h__ */
