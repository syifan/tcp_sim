#include "PrimaryUser.h"
#include "Scheduler.h"
#include "CrTcpClient.h"

namespace tcpsim
{

CrTcpClient::CrTcpClient(unsigned int id, BaseStation *base_station,
					Channel *ism_channel, Channel *tv_channel) :
		IsmTcpClient(id, base_station, ism_channel)
{
	this->shared_channel = ism_channel;
	this->tv_channel = tv_channel;
}

CrTcpClient::~CrTcpClient()
{
	// TODO Auto-generated destructor stub
}

void CrTcpClient::tick()
{
	// Get current time
	// double now_time = Scheduler::getInstance()->getNowTime();

	// If sensing states
	if (state == 1)
	{
		PuPresentVerify();
	}
	else if(state == 2)
	{
		PuAbsentVerify();
	}

	// If transit states
	if (state == 3)
	{state = 0;}
	else if(state == 4)
	{state = 0;}
	else if(state == 5)
	{state = 0;}
	else if(state == 6)
	{state = 0;}

	// Traditional TCP state
	if (state == 0)
	{
		Transmit();
	}

}


void CrTcpClient::PuAbsentVerify()
{
	double now_time = Scheduler::getInstance()->getNowTime();

	// Pause timer during sensing
	PauseTimer();
	if (now_time - change_state_time > sensing_duration)
	{
		is_sensing = false;
		PrimaryUser *pu = PrimaryUser::getInstance();
		if (pu->isOn())
		{
			this->ism_channel = shared_channel;
			state = 5;
			pu_present = true;
		}
		else
		{
			this->ism_channel = tv_channel;
			state = 6;
			pu_present = false;
		}
		change_state_time = now_time;
	}
	else
	{
		return;
	}
}


void CrTcpClient::PuPresentVerify()
{
	double now_time = Scheduler::getInstance()->getNowTime();

	// Pause TCP timer during sensing.
	PauseTimer();
	if (now_time - change_state_time > sensing_duration)
	{
		is_sensing = false;
		PrimaryUser *pu = PrimaryUser::getInstance();
		if (pu->isOn())
		{
			this->ism_channel = shared_channel;
			state = 3;
			pu_present = true;
		}
		else
		{
			this->ism_channel = tv_channel;
			state = 4;
			pu_present = false;
		}
		change_state_time = now_time;
	}
	else
	{
		return;
	}
}

void CrTcpClient::Transmit()
{
	double now_time = Scheduler::getInstance()->getNowTime();
	if (now_time - change_state_time > tx_duration)
	{
		is_sensing = true;
		if (pu_present)
			state = 1;
		else
			state = 2;
		change_state_time = now_time;
	}
	else
	{
		IsmTcpClient::tick();
	}
}

} /* namespace tcpsim */
