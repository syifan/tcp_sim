#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_

#include <memory>

namespace tcpsim
{

/// Singleton
class Scheduler
{
	// Constructor
	Scheduler();

	// Instance
	static std::unique_ptr<Scheduler> instance;

	// Current time
	double now_time = 0;

	// Max time
	double max_time = 2000;

	// Dump progress interval
	double dump_progress_interval = 100;

	// Last time when progress is dump
	double last_dump_time = 0;

public:

	/// Return the pointer to the unique instance
	static Scheduler *getInstance();

	/// Move current time forward
	void tick(double time_lapsed);

	/// Destructor
	virtual ~Scheduler();

	/// Returns now time
	double getNowTime() const { return now_time; }

	/// Dump progress
	void DumpProgress();
};

} /* namespace tcpsim */

#endif 
