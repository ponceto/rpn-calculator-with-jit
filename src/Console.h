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

// ---------------------------------------------------------------------------
// rpn::Console
// ---------------------------------------------------------------------------

namespace rpn {

class Console
{
public: // public interface
    Console(std::istream& cin, std::ostream& cout, std::ostream& cerr);

    Console(const Console&) = delete;

    Console& operator=(const Console&) = delete;

    virtual ~Console() = default;

    void log_debug(const std::string& message);

    void log_trace(const std::string& message);

    void log_print(const std::string& message);

    void log_alert(const std::string& message);

    void log_error(const std::string& message);

    void set_debug(const bool enabled);

    void set_trace(const bool enabled);

    void set_print(const bool enabled);

    void set_alert(const bool enabled);

    void set_error(const bool enabled);

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

private: // private static data
    static constexpr int FL_ALL   = (~0);
    static constexpr int FL_NONE  = 0x00;
    static constexpr int FL_DEBUG = 0x01;
    static constexpr int FL_TRACE = 0x02;
    static constexpr int FL_PRINT = 0x04;
    static constexpr int FL_ALERT = 0x08;
    static constexpr int FL_ERROR = 0x10;

private: // private data
    int           _flags;
    std::istream& _input_stream;
    std::ostream& _print_stream;
    std::ostream& _error_stream;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_Console_h__ */
