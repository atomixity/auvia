/** asm.h
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

#if defined(__GNUC__)

#define __barrier__(...)    asm volatile("" ::: "memory")

#define __used__            __attribute__((used))
#define __pack__            __attribute__((pack))
#define __noinline__        __attribute__((noinline))
#define __always_inline__   inline __attribute__((always_inline))

#else /* !__GNUC__ */

#define __barrier__(...)

#define __used__
#define __pack__
#define __noinline__
#define __always_inline__   inline

#endif /* __GNUC__ */

/* compile-time assert */
#define BUILD_BUG_ON(condition) (sizeof(char[1 - 2*!!(condition)]))
