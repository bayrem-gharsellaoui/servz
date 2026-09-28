#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main()
{
	LOG_INF("Hello world!");

	while (true) {
		k_msleep(1000);
	}

	return 0;
}
