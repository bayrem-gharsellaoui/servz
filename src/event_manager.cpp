#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(event_manager, LOG_LEVEL_INF);

#include "event_manager.hpp"
#include "service.hpp"

static void publish_event(MyProject::EventId event)
{
	SERVICE_FOREACH(registration)
	{
		auto &service = *registration->service;

		if (!service.subscribes_to(event)) {
			continue;
		}

		if (service.post_event(event) != 0) {
			LOG_ERR("Event queue full for %s", service.get_name());
		}
	}
}

void MyProject::EventManager::publish(EventId event)
{
	publish_event(event);
}
