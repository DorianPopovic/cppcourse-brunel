#include "neuron.h"
#include "Network.h"
#include <iostream>

using namespace std;

int main()
{
	int t_start =0;
	int t_stop =10000;
	

	
	Network Final_Network;
	cout << "autre connerie" << endl;
	
	Final_Network.Connect_Network();
	cout << "conneries" << endl;
	
	Final_Network.Simulate_Network(t_start, t_stop);
	
	
	return 0;
}
