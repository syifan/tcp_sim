/*
 * SimpleCrTcpClient.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: uranusbean
 */

#include "SimpleCrTcpClient.h"
#include "PrimaryUser.h"
#include "Scheduler.h"

namespace tcpsim {

SimpleCrTcpClient::SimpleCrTcpClient(unsigned int id,
		BaseStation *base_station,
		Channel *ism_channel, Channel *tv_channel) :
				IsmTcpClient(id, base_station, ism_channel)
{
	this->tv_channel = tv_channel;
	this->shared_channel = ism_channel;
}

SimpleCrTcpClient::~SimpleCrTcpClient() {
}


void SimpleCrTcpClient::tick()
{
	double now_time = Scheduler::getInstance()->getNowTime();
	if (is_sensing)
	{
		if (now_time - change_state_time > sensing_duration)
		{
			is_sensing = false;
			PrimaryUser *pu = PrimaryUser::getInstance();
			if (pu->isOn())
			{
				this->ism_channel = shared_channel;
			}
			else
			{
				this->ism_channel = tv_channel;
			}
		}
		else
		{
			return;
		}
	}

	if (!is_sensing)
	{
		if (now_time - change_state_time > tx_duration)
		{
			is_sensing = true;
			IsmTcpClient::tick();
		}
		else
		{
			return;
		}
	}
}

} /* namespace tcpsim */
