#include "neuron.h"
#include <cmath>
#include <random>
#include <fstream>
#include <iostream>

using namespace std;


/************************************************** 
 * 	   	   CONSTRUCTOR
*************************************************/

Neuron:: Neuron()
    :
    /**
    * Converting the steps for the refractory
    * period to have an unsigned long
    **/
    RefSteps_ (static_cast<const unsigned long>( RefTime_ / h_)),
    V_(0.0),
    I_ext_(0.0),
    Num_Spikes_(0),
    Last_Spike_time_(0),
    Clock_(0),
    Delay_(1.5),
    Buffer_()
    {
		C1_ = exp(-h_ / Tau_);
		C2_ = R_*(1.0 - C1_);
		
		/***
		 * Computes the smallest integer value not less than (Delay_/h_)
		 ***/
		DelaySteps_ = static_cast<unsigned long>(ceil(Delay_/h_));
		
		/***
		 * Make sur that the buffer has the right size
		 ***/
		 Buffer_.resize(DelaySteps_ + 1, 0.0);
	}




/************************************************** 
 * 	   	    GETTERS
*************************************************/

double Neuron::getV_() const
{
	return V_;
}

double Neuron::getI_ext_() const
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





/************************************************** 
 * 	   	    SETTERS
*************************************************/

void Neuron::setV_(double v)
{
	V_ = v;
}

void Neuron::setI_ext_(double i)
{
	I_ext_ = i;
}

void Neuron::setLast_Spike_time_(unsigned long T)
{
	Last_Spike_time_ = T;
}




/************************************************** 
 * 	          UPDATE METHODS
*************************************************/

bool Neuron::update(unsigned long simsteps)
{
	if (simsteps == 0) return false;
	
	bool spike = false;
	
	/***
	* How many steps until we stop the updating
	***/
	const auto stoptime_ = Clock_ + simsteps;
	
	
	while (Clock_ < stoptime_)
	{
		const auto IN = Clock_ % (DelaySteps_ + 1);
		if ( Vth_ < V_ ) 
		{
			 /***
			 *Spike occurs :
			 *  --> increment the number of spikes.
			 *  --> time of the last spike is the internal clock time.
			 ***/
			 spike = true;
			 ++Num_Spikes_;
			 Last_Spike_time_ = Clock_;
			
		}
		if ((Last_Spike_time_ > 0 ) and ((Clock_ - Last_Spike_time_) < RefSteps_)) 
		{
			 /***
			 * Refractory period is until we didn't 
			 * pass the last spike time by (RefSteps)
			 ***/
			 V_ = 0.0;
		}
		else
		{
			 
			  /***
			   * generating the random devices for
			   * the poisson distribution calculation 
			   ***/
			   static random_device rd;
			   static mt19937 gen(rd());
			   static poisson_distribution<> Ext_Rate_(2);
			   
			  /***
			   * We solve equation for the membrane potential
			   *   --> using the constants computed earlier
			   *   --> adding what is in the buffer
			   *   --> generating random external input using poisson distribution
			   ***/
			   V_ = C1_*V_ + I_ext_*C2_ + Buffer_[IN] + Ext_J_*Ext_Rate_(gen);
		}
		
	    /***
	     * don't forget to clean buffer and 
	     * increment clock at each time steps
	     ***/
	    Buffer_[IN] = 0.0;
	    ++Clock_;
	}
	return spike;
}



/***
 * Same function as update function excpet there is no random external input.
 * Use for the google tests to still work after we add poisson distribution.
***/
bool Neuron::update_test(unsigned long simsteps)
{
	if (simsteps == 0) return false;
	
	bool spike = false;
	const auto stoptime_ = Clock_ + simsteps;
	
	
	while (Clock_ < stoptime_)
	{
		const auto IN = Clock_ % (DelaySteps_ + 1);
		if ( Vth_ < V_ ) 
		{
			spike = true;
			++Num_Spikes_;
			Last_Spike_time_ = Clock_;
		}
		if ((Last_Spike_time_ > 0 ) and ((Clock_ - Last_Spike_time_) < RefSteps_)) 
		{
			 V_ = 0.0;
		}
		else
		{
			V_ = C1_*V_ + I_ext_*C2_ + Buffer_[IN]; 
		}
		
	    Buffer_[IN] = 0.0;
	    ++Clock_;
	}
	return spike;
}





/************************************************** 
 * 	    METHOD TO RECEIVE THE SPIKES
*************************************************/

void Neuron::spike_receive(unsigned long t, double J)
{
	/***
	 * Received spike will be received (OUT)
	 * after 15 steps so we put it into buffer[16]
	 * and when we reach that buffer index in
	 * the update method we take it out
	 ***/
	const size_t OUT = t % (DelaySteps_ + 1);
	Buffer_[OUT] += J;
}




/******************************************************************************************************** 
 * 	    						METHOD THAT SIMULATES THE NEURON
*********************************************************************************************************/
void Neuron::simulate_one_neuron(int endtime, int current_start, int current_end, double I_ext)
{
	
	ofstream MembPotFile;  		
    MembPotFile.open ("./SingleNeuronMembPotFile");
    MembPotFile << "Starting Simulation.\n";
	
	
	for( int simtime=0; simtime < endtime; ++simtime )
	{
		if( (current_start <= simtime) and (simtime < current_end) )
		{
			 setI_ext_(I_ext);
		}
		else
		{
			setI_ext_(0.0);
		}
		
		bool single_Spike = update_test(1);
		MembPotFile << "At time t= " << simtime*0.1 << "ms    V= " << getV_() << endl;
		
		if (single_Spike)
		{
			cout << " SPIKE FROM THE SINGLE NEURON AT t= " << simtime*0.1 << "ms" << endl;
		}
	}
	
	MembPotFile.close();
	cout << " Number of spikes for the single_neuron : " << getNum_Spikes_() << endl;
}




/*********************************************************************************************************************************** 
 * 	    						   METHOD THAT SIMULATES TCONNECTION BETWEEN TWO NEURONS WITH BUFFER
************************************************************************************************************************************/
void Neuron::simulate_two_neurons(Neuron connected_neuron, int endtime, int current_start, int current_end, double I_ext, int Delay)
{	
	ofstream MembPotFile;  		
    MembPotFile.open ("./TwoNeuronsMembPotFile");
    MembPotFile << "Starting Simulation.\n";
	
	
	for( int simtime=0; simtime < endtime; ++simtime )
	{
		if( (current_start <= simtime) and (simtime < current_end) )
		{
			 setI_ext_(I_ext);
		}
		else
		{
			setI_ext_(0.0);
		}
		bool single_Spike = update_test(1);
		bool connected_Spike = connected_neuron.update_test(1);
		
		MembPotFile << "At time t= " << simtime*0.1 << "ms    V= " << connected_neuron.getV_() << endl;
		
		if (single_Spike)
		{
			 cout << " SPIKE FROM THE SINGLE NEURON AT t= " << simtime*0.1 << "ms" << endl;
			 connected_neuron.spike_receive(simtime+Delay, 0.1);
		}
		if (connected_Spike)
		{
			cout << " SPIKE FROM THE CONNECTED NEURON AT t= " << simtime*0.1 << "ms" << endl;
		}
	}
	
	cout << " Number of spikes for the single neuron : " << getNum_Spikes_() << endl;
	cout << " Number of spikes for the connected neuron : " << connected_neuron.getNum_Spikes_() << endl;
}


