#pragma once

#include "service.hpp"

class ServiceA final: public MyProject::Service
{
public:
	ServiceA(const char *name, k_msgq &event_queue);

protected:
	void on_start() override;
	void on_event(MyProject::EventId event) override;

private:
	enum class Event : MyProject::EventId {
		Dummy,
	};

	static constexpr auto Subscriptions = MyProject::EventMask::of(Event::Dummy);
};
