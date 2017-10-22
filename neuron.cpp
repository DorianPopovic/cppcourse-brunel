#include "neuron.h"
#include <cmath>

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
    //Buffer_() NOT USED YET
    {
		C1_ = exp(-h_ / Tau_);
		C2_ = R_*(1.0 - C1_);
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
			 V_ = C1_*V_ + I_ext_*C2_;
		}
		
	    ++Clock_;
	}
	return spike;
}





//---------------------METHOD TO RECEIVE SPIKES----------------//
/** Updates our neuron when it receives a spike from another neuron
 *   FIRST WITHOUT THE DELAY --> membrane potential goes up immediately after the spike
 *   @param J --> by how much does V go up when it receives a spike
 *            --> J usually equals 0.1, but it can change depending on the conections*/
void Neuron::spike_receive(double J)
{
	V_ += J;
}
