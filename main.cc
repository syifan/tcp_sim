#include "Scheduler.h"
#include "BaseStation.h"
#include "IsmTcpClient.h"
#include "PrimaryUser.h"
#include "Channel.h"
#include "SimpleCrTcpClient.h"
#include "CrTcpClient.h"

int main()
{
	tcpsim::Scheduler *scheduler = tcpsim::Scheduler::getInstance();
	tcpsim::PrimaryUser *pu = tcpsim::PrimaryUser::getInstance();
	unsigned int ism_bandwidth = 5e6;
	unsigned int tv_bandwidth = 50e6;

	double time_granularity = 1e-3;
	unsigned int num_clients = 10;

	tcpsim::Channel *ism_channel = new tcpsim::Channel(ism_bandwidth);
	tcpsim::Channel *simple_cr_ism_channel = new tcpsim::Channel(ism_bandwidth);
	tcpsim::Channel *cr_ism_channel = new tcpsim::Channel(ism_bandwidth);

	tcpsim::Channel *tv_channel[num_clients];
	tcpsim::Channel *simple_cr_tv_channel[num_clients];
	tcpsim::Channel *cr_tv_channel[num_clients];


	tcpsim::BaseStation ism_tcp_base_station;
	tcpsim::BaseStation tv_tcp_base_station;
	tcpsim::BaseStation simple_cr_base_station;
	tcpsim::BaseStation cr_base_station;

	tcpsim::IsmTcpClient *ism_tcp_client[num_clients];
	tcpsim::IsmTcpClient *tv_tcp_client[num_clients];
	tcpsim::SimpleCrTcpClient *simple_cr_client[num_clients];
	tcpsim::CrTcpClient *cr_client[num_clients];

	for (unsigned int i = 0; i < num_clients; i++)
	{
		ism_tcp_client[i] = new tcpsim::IsmTcpClient(
				i, &ism_tcp_base_station, ism_channel);

		tv_channel[i] = new tcpsim::Channel(tv_bandwidth);
		tv_tcp_client[i] = new tcpsim::IsmTcpClient(
				i+num_clients, &tv_tcp_base_station, tv_channel[i]);

		simple_cr_tv_channel[i] = new tcpsim::Channel(tv_bandwidth);
		simple_cr_client[i] = new tcpsim::SimpleCrTcpClient(i+2*num_clients,
				&simple_cr_base_station, simple_cr_ism_channel,
				simple_cr_tv_channel[i]);

		cr_tv_channel[i] = new tcpsim::Channel(tv_bandwidth);
		cr_client[i] = new tcpsim::CrTcpClient(i+3*num_clients,
				&cr_base_station, cr_ism_channel,
				cr_tv_channel[i]);

	}



	// Main loop
	while(1)
	{
		scheduler->tick(time_granularity);
		pu->tick();
		ism_tcp_base_station.tick();
		tv_tcp_base_station.tick();
		simple_cr_base_station.tick();
		cr_base_station.tick();

		for(unsigned int i = 0; i < num_clients; i++)
		{
			ism_tcp_client[i]->tick();

			tv_tcp_client[i]->tick();
			tv_channel[i]->tick();

			simple_cr_client[i]->tick();
			simple_cr_tv_channel[i]->tick();

			cr_client[i]->tick();
			cr_tv_channel[i]->tick();

		}
		simple_cr_ism_channel->tick();
		ism_channel->tick();
		cr_ism_channel->tick();
	}


}
