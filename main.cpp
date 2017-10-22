#include "neuron.h"
#include <iostream>
#include <fstream>

using namespace std;


/** 
 * MAIN TWO NEURONS CONNECTION SIMULATION LOOP
 * --> Updates two given neurons during each step time, beginning at t = 0.
 * --> Writes the value of the membrane potential in a file after each time step.
 * --> Makes the connected neuron deal with spikes, FIRST WITHOUT BUFFER.
 */

int main()
{
	/** CHANGE THE SIMULATION TIMES HERE (in integers = *10 the time you want in ms)
	 *  endtime          --> when does the simulation end ?
	 *  current_start    --> when does the current input start ?
	 *  current_end      --> when does the current input stop ?
	 *  single_neuron    --> has input current and can send spikes to the other neuron
	 *  connected_neuron --> no input current, receives spikes from the other neuron
	 */
	int endtime = 5000;
	int current_start = 1000;
	int current_end = 4000;
	double I_ext = 1.01;
	
	Neuron single_neuron;
	Neuron connected_neuron;
	
	
	ofstream MembPotFile;  		
    MembPotFile.open ("./MembPotFile");
    MembPotFile << "Starting Simulation.\n";
	
	
	for( int simtime=0; simtime < endtime; ++simtime )
	{
		if( (current_start <= simtime) and (simtime < current_end) )
		{
			/** Current input time interval ONLY FOR single_neuron who can send spikes
			 *  --> set I_ext_ to the entered value up here.
			 *  --> else no current input.
			 *  --> connected_neuron has no current input during the simulation
			 */
			 single_neuron.setI_ext_(I_ext);
		}
		else
		{
			single_neuron.setI_ext_(0.0);
		}
		
		/** 
		 * Updating the neuron(s) for a single time-step :
		 * --> store the membrane potential in a file, for the connected_neuron.
		 * --> if the neuron(s) spike during this single time-step, write it in the terminal. */
		bool single_Spike = single_neuron.update(1);
		bool connected_Spike = connected_neuron.update(1);
		
		MembPotFile << "At time t= " << simtime*0.1 << "ms    V= " << connected_neuron.getV_() << endl;
		
		if (single_Spike)
		{
			/** When the single_neuron spikes
			 * --> write it in terminal.
			 * --> connected neuron has to receive the spike (J=0.1).
			 */
			 cout << " SPIKE FROM THE SINGLE NEURON AT t= " << simtime*0.1 << "ms" << endl;
			 connected_neuron.spike_receive(0.1);
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


