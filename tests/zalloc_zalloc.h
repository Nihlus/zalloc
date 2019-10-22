//
//  base.h
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
#ifndef ZALLOC_META_ZALLOC_ZALLOC_H
#define ZALLOC_META_ZALLOC_ZALLOC_H

#include <errno.h>
#include <zalloc/zalloc.h>
#include "check.h"

START_TEST(zalloc_can_allocate)
{
    void* bytes = zalloc(64);

    ck_assert_ptr_ne(bytes, NULL);
    zfree(&bytes);
}
END_TEST

START_TEST(zalloc_returns_null_for_zero)
{
    void* bytes = zalloc(0);
    ck_assert_ptr_eq(bytes, NULL);
}
END_TEST

START_TEST(zalloc_sets_correct_errno_for_zero)
{
    void* bytes = zalloc(0);
    ck_assert_int_eq(errno, ZERR_INVALID_SIZE);
}
END_TEST

START_TEST(zalloc_returns_null_for_negative_values)
{
    void* bytes = zalloc(-1);
    ck_assert_ptr_eq(bytes, NULL);
}
END_TEST

START_TEST(zalloc_sets_correct_errno_for_negative_values)
{
    void* bytes = zalloc(-1);
    ck_assert_int_eq(errno, ZERR_INVALID_SIZE);
}
END_TEST

#endif //ZALLOC_META_ZALLOC_ZALLOC_H
