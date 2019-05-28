//
//  attributes.h
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
#ifndef ZALLOC_ZA_ATTRIBUTES_H
#define ZALLOC_ZA_ATTRIBUTES_H

#ifdef __GNUC__
    /**
     * Defines a generic attribute that marks a function as being malloc-like.
     * This implementation uses the GCC malloc attribute.
     */
    #define za_malloc __attribute__((malloc))

    /**
     * Defines a generic attribute that marks a function as being pure; that is, it has no observable side effects.
     * This implementation uses the GCC const attribute.
     */
    #define za_pure __attribute__((const))

    /**
     * Defines a generic attribute that marks parameters of a function as being nonnull; that is, they must never
     * take on a null value.
     * This implementation uses the GCC nonnull attribute.
     */
    #define za_nonnull(...) __attribute__((nonnull(__VA_ARGS__)))

    /**
     * Defines a generic attribute that specifies that it is an error for the programmer to not use the return value
     * of the function.
     * This implementation uses the GCC warn_unused_result attribute.
     */
    #define za_donotdiscard __attribute((warn_unused_result))

    #if __GNUC__ > 4
        /**
         * Defines a generic attribute that marks a type or function as only being visible within the current DSO.
         * This implementation uses the GCC visibility attribute.
         */
        #define za_internal __attribute((visibility("hidden")))

        /**
         * Defines a generic attribute that marks a type or function as being visible outside of the current DSO.
         * This implementation uses the GCC visibility attribute.
         */
        #define za_public __attribute__((visibility("default")))
    #endif
#endif

#ifdef _MSC_VER
    #define za_public __declspec(dllexport)
#endif

/**
 * Empty placeholder attribute definitions.
 */

#ifndef za_donotdiscard
    #define za_donotdiscard
#endif

#ifndef za_nonnull
    #define za_nonnull
#endif

#ifndef za_pure
    #define za_pure
#endif

#ifndef za_malloc
    #define za_malloc
#endif

#ifndef za_internal
    #define za_internal
#endif

#ifndef za_public
    #define za_public
#endif

#endif //ZALLOC_ZA_ATTRIBUTES_H
