/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>

#include <servz/event_manager.hpp>

#include "test_services.hpp"

namespace
{

void delivery_before(void *)
{
	k_sem_reset(&event_received_a);
	k_sem_reset(&event_received_b);
}

} // namespace

ZTEST_SUITE(servz_delivery, nullptr, nullptr, delivery_before, nullptr, nullptr);

ZTEST(servz_delivery, test_event_is_delivered_to_single_subscriber)
{
	(void)servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::AOnly));

	zassert_ok(k_sem_take(&event_received_a, K_MSEC(100)),
		   "Subscriber A did not receive event");

	zassert_not_equal(k_sem_take(&event_received_b, K_MSEC(20)), 0,
			  "Event was delivered to subscriber B");
}

ZTEST(servz_delivery, test_unsubscribed_event_is_not_delivered)
{
	(void)servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::Ignored));

	zassert_not_equal(k_sem_take(&event_received_a, K_MSEC(20)), 0,
			  "Unsubscribed event was delivered to subscriber A");

	zassert_not_equal(k_sem_take(&event_received_b, K_MSEC(20)), 0,
			  "Unsubscribed event was delivered to subscriber B");
}

ZTEST(servz_delivery, test_event_is_delivered_to_multiple_subscribers)
{
	(void)servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::Both));

	zassert_ok(k_sem_take(&event_received_a, K_MSEC(100)),
		   "Subscriber A did not receive event");

	zassert_ok(k_sem_take(&event_received_b, K_MSEC(100)),
		   "Subscriber B did not receive event");
}
