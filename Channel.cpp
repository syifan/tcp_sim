#include <iostream>
#include <cmath>

#include "Misc.h"
#include "Channel.h"

namespace tcpsim {

Channel::Channel(unsigned int bandwidth) {
	this->bandwidth = bandwidth;
}

Channel::~Channel() {
}


double Channel::getTransProb() const
{
	unsigned int packet_size_in_bit = 4000;

	// Random channel efficiency from 0.3 - 0.8
	double channel_efficiency = ( 0.1 * (double)rand()/RAND_MAX ) + 0.9;

	double time_to_send_one_packet = (double)packet_size_in_bit
			/ bandwidth;

	double max_packet_can_send = wait_time
			/ time_to_send_one_packet * channel_efficiency;

	double prob = max_packet_can_send / packet_to_trans;

//	std::cout << "Num_packet_to_send: " << packet_to_trans
//			<< ", Probability: " << prob << "\n";
	return prob;
}


double Channel::getHaveErrorPacket(unsigned int num_packet) const
{
	return 1 - pow((1 - packet_error_rate), num_packet);
}


void Channel::TransmitOn(Client *from,
		BaseStation* to, unsigned int num_packets)
{
	Transmission *trans = new Transmission();
	trans->from = from;
	trans->to = to;
	trans->num_packet = num_packets;

	packet_to_trans += num_packets;
	transmissions.push_back(std::unique_ptr<Transmission>(trans));
}


void Channel::tick()
{
	if (transmissions.empty())
		return;

	std::random_shuffle(transmissions.begin(), transmissions.end());
	for(auto it = transmissions.begin(); it != transmissions.end(); it++)
	{
		Transmission *tran = (*it).get();
		double prob = getTransProb();
		double error_prob = this->getHaveErrorPacket(tran->num_packet);
		if (Misc::Happen(prob) && (!Misc::Happen(error_prob)))
		{
			tran->to->Receive(tran->num_packet, tran->from);
		}
	}
	transmissions.clear();
	this->packet_to_trans = 0;
}

} /* namespace tcpsim */
