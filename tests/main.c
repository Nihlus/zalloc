//
//  main.c
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

#include <stdlib.h>

#include "zalloc_zalloc.h"
#include "zalloc_zsize.h"
#include "zalloc_zfree.h"

Suite* zsize_suite()
{
    Suite* suite = suite_create("zalloc");

    TCase* tc_zalloc = tcase_create("zalloc");
    tcase_add_test(tc_zalloc, zalloc_can_allocate);
    tcase_add_test(tc_zalloc, zalloc_returns_null_for_zero);
    tcase_add_test(tc_zalloc, zalloc_sets_correct_errno_for_zero);
    tcase_add_test(tc_zalloc, zalloc_returns_null_for_negative_values);
    tcase_add_test(tc_zalloc, zalloc_sets_correct_errno_for_negative_values);

    TCase* tc_zfree = tcase_create("zfree");
    tcase_add_test(tc_zfree, zfree_can_free);
    tcase_add_test(tc_zfree, zfree_actually_zeroes);
    tcase_add_test(tc_zfree, zfree_returns_false_if_memory_was_not_allocated_with_zalloc);
    tcase_add_test(tc_zfree, zfree_sets_correct_errno_if_memory_was_not_allocated_with_zalloc);
    tcase_add_test(tc_zfree, zfree_returns_false_if_memory_pointer_is_null);
    tcase_add_test(tc_zfree, zfree_sets_correct_errno_if_memory_pointer_is_null);

    TCase* tc_zsize = tcase_create("zsize");
    tcase_add_test(tc_zsize, zsize_can_get_size);
    tcase_add_test(tc_zsize, zsize_returns_zero_if_memory_was_not_allocated_with_zalloc);
    tcase_add_test(tc_zsize, zsize_sets_correct_errno_if_memory_was_not_allocated_with_zalloc);

    suite_add_tcase(suite, tc_zalloc);
    suite_add_tcase(suite, tc_zfree);
    suite_add_tcase(suite, tc_zsize);

    return suite;
}

int main()
{
    int number_failed = 0;
    Suite* suite = zsize_suite();
    SRunner* runner = srunner_create(suite);

    srunner_set_fork_status(runner, CK_NOFORK);

    srunner_run_all(runner, CK_VERBOSE);
    number_failed = srunner_ntests_failed(runner);

    srunner_free(runner);
    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
