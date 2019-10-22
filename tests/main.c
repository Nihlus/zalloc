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
#include "base.h"
#include "zalloc_size.h"

Suite* zalloc_suite()
{
    Suite* suite;
    TCase* tc_core;

    suite = suite_create("zalloc");
    tc_core = tcase_create("base");

    tcase_add_test(tc_core, can_allocate);
    tcase_add_test(tc_core, can_free);
    tcase_add_test(tc_core, zalloc_returns_null_for_zero);
    tcase_add_test(tc_core, zalloc_sets_correct_errno_for_zero);
    tcase_add_test(tc_core, zalloc_returns_null_for_negative_values);
    tcase_add_test(tc_core, zalloc_sets_correct_errno_for_negative_values);

    suite_add_tcase(suite, tc_core);

    return suite;
}

int main()
{
    int number_failed = 0;
    Suite* suite = zalloc_suite();
    SRunner* runner = srunner_create(suite);

    srunner_set_fork_status(runner, CK_NOFORK);

    srunner_run_all(runner, CK_VERBOSE);
    number_failed = srunner_ntests_failed(runner);

    srunner_free(runner);
    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
