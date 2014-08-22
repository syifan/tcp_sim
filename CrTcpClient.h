#ifndef CRTCPCLIENT_H_
#define CRTCPCLIENT_H_

#include "Client.h"
#include "IsmTcpClient.h"

namespace tcpsim
{

class CrTcpClient: public IsmTcpClient
{

	// State of proposed status
	unsigned int state = 1;

	// The time when last time the state changed
	double change_state_time = 0;

	// Sensing time
	double sensing_duration = 0.2;

	// Transmission time
	double tx_duration = 0.8;

	// Determine if PU present, in last cycle
	bool pu_present = true;

	// Determines if the node is sensing
	bool is_sensing = false;

	// Shared ISM Channel
	Channel *shared_channel;

	// Dedicated TV Channel
	Channel *tv_channel;

	// Perform sensing in state 1
	void PuPresentVerify();

	// Perform sensing in state 2
	void PuAbsentVerify();

	// Transmit data in traditional TCP state
	void Transmit();

public:

	/// Constructor
	CrTcpClient(unsigned int id, BaseStation *base_station,
			Channel *ism_channel, Channel *tv_channel);

	/// Destructor
	virtual ~CrTcpClient();

	/// Do action
	void tick();




};

} /* namespace tcpsim */

#endif 
