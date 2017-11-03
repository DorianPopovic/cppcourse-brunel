#ifndef NEURON_H
#define NEURON_H
#include <vector>


/**
* Neuron Class
*/
class Neuron{
	
	/*********************************************************************************//**
	 * 
	 * 						PUBLIC ARGUMENTS FOR THE NEURON CLASS
	 * 
	 ************************************************************************************/
	
	public:
	
	/**
	 * Neuron constructor
	 */
	Neuron ();
	
	/*********************************************************************************//**
	 * 										GETTERS
	 ************************************************************************************/
	
	/**
	 * Gives access to the membrane potential value
	 * @return Membrane potential value
	 */
	double getV_() const;
	
	/**
	 * Gives access to the external current value
	 * @return specified external current for the neuron
	 */
	double getI_ext_() const;
	
	/**
	 * Gives acces to the number of spikes of the neuron
	 * @return total number of spikes
	 */
	unsigned long getNum_Spikes_() const;
	
	/**
	 * Gives access to the time of the last occured spike
	 * @return last occuring spike time
	 */
	unsigned long getLast_Spike_time_() const;
	
	/**
	 * Gives access to the internal neuron time
	 * @return internal clock neuron time
	 */
	unsigned long getClock_() const;
	
	
	
	
	/*********************************************************************************//**
	 * 										SETTERS
	 ************************************************************************************/
	
	
	/**
	 * Sets the potential membrane value
	 * @param v wanted value of the membrane potential
	 */
	void setV_(double v);
	
	/**
	 * Sets the external curent value
	 * @param i wanted value of the ternal current
	 */
	void setI_ext_(double i);
	
	/**
	 * Sets the time of the last occuring spike
	 * @param T time of the last occuring spike
	 */
	void setLast_Spike_time_(unsigned long T);
	
 
    /*********************************************************************************//**
	 * 				  FUNCTIONS PROTOTYPES FOR THE NEURON SIMULATION
	 ************************************************************************************/
	
	/**
	 * Updates the neuron over time
	 * @param simsteps number of simulation steps to update the neuron for
	 * @return true if there was a spike durin the time-step, false otherwise
	 */
	bool update(unsigned long simsteps);
	
	/**
	 * Update method used for google tests (similar to update, but without poisson)
	 * @param simsteps number of simulation steps to update the neuron for 
	 */
	bool update_test(unsigned long simsteps);
	
	/**
	 * 	Deals with the received spikes from other neurons
	 * @param t time of arrival of the received spike
	 * @param J weight of the received spike
	 */
	void spike_receive(unsigned long t, double J);
	
	
	
	
	/*********************************************************************************//**
	 * 
	 * 						PRIVATE ARGUMENTS FOR THE NEURON CLASS
	 * 
	 ************************************************************************************/
	
	private:
	
	double V_;       //!< Membrane potential value (mV)
	double I_ext_;   //!< External specified current
	double Delay_;   //!< Delay (in ms) for the spike to travel to the receiving neuron 
	
	unsigned long Num_Spikes_;        //!< Number of spikes that occured during the neuron simulation
	unsigned long Last_Spike_time_;   //!< Time when the last spike occured
	unsigned long Clock_;             //!< Local clock for each neuron
	unsigned long DelaySteps_;        //!< Synaptic delay converted in steps for the simulation           
	std::vector<double> Buffer_;      //!< Storage for the spikes to be received according to the delay (=1.5ms)
	
	
	/**********************************************//** 
	 * 		 DIFFERENTIAL EQUATION CONSTANTS
	 *************************************************/
	
	double C1_;  //!< Decaying part of the solution
	double C2_;	 //!< External current input part of the solution
	
	
	/**********************************************//** 
	 * 		    NEURON SIMULATION CONSTANTS
	 *************************************************/
	
	const double R_ =20.0;              //!< Membrane resistance (Ohm)
	const double Tau_ =20.0;            //!< Membrane constant time (ms)
	const double Vth_ =20.0;            //!< Threshold at wich spike occurs (mV)
	const double RefTime_ =2.0;         //!< Refractory period duration (ms)
	const double h_ =0.1;               //!< Simulation time step (ms)
	const unsigned long RefSteps_;      //!< How many time steps for the refractory period (simulation steps h=0.1 ms)
	const double Ext_J_ =0.1;           //!< Weight of the external random connections (mA)
	
};

#endif /* NEURON_H */
