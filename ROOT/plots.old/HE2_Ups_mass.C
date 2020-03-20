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

void HE2_Ups_mass()
{
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

		TFile *fileHE2_Ups = TFile::Open("../data/HE_Upsilon_2.root");

		TTreeReader readHE2_Ups("tree", fileHE2_Ups);

		TTreeReaderValue<Double_t> HE2_p_pT(readHE2_Ups, "p_pT");
		TTreeReaderValue<Double_t> HE2_p_eta(readHE2_Ups, "p_eta");
		TTreeReaderValue<Double_t> HE2_p_phi(readHE2_Ups, "p_phi");
		TTreeReaderValue<Double_t> HE2_p_e(readHE2_Ups, "p_e");

		TH1D *HE2 = new TH1D("HE2", "", 400, 85, 105);
		TLorentzVector *Lorentz = new TLorentzVector();
		while(readHE2_Ups.Next())
		{
			Lorentz->SetPtEtaPhiE(*HE2_p_pT, *HE2_p_eta, *HE2_p_phi, *HE2_p_e);
			HE2->Fill(Lorentz->M2());
		}

		TCanvas* c1 = new TCanvas("c1", "Ups mass spectrum", 800, 600);
		c1->SetLogy();

		HE2->SetMarkerStyle(20);
		HE2->SetMarkerSize(1);
		HE2->SetLineColor(kBlue);
		HE2->SetMarkerColor(kBlue);

		HE2->GetYaxis()->SetTitle("Count");
		HE2->GetYaxis()->LabelsOption("v");
		HE2->GetYaxis()->SetTitleOffset(1);

		HE2->GetXaxis()->SetTitle("m [GeV/c^{2}]");
		HE2->GetXaxis()->SetTitleOffset(1.25);
		//HE2->GetYaxis()->SetRangeUser(0.0001,1000000.);

		HE2->SetStats(kFALSE);

		c1->cd();
		HE2->Draw("");

		TLegend *leg = new TLegend(.5,.7,.9,.9);
		leg->SetTextSize(0.035);
		leg->SetHeader("p+p@500 GeV, |#eta| < 1");
		leg->AddEntry(HE2->DrawCopy("same"), "HERWIG 7, k_{T} = 2", "f");

		leg->Draw("same");

		c1->cd();
	c1->Print("../output/HE2_Ups_mass.png", "png");
}
