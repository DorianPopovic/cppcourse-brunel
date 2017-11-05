#include <iostream>
#include <cmath>
#include "neuron.h"
#include "gtest/gtest.h"

using namespace std;


/***
 * This test checks if the membrane potential
 * is computed correctly in the update method.
 ***/
TEST (NeuronTest, MembranePotential)
{
	Neuron test_neuron;
	test_neuron.setI_ext_(1.0);

	//Test after single update:
	test_neuron.update_test(1);
	//Check if the computing of the membrane potential works.
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0)), test_neuron.getV_());

	//Test after more updates(added many steps to get to the wanted value):
	test_neuron.update_test(100000);

	//With this current input, membrane potential should tend to 20 but never reach it, so no spikes.
	EXPECT_EQ(0, test_neuron.getNum_Spikes_());
	EXPECT_GT(1E-4, fabs(19.9999 - test_neuron.getV_()));

	
	//With no external input, the membrane potential should tend toward 0.
	test_neuron.setI_ext_(0.0);
	test_neuron.update_test(3000);
	EXPECT_NEAR(0, test_neuron.getV_(), 1e-3);
}


/***
 * This test checks if the right number of spikes
 * occurs, and if they occur at the right time.
 * We will test for the first two spikes.
 ***/
TEST (Neurontest, Spikes)
{

	Neuron test_neuron;
	test_neuron.setI_ext_(1.01);

	//Excepted spike times: 92.4, 186.8, 281.2 and 375.6 (in ms, not steps) according to our simulation parameters
	//h = 0.1 so we needd 925 steps to get to the first spike
	test_neuron.update_test(924);
	
	EXPECT_EQ(0, test_neuron.getNum_Spikes_());
	test_neuron.update_test(1);
	EXPECT_EQ(1, test_neuron.getNum_Spikes_());
	
	//check if membrane potential is set to zero during refractory period
	EXPECT_EQ(0.0, test_neuron.getV_());

	

	//Idem for the second spike at step 1868 (1868-925=943)
	test_neuron.update_test(943);
	EXPECT_EQ(1, test_neuron.getNum_Spikes_());
	test_neuron.update_test(1);
	EXPECT_EQ(2, test_neuron.getNum_Spikes_());

}


/***
 * This test checks if enough spikes occured 
 * according to our external current value.
 ***/
TEST (Neurontest, SpikeNumber)
{
	Neuron test_neuron;
	test_neuron.setI_ext_(1.01);
	test_neuron.update_test(4000);
	
	//Checking if enough spikes occured
	EXPECT_EQ(4, test_neuron.getNum_Spikes_());
}


/***
 * This test checks the connection between tow neurons.
 * One has external input so that it spikes, the other
 * has none and waits to receive the spike.
 ***/
TEST (NeuronConnection, WithoutSpike)
{
	Neuron neuron1;
	Neuron neuron2;
	int delay = 15;
	
	neuron1.setI_ext_(1.01);
	
	for (auto i=0; i<925+delay; i++)
	{
		if (neuron1.update_test(1))
		{
			neuron2.spike_receive(i + static_cast<unsigned long>(delay), 0.1);
			EXPECT_EQ(0.0, neuron1.getV_());
		}
	
		neuron2.update_test(1);
	}
	
	//Checking if the spike (weight J=0.1) is recieved by the second neuron.
	EXPECT_EQ(0.1, neuron2.getV_());
}



/***
 * Here we check if the second neuron also 
 * spikes after enough time steps, after
 * receiving the spike from the first neuron.
 ***/
TEST (NeuronConnection, WithSpike)
{
	Neuron neuron1;
	Neuron neuron2;
	int delay = 15;
	
	neuron1.setI_ext_(1.01);
	neuron2.setI_ext_(1.0);
	
	for(auto i=0; i<(1869+delay); i++)
	{
		if (neuron1.update_test(1))
		{
			neuron2.spike_receive(i + static_cast<unsigned long>(delay), 0.1);
			EXPECT_EQ(0.0, neuron1.getV_());
		}
		
		neuron2.update_test(1);
	}
	
	//Normally no spikes yet.
	EXPECT_EQ(0, neuron2.getNum_Spikes_());
	
	neuron2.update_test(1);
	
	//Second neuron should have spiked and reset its membrane potential to zero.
	EXPECT_EQ(0.0, neuron2.getV_());
	EXPECT_EQ(1, neuron2.getNum_Spikes_());
	
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

