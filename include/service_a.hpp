/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "service.hpp"

class ServiceA final: public servz::Service
{
public:
	ServiceA(const char *name, k_msgq &event_queue);

protected:
	void on_start() override;
	void on_event(servz::EventId event) override;

private:
	static constexpr servz::EventMask Subscriptions{};
};
