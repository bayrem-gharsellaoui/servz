#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(event_manager, LOG_LEVEL_INF);

#include "event_manager.hpp"
#include "service.hpp"

bool MyProject::EventManager::publish(EventId event)
{
	bool delivered = true;

	Service::for_each([event, &delivered](Service &service) {
		if (!service.subscribes_to(event)) {
			return;
		}

		const int ret = service.post_event(event);

		if (ret != 0) {
			LOG_ERR("Failed to post event to %s: %d", service.get_name(), ret);

			delivered = false;
		}
	});

	return delivered;
}
