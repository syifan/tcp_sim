#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <list>
#include <vector>

#include "Client.h"
#include "BaseStation.h"


namespace tcpsim {

class Channel {

	struct Transmission
	{
		Client *from;
		BaseStation *to;
		unsigned int num_packet;
	};

	// Bandwidth in bit per second
	unsigned int bandwidth;

	// Average packet size in bit
	unsigned int packet_size = 4000;

	// maximum time can each TCP client wait for the ACK
	double wait_time = 0.1;

	// Packet error rate
	double packet_error_rate = 1e-11;

	// Pending transmission
	unsigned int packet_to_trans = 0;

	// Get the probability that a bunch can be transmitted
	double getTransProb() const;

	// Get the probability that at least one of the packet is error
	double getHaveErrorPacket(unsigned int num_packet) const;

	// List of transmissions
	std::vector<std::unique_ptr<Transmission>> transmissions;


public:

	/// Constructor
	Channel(unsigned int bandwidth);

	virtual ~Channel();

	/// Do action
	void tick();

	/// Transmit on channel
	void TransmitOn(Client *from, BaseStation* to, unsigned int num_packets);

	/// Return round trip time
	double getRTT() const { return (double)packet_size / bandwidth; }

	/// Return wait time
	double getWaitTime() const { return (double)wait_time; }

};

} /* namespace tcpsim */

#endif /* CHANNEL_H_ */
