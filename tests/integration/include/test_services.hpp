/*
 * Copyright (c) 2026 Bayrem Gharsellaoui
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <zephyr/kernel.h>

#include <servz/service.hpp>

enum class TestEvent : servz::EventId {
	AOnly,
	Both,
	Ignored,
	OverflowBlock,
	Overflow,
	Startup,
};

extern struct k_sem event_received_a;
extern struct k_sem event_received_b;
extern struct k_sem overflow_entered;
extern struct k_sem overflow_release;
extern struct k_sem healthy_received;
extern struct k_sem startup_received;

class TestSubscriberA final: public servz::Service
{
public:
	TestSubscriberA(const char *name, k_msgq &event_queue);

protected:
	void on_event(servz::EventId event) override;

private:
	static constexpr auto Subscriptions =
		servz::EventMask::of(TestEvent::AOnly, TestEvent::Both);
};

class TestSubscriberB final: public servz::Service
{
public:
	TestSubscriberB(const char *name, k_msgq &event_queue);

protected:
	void on_event(servz::EventId event) override;

private:
	static constexpr auto Subscriptions = servz::EventMask::of(TestEvent::Both);
};

class OverflowSubscriber final: public servz::Service
{
public:
	OverflowSubscriber(const char *name, k_msgq &event_queue);

protected:
	void on_event(servz::EventId event) override;

private:
	static constexpr auto Subscriptions =
		servz::EventMask::of(TestEvent::OverflowBlock, TestEvent::Overflow);
};

class HealthySubscriber final: public servz::Service
{
public:
	HealthySubscriber(const char *name, k_msgq &event_queue);

protected:
	void on_event(servz::EventId event) override;

private:
	static constexpr auto Subscriptions = servz::EventMask::of(TestEvent::Overflow);
};

class StartupPublisher final: public servz::Service
{
public:
	StartupPublisher(const char *name, k_msgq &event_queue);

protected:
	void on_start() override;
	void on_event(servz::EventId event) override;
};

class StartupSubscriber final: public servz::Service
{
public:
	StartupSubscriber(const char *name, k_msgq &event_queue);

protected:
	void on_event(servz::EventId event) override;

private:
	static constexpr auto Subscriptions = servz::EventMask::of(TestEvent::Startup);
};
