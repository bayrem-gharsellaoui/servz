#pragma once

#include "event.hpp"

namespace MyProject
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

} // namespace MyProject
