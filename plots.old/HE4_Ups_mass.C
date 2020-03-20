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

void HE4_Ups_mass()
{
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

		TFile *fileHE4_Ups = TFile::Open("../data/HE_Upsilon_4.root");

		TTreeReader readHE4_Ups("tree", fileHE4_Ups);

		TTreeReaderValue<Double_t> HE4_p_pT(readHE4_Ups, "p_pT");
		TTreeReaderValue<Double_t> HE4_p_eta(readHE4_Ups, "p_eta");
		TTreeReaderValue<Double_t> HE4_p_phi(readHE4_Ups, "p_phi");
		TTreeReaderValue<Double_t> HE4_p_e(readHE4_Ups, "p_e");

		TH1D *HE4 = new TH1D("HE4", "", 400, 85, 105);
		TLorentzVector *Lorentz = new TLorentzVector();
		while(readHE4_Ups.Next())
		{
			Lorentz->SetPtEtaPhiE(*HE4_p_pT, *HE4_p_eta, *HE4_p_phi, *HE4_p_e);
			HE4->Fill(Lorentz->M2());
		}

		TCanvas* c1 = new TCanvas("c1", "Ups mass spectrum", 800, 600);
		c1->SetLogy();

		HE4->SetMarkerStyle(20);
		HE4->SetMarkerSize(1);
		HE4->SetLineColor(kBlue);
		HE4->SetMarkerColor(kBlue);

		HE4->GetYaxis()->SetTitle("Count");
		HE4->GetYaxis()->LabelsOption("v");
		HE4->GetYaxis()->SetTitleOffset(1);

		HE4->GetXaxis()->SetTitle("m [GeV/c^{2}]");
		HE4->GetXaxis()->SetTitleOffset(1.25);
		//HE4->GetYaxis()->SetRangeUser(0.0001,1000000.);

		HE4->SetStats(kFALSE);

		c1->cd();
		HE4->Draw("");

		TLegend *leg = new TLegend(.5,.7,.9,.9);
		leg->SetTextSize(0.035);
		leg->SetHeader("p+p@500 GeV, |#eta| < 1");
		leg->AddEntry(HE4->DrawCopy("same"), "HERWIG 7, k_{T} = 4", "f");

		leg->Draw("same");

		c1->cd();
	c1->Print("../output/HE4_Ups_mass.png", "png");
}
