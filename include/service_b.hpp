/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "app_event.hpp"
#include "service.hpp"

class ServiceB final: public servz::Service
{
public:
	ServiceB(const char *name, k_msgq &event_queue);

protected:
	void on_start() override;
	void on_event(servz::EventId event) override;

private:
	static constexpr auto Subscriptions = servz::EventMask::of(Event::ServiceAStarted);
};
