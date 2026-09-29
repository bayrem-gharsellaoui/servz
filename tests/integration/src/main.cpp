/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>

ZTEST_SUITE(my_integration_suite, NULL, NULL, NULL, NULL, NULL);

ZTEST(my_integration_suite, test_something)
{
    zassert_true(1, "basic sanity check failed");
}
