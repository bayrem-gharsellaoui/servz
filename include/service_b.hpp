#pragma once

#include "app_event.hpp"
#include "service.hpp"

class ServiceB final: public MyProject::Service
{
public:
	ServiceB(const char *name, k_msgq &event_queue);

protected:
	void on_start() override;
	void on_event(MyProject::EventId event) override;

private:
	static constexpr auto Subscriptions = MyProject::EventMask::of(Event::ServiceAStarted);
};
