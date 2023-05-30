/*
 * Buffer.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_Buffer_h__
#define __RPN_Buffer_h__

// ---------------------------------------------------------------------------
// rpn::Buffer
// ---------------------------------------------------------------------------

namespace rpn {

class Buffer
{
public: // public interface
    Buffer();

    Buffer(Buffer&&) = delete;

    Buffer(const Buffer&) = delete;

    Buffer& operator=(const Buffer&) = delete;

    virtual ~Buffer() = default;

    const uint8_t* begin() const
    {
        return _buffer;
    }

    const uint8_t* end() const
    {
        return _bufptr;
    }

    void reset(const uint8_t value);

    void write(const uint8_t value);

protected: // protected data
    uint8_t* _buffer;
    uint8_t* _bufptr;
    size_t   _buflen;
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_Buffer_h__ */
