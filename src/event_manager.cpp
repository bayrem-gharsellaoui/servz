/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(event_manager, LOG_LEVEL_INF);

#include <servz/event_manager.hpp>
#include <servz/service.hpp>

bool servz::EventManager::publish(EventId event)
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
