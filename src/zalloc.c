//
//  zalloc.c
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

#include "zalloc.h"

#include "internal/zmem_header.h"
#include "internal/helpers.h"

#include <malloc.h>
#include <errno.h>
#include <string.h>

void* zalloc(size_t size)
{
    // Guard against overflows later down the line if some idiot passes negative values
    if ((size + sizeof(zmem_header_t)) < size)
    {
        errno = ZERR_INVALID_SIZE;
        return NULL;
    }

    // Allocating zero-sized blocks is not allowed
    if (size < 1)
    {
        errno = ZERR_INVALID_SIZE;
        return NULL;
    }

    // calloc might return a nullptr if we're out of memory, so check for that
    void* mem = calloc(size + sizeof(zmem_header_t), 1);
    if (mem == NULL)
    {
        return NULL;
    }

    zmem_header_t* header = (zmem_header_t*)mem;
    zmem_header(header, size);

    return (char*)mem + sizeof(zmem_header_t);
}

bool zfree(void** mem)
{
    if (mem == NULL)
    {
        errno = ZERR_INVALID_HANDLE;
        return false;
    }

    zmem_header_t* header = NULL;
    if (!try_get_zmem_header(*mem, &header))
    {
        return false;
    }

    size_t size = header->size;

    char* actual_start = ((*(char**)mem) - sizeof(zmem_header_t));
    secure_erase((void*)actual_start, size + sizeof(zmem_header_t));

    free((void*)actual_start);
    *mem = NULL;

    return true;
}

size_t zsize(const void* mem)
{
    zmem_header_t* header = NULL;
    if (!try_get_zmem_header(mem, &header))
    {
        return false;
    }

    return header->size;
}
