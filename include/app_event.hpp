#pragma once

#include "event.hpp"

enum class Event : MyProject::EventId {
	ServiceAStarted,

	Count,
};

static_assert(static_cast<MyProject::EventId>(Event::Count) <= 32);
