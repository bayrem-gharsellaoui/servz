#include "service_a.hpp"

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(service_a, LOG_LEVEL_INF);

ServiceA::ServiceA(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void ServiceA::on_start()
{
	LOG_INF("%s started", get_name());
}

void ServiceA::on_event(MyProject::EventId event)
{
	ARG_UNUSED(event);
}

SERVICE_DEFINE(service_a, ServiceA, 1024, 5, 8);
