#include "neuron.h"
#include <iostream>


int main(){
	
	Neuron neuron;
	double I;
	
	//getting the different constants for the simulation
	std::cout << "Enter the current in mV :\n";
    std::cin >> I;
    
    
    //run the simulation for the neuron
	neuron.update(h, simtime, endtime, a, b, Iext, Vth);
	
	return 0;
}


