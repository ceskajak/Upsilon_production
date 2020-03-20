#include "Pythia8/Pythia.h"

#include "TInterpreter.h"
#include "TTree.h"
#include "TFile.h"

#include <vector>

#include "Pythia8Plugins/Pythia8Rivet.h"

using namespace std;
using namespace Pythia8;

int main()
{
	// create Pythia instance
	Pythia pythia;
	
	// static settings
	Settings & settings = pythia.settings;
	Info & info = pythia.info;

	// load settings
	pythia.readFile("rivet_MinBias.cmnd");

	// define parameters from runcard
	int maxNumberOfEvents = settings.mode("Main:numberOfEvents");
	int maxErrors = settings.mode("Main:timesAllowErrors");

	// initialize Pythia
	pythia.init();

	// add Rivet analysis
	// initialise communication /w Rivet
	Pythia8Rivet rivet(pythia, "output.yoda");
	// select analysis
	rivet.addAnalysis("CMS_2011_S8884919");

	// define ROOT TTree
	TTree * tree = new TTree("tree", "tree");

	// define parameters to save
	Double_t event_weight;
	Int_t nChar;

	// create TTree branches
	tree->Branch("event_weight", &event_weight, "event_weight/D");
	tree->Branch("nChar", &nChar, "nChar/I");

	// Define temporary Particle
	Particle particle;

	// loop over all events (run loop)
	for (int i = 0; i < maxNumberOfEvents; i++)
	{
		if (!pythia.next())
			continue;
		
		// init. parameters for new loop
		event_weight = info.weight();
		nChar = 0;

		// single event loop (event loop)
		for (int j = 0; j < pythia.event.size(); j++)
		{
			// Set current particle
			particle = pythia.event[j];

			// multiplicity counter
			if (particle.isFinal() && particle.isCharged())
			{
				if (particle.pT() >= .20 && abs(particle.eta()) < 1.0)
				{
					nChar++;
				}
			}

		// call Rivet analysis
		rivet();
		}	// end event loop

		tree->Fill();
	}	// end run loop

	// statistics
	pythia.stat();
	
	// finish Rivet analysis
	rivet.done();

	// select output file
	TFile out("rivet_MinBias.root", "recreate");

	// write tree
	tree->Write();

	// done
	return 0;
}