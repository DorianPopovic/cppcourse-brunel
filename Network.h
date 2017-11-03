#ifndef NETWORK_H
#define NETWORK_H
#include "neuron.h"
#include <vector>

using namespace std;


/**
* Network Class
*/
class Network{
	
	/*********************************************************************************//**
	 * 
	 * 			PUBLIC ARGUMENTS FOR THE NETWORK CLASS
	 * 
	 ************************************************************************************/
	
	public:
	
	/**
	 * Network constructor
	 */
	Network();
	
	
	/*********************************************************************************//**
	 * 		   FUNCTIONS PROTOTYPES FOR THE NETWORK SIMULATION
	 ************************************************************************************/
	
	/**
	 * Randomly connects all the neurons to create the network
	 */
	void Connect_Network();
	
	/**
	 * Simulates the time updating of the neuronal network
	 * @param simtime time when the simulation starts
	 * @param t_stop time when the simulation stops
	 */
	void Simulate_Network(int simtime, int t_stop);
	
	
	
	
	/*********************************************************************************//**
	 * 
	 * 			PRIVATE ARGUMENTS FOR THE NETWORK CLASS
	 * 
	 ************************************************************************************/
	
	private:
	
	
	
	vector<Neuron> All_Neurons_;			//!< Vector containing all the neurons for the simulation			
	vector< vector<int> > Connections_;		//!< Vector containing the vectors with the connected neurons for each neuron
	
	
	/**********************************************//** 
	 * 	   NETWORK SIMULATION CONSTANTS
	 *************************************************/
	
	int TotalNeurons_;		//!< Total number of neurons for the simulation
	int Num_Ex_;			//!< Number of Excitatory neurons
	int Num_In_;			//!< Number of Inhibitory neurons
	int Num_Ci_;			//!< Number of connexions received from inhibitory neurons
	int Num_Ce_;			//!< Number of connexions received from excitatory neurons
	double J_Ex_;			//!< Weight of the spike sent by excitatory neurons
	double J_In_;			//!< Weight of the spike sent by inhibitory neurons
	int DELAY_;			//!< Delay for the spike reception (needed for the buffer)
					
	
};  

#endif /* NETWORK_H */
