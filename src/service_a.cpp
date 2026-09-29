
/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(service_a, LOG_LEVEL_INF);

#include "service_a.hpp"
#include "app_event.hpp"
#include "event_manager.hpp"

ServiceA::ServiceA(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void ServiceA::on_start()
{
	LOG_INF("%s started", get_name());

	LOG_INF("Publishing ServiceAStarted");

	servz::EventManager::publish(static_cast<servz::EventId>(Event::ServiceAStarted));
}

void ServiceA::on_event(servz::EventId event)
{
	ARG_UNUSED(event);
}

SERVICE_DEFINE(service_a, ServiceA, 1024, 5, 8);
