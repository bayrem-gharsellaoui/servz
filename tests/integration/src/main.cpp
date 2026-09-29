/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include <zephyr/ztest.h>

#include <servz/event_manager.hpp>

#include "test_services.hpp"

ZTEST_SUITE(servz_integration, nullptr, nullptr, nullptr, nullptr, nullptr);

ZTEST(servz_integration, test_service_is_registered)
{
	bool found = false;

	servz::Service::for_each([&found](servz::Service &service) {
		if (strcmp(service.get_name(), "test_subscriber") == 0) {
			found = true;
		}
	});

	zassert_true(found);
}

ZTEST(servz_integration, test_subscribed_event_is_delivered)
{
	k_sem_reset(&event_received);

	(void)servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::Ping));

	zassert_ok(k_sem_take(&event_received, K_MSEC(100)));
}

ZTEST(servz_integration, test_unsubscribed_event_is_not_delivered)
{
	k_sem_reset(&event_received);

	(void)servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::Ignored));

	zassert_not_equal(k_sem_take(&event_received, K_MSEC(20)), 0);
}
