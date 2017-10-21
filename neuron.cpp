#include "neuron.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

Neuron:: Neuron()
    :
    RefSteps_ (static_cast<const unsigned long>( Reftime_ / h_)),
    V_(0.0),
    I_ext_(0.0),
    Num_Spikes_(0),
    Last_Spike_time_(0),
    Clock_(0)
    {
		C1_ = exp(-h_ / Tau_);
		C2_ = R_*(1.0 - C1_);
	}


//---------------METHODS GIVING ACCESS TO THE ATTRIBUTES-------------//

double Neuron::getV_() const
{
	return V_;
}

double Neuron::getI_ext_()
{
	return I_ext_;
}

unsigned long Neuron::getNum_Spikes_() const
{
	return Num_Spikes_;
}

unsigned long Neuron::getLast_Spike_time_() const
{
	return Last_Spike_time_;
}

unsigned long Neuron::getClock_() const
{
	return Clock_;
}



//------------METHODS SETTING THE VALUES FOR THE ATTRIBUTES------------//

void Neuron::setV_(double v)
{
	V_ = v;
}

void Neuron::setI_ext_(double i)
{
	I_ext_ = i;
}

void setLast_Spike_time_(unsigned long T)
{
	Last_Spike_time_ = T;
}




//final upadte method
void Neuron::update(double h, double simtime, double endtime, double a, double b, double Iext, double Vth)
{
	double I;
	ofstream MembPotFile;  		//Instantiate output file
    MembPotFile.open ("./MembPotFile");	//Open with a given name
    MembPotFile << "Starting Simulation.\n";
	
	while (simtime < endtime)
	{
		if ( (a <= simtime) and (simtime < b)) // sets incoming current during the decide time interval
		{
			I = Iext;
		}
		else
		{
			I = 0.0;
		}
		
	    if ((!Time.empty()) and ((Time.back() <= simtime) and (simtime <= (Time.back() + 1)))) // refractory period is 1ms
		{
			MembPotFile << " REFRACTORY PERIOD V = " << V << endl;
		}
		else if ( Vth < V )
		{
			Time.push_back(simtime);
			++Spikes;
			cout << " SPIKE AT " << simtime << " ms" << endl;
			V = 10.0;
		}
		
		else 
		{
			double newV = exp(-h/Tau)*V + I*R*(1 - exp(-h/Tau));
		    V = newV;
			
		}
		
		simtime += h;
		MembPotFile << " At time : " << simtime << "ms, V = " << V << endl;
		
	}
	
	MembPotFile.close();
}
