//
//  zalloc.h
//
//  Author:
//       Jarl Gullberg <jarl.gullberg@gmail.com>
//
//  Copyright (c) 2019 Jarl Gullberg
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef ZALLOC_ZALLOC_H
#define ZALLOC_ZALLOC_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "za_attributes.h"

/**
 * Set when an invalid size (typically 0) is passed to @see zalloc.
 */
#define ZERR_INVALID_SIZE (1u << 0u)

/**
 * Set when an invalid handle (typically null in one form or another) is passed to @see zfree.
 */
#define ZERR_INVALID_HANDLE (1u << 1u)

/**
 * Set when a handle that was not allocated by @see zalloc is passed to a zalloc function.
 */
#define ZERR_BAD_MAGIC (1u << 2u)

/**
 * Defines a pointer a block of memory allocated by zalloc.
 */
typedef uint8_t* zmem_t;

/**
 * Defines a constant pointer to a block of memory allocated by zalloc.
 */
typedef const uint8_t* const_zmem_t;

/**
 * Allocates a block of zero-initialized memory.
 * @param size The size (in bytes) of the block that is to be allocated.
 * @return A pointer to the block, or @see nullptr.
 * @remarks In the case of an error where zalloc returns nullptr, examine @see errno for more information. The possible
 * values errno can take on include @see ZERR_INVALID_SIZE (which is set when @see size is 0), as well as any error
 * codes @see calloc can set.
 */
za_malloc za_public za_donotdiscard zmem_t zalloc(size_t size);

/**
 * Frees a block of memory allocated by @see zalloc, zeroes its full span, and sets the referenced pointer to null.
 * @param mem A reference to the pointer that points to the start of the allocated data block.
 * @return true if the memory was successfully freed; otherwise, false.
 * @remarks In the case of an error where zfree returns false, examine @see errno for more information. The possible
 * values errno can take on include @see ZERR_INVALID_HANDLE (which is set when @see mem is either null itself or
 * points to a null value) or @see ZERR_BAD_MAGIC (which is set when the passed pointer wasn't allocated by @see zalloc.
 */
za_public za_nonnull(1) za_donotdiscard bool zfree(zmem_t* mem);

/**
 * Determines the size of the given memory block allocated by @see zalloc.
 * @param mem A pointer to the start of the allocated data block.
 * @return The size of the allocated data block, or 0 if no size could be determined.
 * @remarks In the case of an error where no size could be determined, examine @see errno for more information. The
 * possible values errno can take on include @see ZERR_INVALID_HANDLE (which is set when @see mem is null or @see
 * ZERR_BAD_MAGIC (which is set when the passed pointer wasn't allocated by @see zalloc.
 */
za_public za_pure za_nonnull(1) size_t zsize(const_zmem_t mem);

#endif //ZALLOC_ZALLOC_H
