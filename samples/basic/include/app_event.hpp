/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <servz/event.hpp>

enum class Event : servz::EventId {
	ServiceAStarted,

	Count,
};

static_assert(static_cast<servz::EventId>(Event::Count) <= 32);
