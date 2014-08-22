#include <iostream>

#include "Misc.h"
#include "Scheduler.h"
#include "PrimaryUser.h"

namespace tcpsim
{

std::unique_ptr<PrimaryUser> PrimaryUser::instance;

PrimaryUser::PrimaryUser()
{
	pu_logger.reset(new Logger("PU.log"));
}

PrimaryUser::~PrimaryUser()
{
}

void PrimaryUser::tick()
{
	// Get time duration from last tick
	double now_time = Scheduler::getInstance()->getNowTime();
	double time_diff = now_time- last_time;

	// Set PU on/off according to Poisson distribution
	if (on)
	{
		double prob_off = time_diff / expected_off_time;
		if (Misc::Happen(prob_off))
		{
			on = false;
			pu_logger->Log("0");
		}
	}
	else
	{
		double prob_on = time_diff / expected_on_time;
		if (Misc::Happen(prob_on))
		{
			on = true;
			pu_logger->Log("1");
		}
	}

	// Reset the last time field
	last_time = now_time;
}

PrimaryUser *PrimaryUser::getInstance()
{
	if (instance.get())
		return instance.get();

	instance.reset(new PrimaryUser());
	return instance.get();
}

} /* namespace tcpsim */
