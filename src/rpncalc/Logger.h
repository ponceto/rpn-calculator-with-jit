/*
 * Logger.h - Copyright (c) 2023-2025 - Olivier Poncet
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
#ifndef __RPN_Logger_h__
#define __RPN_Logger_h__

// ---------------------------------------------------------------------------
// rpn::Logger
// ---------------------------------------------------------------------------

namespace rpn {

class Logger
{
public: // public interface
    Logger() = default;

    virtual ~Logger() = default;

    virtual void log_debug(const std::string& message) = 0;

    virtual void log_trace(const std::string& message) = 0;

    virtual void log_print(const std::string& message) = 0;

    virtual void log_alert(const std::string& message) = 0;

    virtual void log_error(const std::string& message) = 0;

    virtual void set_debug(const bool enabled) = 0;

    virtual void set_trace(const bool enabled) = 0;

    virtual void set_print(const bool enabled) = 0;

    virtual void set_alert(const bool enabled) = 0;

    virtual void set_error(const bool enabled) = 0;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_Logger_h__ */
