#include "neuron.h"
#include <iostream>
#include <fstream>

using namespace std;


int main()
{

	int endtime = 5000;
	int current_start = 1000;
	int current_end = 4000;
	double I_ext = 1.01;
	int Delay = 15;
	
	Neuron single_neuron;
	Neuron connected_neuron;
	
	
	ofstream MembPotFile;  		
    MembPotFile.open ("./MembPotFile");
    MembPotFile << "Starting Simulation.\n";
	
	
	for( int simtime=0; simtime < endtime; ++simtime )
	{
		if( (current_start <= simtime) and (simtime < current_end) )
		{
			 single_neuron.setI_ext_(I_ext);
		}
		else
		{
			single_neuron.setI_ext_(0.0);
		}
		bool single_Spike = single_neuron.update_test(1);
		bool connected_Spike = connected_neuron.update_test(1);
		
		MembPotFile << "At time t= " << simtime*0.1 << "ms    V= " << connected_neuron.getV_() << endl;
		
		if (single_Spike)
		{
			 cout << " SPIKE FROM THE SINGLE NEURON AT t= " << simtime*0.1 << "ms" << endl;
			 connected_neuron.spike_receive(simtime+Delay, 0.1);
		}
		if (connected_Spike)
		{
			cout << " SPIKE FROM THE CONNECTED NEURON AT t= " << simtime*0.1 << "ms" << endl;
		}
	}
	
	cout << " Number of spikes for the single neuron : " << single_neuron.getNum_Spikes_() << endl;
	cout << " Number of spikes for the connected neuron : " << connected_neuron.getNum_Spikes_() << endl;
	
	return 0;
}
