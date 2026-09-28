#pragma once

#include "event.hpp"

namespace MyProject
{

class EventManager
{
public:
	EventManager() = delete;

	static void publish(EventId event);
};

} // namespace MyProject
