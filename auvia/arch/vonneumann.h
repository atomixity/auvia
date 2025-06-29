/** vonneumann.h
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

#include <modules/bus/matu.h>

namespace auvia::arch {

/**
 * @brief Represents von Neumann architecture.
 */
class vonneumann
{
public:
    vonneumann() = default;
~vonneumann() = default;

protected:
    bus::matu   mCpuBus; /* {instruction, data} bus */
};
} // namespace auvia::arch
