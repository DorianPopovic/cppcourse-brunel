# Neuron-Project
Dynamics of Sparsely Connected Networks of Excitatory and Inhibitory Spiking Neurons.

The goal of this project is to implement a neuronal network using the model described in the following paper: 

		Dynamics of Sparsely Connected Networks of Excitatory and Inhibitory Spiking Neurons
						NICOLAS BRUNEL
		LPS, Ecole Normale Superieure, 24 rue Lhomond, 75231 Paris Cedex 05, France
						brunel@lps.ens.fr

In the end the program should be able to reproduce the figure 8 from this paper.



						RUNNING THE PROGRAM

==> Clone this repository in your files

You will have a new cppcourse-brunel folder containing everything

==> Download the googletest library from github and drag it into the newly created folder (juste the googletest folder from the googletest master)

FROM THE "cppcourse-brunel" FOLDER:

STEP 1: run the program

In the terminal tap

$ mkdir build

$ cd build

$ cmake ..

$ make (to generate all the executable files)

$ make doc (to generate the program doxygen documentation)

This last step will create 2 new folders. Go to the "html" folder and click on "annotated.hmtl" to open the web page corresponding to this program documentation. 


This should generate all the cmake files needed to run the program.

STEP 2 (from build):Execute the program 

$ ./SingleNeuron (execute the simulation for one neuron)

$ ./TwoNeurons   (execute the simulation of two neurons)

$ ./unit_test    (executes the tests)

This is how to execute all the files except the final simulation.

						EXECUTE THE FINAL SIMULATION

//! STEPS TO FOLLOW BEFORE TAPING ./Final !\\

OPEN:

FinalMain.cpp
Network.cpp
Neuron.cpp

Instructions are given there on how to uncomment the program depending on what plot you want to reproduce.

STEP 1:

In FinalMain.cpp

==> choose the time you want to run the simulation for depending on what plot to reproduce (or your own)
 
STEP 2:

In Neuron.cpp

==> GO TO the update method definition and where the potential membrane is calculated juste after the declaration of the poisson variable will be instructions

==> Change the value in the poisson generate Ext_Rate_(xxx) again depending on what plot to reproduce

STEP 3:

In Network.cpp

==> GO TO the simulate_network method definition and where there is commented red text

==> choose wich one to uncoment depending on the chosen simulation

FINAL STEP:

In FinalMain.cpp

==> uncomment the "setJ_In_" commented line corresponding to the chosen simulation

After you chose the simulation and uncommented just tap from the build folder:

$ ./Final (to execute the final simulation)


							PLOT THE RESULTS:

The final execution should have generated a new "spike.gdf" file. On jupyter.org upload this file and create a new Python page.

Paste the following text :

import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('spikes.gdf')

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()
pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none');
pl.show();

n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
pl.show();


And click on the run button.







