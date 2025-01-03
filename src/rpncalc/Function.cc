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
#include "Function.h"

// ---------------------------------------------------------------------------
// rpn::Function
// ---------------------------------------------------------------------------

namespace rpn {

Function::Function()
    : _basic_blocks()
{
}

bool Function::callable() const
{
    if(_basic_blocks.empty()) {
        return false;
    }
    return true;
}

void Function::execute() const
{
    if(_basic_blocks.size() > 0) {
        const auto& basic_block(*_basic_blocks.begin());
        basic_block.execute();
    }
    else {
        throw std::runtime_error("cannot execute empty function");
    }

}

void Function::clear()
{
    _basic_blocks.clear();
}

void Function::add(const BasicBlock& basic_block)
{
    _basic_blocks.push_back(basic_block);
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
