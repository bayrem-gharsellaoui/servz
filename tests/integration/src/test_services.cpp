/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#include "test_services.hpp"

K_SEM_DEFINE(event_received, 0, 1);

TestSubscriber::TestSubscriber(const char *name, k_msgq &event_queue)
	: Service(name, event_queue, kSubscriptions)
{
}

void TestSubscriber::on_event(servz::EventId event)
{
	ARG_UNUSED(event);

	k_sem_give(&event_received);
}

SERVZ_SERVICE_DEFINE(test_subscriber, TestSubscriber, 1024, 5, 4);
