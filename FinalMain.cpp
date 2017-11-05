#include "neuron.h"
#include "Network.h"
#include <iostream>

using namespace std;

int main()
{
	/***
     * Change the time you want to simulate the network for below
	 *  --> t_start = start for the simulation
	 *  --> t_stop = stop for the simulation 
	 * 
	 * DEPENDING ON WHAT BRUNELS FIGURE YOU WANT TO PLOT:
	 * A) t_start =0 & t_stop = 6000
	 * B) t_start =0 & t_stop = 12000
	 * C) t_start =0 & t_stop = 12000
	 * D) t_start =0 & t_stop = 12000
	 * 
	 * ==> GO TO Neuron.cpp update method for further instructions before simulation.
	 ****/
	 int t_start =0;
	 int t_stop =6000;
	
	
	Network Final_Network;
	
	/***
	 * Uncomment as follow before simulation !! (J_In_ is 0.0 by default) !!
	 * first line for figure A)
	 * second line for figure B)
	 * third line for figure C)
	 * fourth line for figure D)
	 ***/
	 /*Final_Network.setJ_In_(-0.3);*/
	 /*Final_Network.setJ_In_(-0.6);*/
	 /*Final_Network.setJ_In_(-0.5);*/
	 /*Final_Network.setJ_In_(-0.45);*/
	 
	 
	Final_Network.Connect_Network();
	Final_Network.Simulate_Network(t_start, t_stop);
	
	return 0;
}
