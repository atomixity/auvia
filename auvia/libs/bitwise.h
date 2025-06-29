/** bitwise.h
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

#include <libs/asm.h>
#include <libs/type.h>

/**
 * @brief Left shifts x by y bits.
 * 
 * @param x Value to shift.
 * @param y Number of bits to shift.
 * @return Shifted result.
 */
#define X_BIT_LSL(x, y)         (x ## u << (y))

/**
 * @brief Right shifts x by y bits.
 * 
 * @param x Value to shift.
 * @param y Number of bits to shift.
 * @return Shifted result.
 */
#define X_BIT_LSR(x, y)         (x ## u >> (y))

/**
 * @brief Left shifts 1u by y bits.
 * 
 * @param y Number of bits to shift.
 * @return Shifted result.
 */
#define BIT_LSL(y)              X_BIT_LSL(1, y)

/**
 * @brief Right shifts 1u by y bits.
 * 
 * @param y Number of bits to shift.
 * @return Shifted result.
 */
#define BIT_LSR(y)              X_BIT_LSR(1, y)

/**
 * @brief Sets bits in dst using (x << y).
 * 
 * @param dst Target variable.
 * @param x Value to shift.
 * @param y Shift amount.
 * @return dst with bits set.
 */
#define X_BIT_SET(dst, x, y)    (dst | X_BIT_LSL(x, y))

/**
 * @brief Clears bits in dst using (x << y).
 * 
 * @param dst Target variable.
 * @param x Value to shift.
 * @param y Shift amount.
 * @return dst with bits cleared.
 */
#define X_BIT_CLEAR(dst, x, y)  (dst & ~X_BIT_LSL(x, y))

/**
 * @brief Sets bits in dst using (1u << y).
 * 
 * @param dst Target variable.
 * @param y Shift amount.
 * @return dst with bits set.
 */
#define BIT_SET(dst, y)         X_BIT_SET(dst, 1, y)

/**
 * @brief Clears bits in dst using (1u << y).
 * 
 * @param dst Target variable.
 * @param y Shift amount.
 * @return dst with bits cleared.
 */
#define BIT_CLEAR(dst, y)       X_BIT_CLEAR(dst, 1, y)
