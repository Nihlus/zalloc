//
//  zalloc_zfree.h
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

#ifndef ZALLOC_META_ZALLOC_ZFREE_H
#define ZALLOC_META_ZALLOC_ZFREE_H

#include <zalloc/zalloc.h>

#include "check.h"

START_TEST(zfree_can_free)
{
    zmem_t bytes = zalloc(64);
    ck_assert(zfree(&bytes));
}
END_TEST

START_TEST(zfree_actually_zeroes)
{
    zmem_t bytes = zalloc(64);
    memset(bytes, 0xF, 64);
    for (int i = 0; i < 64; ++i)
    {
        ck_assert_int_eq(bytes[i], 0xF);
    }

    zmem_t ptrCopy = bytes;
    zfree(&bytes);

    for (int i = 0; i < 64; ++i)
    {
        ck_assert_int_eq(ptrCopy[i], 0);
    }
}
END_TEST

START_TEST(zfree_returns_false_if_memory_was_not_allocated_with_zalloc)
{
    zmem_t bytes = calloc(1, 64);

    ck_assert(!zfree(&bytes));

    // Cleanup
    free(bytes);
}
END_TEST

START_TEST(zfree_sets_correct_errno_if_memory_was_not_allocated_with_zalloc)
{
    zmem_t bytes = calloc(1, 64);

    zfree(&bytes);
    ck_assert(errno == ZERR_BAD_MAGIC);

    // Cleanup
    free(bytes);
}
END_TEST

START_TEST(zfree_returns_false_if_memory_pointer_is_null)
{
    ck_assert(!zfree(NULL));
}
END_TEST

START_TEST(zfree_sets_correct_errno_if_memory_pointer_is_null)
{
    zfree(NULL);
    ck_assert(errno == ZERR_INVALID_HANDLE);
}
END_TEST

#endif //ZALLOC_META_ZALLOC_ZFREE_H
