/*
 * BasicBlock.cc - Copyright (c) 2023 - Olivier Poncet
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
#include "BasicBlock.h"

// ---------------------------------------------------------------------------
// <anonymous>::FunctionPtr
// ---------------------------------------------------------------------------

namespace {

using FunctionPtr = void(*)(void);

}

// ---------------------------------------------------------------------------
// rpn::BasicBlock
// ---------------------------------------------------------------------------

namespace rpn {

BasicBlock::BasicBlock()
    : BasicBlock(nullptr, nullptr)
{
}

BasicBlock::BasicBlock(const uint8_t* start, const uint8_t* end)
    : _start(start)
    , _end(end)
{
}

void BasicBlock::reset()
{
    _start = nullptr;
    _end   = nullptr;
}

bool BasicBlock::valid() const
{
    if((_start != nullptr) && (_end != nullptr) && (_start < _end)) {
        return true;
    }
    return false;
}

void BasicBlock::execute() const
{
    FunctionPtr function = reinterpret_cast<FunctionPtr>(const_cast<uint8_t*>(_start));

    if(function != nullptr) {
        (*function)();
    }
    else {
        throw std::runtime_error("cannot execute null basic block");
    }
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
