/*
 *  Multi2Sim
 *  Copyright (C) 2014  Yifan Sun (yifansun@coe.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef ISMTCPCLIENT_H_
#define ISMTCPCLIENT_H_

#include "Logger.h"
#include "Client.h"
#include "Channel.h"

namespace tcpsim
{

class Logger;

class IsmTcpClient: public Client
{
protected:

	/// TCP state, 0 - ss, 1 - ac
	unsigned int tcp_state = 0;

	/// Is waiting for ack
	bool is_waiting_for_ack = false;

	/// The time when the last packet is sent
	double last_packet_send_time = 0;

	/// The time when tick or pause timer called
	double last_tick_time = 0;

	/// Congestion window
	double congestion_window = 1;

	/// After sending a packet, this value is set to "no". When the
	/// base station receive a packet and reply with an ack, set it to
	/// "dup" or "ack"
	std::string ack_received = "no";

	/// Slow start threshold
	unsigned int ss_threshold = 100000;

	/// ISM channel to use
	Channel *ism_channel;

	/// Loggers
	std::unique_ptr<Logger> cw_logger;
	std::unique_ptr<Logger> throughput_logger;

public:

	/// Constructor
	IsmTcpClient(unsigned int id, BaseStation *base_station,
			Channel *ism_channel);

	/// Destructor
	virtual ~IsmTcpClient();

	/// Receive an ack
	void ReceiveAck(const std::string& ack);

	/// Do action
	void tick();

	/// Pause the timer when upper layer requires
	void PauseTimer();

	/// Set congestion window
	void setCongestionWindow(double cw);

	/// Send a bunch of packets
	void SendPackets();

	/// Increase congestion window linearly or exponentially
	void ProcessPositiveAck();

	/// Cut congestion window by half
	void ProcessDuplicatedAck();

	/// Reset congestion window to 1
	void ProcessAckTimeout();
};

} /* namespace tcpsim */

#endif 
