#include "Network.h"
#include <random>
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;



Network:: Network()
	:
	TotalNeurons_(12500),
	Num_Ex_(10000),
	Num_In_(2500),
	Num_Ce_(0.1*Num_Ex_),
	Num_Ci_(0.1*Num_In_),
	J_Ex_(0.1),
	J_In_(-0.5),
	DELAY_(15)
	{
		/*** 
		 * from 0 to 9999 the will be excitatory
		 * from 9999 to 12499 the will be inhibitory
		 ***/
		for (size_t i=0; i<TotalNeurons_; i++)
		{
			All_Neurons_.push_back(Neuron());
		}
		assert(All_Neurons_.size()==TotalNeurons_);
		/***
		 * Each neurons gets an empty vector of
		 * neurons it has to send the spike to
		 ***/
		for (size_t j=0; j<TotalNeurons_; ++j)
		{
			vector<int> empty;
			Connections_.push_back(empty);
			assert(Connections_[j].empty());
		}
	}



/*************************************************************************************
* 				 CONNECTION METHOD
*************************************************************************************/
void Network::Connect_Network()
{
	
	for (size_t neuron_i=0;  neuron_i < TotalNeurons_; neuron_i++)
	{
		/***
		 * iterating for every neuron as following :
		 * --> for each neuron we will choose a random number 
		 * --> two times (first 1000 times for excitatory then 250 times for inhibitory)
		 * --> the random number chosen means that this neuron will have to send its 
		 *     spikes to the neuron we are iterating on
		 * --> so we push back the index of the neuron we are iterating on
		 *     to the randomly chosen number
		 * ***/                  
		
		
		//------------------------Excitatory loop--------------------//
		for (size_t i=0; i<Num_Ce_; ++i)
		{
			static random_device rd;
			static mt19937 gen(rd());
			static uniform_int_distribution<> connected_neuron(0, Num_Ex_ -1);
			
			Connections_[connected_neuron(gen)].push_back(neuron_i);
		}
		
		//------------------------Inhibitory loop--------------------//
		for (size_t j=10000; j<(10000 + Num_Ci_); ++j)
		{
			static random_device rd;
			static mt19937 gen(rd());
			static uniform_int_distribution<> connected_neuron(Num_Ex_, (TotalNeurons_ -1));
			
			Connections_[connected_neuron(gen)].push_back(neuron_i);
		}
	}
}


/*************************************************************************************
* 				 SIMULATE METHOD
*************************************************************************************/
void Network::Simulate_Network(int simtime, int t_stop)
{
	/***
	 * Checking if the 
	 * inputs are correct
	 ***/
	assert(simtime >= 0);
	assert(t_stop > 0);
	assert(t_stop > simtime);
	
	ofstream Spikesfile;  		
    Spikesfile.open ("./spikes.gdf");
    
	int progress(1);
	int progress_rate(0.01*t_stop);
    
   
	 while (simtime < t_stop)
	{
		
		if(simtime > progress_rate)
		{
			/***
			 * --> This is for showing the progression rate in percentage
			 ***/
			 
			 cout << progress << "%" << endl;
			 ++progress;
			 progress_rate += 0.01*t_stop;
		}
		
		
		
		for (size_t i=0; i < All_Neurons_.size(); ++i)
		{
			
			/***
			 * We update each neuron over one step time and if it spikes
			 * it has to send the weight (depending on if Ex or In)
			 * to all the neuron that it is connected to and we store in the file.
			 * So each neuron is connected to:
			 * --> 1000 random excitatory neurons
			 * --> 250 random inhibitory neurons
			 ***/
			
			
			if (All_Neurons_[i].update(1))
			{
				/******
				 * Uncomment as following to get the same time interval as 
				 * in Brunel's figure 8 (1000ms to 1200ms) depending 
				 * on what plot you want to reproduce:
				 * ==> First "if loop" for figure A)
				 * ==> Second "if loop" for figure B), C) and D)
				 ******/
				/*if (5000<simtime and simtime <6000)
				{
					Spikesfile << simtime << "\t" << i << "\n";
				}*/
				
				/*if (10000<simtime and simtime <12000)
				{
					Spikesfile << simtime << "\t" << i << "\n";
				}*/
				
				/***
				 * UNCOMMENT ME IF YOU CHOSE THE FASTER SIMULATION
				 ***/
				 /*Spikesfile << simtime << "\t" << i << "\n";*/
				
			
				for (size_t j=0; j<Connections_[i].size(); ++j)
				{
					int receiver (Connections_[i][j]);
					
					if (i < Num_Ex_ )
					{
						All_Neurons_[receiver].spike_receive(simtime+DELAY_, J_Ex_);
					}
					else
					{
						All_Neurons_[receiver].spike_receive(simtime+DELAY_, J_In_);
					}
				}
			}
		}
		
	++ simtime;
	}
	
	Spikesfile.close();
}



/*****************************************
* 		SETTERS
*****************************************/
void Network::setJ_In_(double J_In)
{
	J_In_=J_In;
}
