#ifndef NEURON_H
#define NEURON_H
#include <vector>

class Neuron{
	
	//-------------------PUBLIC ARGUMENTS AND METHODS PROTOTYPES--------------//
	
	public:
	Neuron ();
	
	//-------------GETTERS--------//
	double getV_() const;
	double getI_ext_() const;
	unsigned long getNum_Spikes_() const;
	unsigned long getLast_Spike_time_() const;
	unsigned long getClock_() const;
	
	//-------------SETTERS-------//
	void setV_(double);
	void setI_ext_(double);
	void setLast_Spike_time_(unsigned long);
	
 
    //-----------------UPDATE FUNCTION PROTOTYPE------------//
	bool update(unsigned long);
	
	//-------------FUNCTION FOR RECEIVING SPIKES PROTOTYPE------------//
	void spike_receive(unsigned long, double);
	
	
	//--------------------------------PRIVATE ARGUMENTS---------------------------------//
	
	private:
	
	double V_;       // -> Membrane potential
	double I_ext_;   // -> External specified current
	double Delay_;   // -> Delay (in ms) for the spike to travel to the receiving neuron 
	
	unsigned long Num_Spikes_;        // -> Number of spikes that occured during the simulation
	unsigned long Last_Spike_time_;   // -> Time when the last spike occured
	unsigned long Clock_;             // -> Local clock for each neuron
	unsigned long DelaySteps_;        // -> Synaptic delay converted in steps for the simulation           
	std::vector<double> Buffer_;      // -> Stores the spikes to be received according to the delay (=1.5ms)
	
	
	//---------CONSTANTS FOR THE EQUATION-----------
	double C1_;
	double C2_;
	
	
	//---------CONSTANTS FOR THE NEURON SIMULATION-----------
	const double R_ =20.0;              // -> Membrane resistance
	const double Tau_ =20.0;             // -> Membrane constant time
	const double Vth_ =20.0;            // -> Threshold at wih spike occurs
	const double RefTime_ =2.0;         // -> Refractory period duration
	const double h_ =0.1;               // -> Simulation time step
	const unsigned long RefSteps_;      // -> How many time steps for the refractory period
	
};

#endif /* NEURON_H */
