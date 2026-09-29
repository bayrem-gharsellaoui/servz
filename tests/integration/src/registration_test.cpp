/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include <zephyr/ztest.h>

#include <servz/service.hpp>

ZTEST_SUITE(servz_registration, nullptr, nullptr, nullptr, nullptr, nullptr);

ZTEST(servz_registration, test_services_are_registered)
{
	bool subscriber_a_found = false;
	bool subscriber_b_found = false;

	servz::Service::for_each([&](servz::Service &service) {
		if (strcmp(service.get_name(), "test_subscriber_a") == 0) {
			subscriber_a_found = true;
		}

		if (strcmp(service.get_name(), "test_subscriber_b") == 0) {
			subscriber_b_found = true;
		}
	});

	zassert_true(subscriber_a_found, "test_subscriber_a is not registered");
	zassert_true(subscriber_b_found, "test_subscriber_b is not registered");
}
