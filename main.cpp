#include "neuron.h"
#include <iostream>
#include <fstream>

using namespace std;


/** 
 * MAIN SINGLE-NEURON SIMULATION LOOP
 * --> Updates a given neuron during each step time, beginning at t = 0.
 * --> Writes the value of the membrane potential in a file after each time step.
 */

int main()
{
	/** CHANGE THE SIMULATION TIMES HERE (in integers = *10 the time you want in ms)
	 *  endtime       --> when does the simulation end ?
	 *  current_start --> when does the current input start ?
	 *  current_end   --> when does the current input stop ?
	 */
	int endtime = 5000;
	int current_start = 1000;
	int current_end = 4000;
	double I_ext = 1.01;
	Neuron single_neuron;
	
	
	ofstream MembPotFile;  		
    MembPotFile.open ("./MembPotFile");
    MembPotFile << "Starting Simulation.\n";
	
	
	for( int simtime=0; simtime < endtime; ++simtime )
	{
		if( (current_start <= simtime) and (simtime < current_end) )
		{
			/** Current input time interval
			 *  --> set I_ext_ to the entered value up here.
			 *  --> else no current input.
			 */
			 single_neuron.setI_ext_(I_ext);
		}
		else
		{
			single_neuron.setI_ext_(0.0);
		}
		
		/** 
		 * Updating the neuron for a single time-step :
		 * --> store the membrane potential in a file.
		 * --> if the neuron spikes during this single time-step, write it in the terminal. */
		bool Spike = single_neuron.update(1);
		MembPotFile << "At time t= " << simtime*0.1 << "ms    V= " << single_neuron.getV_() << endl;
		
		if (Spike)
		{
			cout << " SPIKE AT t= " << simtime*0.1 << "ms" << endl;
		}
	}
	
	cout << " Number of spikes during the single-neuron simulation: " << single_neuron.getNum_Spikes_() << endl;
	
	return 0;
}


