
/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(service_b, LOG_LEVEL_INF);

#include "service_b.hpp"

ServiceB::ServiceB(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void ServiceB::on_start()
{
	LOG_INF("%s started", get_name());
}

void ServiceB::on_event(servz::EventId event)
{
	switch (static_cast<Event>(event)) {
	case Event::ServiceAStarted: {
		LOG_INF("Received ServiceAStarted");
		break;
	}

	default: {
		break;
	}
	}
}

SERVICE_DEFINE(service_b, ServiceB, 1024, 5, 8);
