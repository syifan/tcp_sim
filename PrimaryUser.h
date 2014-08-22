#ifndef PRIMARYUSER_H_
#define PRIMARYUSER_H_

#include <memory>

#include "Logger.h"

namespace tcpsim
{

/// Primary user
class PrimaryUser
{
	// Constructor
	PrimaryUser();

	// Instance
	static std::unique_ptr<PrimaryUser> instance;

	// Determines if the primary user occupies the channel
	bool on = true;

	/// Expected off time in second
	double expected_off_time = 10;

	/// Expected on time in second
	double expected_on_time = 10;

	/// The scheduler time when last time function tick is ran
	double last_time = 0;

	/// Logger
	std::unique_ptr<Logger> pu_logger;

public:

	/// Return the pointer to the unique instance
	static PrimaryUser *getInstance();

	/// Switch on and off
	void tick();

	/// Determines if the primary user is on
	bool isOn() const { return on; }

	virtual ~PrimaryUser();
};

} /* namespace tcpsim */

#endif 
