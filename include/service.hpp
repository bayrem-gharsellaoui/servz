#pragma once

#include "event.hpp"

#include <zephyr/kernel.h>
#include <zephyr/sys/iterable_sections.h>

namespace MyProject
{

class Service
{
public:
	Service(const Service &) = delete;
	Service &operator=(const Service &) = delete;

	/**
	 * @brief Get the service name.
	 *
	 * @return Service name.
	 */
	[[nodiscard]]
	const char *get_name() const;

	/**
	 * @brief Zephyr thread entry point.
	 *
	 * @param p1 Pointer to the service instance.
	 * @param p2 Unused.
	 * @param p3 Unused.
	 */
	static void thread_trampoline(void *p1, void *p2, void *p3);

protected:
	/**
	 * @brief Construct a service.
	 *
	 * @param name Service name.
	 * @param event_queue Event queue associated with the service.
	 * @param subscriptions Events subscribed to by the service.
	 */
	Service(const char *name, k_msgq &event_queue, EventMask subscriptions);

	~Service() = default;

	/**
	 * @brief Called once when the service thread starts.
	 */
	virtual void on_start()
	{
	}

	/**
	 * @brief Handle an event received by the service.
	 *
	 * @param event Event identifier.
	 */
	virtual void on_event(EventId event) = 0;

private:
	void run();

	const char *m_name;
	k_msgq &m_event_queue;
	EventMask m_subscriptions;
};

} // namespace MyProject

/**
 * @brief Service registration entry.
 */
struct service_registration {
	MyProject::Service *service;
};

/**
 * @brief Define and register a service.
 *
 * Creates the service event queue, service instance, static kernel thread,
 * and iterable-section registration entry.
 */
#define SERVICE_DEFINE(instance_name, service_type, stack_size, priority, queue_depth, ...)        \
	K_MSGQ_DEFINE_STATIC_TYPE(instance_name##_queue, MyProject::EventId, queue_depth);         \
                                                                                                   \
	static service_type instance_name{#instance_name, instance_name##_queue, ##__VA_ARGS__};   \
                                                                                                   \
	K_KERNEL_THREAD_DEFINE(instance_name##_thread, stack_size,                                 \
			       MyProject::Service::thread_trampoline, &instance_name, nullptr,     \
			       nullptr, priority, 0, 0);                                           \
                                                                                                   \
	const STRUCT_SECTION_ITERABLE(service_registration,                                        \
				      instance_name##_registration) = {&instance_name}

/**
 * @brief Iterate over all registered services.
 */
#define SERVICE_FOREACH(iterator) STRUCT_SECTION_FOREACH(service_registration, iterator)
