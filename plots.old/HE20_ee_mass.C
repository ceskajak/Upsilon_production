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

void HE20_ee_mass()
{
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	TFile *fileHE20_Ups = TFile::Open("../data/HE_Upsilon_20.root");

	TTreeReader readHE20_Ups("tree", fileHE20_Ups);

	TTreeReaderValue<Double_t> HE20_d1_pT(readHE20_Ups, "d1_pT");
	TTreeReaderValue<Double_t> HE20_d1_eta(readHE20_Ups, "d1_eta");
	TTreeReaderValue<Double_t> HE20_d1_phi(readHE20_Ups, "d1_phi");
	TTreeReaderValue<Double_t> HE20_d1_e(readHE20_Ups, "d1_e");
	TTreeReaderValue<Double_t> HE20_d2_pT(readHE20_Ups, "d2_pT");
	TTreeReaderValue<Double_t> HE20_d2_eta(readHE20_Ups, "d2_eta");
	TTreeReaderValue<Double_t> HE20_d2_phi(readHE20_Ups, "d2_phi");
	TTreeReaderValue<Double_t> HE20_d2_e(readHE20_Ups, "d2_e");

	TH1D *HE20 = new TH1D("HE20", "", 400, 85, 105);
	TLorentzVector *Lorentz1 = new TLorentzVector();
	TLorentzVector *Lorentz2 = new TLorentzVector();
	while(readHE20_Ups.Next())
	{
		Lorentz1->SetPtEtaPhiE(*HE20_d1_pT, *HE20_d1_eta, *HE20_d1_phi, *HE20_d1_e);
		Lorentz2->SetPtEtaPhiE(*HE20_d2_pT, *HE20_d2_eta, *HE20_d2_phi, *HE20_d2_e);
		HE20->Fill((*Lorentz1+*Lorentz2).M2());
	}

	TCanvas* c1 = new TCanvas("c1", "Ups mass spectrum", 800, 600);
	c1->SetLogy();

	HE20->SetMarkerStyle(20);
	HE20->SetMarkerSize(1);
	HE20->SetLineColor(kBlue);
	HE20->SetMarkerColor(kBlue);

	HE20->GetYaxis()->SetTitle("Count");
	HE20->GetYaxis()->LabelsOption("v");
	HE20->GetYaxis()->SetTitleOffset(1);

	HE20->GetXaxis()->SetTitle("m [GeV/c^{2}]");
	HE20->GetXaxis()->SetTitleOffset(1.25);
	//HE20->GetYaxis()->SetRangeUser(0.0001,1000000.);

	HE20->SetStats(kFALSE);

	c1->cd();
	HE20->Draw("");

	TLegend *leg = new TLegend(.5,.7,.9,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg->AddEntry(HE20->DrawCopy("same"), "HERWIG 7, k_{T} = 20", "f");

	leg->Draw("same");

	c1->cd();
	c1->Print("../output/HE20_ee_mass.png", "png");
}
