#include "server_type.h"
#include "server_list.h"

ServerList::ServerList(int number)
{
	numServers = number;
	servers = new ServerType[numServers];
}

ServerList::~ServerList()
{
	delete[] servers;
}

// Find an index of a free server and store it in the output parameters
void ServerList::GetFreeServerID(int& serverID, bool& found)
{
	for (int i = 0; i < numServers; i++)
	{
		if (servers[i].IsFree())
		{
			serverID = i;
			found = true;
			return;
		}
	}
	found = false;
}

void ServerList::EngageServer(int serverId, int transactionTime)
{
	bool server_found;
	GetFreeServerID(serverId, server_found);
	if (server_found)
	{
		servers[serverId].SetTimeRemaining(transactionTime);
		servers[serverId].SetBusy();
	}
}

void ServerList::UpdateBusyServersTimes()
{
	for (int i = 0; i < numServers; i++)
		if (!servers[i].IsFree())
			servers[i].DecrementTimeRemaining();
}
