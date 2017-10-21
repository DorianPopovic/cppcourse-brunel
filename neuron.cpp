#include "neuron.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

Neuron:: Neuron()
{
	// initialise the attributes by default
	V = 0.0;
	Spikes = 0;
	Time;
	
	//give the constant values to the neuron
	C = 1.0;
	Tau = 20.0; //ms
	R = C*Tau;
}

//methods giving acces to the attributes
double Neuron::getV() const
{
	return V;
}
int Neuron::getSpikes() const
{
	return Spikes;
}
double Neuron::getTime(int i) const //Gets the "i"th value of the vector
{
	return Time [i];
}


//methods setting the values of the attributes
void Neuron::setV(double v)
{
	V = v;
}
void Neuron::setSpikes(int spikes)
{
	Spikes = spikes;
}
void Neuron::setTime(double time)    //Append the spike time at the end of the vector
{
	Time.push_back(time);
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
