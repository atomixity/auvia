/** matu.cc
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

#include "matu.h"

namespace bus {

matu::~matu()
{
    for (auto& dev : mDevs) {
        if (dev.first) {
            dev.second->release();
        }
    }
}

usize matu::attach(device* const new_dev)
{
    auto& dev = mDevs[new_dev->get_type()];

    dev.first = true;
    dev.second = new_dev;

    return new_dev->get_type();
}

device* matu::detach(const usize dev_type)
{
    auto& dev = mDevs[dev_type];
    device* old = dev.second;
    __barrier__();

    dev.first = false;
    dev.second = nullptr;

    return old;
}

void matu::setup_devices()
{
    for (auto& dev : mDevs) {
        if (dev.first == true) {
            device* rd = dev.second;
            rd->setup();
        }
    }
}

device* matu::get_device_or_null(const usize dev_type)
{
    auto& box = mDevs[dev_type];

    if (box.first == true) {
        return box.second;
    }

    return nullptr;
}

device* matu::find_device_or_null(const addr_t va)
{
    /* TODO: fastpath: use cache */

    /* slowpath: iterate on devices */
    for (auto& dev : mDevs) {
        if (dev.first == false) {
            continue;
        }

        device* rd = dev.second;
        if (rd->has_range_of(va)) {
            return rd;
        }
    }

    return nullptr;
}

Variant matu::operator[](const addr_t va)
{
    Variant addr = translate(va);
    if (trap::has_err(addr)) {
        panic("Unhandled %s: va(0x%x)", trap::kind_of(addr), va);
    }
    return addr;
}

Variant matu::operator*(const addr_t va)
{
    return operator[](va);
}

Variant matu::translate(addr_t va)
{
    device* dev = find_device_or_null(va);
    if (dev == nullptr) {
        return trap::error(trap::kind::NODEV);
    }

    return (*dev)[va];
}

} // namespace bus
