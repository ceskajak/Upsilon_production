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

void nchar_MB()
{
	// Setup canvas
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	// Open files
	TFile *filePY_MB_all = TFile::Open("../data/PY_MinBias_all.root");
	TFile *filePY_MB_ND = TFile::Open("../data/PY_MinBias_ND.root");
	TFile *filePY_MB_all_clear = TFile::Open("../data/PY_MinBias_all_clear.root");
	TFile *filePY_MB_all_CR1 = TFile::Open("../data/PY_MinBias_all_CR1.root");
	TFile *fileHE_MB_all = TFile::Open("../data/HE_MinBias_all.root");
	TFile *fileHE_MB_ND = TFile::Open("../data/HE_MinBias_ND.root");

	// Read TTree from files
	TTreeReader readPY_MB_all("tree", filePY_MB_all);
	TTreeReader readPY_MB_ND("tree", filePY_MB_ND);
	TTreeReader readPY_MB_all_clear("tree", filePY_MB_all_clear);
	TTreeReader readPY_MB_all_CR1("tree", filePY_MB_all_CR1);
	TTreeReader readHE_MB_all("tree", fileHE_MB_all);
	TTreeReader readHE_MB_ND("tree", fileHE_MB_ND);

	// Read nChar values from TTree
	TTreeReaderValue<Int_t> PY_nChar_all(readPY_MB_all, "nChar");
	TTreeReaderValue<Int_t> PY_nChar_ND(readPY_MB_ND, "nChar");
	TTreeReaderValue<Int_t> PY_nChar_all_clear(readPY_MB_all_clear, "nChar");
	TTreeReaderValue<Int_t> PY_nChar_all_CR1(readPY_MB_all_CR1, "nChar");
	TTreeReaderValue<Int_t> HE_nChar_all(readHE_MB_all, "nChar");
	TTreeReaderValue<Int_t> HE_nChar_ND(readHE_MB_ND, "nChar");

	// Load nChar values for PYTHIA all
	TH1D *PY_all = new TH1D("PY_all", "", 70, 0, 70);
	while(readPY_MB_all.Next())
	{
		if (*PY_nChar_all == 0)
			continue;
		else
		{
			PY_all->Fill(*PY_nChar_all);
		}
	}

	// Normalise PYTHIA all histogram
	PY_all->Scale(1/(PY_all->GetEntries()));

	// Load nChar for PYTHIA non-diffractive
	TH1D *PY_ND = new TH1D("PY_ND", "", 70, 0, 70);
	while(readPY_MB_ND.Next())
	{
		if (*PY_nChar_ND == 0)
			continue;
		else
		{
			PY_ND->Fill(*PY_nChar_ND);
		}
	}

	// Normalise PYTHIA non-diffractive histogram
	PY_ND->Scale(1/(PY_ND->GetEntries()));

	// Load nChar values for PYTHIA all default
	TH1D *PY_all_clear = new TH1D("PY_all_clear", "", 70, 0, 70);
	while(readPY_MB_all_clear.Next())
	{
		if (*PY_nChar_all_clear == 0)
			continue;
		else
		{
			PY_all_clear->Fill(*PY_nChar_all_clear);
		}
	}

	// Normalise PYTHIA all histogram default
	PY_all_clear->Scale(1/(PY_all_clear->GetEntries()));

	// Load nChar values for PYTHIA all with colour reconnect 1
	TH1D *PY_all_CR1 = new TH1D("PY_all_CR1", "", 70, 0, 70);
	while(readPY_MB_all_CR1.Next())
	{
		if (*PY_nChar_all_CR1 == 0)
			continue;
		else
		{
			PY_all_CR1->Fill(*PY_nChar_all_CR1);
		}
	}

	// Normalise PYTHIA all histogram with colour reconnect 1
	PY_all_CR1->Scale(1/(PY_all_CR1->GetEntries()));

	// Load nChar for Herwig all
	TH1D *HE_all = new TH1D("HE_all", "", 70, 0, 70);
	while(readHE_MB_all.Next())
	{
		if (*HE_nChar_all == 0)
			continue;
		else
		{
			HE_all->Fill(*HE_nChar_all);
		}
	}

	// Normalise Herwig all histogram
	HE_all->Scale(1/(HE_all->GetEntries()));

	// Load nChar for Herwig non-diffractive
	TH1D *HE_ND = new TH1D("HE_ND", "", 70, 0, 70);
	while(readHE_MB_ND.Next())
	{
		if (*HE_nChar_ND == 0)
			continue;
		else
		{
			HE_ND->Fill(*HE_nChar_ND);
		}
	}

	// Normalise Herwig non-diffractive
	HE_ND->Scale(1/(HE_ND->GetEntries()));


	// Define canvas
	TCanvas* c1 = new TCanvas("MB nChar spectrum", "MB nChar spectrum", 800, 600);
	c1->SetLogy();


	// Format PYTHIA all hist.
	PY_all->SetMarkerStyle(20);
	PY_all->SetMarkerSize(.75);
	PY_all->SetMarkerColor(kBlue);
	PY_all->SetLineColor(kBlue);

	PY_all->GetYaxis()->SetTitle("Normalised Count");
	PY_all->GetYaxis()->LabelsOption("v");
	PY_all->GetYaxis()->SetTitleOffset(1);

	PY_all->GetXaxis()->SetTitle("N_{Ch}");
	PY_all->GetXaxis()->SetTitleOffset(1.25);
	PY_all->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_all->SetStats(kFALSE);

	// Format PYTHIA non-diffractive hist.
	PY_ND->SetMarkerStyle(20);
	PY_ND->SetMarkerSize(.75);
	PY_ND->SetMarkerColor(kRed);
	PY_ND->SetLineColor(kRed);

	PY_ND->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_ND->SetStats(kFALSE);

	// Format PYTHIA all default hist.
	PY_all_clear->SetMarkerStyle(20);
	PY_all_clear->SetMarkerSize(.75);
	PY_all_clear->SetMarkerColor(kTeal);
	PY_all_clear->SetLineColor(kTeal);

	PY_all_clear->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_all_clear->SetStats(kFALSE);

	// Format PYTHIA all default hist.
	PY_all_CR1->SetMarkerStyle(20);
	PY_all_CR1->SetMarkerSize(.75);
	PY_all_CR1->SetMarkerColor(kOrange);
	PY_all_CR1->SetLineColor(kOrange);

	PY_all_CR1->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_all_CR1->SetStats(kFALSE);

	// Format Herwig all hist.
	HE_all->SetMarkerStyle(20);
	HE_all->SetMarkerSize(.75);
	HE_all->SetMarkerColor(kGreen);
	HE_all->SetLineColor(kGreen);

	HE_all->GetYaxis()->SetRangeUser(0.0001,0.5);

	HE_all->SetStats(kFALSE);

	// Format Herwig non-diffractive hist.
	HE_ND->SetMarkerStyle(20);
	HE_ND->SetMarkerSize(.75);
	HE_ND->SetMarkerColor(kViolet);
	HE_ND->SetLineColor(kViolet);

	HE_ND->GetYaxis()->SetRangeUser(0.0001,0.5);

	HE_ND->SetStats(kFALSE);

	// Add hists to canvas
	c1->cd();
	PY_all->Draw("P");
	PY_ND->Draw("P same");
	PY_all_clear->Draw("P same");
	PY_all_CR1->Draw("P same");
	HE_all->Draw("P same");
	HE_ND->Draw("P same");
	
	// Define legend
	TLegend *leg = new TLegend(.5,.6,.9,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, |#eta| < 1, p_{T} > 200 MeV");
	leg->AddEntry(PY_all, "PYTHIA 8, all", "p");
	leg->AddEntry(PY_ND, "PYTHIA 8, non-diffractive", "p");
	leg->AddEntry(PY_all_clear, "PYTHIA 8, all, default", "p");
	leg->AddEntry(PY_all_CR1, "PYTHIA 8, all, CR1", "p");
	leg->AddEntry(HE_all, "Herwig 7, all", "p");
	leg->AddEntry(HE_ND, "Herwig 7, non-diffractive", "p");

	leg->Draw("same");

	c1->Print("../output/nChar_MB.png", "png");
}
