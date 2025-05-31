/** matu.h
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

#include <libs/type.h>
#include <libs/device.h>
#include <libs/trap.h>

namespace bus {

class matu
{
public:
    typedef std::pair<bool, device*>    dev_tuple_t;

    matu() = default;
~matu();

    Variant operator[](const addr_t va);
    Variant operator*(const addr_t va);

    usize   attach(device* const new_dev);
    device* detach(const usize dev_type);
    void    setup_devices();
    device* get_device_or_null(const usize dev_type);
    device* find_device_or_null(const addr_t va);

private:
    Variant translate(addr_t va);

    /* XXX: consider using std::vector */
    dev_tuple_t mDevs[device::NR_TYPES];
}; // class mtu

} // namespace bus
