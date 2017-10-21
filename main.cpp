#include "neuron.h"
#include <iostream>


int main(){
	
	Neuron neuron;
	
	double h;//time interval
	double Iext;//external current when we are bewteen a and b
	double a;
	double b;
	double simtime = 0.0;
	double endtime;
	double Vth;//threshold value
	
	
	
	//getting the different constants for the simulation
	std::cout << "Enter the current in mV :\n";
    std::cin >> Iext;
    
    std::cout << "Enter the step time (h) in ms :\n";
    std::cin >> h;
    
    do
    {
	   std::cout << "Enter the end time in ms :\n";
	   std::cin >> endtime;
    } while (endtime <= 0);
  
	do
	{
		std::cout << "Enter the time interval :\n";
		std::cin >> a;
		std::cin >> b;
	} while (a >= b);
	
	std::cout << "Enter the threshold value :\n";
	std::cin >> Vth;
	
	//run the simulation for the neuron
	neuron.update(h, simtime, endtime, a, b, Iext, Vth);
	
	return 0;
}


