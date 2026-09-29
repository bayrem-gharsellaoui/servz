/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>

#include <servz/event.hpp>

namespace
{

enum class Event : servz::EventId {
	A = 0,
	B,
	C,
	Last = 31,
};

} // namespace

ZTEST_SUITE(event_mask, nullptr, nullptr, nullptr, nullptr, nullptr);

ZTEST(event_mask, test_default_mask_is_empty)
{
	const servz::EventMask mask{};

	zassert_false(mask.contains(static_cast<servz::EventId>(Event::A)));
	zassert_false(mask.contains(static_cast<servz::EventId>(Event::B)));
	zassert_false(mask.contains(static_cast<servz::EventId>(Event::C)));
}

ZTEST(event_mask, test_single_event)
{
	const auto mask = servz::EventMask::of(Event::A);

	zassert_true(mask.contains(static_cast<servz::EventId>(Event::A)));
	zassert_false(mask.contains(static_cast<servz::EventId>(Event::B)));
}

ZTEST(event_mask, test_multiple_events)
{
	const auto mask = servz::EventMask::of(Event::A, Event::B, Event::C);

	zassert_true(mask.contains(static_cast<servz::EventId>(Event::A)));
	zassert_true(mask.contains(static_cast<servz::EventId>(Event::B)));
	zassert_true(mask.contains(static_cast<servz::EventId>(Event::C)));
}

ZTEST(event_mask, test_last_supported_event)
{
	const auto mask = servz::EventMask::of(Event::Last);

	zassert_true(mask.contains(static_cast<servz::EventId>(Event::Last)));
	zassert_false(mask.contains(static_cast<servz::EventId>(Event::A)));
}

ZTEST(event_mask, test_events_do_not_overlap)
{
	const auto mask_a = servz::EventMask::of(Event::A);
	const auto mask_b = servz::EventMask::of(Event::B);

	zassert_true(mask_a.contains(static_cast<servz::EventId>(Event::A)));
	zassert_false(mask_a.contains(static_cast<servz::EventId>(Event::B)));

	zassert_true(mask_b.contains(static_cast<servz::EventId>(Event::B)));
	zassert_false(mask_b.contains(static_cast<servz::EventId>(Event::A)));
}
