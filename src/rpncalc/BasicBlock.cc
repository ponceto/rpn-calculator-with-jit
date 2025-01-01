/*
 * BasicBlock.cc - Copyright (c) 2023-2025 - Olivier Poncet
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
// <anonymous>::PointerToFunction
// ---------------------------------------------------------------------------

namespace {

using PointerToFunction = void(*)(void);

}

// ---------------------------------------------------------------------------
// rpn::BasicBlock
// ---------------------------------------------------------------------------

namespace rpn {

BasicBlock::BasicBlock()
    : _begin(nullptr)
    , _end(nullptr)
{
}

void BasicBlock::begin(const uint8_t* begin)
{
    if(_begin == nullptr) {
        _begin = begin;
    }
    else {
        throw std::runtime_error("basic block already has a beginning");
    }
}

void BasicBlock::end(const uint8_t* end)
{
    if(_end == nullptr) {
        _end = end;
    }
    else {
        throw std::runtime_error("basic block already has an end");
    }
}

void BasicBlock::reset()
{
    _begin = nullptr;
    _end   = nullptr;
}

bool BasicBlock::valid() const
{
    if((_begin != nullptr) && (_end != nullptr) && (_begin < _end)) {
        return true;
    }
    return false;
}

void BasicBlock::execute() const
{
    PointerToFunction function = reinterpret_cast<PointerToFunction>(const_cast<uint8_t*>(_begin));

    if((_begin != nullptr) && (_end != nullptr) && (_begin < _end)) {
        (*function)();
    }
    else {
        throw std::runtime_error("cannot execute invalid basic block");
    }
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
