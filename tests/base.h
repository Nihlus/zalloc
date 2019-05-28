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
#ifndef ZALLOC_META_BASE_H
#define ZALLOC_META_BASE_H

#include <zalloc/zalloc.h>
#include "check.h"

START_TEST(can_allocate)
{
    void* bytes = zalloc(64);

    ck_assert_ptr_ne(bytes, NULL);
    zfree(&bytes);
}
END_TEST

START_TEST(can_free)
{
    void* bytes = zalloc(64);
    ck_assert(zfree(&bytes));
}
END_TEST


#endif //ZALLOC_META_BASE_H
