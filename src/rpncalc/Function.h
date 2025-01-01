/*
 * Function.h - Copyright (c) 2023-2025 - Olivier Poncet
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
#ifndef __RPN_Function_h__
#define __RPN_Function_h__

#include "BasicBlock.h"

// ---------------------------------------------------------------------------
// rpn::Function
// ---------------------------------------------------------------------------

namespace rpn {

class Function
{
public: // public interface
    Function();

    Function(Function&&) = delete;

    Function& operator=(Function&&) = delete;

    Function(const Function&) = delete;

    Function& operator=(const Function&) = delete;

    virtual ~Function() = default;

    bool callable() const;

    void execute() const;

    void clear();

    void add(const BasicBlock& basic_block);

private: // private data
    std::vector<BasicBlock> _basic_blocks;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_BasicBlock_h__ */
