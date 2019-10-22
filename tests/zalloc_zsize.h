//
//  zsize_size.h
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

#ifndef ZALLOC_META_ZALLOC_ZSIZE_H
#define ZALLOC_META_ZALLOC_ZSIZE_H

#include <zalloc/zalloc.h>
#include <errno.h>

#include "check.h"

START_TEST(zsize_can_get_size)
{
    size_t size = 64;
    void* bytes = zalloc(size);

    size_t storedSize = zsize(bytes);
    ck_assert(size == storedSize);

    // Cleanup
    zfree(&bytes);
}
END_TEST

START_TEST(zsize_returns_zero_if_memory_was_not_allocated_with_zalloc)
{
    void* bytes = malloc(64);

    ck_assert(zsize(bytes) == 0);

    // Cleanup
    free(bytes);
}
END_TEST

START_TEST(zsize_sets_correct_errno_if_memory_was_not_allocated_with_zalloc)
{
    void* bytes = calloc(1, 64);

    size_t size = zsize(bytes);
    ck_assert(errno == ZERR_BAD_MAGIC);

    // Cleanup
    free(bytes);
}
END_TEST

#endif //ZALLOC_META_ZALLOC_ZSIZE_H
