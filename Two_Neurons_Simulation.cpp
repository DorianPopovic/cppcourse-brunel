#include "neuron.h"
#include <iostream>
#include <fstream>

using namespace std;


int main()
{
	/*************************************************************************
	 *   CHANGE THE SIMUALTION CONSTANTS HERE
	 * 
	 * -> endtime: when does the simulation end ?
	 * -> current_start: when does the input begin ?
	 * -> current_start: when does the input stop ?
	 * -> I_ext: how much is the external input ?
	 * -> Delay : how many time does the spike take to travel (1.5 ms for us)
	 *************************************************************************/

	int endtime = 5000;
	int current_start = 1000;
	int current_end = 4000;
	double I_ext = 1.01;
	int Delay = 15;
	
	Neuron single_neuron;
	Neuron connected_neuron;
	
	single_neuron.simulate_two_neurons(connected_neuron, endtime, current_start, current_end, I_ext, Delay);

	
	return 0;
}
