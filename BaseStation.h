#ifndef BASESTATION_H_
#define BASESTATION_H_

#include "Client.h"

namespace tcpsim
{

class Client;

class BaseStation
{
	// Maximum buffer size
	unsigned int buffer_size = 1000000;

	// Buffer packets consumption rate
	unsigned int buffer_consume_per_second = 200000;

	// Current buffer level
	unsigned int buffer_fullness = buffer_size/2;

	// The time last time tick is called
	double last_tick_time = 0;

	// Remove packets from the buffer
	void ConsumePackets(double time_passed);

public:

	/// Constructor
	BaseStation();

	/// Destructor
	virtual ~BaseStation();

	/// Do action
	void tick();

	/// Receive n packets.
	void Receive(unsigned int num_packet, Client *client);

};

} /* namespace tcpsim */

#endif 
