#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TSystem.h>

#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "TMathBase.h"

#include "../headers/LoadXYscanned.h"
#include "../headers/LoadEventActivity.h"

#include "vector"

void PY_Ups_mass()
{
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	TFile *filePY_Ups = TFile::Open("../data/PY_Upsilon_ee.root");

	TTreeReader readPY_Ups("tree", filePY_Ups);

	TTreeReaderValue<Double_t> PY_p_pT(readPY_Ups, "p_pT");
	TTreeReaderValue<Double_t> PY_p_eta(readPY_Ups, "p_eta");
	TTreeReaderValue<Double_t> PY_p_phi(readPY_Ups, "p_phi");
	TTreeReaderValue<Double_t> PY_p_e(readPY_Ups, "p_e");

	TH1D *PY = new TH1D("PY", "", 400, 85, 105);
	TLorentzVector *Lorentz = new TLorentzVector();
	while(readPY_Ups.Next())
	{
		Lorentz->SetPtEtaPhiE(*PY_p_pT, *PY_p_eta, *PY_p_phi, *PY_p_e);
		PY->Fill(Lorentz->M2());
	}

	TCanvas* c1 = new TCanvas("c1", "Ups mass spectrum", 800, 600);
	c1->SetLogy();

	PY->SetMarkerStyle(20);
	PY->SetMarkerSize(1);
	PY->SetLineColor(kBlue);
	PY->SetMarkerColor(kBlue);

	PY->GetYaxis()->SetTitle("Count");
	PY->GetYaxis()->LabelsOption("v");
	PY->GetYaxis()->SetTitleOffset(1);

	PY->GetXaxis()->SetTitle("m [GeV/c^{2}]");
	PY->GetXaxis()->SetTitleOffset(1.25);
	//PY->GetYaxis()->SetRangeUser(0.0001,1000000.);

	PY->SetStats(kFALSE);

	c1->cd();
	PY->Draw("");

	TLegend *leg = new TLegend(.5,.7,.9,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg->AddEntry(PY->DrawCopy("same"), "Pythia 8 STAR HF tune", "f");

	leg->Draw("same");

	c1->cd();
	c1->Print("../output/PY_Ups_mass.png", "png");
}
