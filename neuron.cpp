#include "neuron.h"
#include <cmath>
#include <random>


using namespace std;


//------------------CONSTRUCTOR----------------//

Neuron:: Neuron()
    :
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
		DelaySteps_ = static_cast<unsigned long>(ceil(Delay_/h_)); //Computes the smallest integer value not less than Delay_/h_
		Buffer_.resize(DelaySteps_ + 1, 0.0);
	}


//---------------METHODS GIVING ACCESS TO THE ATTRIBUTES-------------//

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



//------------METHODS SETTING THE VALUES FOR THE ATTRIBUTES------------//
/** 
 *  setV_               ---> Sets the membrane potential to @param v.
 *  setI_ext_           ---> Sets the external current to @param i.
 *  setLast_Spike_time_ ---> Sets the time of the last occurin spike to @param T.  
 */

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




//-----------------------UPDATE METHOD----------------------//
/** 
 * Updates our neuron in time for how many simulation steps we want.
 * @param simsteps    --> for how many simulation steps do we want to update our neuron
 * @return bool spike --> returns TRUE if there was a spike during "simsteps" steps
 *                    --> returns FALSE if there were no spikes during the steps. 
 */
bool Neuron::update(unsigned long simsteps)
{
	if (simsteps == 0) return false;
	
	bool spike = false;
	const auto stoptime_ = Clock_ + simsteps;
	
	
	while (Clock_ < stoptime_)
	{
		const auto IN = Clock_ % (DelaySteps_ + 1);
		if ( Vth_ < V_ ) 
		{
			/**
			 * Spike occurs :
			 * --> increment the number of spikes.
			 * --> time of the last spike is the internal clock time.
			 */
			spike = true;
			++Num_Spikes_;
			Last_Spike_time_ = Clock_;
			
		}
		if ((Last_Spike_time_ > 0 ) and ((Clock_ - Last_Spike_time_) < RefSteps_)) 
		{
			/** 
			 * REFRACTORY PERIOD :
			 * --> set the membrane potential to 0 or 10.
			 */
			 V_ = 0.0;
		}
		else
		{
			/**
			 * No spike and not refractory :
			 * --> Solve the membrane potential differential equation using the constants (see constructor).
			 * --> I_ext_ will be checked and set in the main loop.
			 */
				static random_device rd;
				static mt19937 gen(rd());
				static poisson_distribution<> Ext_Rate_(2);
			 
			 V_ = C1_*V_ + I_ext_*C2_ + Buffer_[IN] + Ext_J_*Ext_Rate_(gen);
		}
		
	    Buffer_[IN] = 0.0;
	    ++Clock_;
	}
	return spike;
}




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
			/**
			 * Spike occurs :
			 * --> increment the number of spikes.
			 * --> time of the last spike is the internal clock time.
			 */
			spike = true;
			++Num_Spikes_;
			Last_Spike_time_ = Clock_;
			
		}
		if ((Last_Spike_time_ > 0 ) and ((Clock_ - Last_Spike_time_) < RefSteps_)) 
		{
			/** 
			 * REFRACTORY PERIOD :
			 * --> set the membrane potential to 0 or 10.
			 */
			 V_ = 0.0;
		}
		else
		{
			/**
			 * No spike and not refractory :
			 * --> Solve the membrane potential differential equation using the constants (see constructor).
			 * --> I_ext_ will be checked and set in the main loop.
			 */
			 
			
			 V_ = C1_*V_ + I_ext_*C2_ + Buffer_[IN];
		}
		
	    Buffer_[IN] = 0.0;
	    ++Clock_;
	}
	return spike;
}





//---------------------METHOD TO RECEIVE SPIKES----------------//
/** Updates our neuron when it receives a spike from another neuron
 *   FIRST WITHOUT THE DELAY --> membrane potential goes up immediately after the spike
 *   SECOND WITH DELAY       --> delay for the time it takes the spike to travel has to be taken into account
 *   FIRST : @param J --> by how much does V go up when it receives a spike
 *                    --> J usually equals 0.1, but it can change depending on the conections
 *   
 *   SECOND: @param t --> time when the spike should be received
 *                    --> internal clock of the neuron sending the spike + delay for the travel
 */
void Neuron::spike_receive(unsigned long t, double J)
{
	const size_t OUT = t % (DelaySteps_ + 1);
	Buffer_[OUT] += j;
}
