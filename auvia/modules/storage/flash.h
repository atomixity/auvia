/** flash.h
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

#include <libs/type.h>
#include <libs/device.h>

namespace auvia::storage {

class flash final : public device
{
public:
    flash(const usize start, const usize size)
        : device(kind::STORAGE, start, size)
        , mMemory(new u8[size])
    { }
~flash() { delete[] mMemory; }

    Variant operator[](const usize offset) override {
        if (out_of_range(offset)) {
            return trap::error(trap::kind::PAGE_FAULT);
        }
        return Variant(&mMemory[offset]);
    }

    Variant operator*(const usize offset) {
        return operator[](offset);
    }

    bool setup() override {
        return true;
    }

    bool release() override {
        return true;
    }

private:
    u8*     mMemory;
};
} // namespace auvia::storage
