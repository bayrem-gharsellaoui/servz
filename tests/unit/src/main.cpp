/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>

ZTEST_SUITE(my_unit_suite, NULL, NULL, NULL, NULL, NULL);

ZTEST(my_unit_suite, test_my_function)
{
    zassert_equal(1, 1, "1 != 1");
}
