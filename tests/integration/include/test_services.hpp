/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <zephyr/kernel.h>

#include <servz/service.hpp>

enum class TestEvent : servz::EventId {
	Ping,
	Ignored,
};

extern struct k_sem event_received;

class TestSubscriber final: public servz::Service
{
public:
	TestSubscriber(const char *name, k_msgq &event_queue);

protected:
	void on_event(servz::EventId event) override;

private:
	static constexpr auto kSubscriptions = servz::EventMask::of(TestEvent::Ping);
};
