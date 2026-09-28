#include "service_b.hpp"

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(service_b, LOG_LEVEL_INF);

ServiceB::ServiceB(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void ServiceB::on_start()
{
	LOG_INF("%s started", get_name());
}

void ServiceB::on_event(MyProject::EventId event)
{
	ARG_UNUSED(event);
}

SERVICE_DEFINE(service_b, ServiceB, 1024, 5, 8);
