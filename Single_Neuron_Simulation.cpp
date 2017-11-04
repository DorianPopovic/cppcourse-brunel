#include "neuron.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	/***********************************************
	 *   CHANGE THE SIMUALTION CONSTANTS HERE
	 * 
	 * -> endtime: when does the simulation end ?
	 * -> current_start: when does the input begin ?
	 * -> current_start: when does the input stop ?
	 * -> I_ext: how much is the external input ?
	 ***********************************************/
	
	int endtime = 5000;
	int current_start = 0;
	int current_end = 4000;
	double I_ext = 1.01;
	
	Neuron single_neuron;
	
	
	single_neuron.simulate_one_neuron(endtime, current_start, current_end, I_ext);
	
	return 0;
}
