#ifndef NETWORK_H
#define NETWORK_H
#include "neuron.h"
#include <vector>

using namespace std;



class Network{
	
	//-------------------PUBLIC ARGUMENTS AND METHODS PROTOTYPES--------------//
	
	public:
	Network();
	
	void Connect_Network();
	
	void Simulate_Network(int, int);
	
	
	//--------------------------------PRIVATE ARGUMENTS---------------------------------//
	
	private:
	
	//-----------------ARGUMENTS FOR THE NEURON NETWORK-----------------//
	
	vector<Neuron> All_Neurons_;
	
	vector< vector<int> > Connections_;
	
	
	
	//---------CONSTANTS FOR THE NETWORK SIMULATION-----------//
	
	int TotalNeurons_;
	int Num_Ex_;
	int Num_In_;
	int Num_Ci_;
	int Num_Ce_;
	double J_Ex_;
	double J_In_;
	int DELAY_;
	
	
};  

#endif /* NETWORK_H */
