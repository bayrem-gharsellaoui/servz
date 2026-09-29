/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

namespace servz
{

using EventId = uint8_t;

class EventMask
{
public:
	constexpr EventMask() = default;

	template <typename... Events> static constexpr EventMask of(Events... events)
	{
		return EventMask{(0U | ... | bit(events))};
	}

	[[nodiscard]]
	constexpr bool contains(EventId event) const
	{
		return (m_bits & (1UL << event)) != 0U;
	}

private:
	explicit constexpr EventMask(uint32_t bits) : m_bits(bits)
	{
	}

	template <typename Event> static constexpr uint32_t bit(Event event)
	{
		return 1UL << static_cast<EventId>(event);
	}

	uint32_t m_bits{0U};
};

} // namespace servz
