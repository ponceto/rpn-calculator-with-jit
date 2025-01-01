/*
 * Buffer.cc - Copyright (c) 2023-2025 - Olivier Poncet
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
#include "Buffer.h"

// ---------------------------------------------------------------------------
// rpn::Buffer
// ---------------------------------------------------------------------------

namespace rpn {

Buffer::Buffer()
    : _buffer(nullptr)
    , _bufptr(nullptr)
    , _buflen(0)
{
}

void Buffer::clear(const uint8_t value)
{
    auto fill = [&](uint8_t* begin, uint8_t* end, uint8_t value) -> void
    {
        if((begin != nullptr) && (end != nullptr)) {
            std::fill(begin, end, value);
        }
    };

    return fill((_bufptr = _buffer), (_buffer + _buflen), value);
}

void Buffer::write(const uint8_t value)
{
    if(_bufptr < (_buffer + _buflen)) {
        *_bufptr++ = value;
    }
    else {
        throw std::runtime_error("buffer is full");
    }
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
