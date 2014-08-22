#include <iostream>
#include <cmath>

#include "Scheduler.h"
#include "Misc.h"
#include "IsmTcpClient.h"

namespace tcpsim
{

IsmTcpClient::IsmTcpClient(unsigned int id, BaseStation *base_station,
		Channel *ism_channel) :
				Client(id, base_station)
{
	cw_logger.reset(new Logger("cw" + std::to_string(id) + ".log"));
	throughput_logger.reset(new Logger("throughput" + std::to_string(id) + ".log"));
	this->ism_channel = ism_channel;
	this->congestion_window = ceil(((double)rand()/RAND_MAX) * 100) ;

}

IsmTcpClient::~IsmTcpClient()
{
	cw_logger.release();
	throughput_logger.release();
}


void IsmTcpClient::ReceiveAck(const std::string& ack)
{
	ack_received = ack;
}


void IsmTcpClient::setCongestionWindow(double cw)
{
	if (cw < 1)
	{
		try{
			throw cw;
		}
		catch(double cw){
			std::cerr << "Set congestion window to be less than 1.\n";
		}
	}

	congestion_window = cw;
	cw_logger->Log(std::to_string(cw));
}


void IsmTcpClient::PauseTimer()
{
	// Get now time
	double now_time = Scheduler::getInstance()->getNowTime();

	// Get time passed since last tick or pause timer
	double time_passed = now_time - last_tick_time;

	// Move the timers in the client forward
	last_packet_send_time += time_passed;

	// Record current time
	last_tick_time = now_time;
}


void IsmTcpClient::tick()
{
	// Get now time
	double now_time = Scheduler::getInstance()->getNowTime();
	last_tick_time = now_time;

	// During the time waiting for ack, check if the ack is received.
	if (is_waiting_for_ack)
	{
		double time_passed = now_time - last_packet_send_time;

		// Wait until the ack packet to be back
		if(time_passed < ism_channel->getWaitTime())
		{
			return;
		}

		if(ack_received == "ack") // ACK received
		{
			is_waiting_for_ack = false;
			ProcessPositiveAck();
		}
		else if(ack_received == "dup" ) // Duplicate ack received
		{
			is_waiting_for_ack = false;
			ProcessDuplicatedAck();
		}
		else
		{
			// Determine if ack time out
			if (time_passed > 2 * ism_channel->getWaitTime())
			{
				ProcessAckTimeout();
			}
			else // still wait for tcp action
			{
				return;
			}
		}
	}

	// Send packets
	SendPackets();

}


void IsmTcpClient::ProcessPositiveAck()
{
	if (tcp_state == 0)
	{
		setCongestionWindow(congestion_window * 2);
		if (congestion_window >= ss_threshold)
		{
			tcp_state = 1;
		}
	}
	else
	{
		setCongestionWindow(congestion_window + 1);
	}
}


void IsmTcpClient::ProcessDuplicatedAck()
{
	tcp_state = 1; // State in collision avoidance
	if (congestion_window >2)
	{
		ss_threshold = congestion_window / 2;
		setCongestionWindow(ss_threshold);
	}
	else
	{
		ss_threshold = 1;
		setCongestionWindow(ss_threshold);
	}
}


void IsmTcpClient::ProcessAckTimeout()
{
	tcp_state = 0; // Back to slow start phase
	ss_threshold = congestion_window / 2;
	setCongestionWindow(1);
	is_waiting_for_ack = false;
}


void IsmTcpClient::SendPackets()
{
	double now_time = Scheduler::getInstance()->getNowTime();
	is_waiting_for_ack = true;
	ack_received = "no";
	this->last_packet_send_time = now_time;
	throughput_logger->Log(std::to_string(congestion_window));

	ism_channel->TransmitOn(this, base_station, ceil(congestion_window));

}

} /* namespace tcpsim */
