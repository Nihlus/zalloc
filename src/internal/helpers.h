//
//  helpers.h
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

#ifndef ZALLOC_HELPERS_H
#define ZALLOC_HELPERS_H

#include <stdlib.h>
#include <string.h>

#ifndef nullptr
    #define nullptr NULL
#endif

#define __STDC_WANT_LIB_EXT1__ 1

/**
 * Securely(ish) erases a block of memory by zeroing it out, and ensuring optimiztions don't mess with our results.
 * @param pointer A pointer to the start of the block to erase.
 * @param size_data The size of the data.
 * @remarks Big thanks to Robert Seacord and David Wong over at
 * https://www.cryptologie.net/article/419/zeroing-memory-compiler-optimizations-and-memset_s/ for providing this
 * technique and a detailed explanation to boot. Minor changes have been made to simplify the usage.
 */
void secure_erase(void* pointer, size_t size)
{
    #ifdef __STDC_LIB_EXT1__
        memset_s(pointer, size, 0, size);
    #else
        volatile unsigned char *p = pointer;
        while (size--)
        {
            *p++ = 0;
        }
    #endif
}

#endif //ZALLOC_HELPERS_H
