/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>

#include <servz/event_manager.hpp>

#include "test_services.hpp"

namespace
{

void overflow_before(void *)
{
	k_sem_reset(&overflow_entered);
	k_sem_reset(&overflow_release);
	k_sem_reset(&healthy_received);
}

void overflow_after(void *)
{
	/* Ensure the overflow subscriber is never left blocked after a test. */
	k_sem_give(&overflow_release);
}

} // namespace

ZTEST_SUITE(servz_overflow, nullptr, nullptr, overflow_before, overflow_after, nullptr);

ZTEST(servz_overflow, test_full_queue_does_not_block_other_subscribers)
{
	/*
	 * Block the overflow subscriber inside on_event().
	 */
	const bool block_delivered =
		servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::OverflowBlock));

	zassert_true(block_delivered, "Failed to deliver blocking event");

	zassert_ok(k_sem_take(&overflow_entered, K_MSEC(100)),
		   "Overflow subscriber did not enter blocking state");

	/*
	 * Fill its one-element queue while its thread is blocked.
	 * The healthy subscriber should receive this event normally.
	 */
	const bool first_delivered =
		servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::Overflow));

	zassert_true(first_delivered, "Failed to queue first overflow event");

	zassert_ok(k_sem_take(&healthy_received, K_MSEC(100)),
		   "Healthy subscriber did not receive first event");

	/*
	 * The overflow subscriber queue is now full.
	 * Delivery to it must fail, but the healthy subscriber must
	 * still receive the event.
	 */
	const bool second_delivered =
		servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::Overflow));

	zassert_false(second_delivered, "publish() did not report partial delivery failure");

	zassert_ok(k_sem_take(&healthy_received, K_MSEC(100)),
		   "Healthy subscriber did not receive event after queue overflow");

	/*
	 * Allow the blocked subscriber to continue.
	 */
	k_sem_give(&overflow_release);
}
