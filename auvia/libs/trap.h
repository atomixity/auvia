/** trap.h
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

#include <cstdlib>

#include <libs/asm.h>
#include <libs/type.h>

struct trap
{
public:
    enum class kind {
        NODEV       = -1,
        PAGE_FAULT  = -2,
        BUSERR      = -3,
    };

    static inline Variant error(trap::kind errno) {
        return Variant(static_cast<phys_t>(errno));
    }

    static inline bool has_err(Variant& pa) {
        switch ((trap::kind)static_cast<phys_t>(pa)) {
        case kind::NODEV:
        case kind::PAGE_FAULT:
        case kind::BUSERR:
            return true;
        default:
            return false;
        }
    }

    static inline const char* kind_of(Variant& pa) {
        switch ((trap::kind)static_cast<phys_t>(pa)) {
        case kind::NODEV:
            return "no such device";
        case kind::PAGE_FAULT:
            return "page fault";
        case kind::BUSERR:
            return "bus error";
        default:
            return "unknown fault";
        }
    }
};

#define panic(fmt, ...)                             \
    do {                                            \
        fprintf(stderr, fmt "\n", ##__VA_ARGS__);   \
        std::abort();                               \
    } while(false)

#define debug(...)              \
    do {                        \
        for(;;) __barrier__();  \
    } while(false)
