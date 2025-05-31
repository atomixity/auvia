/** types.h
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

#include <cstdio>
#include <cstdint>

#include <libs/asm.h>

typedef int8_t      s8;
typedef int16_t     s16;
typedef int32_t     s32;
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;

typedef size_t      usize;
typedef ssize_t     ssize;

#if !defined(addr_t)
/**
 * @brief Represents vMCU address space.
 *
 * Note: default is uint32_t, but platform independent.
 */
#define addr_t      uint32_t
#endif
typedef uintptr_t   phys_t;


/**
 * @brief high-performance flexible Variant type.
 *
 * Supports:
 * - u8, u16, and u32   (unsigned)
 * - s8, s16, and s32   (signed)
 * - phys_t             (host virt-addr)
 * - void*              (as input, and address-of)
 */
struct Variant 
{
public:
    Variant(phys_t p): pa(p) { }
    Variant(void* p) : res1(p) { }
~Variant() = default;

    /* unsigned */
    operator u8()                   { return *pu8; }
    operator u16()                  { return *pu16; }
    operator u32()                  { return *pu32; }
    Variant& operator=(u8 val)      { *pu8 = val; return *this; }
    Variant& operator=(u16 val)     { *pu16 = val; return *this; }
    Variant& operator=(u32 val)     { *pu32 = val; return *this; }

    /* signed */
    operator s8()                   { return *ps8; }
    operator s16()                  { return *ps16; }
    operator s32()                  { return *ps32; }
    Variant& operator=(s8 val)      { *ps8 = val; return *this; }
    Variant& operator=(s16 val)     { *ps16 = val; return *this; }
    Variant& operator=(s32 val)     { *ps32 = val; return *this; }

    /* host virt-addr */
    operator phys_t()               { return pa; }
    Variant& operator=(phys_t val)  { pa = val; return *this; }

    /* address-of operator */
    void*    operator&()            { return res1; }

private:
    union {
        u8*     pu8;
        u16*    pu16;
        u32*    pu32;
        s8*     ps8;
        s16*    ps16;
        s32*    ps32;

        phys_t  pa;
        void*   res1;
    };

private:
    /* issue if this fails at compile-time */
    Variant() : pa(BUILD_BUG_ON(sizeof(Variant) % sizeof(void*))) { }
}; // struct Variant
    