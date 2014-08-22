#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>

#include "BaseStation.h"

namespace tcpsim
{

class BaseStation;

class Client
{
protected:
	// Client id
	unsigned int id;

	// The Base station it transmit to
	BaseStation *base_station;

	// Sensing time
	double sensing_time = 0.2;

public:

	/// Constructor
	Client(unsigned int id, BaseStation *base_station);

	/// Destructors
	virtual ~Client();

	/// Receice ACK
	virtual void ReceiveAck(const std::string &ack) = 0;

	/// Do action
	virtual void tick() = 0;
};

} /* namespace tcpsim */

#endif 
