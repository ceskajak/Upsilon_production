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

void PY_ee_mass()
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

	TTreeReaderValue<Double_t> PY_d1_pT(readPY_Ups, "d1_pT");
	TTreeReaderValue<Double_t> PY_d1_eta(readPY_Ups, "d1_eta");
	TTreeReaderValue<Double_t> PY_d1_phi(readPY_Ups, "d1_phi");
	TTreeReaderValue<Double_t> PY_d1_e(readPY_Ups, "d1_e");
	TTreeReaderValue<Double_t> PY_d2_pT(readPY_Ups, "d2_pT");
	TTreeReaderValue<Double_t> PY_d2_eta(readPY_Ups, "d2_eta");
	TTreeReaderValue<Double_t> PY_d2_phi(readPY_Ups, "d2_phi");
	TTreeReaderValue<Double_t> PY_d2_e(readPY_Ups, "d2_e");

	TH1D *PY = new TH1D("PY", "", 400, 85, 105);
	TLorentzVector *Lorentz1 = new TLorentzVector();
	TLorentzVector *Lorentz2 = new TLorentzVector();
	while(readPY_Ups.Next())
	{
		Lorentz1->SetPtEtaPhiE(*PY_d1_pT, *PY_d1_eta, *PY_d1_phi, *PY_d1_e);
		Lorentz2->SetPtEtaPhiE(*PY_d2_pT, *PY_d2_eta, *PY_d2_phi, *PY_d2_e);
		PY->Fill((*Lorentz1+*Lorentz2).M2());
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
	c1->Print("../output/PY_ee_mass.png", "png");
}
