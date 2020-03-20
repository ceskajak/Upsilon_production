// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the BrowserAnalysis class.
//

#include "Browser.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"


//using namespace LHAPDF;
using namespace Mira;
using namespace HepMC;
using namespace Herwig;
using namespace std;
using namespace fastjet;

Browser::Browser() {}

Browser::~Browser() {}



#ifndef LWH_AIAnalysisFactory_H
#ifndef LWH 
#define LWH ThePEGLWH
#endif
#include "ThePEG/Analysis/LWH/AnalysisFactory.h"
#endif

void Browser::analyze(tEventPtr event, long ieve, Int_t loop, Int_t state) {
  AnalysisHandler::analyze(event, ieve, loop, state);
// Rotate to CMS, extract final state particles and call analyze(particles).

// Rotate to CMS, extract final state particles and call analyze(particles).
  	nChar = 0;

	StepVector::const_iterator sit = event->primaryCollision()->steps().begin();
	StepVector::const_iterator send = event->primaryCollision()->steps().end();
	for(;sit!=send;++sit)
	{

	ParticleSet part = (**sit).all();
	ParticleSet::const_iterator iter = part.begin();
	ParticleSet::const_iterator end = part.end();
      	for(;iter!=end;++iter)
	{
		if(((**iter).children().size() == 0) && (((**iter).momentum().perp()/GeV) >= 0.2) && ((**iter).data().charged()) && (fabs(((**iter).eta())) <= 1.0))
			nChar++;
	}
	}
	if(nChar != 0)
  		tree->Fill();

}


LorentzRotation Browser::transform(tcEventPtr event) const {
  return LorentzRotation();
  // Return the Rotation to the frame in which you want to perform the analysis.
}



void Browser::analyze(const tPVector & particles, double weight) {
  AnalysisHandler::analyze(particles);
  // Calls analyze() for each particle.
}


void Browser::analyze(tPPtr, double weight) {}

void Browser::dofinish() {
  AnalysisHandler::dofinish();



  //Scale_histograms();

  file_->Write();
  file_->Close();

}

void Browser::doinitrun() {
  AnalysisHandler::doinitrun();
  // *** ATTENTION *** histogramFactory().registerClient(this); // Initialize histograms.
  // *** ATTENTION *** histogramFactory().mkdirs("/SomeDir"); // Put histograms in specal directory.

  
//  TString hist_name;
//  batch =atoi(gSystem->Getenv("BATCH")); //minimal pT of the jet's leading track
  //file_ = TFile::Open("HERWIG_simulace.root","RECREATE");
  //file_ = TFile::Open("HERWIG_data.root","RECREATE");
  //file_ = TFile::Open("HERWIG_test.root","RECREATE");
  file_ = TFile::Open("Output.root","RECREATE");

//  topDirectory = gDirectory;

  tree = new TTree("tree","tree");
  tree->Branch("nChar",&nChar,"nChar/I");
}


IBPtr Browser::clone() const {
  return new_ptr(*this);
}

IBPtr Browser::fullclone() const {
  return new_ptr(*this);
}


// If needed, insert default implementations of virtual function defined
// in the InterfacedBase class here (using ThePEG-interfaced-impl in Emacs).



// *** Attention *** The following static variable is needed for the type
// description system in ThePEG. Please check that the template arguments
// are correct (the class and its base class), and that the constructor
// arguments are correct (the class name and the name of the dynamically
// loadable library where the class implementation can be found).
DescribeNoPIOClass<Browser,AnalysisHandler>
  describeMiraBrowser("Mira::Browser", "Browser.so");

void Browser::Init() {

  static ClassDocumentation<Browser> documentation
    ("There is no documentation for the Browser class");

}




//void Browser::Scale_histograms()
//{
/*
  CrossSection sigma = generator()->eventHandler()->integratedXSec();
  double Xsec = sigma/nanobarn;
  Xsec = Xsec/Nevt;
//  double sc;

 
  h_Lep1_pt->Scale(Xsec,"width");
  h_Lep2_pt->Scale(Xsec,"width");
  h_Lep1_eta->Scale(Xsec,"width");
  h_Lep2_eta->Scale(Xsec,"width");  
  h_lep_m->Scale(Xsec,"width");
  h_Jet1_Pt->Scale(Xsec,"width");
*/
// be careful with scaling!  "width" means scale it wrt bin width! -> Integral gives Xsection when hist->Integral("width") 
  
//}




/*
bool Browser::isParton(int id)
{
  bool dec = false;
  int partonIDs[9] = {1, 2, 3, 4, 5, 6, 7, 8, 21};
  for (int i=0; i<9; i++) {
    if (fabs(id) == partonIDs[i]) dec=true;
  }
  return dec;
}


bool Browser::isRemnant(int id)
{
  bool dec = false;
  if( (fabs(id) > 1000) && (fabs(id) < 6000) ) dec=true;
 
// remnant is actually PDGID 81 in Herwig

  return dec;
}
*/

vector<PPtr> Browser::sort_particles_pt(vector<PPtr> particles)
{
  Double_t temp_pt1, temp_pt2;
  bool swapped = true;
  Int_t treshold = Int_t(particles.size()-2);
  do{
    swapped = false;
    for (Int_t i = 0; i <= treshold; i++)
    {
      temp_pt1 = particles[i]->momentum().perp()/GeV;
      temp_pt2 = particles[i+1]->momentum().perp()/GeV;
      if( temp_pt1 < temp_pt2 ) 
      { 
        swap(particles[i], particles[i+1] );
        swapped = true;
      }
    }
  } while (swapped == true);
  return particles;
}


vector<tcPPtr> Browser::sort_particles_pt(vector<tcPPtr> particles)
{
  Double_t temp_pt1, temp_pt2;
  bool swapped = true;
  Int_t treshold = Int_t(particles.size()-2);
  do{
    swapped = false;
    for (Int_t i = 0; i <= treshold; i++)
    {
      temp_pt1 = particles[i]->momentum().perp()/GeV;
      temp_pt2 = particles[i+1]->momentum().perp()/GeV;
      if( temp_pt1 < temp_pt2 ) 
      { 
        swap(particles[i], particles[i+1] );
        swapped = true;
      }
    }
  } while (swapped == true);
  return particles;
}


vector<Lorentz5Momentum> Browser::sort_particles_pt(vector<Lorentz5Momentum> particles)
{
  Double_t temp_pt1, temp_pt2;
  bool swapped = true;
  Int_t treshold = Int_t(particles.size()-2);
  do{
    swapped = false;
    for (Int_t i = 0; i <= treshold; i++)
    {
      temp_pt1 = particles[i].perp()/GeV;
      temp_pt2 = particles[i+1].perp()/GeV;
      if( temp_pt1 < temp_pt2 ) 
      { 
        swap(particles[i], particles[i+1] );
        swapped = true;
      }
    }
  } while (swapped == true);
  return particles;
}



Double_t Browser::DeltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2){
  Double_t deta = eta1-eta2;
  Double_t dphi = TVector2::Phi_mpi_pi(phi1-phi2);
  
  
  return TMath::Sqrt( deta*deta+dphi*dphi );
}

Double_t Browser::efficiencyPP(Double_t pt)
{
   if(pt>9.9)pt=9.9;
//   TF1* f_Efficiency = new TF1("f_EfficiencyCent",Eff_track_rec_function,0,10.0,3);
//   f_Efficiency->SetParameters(9.06946e-01,1.45242e-01,2.87409e+00);
//   Double_t eff=f_Efficiency->Eval(pt);
    Double_t y;
    Double_t A =9.3e-01;
    Double_t B =1.5e-01;
    Double_t C =2.9e+00;
    y=A*(exp(-pow(B/pt,C)));
   return y;
}
/*
Double_t Browser::Eff_track_rec_function(Double_t* x,Double_t* par)
{
    // Track reconstruction efficiency parametrization
    Double_t pt,y;
    Double_t A =9.06946e-01;
    Double_t B =1.45242e-01;
    Double_t C =2.87409e+00;
    pt=x[0];
    return y;
}
*/
Double_t Browser::smear_track_pt(Double_t pt)
{
//  TF1* fsmear=new TF1("fsmear", gaus,  0., 100.,3);
  Double_t sigma = 0.01*pt*pt;
//  fsmear->SetParameters(1.,pt,sigma); //set normalization
  return gRandom->Gaus(pt,sigma);

}


