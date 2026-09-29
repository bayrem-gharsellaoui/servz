/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <servz/service.hpp>

namespace servz
{

Service::Service(const char *name, k_msgq &event_queue, EventMask subscriptions)
	: m_name(name), m_event_queue(event_queue), m_subscriptions(subscriptions)
{
}

const char *Service::get_name() const
{
	return m_name;
}

bool Service::subscribes_to(EventId event) const
{
	return m_subscriptions.contains(event);
}

int Service::post_event(EventId event)
{
	return k_msgq_put(&m_event_queue, &event, K_NO_WAIT);
}

void Service::thread_trampoline(void *p1, void *, void *)
{
	auto *self = static_cast<Service *>(p1);
	self->run();
}

void Service::run()
{
	on_start();

	while (true) {
		EventId event{};

		if (k_msgq_get(&m_event_queue, &event, K_FOREVER) == 0) {
			on_event(event);
		}
	}
}

} // namespace servz
