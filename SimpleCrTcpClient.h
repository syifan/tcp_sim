/*
 * SimpleCrTcpClient.h
 *
 *  Created on: Aug 8, 2014
 *      Author: uranusbean
 */

#ifndef SIMPLECRTCPCLIENT_H_
#define SIMPLECRTCPCLIENT_H_

#include "IsmTcpClient.h"

namespace tcpsim {

class SimpleCrTcpClient : public IsmTcpClient
{
	// Determines if doing sensing
	bool is_sensing = 0;

	// The time when sensing start
	double change_state_time = 0;

	// Time in sensing period
	double sensing_duration = 0.2;

	// Time in  transmission time
	double tx_duration = 0.8;

	// The licenced channel it working in
	Channel *tv_channel;

	// The shared_channel
	Channel *shared_channel;

public:

	/// Constructor
	SimpleCrTcpClient(unsigned int id, BaseStation *base_station,
			Channel *ism_channel, Channel *tv_channel);

	/// Destructor
	virtual ~SimpleCrTcpClient();

	void tick();
};

} /* namespace tcpsim */

#endif /* SIMPLECRTCPCLIENT_H_ */
