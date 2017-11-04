#include "neuron.h"
#include "Network.h"
#include <iostream>

using namespace std;

int main()
{
	/***
	 * Change the times you want to simulate the network here 
	 *  --> t_start = start for the simulation
	 *  --> t_stop = stop for the simulation 
	 ****/
	 int t_start =0;
	 int t_stop =12000;
	
	
	Network Final_Network;
	Final_Network.Connect_Network();
	Final_Network.Simulate_Network(t_start, t_stop);
	
	return 0;
}
