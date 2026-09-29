/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <zephyr/kernel.h>
#include <zephyr/sys/iterable_sections.h>

#include "event.hpp"

namespace servz
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
	 * @brief Check whether the service subscribes to an event.
	 *
	 * @param event Event identifier.
	 *
	 * @return true if the service subscribes to the event.
	 */
	[[nodiscard]]
	bool subscribes_to(EventId event) const;

	/**
	 * @brief Post an event to the service.
	 *
	 * @param event Event identifier.
	 *
	 * @return 0 on success, otherwise a negative error code.
	 */
	int post_event(EventId event);

	/**
	 * @brief Invoke a callable for each registered service.
	 *
	 * @tparam Callable Callable type accepting a Service reference.
	 * @param callable Callable to invoke for each registered service.
	 */
	template <typename Callable>
	static void for_each(Callable &&callable);

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

} // namespace servz

struct service_registration {
	servz::Service *service;
};

/**
 * @brief Invoke a callable for each registered service.
 *
 * @tparam Callable Callable type accepting a Service reference.
 * @param callable Callable to invoke for each registered service.
 */
template <typename Callable>
void service_for_each(Callable &&callable)
{
	STRUCT_SECTION_FOREACH(service_registration, registration) {
		callable(*registration->service);
	}
}

template <typename Callable> void servz::Service::for_each(Callable &&callable)
{
	::service_for_each(static_cast<Callable &&>(callable));
}

#define SERVICE_DEFINE(instance_name, service_type, stack_size, priority, queue_depth, ...)        \
	K_MSGQ_DEFINE_STATIC_TYPE(instance_name##_queue, servz::EventId, queue_depth);             \
                                                                                                   \
	static service_type instance_name{#instance_name, instance_name##_queue, ##__VA_ARGS__};   \
                                                                                                   \
	K_KERNEL_THREAD_DEFINE(instance_name##_thread, stack_size,                                 \
			       servz::Service::thread_trampoline, &instance_name, nullptr,         \
			       nullptr, priority, 0, 0);                                           \
                                                                                                   \
	const STRUCT_SECTION_ITERABLE(service_registration,                                        \
				      instance_name##_registration) = {&instance_name}
