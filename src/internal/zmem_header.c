//
//  zmem_header.c
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

#include <errno.h>
#include <assert.h>

#include "zalloc.h"
#include "zmem_header.h"
#include "helpers.h"

void zmem_header(zmem_header_t* header, size_t size)
{
    header->magic = ZMEM_HEADER_MAGIC;
    header->size = size;
}

bool try_get_zmem_header(const_zmem_t mem, const zmem_header_t** header)
{
    if (header == NULL)
    {
        errno = ZERR_INVALID_HANDLE;
        return false;
    }

    if (*header != NULL)
    {
        errno = ZERR_INVALID_HANDLE;
        return false;
    }

    if (mem == NULL)
    {
        errno = ZERR_INVALID_HANDLE;
        return false;
    }

    const_zmem_t actual_start = mem - sizeof(zmem_header_t);
    const zmem_header_t* found_header = (const zmem_header_t*)actual_start;
    if (found_header->magic != ZMEM_HEADER_MAGIC)
    {
        errno = ZERR_BAD_MAGIC;
        return false;
    }

    *header = found_header;
    return true;
}
