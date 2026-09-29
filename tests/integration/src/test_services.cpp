/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include <servz/event_manager.hpp>

#include "test_services.hpp"

K_SEM_DEFINE(event_received_a, 0, 1);
K_SEM_DEFINE(event_received_b, 0, 1);
K_SEM_DEFINE(overflow_entered, 0, 1);
K_SEM_DEFINE(overflow_release, 0, 1);
K_SEM_DEFINE(healthy_received, 0, 1);
K_SEM_DEFINE(startup_received, 0, 1);

TestSubscriberA::TestSubscriberA(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void TestSubscriberA::on_event(servz::EventId event)
{
	ARG_UNUSED(event);

	k_sem_give(&event_received_a);
}

TestSubscriberB::TestSubscriberB(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void TestSubscriberB::on_event(servz::EventId event)
{
	ARG_UNUSED(event);

	k_sem_give(&event_received_b);
}

OverflowSubscriber::OverflowSubscriber(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void OverflowSubscriber::on_event(servz::EventId event)
{
	switch (static_cast<TestEvent>(event)) {
	case TestEvent::OverflowBlock:
		k_sem_give(&overflow_entered);
		(void)k_sem_take(&overflow_release, K_FOREVER);
		break;

	case TestEvent::Overflow:
		break;

	default:
		break;
	}
}

HealthySubscriber::HealthySubscriber(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void HealthySubscriber::on_event(servz::EventId event)
{
	if (static_cast<TestEvent>(event) == TestEvent::Overflow) {
		k_sem_give(&healthy_received);
	}
}

StartupPublisher::StartupPublisher(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, {})
{
}

void StartupPublisher::on_start()
{
	(void)servz::EventManager::publish(static_cast<servz::EventId>(TestEvent::Startup));
}

void StartupPublisher::on_event(servz::EventId event)
{
	ARG_UNUSED(event);
}

StartupSubscriber::StartupSubscriber(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, Subscriptions)
{
}

void StartupSubscriber::on_event(servz::EventId event)
{
	if (static_cast<TestEvent>(event) == TestEvent::Startup) {
		k_sem_give(&startup_received);
	}
}

SERVZ_SERVICE_DEFINE(test_subscriber_a, TestSubscriberA, 1024, 5, 4);
SERVZ_SERVICE_DEFINE(test_subscriber_b, TestSubscriberB, 1024, 5, 4);
SERVZ_SERVICE_DEFINE(overflow_subscriber, OverflowSubscriber, 1024, 5, 1);
SERVZ_SERVICE_DEFINE(healthy_subscriber, HealthySubscriber, 1024, 5, 4);
SERVZ_SERVICE_DEFINE(startup_publisher, StartupPublisher, 1024, 5, 4);
SERVZ_SERVICE_DEFINE(startup_subscriber, StartupSubscriber, 1024, 5, 4);
