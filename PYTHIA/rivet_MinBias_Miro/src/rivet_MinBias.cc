#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/Pythia8Rivet.h" 


#include <vector>

using namespace std;
using namespace Pythia8;

int main()
{
	// create Pythia instance
	Pythia pythia; 		

	// load settings
	// pythia.readFile("MinBias_all.cmnd");
	int nEvents = 1000000;
	pythia.readString("Beams:idA = 2212");
	pythia.readString("Beams:idB = 2212");
	pythia.readString("Beams:eCM = 900.");

	pythia.readString("SoftQCD:nonDiffractive = on");
	pythia.readString("SoftQCD:doubleDiffractive = on");
	pythia.readString("PhaseSpace:pTHatMin = 0");
	pythia.readString("PhaseSpace:pTHatMax = 900");
	pythia.readString("PhaseSpace:mHatMin = 0");
	pythia.readString("PhaseSpace:mHatMax = 900");
	
	pythia.readString("ParticleDecays:limitTau0 = On");
	pythia.readString("ParticleDecays:tau0Max = 10.0");
	pythia.readString("Next:numberShowEvent = 0");
	
	pythia.readString("Random:setSeed = on");
	pythia.readString("Random:seed = 125442");
	// pythia.readString("Main:runRivet = on");
	
	// initialize Pythia
	pythia.init();
	
	// Initialize the communication with the Rivet program.
	Pythia8Rivet rivet(pythia, "PythiaMB_900.yoda");
	// For the following analysis we need more statistics.
	rivet.addAnalysis("CMS_2011_S8884919");
	
	// loop over all events (run loop)
	for (int i = 0; i < nEvents; i++)
	{
		if (!pythia.next())
			continue;  

		// Send the event to Rivet
		rivet();
	}	// end run loop
	
	// statistics
	pythia.stat(); 			                                  		        								        				
	rivet.done();

	// done
	return 0;
}
