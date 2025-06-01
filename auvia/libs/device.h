/** device.h
 *
 *  Copyright (C) 2025 Leesoo Ahn <lsahn@ooseel.net>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <utility>

#include <libs/asm.h>
#include <libs/type.h>

namespace auvia {

class device
{
public:
    enum kind {
        UNKNOWN = 0,
        CPU,
        MEMORY,
        STORAGE,
        IODEV,

        NR_TYPES,
    };

    typedef std::pair<usize, usize>     mmio_range;

public:
    device(const usize dev_type)
        : mType(dev_type)
    { }
    device(const usize dev_type, const usize start, const usize size)
        : mType(dev_type)
        , mAddrRange(mmio_range(start, size))
    { }
~device() = default;

    virtual Variant operator[](const usize offset) = 0;
    virtual bool    setup() = 0;
    virtual bool    release() = 0;

    void inline mmio_new_range(const usize start, const usize size) {
        mAddrRange.first = start;
        mAddrRange.second = size;
    }

    __always_inline__ usize mmio_start() {
        return mAddrRange.first;
    }

    __always_inline__ usize mmio_end() {
        return (mAddrRange.first + mAddrRange.second);
    }

    __always_inline__ bool has_range_of(const usize addr) {
        return (mmio_start() <= addr && addr < mmio_end());
    }

    __always_inline__ bool out_of_range(const usize addr) {
        return !has_range_of(addr);
    }

    __always_inline__ usize get_type() {
        return mType;
    }

private:
    usize       mType;
    mmio_range  mAddrRange;
};
} // namespace auvia
