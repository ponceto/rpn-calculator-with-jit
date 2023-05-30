/*
 * Parser.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_Parser_h__
#define __RPN_Parser_h__

#include "Listener.h"

// ---------------------------------------------------------------------------
// rpn::Parser
// ---------------------------------------------------------------------------

namespace rpn {

class Parser
{
public: // public interface
    Parser(Listener&);

    Parser(Parser&&) = delete;

    Parser& operator=(Parser&&) = delete;

    Parser(const Parser&) = delete;

    Parser& operator=(const Parser&) = delete;

    virtual ~Parser() = default;

    void parse(std::istream& stream);

    void parse(const std::string& string);

private: // private data
    Listener& _listener;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_Parser_h__ */
