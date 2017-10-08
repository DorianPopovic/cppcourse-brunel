#include <vector>

class Neuron{
	
	public:
	Neuron ();
	
	/* giving access to the membrane potential, the number of 
	spikes and time when spikes occured of the neuron*/
	double getV() const;
	int getSpikes() const;
	double getTime(int) const;
	
	/*enables to set different values for
	the parameters of the neuron*/
	void setV(double);
	void setSpikes(int);
	void setTime(double);
	
 
    //method that updates the neuron in time
	void update(double, double, double, double, double, double, double);
	
	private:
	double V; //membrane potential
	int Spikes;//number of spikes that occured
	std::vector<double> Time;//times when the spikes occured
	
	//constants for each neuron
	double C;
	double R;
	double Tau;
	
};

/* c = 250 pF, tau = 10ms, tau(af) = 2ms, Vreset = -70, h = 0.1*/
