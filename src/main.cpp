#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

#include "service.hpp"

int main()
{
	LOG_INF("Registered services:");

	SERVICE_FOREACH(registration)
	{
		LOG_INF("- %s", registration->service->get_name());
	}

	while (true) {
		k_msleep(1000);
	}

	return 0;
}
