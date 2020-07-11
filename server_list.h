#pragma once

const int max_servers{ 10 };
const int max_simulation_length{ 10000 };
const int max_transaction_length{ 1000 };
const int max_time_between_arrivals{ 1000 };
const int max_queue_size{ 100 };

class ServerType;

class ServerList
{
private:
	int numServers;
	ServerType* servers;   // store a list of servers using dynamically allocated array
public:
	ServerList(int number);
	~ServerList();
	void GetFreeServerID(int& serverID, bool& found);
	void EngageServer(int serverId, int transactionTime);
	void UpdateBusyServersTimes();
};
