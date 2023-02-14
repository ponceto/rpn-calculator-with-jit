/*
 * BasicBlock.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_BasicBlock_h__
#define __RPN_BasicBlock_h__

// ---------------------------------------------------------------------------
// rpn::BasicBlock
// ---------------------------------------------------------------------------

namespace rpn {

class BasicBlock
{
public: // public interface
    BasicBlock();

    BasicBlock(const void* begin, const void* end);

    BasicBlock(const BasicBlock&) = default;

    BasicBlock& operator=(const BasicBlock&) = default;

    virtual ~BasicBlock() = default;

    void clear();

    bool valid() const;

    void execute() const;

private: // private data
    const void* _begin;
    const void* _end;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_BasicBlock_h__ */