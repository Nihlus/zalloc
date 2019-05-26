//
//  zmem_header.h
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

#ifndef ZALLOC_ZMEM_HEADER_H
#define ZALLOC_ZMEM_HEADER_H

#include <stddef.h>
#include <stdint.h>

/**
 * Defines the magic signature for zmem blocks.
 */
#define ZMEM_HEADER_MAGIC 0xBEEF

/**
 * Defines a header for memory blocks allocated with @see zalloc.
 */
typedef struct zmem_header
{
    /**
     * A magic signature for zmem blocks. Always @see ZMEM_HEADER_MAGIC.
     */
    int32_t magic;

    /**
     * The size (in bytes) of the allocated memory block that immediately follows the header.
     */
    size_t size;
} zmem_header_t;

/**
 * Initializes a new instance of the @see zmem_header_t structure.
 */
void zmem_header(zmem_header_t* header, size_t size)
{
    header->magic = ZMEM_HEADER_MAGIC;
    header->size = size;
}

#endif //ZALLOC_ZMEM_HEADER_H
