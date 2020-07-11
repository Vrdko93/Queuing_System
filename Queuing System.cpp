// General purpose simulation program that determines how long items, such as people or cars must wait in line before being served.
// It takes four input values (simulation length, number of servers, transaction time, time between arrivals) and then calculates
// the average time for waiting. Time is represented in minutes.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <vector>
#include <iomanip>
#include "server_list.h"
#include "job_type.h"
using namespace std;

struct ParametersType
{
    int timeLimit;
    int numServers;
    int transactionTime;
    int timeBetween;
};

void GetParameters(ParametersType& simulationInput);
bool Job_Arrives(int time_between);
void UpdateQueue(queue<JobType>& sim_wait_queue);
void ExecuteSimulation(ParametersType& simulationInput);
void SimulationDriver();

int main()
{
    srand(time(0));
    SimulationDriver();
}

void GetParameters(ParametersType& simulationInput)
{
    simulationInput.timeLimit = 1000;
    simulationInput.transactionTime = 5;
    simulationInput.numServers = 2;
    simulationInput.timeBetween = 3;
}

bool Job_Arrives(int time_between)
{
   
    float arrivalProb = 1.0 / time_between;
    float value = float(rand()) / float(RAND_MAX);
    return value <= arrivalProb;
}

void UpdateQueue(queue<JobType>& sim_wait_queue)
{
    int size = sim_wait_queue.size();
    for (int i = 0; i < size; i++)
    {
        auto job = sim_wait_queue.front();
        sim_wait_queue.pop();
        job.IncrementWaitTime();
        sim_wait_queue.push(job);
    }
}

void ExecuteSimulation(ParametersType& simulationInput)
{
    int total_wait_time = 0;
    int num_jobs_served = 0;
    int clock = 0;             // simulation clock

    ServerList sim_server_list(simulationInput.numServers);
    queue<JobType> wait_queue;

    int server_id;
    bool server_found;

    while (clock != simulationInput.timeLimit)
    {
        clock++;
        sim_server_list.UpdateBusyServersTimes();
        UpdateQueue(wait_queue);

        if (Job_Arrives(simulationInput.timeBetween))
            wait_queue.push(JobType{});

        sim_server_list.GetFreeServerID(server_id, server_found);
        if (server_found && !wait_queue.empty())
        {
             auto job = wait_queue.front();
             wait_queue.pop();
             num_jobs_served++;
             total_wait_time += job.GetWaitTime();
             sim_server_list.EngageServer(server_id, simulationInput.transactionTime);
        }
    }

    float average_wait_time;
    if (num_jobs_served > 0)
        average_wait_time = float(total_wait_time) / float(num_jobs_served);
    else
        average_wait_time = 0;

    cout << setprecision(2) << fixed;
    cout << "------------------Simulation Results----------------------\n";
    cout << "\nSimulation length = " << simulationInput.timeLimit << endl;
    cout << "Number of Servers = " << simulationInput.numServers << endl; 
    cout << "Average Transaction = " << simulationInput.transactionTime << endl;
    cout << "Time Between Arrivals = " << simulationInput.timeBetween << endl;
    cout << "Average Wait = " << average_wait_time << endl;
    cout << "Jobs Left = " << wait_queue.size() << endl;
}

void SimulationDriver()
{
    ParametersType simulationInput;
    GetParameters(simulationInput);
    string runAgain;

    cout << "Executing simulation with pre-defined values\n\n";
    ExecuteSimulation(simulationInput);

    cout << "\nDo you want to run the simulation with user input values? yes/no ";
    cin >> runAgain;

    while (runAgain == "yes")
    {
        cout << "Type in a value for time in minutes for simulation length: ";
        cin >> simulationInput.timeLimit;
        cout << "Type in a value for the number of servers: ";
        cin >> simulationInput.numServers;
        cout << "Type in a value for time in minutes for average transaction time: ";
        cin >> simulationInput.transactionTime; 
        cout << "Type in a value for time in minutes for time between arrivals: ";
        cin >> simulationInput.timeBetween;
        cout << endl;

        ExecuteSimulation(simulationInput);

        cout << "\nDo you want to run the simulation again with user input values? yes/no ";
        cin >> runAgain;
    }
}