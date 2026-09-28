#include "service.hpp"

namespace MyProject
{

Service::Service(const char *name, k_msgq &event_queue, EventMask subscriptions)
	: m_name(name), m_event_queue(event_queue), m_subscriptions(subscriptions)
{
}

const char *Service::get_name() const
{
	return m_name;
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

} // namespace MyProject
