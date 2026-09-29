/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "event.hpp"

namespace servz
{

class EventManager
{
public:
	EventManager() = delete;

	/**
	 * @brief Publish an event to all subscribed services.
	 *
	 * @param event Event to publish.
	 *
	 * @return true if the event was delivered to every subscribed service, otherwise false.
	 */
	static bool publish(EventId event);
};

} // namespace servz
