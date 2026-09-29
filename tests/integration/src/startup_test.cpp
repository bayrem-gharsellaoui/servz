/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>

#include "test_services.hpp"

ZTEST_SUITE(servz_startup, nullptr, nullptr, nullptr, nullptr, nullptr);

ZTEST(servz_startup, test_event_published_during_startup_is_delivered)
{
	zassert_ok(k_sem_take(&startup_received, K_MSEC(100)), "Startup event was not delivered");
}
