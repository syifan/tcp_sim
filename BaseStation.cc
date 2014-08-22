#include "Scheduler.h"
#include "BaseStation.h"

namespace tcpsim
{

BaseStation::BaseStation()
{
	// TODO Auto-generated constructor stub

}

BaseStation::~BaseStation()
{
	// TODO Auto-generated destructor stub
}

void BaseStation::tick()
{
	double now_time = Scheduler::getInstance()->getNowTime();
	double time_passed = now_time - last_tick_time;

	ConsumePackets(time_passed);

	last_tick_time = now_time;
}


void BaseStation::ConsumePackets(double time_passed)
{
	// Consume packets in buffer

	unsigned int buffer_consume_this_tick = time_passed
			* buffer_consume_per_second;
	if (buffer_fullness <= buffer_consume_this_tick)
	{
		buffer_fullness = 0;
	}
	else
	{
		buffer_fullness -= buffer_consume_this_tick;
	}
}


void BaseStation::Receive(unsigned int num_packet, Client *client)
{
	this->buffer_fullness += num_packet;
	if (buffer_fullness > buffer_size)
	{
		buffer_fullness = buffer_size;
		client->ReceiveAck("dup");
		return;
	}
	client->ReceiveAck("ack");
}

} /* namespace tcpsim */
