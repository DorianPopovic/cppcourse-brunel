#include "Network.h"
#include <random>
#include <fstream>
#include <iostream>

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
		for (size_t i=0; i<TotalNeurons_; i++)
		{
			All_Neurons_.push_back(Neuron());
		}
		
		for (size_t j=0; j<TotalNeurons_; ++j)
		{
			vector<int> empty;
			Connections_.push_back(empty);
		}
	}




void Network::Connect_Network()
{
	//cout << "je suis dans simulate" << endl;
	
	for (size_t neuron_i=0;  neuron_i < TotalNeurons_; neuron_i++)
	{
		for (size_t i=0; i<Num_Ce_; ++i)
		{
			//random ( 0 à Num_Ex )
			//[random].pushback(neuron_i)
			
			static random_device rd;
			static mt19937 gen(rd());
			static uniform_int_distribution<> connected_neuron(0, Num_Ex_ -1);
			//cout << " avant connections" << endl;
			Connections_[connected_neuron(gen)].push_back(neuron_i);
			//cout << " apres connections" << endl;
		}
		for (size_t j=10000; j<(10000 + Num_Ci_); ++j)
		{
			//cout << "2eme boucle for" << endl;
			//random (10000 à 10000+Num_Im)
			//[random].pushback(neuron.1)
			
			static random_device rd;
			static mt19937 gen(rd());
			static uniform_int_distribution<> connected_neuron(Num_Ex_, (TotalNeurons_ -1));
			
			Connections_[connected_neuron(gen)].push_back(neuron_i);
		}
	}
}


void Network::Simulate_Network(int simtime, int t_stop)
{
	ofstream Spikesfile;  		
    Spikesfile.open ("./spikes.gdf");
    
	int progress(1);
	int progress_rate(0.01*t_stop);
    
   
	 while (simtime < t_stop)
	{
		
		if(simtime > progress_rate)
		{
			cout << progress << "%" << endl;
			++progress;
			progress_rate += 0.01*t_stop;
		}
		
		for (size_t i=0; i < All_Neurons_.size(); ++i)
		{
			//cout << "updating neuron" << i<< endl;
			if (All_Neurons_[i].update(1))
			{
				Spikesfile << simtime << "\t" << i << "\n";
				
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
	
}
