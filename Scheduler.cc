#include <stdlib.h>
#include <iostream>

#include "Scheduler.h"

namespace tcpsim
{

// Instance
std::unique_ptr<Scheduler> Scheduler::instance;

Scheduler::Scheduler()
{
	// TODO Auto-generated constructor stub

}

Scheduler::~Scheduler()
{
	// TODO Auto-generated destructor stub
}


Scheduler *Scheduler::getInstance()
{
	if (instance.get())
		return instance.get();

	instance.reset(new Scheduler());
	return instance.get();
}


void Scheduler::tick(double time_lapsed)
{
	now_time += time_lapsed;
	DumpProgress();
	//std::cout << "Now time: "<< now_time << "\n";
	if (now_time > max_time)
	{
		exit(0);
	}
};


void Scheduler::DumpProgress()
{
	if (now_time - last_dump_time > dump_progress_interval)
	{
		std::cout << "Now time: " << now_time << "\n";
		last_dump_time = now_time;
	}
}

} /* namespace tcpsim */
