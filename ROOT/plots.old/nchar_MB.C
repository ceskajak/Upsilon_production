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
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	TFile *filePY_MB_D = TFile::Open("../data/PY_MinBias_D.root");
	TFile *filePY_MB_ND = TFile::Open("../data/PY_MinBias.root");
	TFile *fileHE_MB_D = TFile::Open("../data/HE_MinBias.root");
	TFile *fileHE_MB_ND = TFile::Open("../data/HE_MinBias_ND.root");

	TTreeReader readPY_MB_D("tree", filePY_MB_D);
	TTreeReader readPY_MB_ND("tree", filePY_MB_ND);
	TTreeReader readHE_MB_D("tree", fileHE_MB_D);
	TTreeReader readHE_MB_ND("tree", fileHE_MB_ND);

	TTreeReaderValue<Double_t> PY_nChar_D(readPY_MB_D, "nChar");
	TTreeReaderValue<Double_t> PY_nChar_ND(readPY_MB_ND, "nChar");
	TTreeReaderValue<Int_t> HE_nChar_D(readHE_MB_D, "nChar");
	TTreeReaderValue<Int_t> HE_nChar_ND(readHE_MB_ND, "nChar");

	TH1D *PY_D = new TH1D("PY_D", "", 100, 0, 100);
	while(readPY_MB_D.Next())
	{
		if (*PY_nChar_D == 0)
			continue;
		else
		{
			PY_D->Fill(*PY_nChar_D);
		}
	}
	PY_D->Scale(1/(PY_D->GetEntries()));

	TH1D *PY_ND = new TH1D("PY_ND", "", 100, 0, 100);
	while(readPY_MB_ND.Next())
	{
		if (*PY_nChar_ND == 0)
			continue;
		else
		{
			PY_ND->Fill(*PY_nChar_ND);
		}
	}
	PY_ND->Scale(1/(PY_ND->GetEntries()));

	TH1D *HE_D = new TH1D("HE_D", "", 100, 0, 100);
	while(readHE_MB_D.Next())
	{
		if (*HE_nChar_D == 0)
			continue;
		else
		{
			HE_D->Fill(*HE_nChar_D);
		}
	}
	HE_D->Scale(1/(HE_D->GetEntries()));

	TH1D *HE_ND = new TH1D("HE_ND", "", 100, 0, 100);
	while(readHE_MB_ND.Next())
	{
		if (*HE_nChar_ND == 0)
			continue;
		else
		{
			HE_ND->Fill(*HE_nChar_ND);
		}
	}
	HE_ND->Scale(1/(HE_ND->GetEntries()));

	TCanvas* c1 = new TCanvas("c1", "nChar MB spectrum", 800, 600);
	c1->SetLogy();

	PY_D->SetMarkerStyle(20);
	PY_D->SetMarkerSize(.75);
	PY_D->SetMarkerColor(kBlue);
	PY_D->SetLineColor(kBlue);

	PY_D->GetYaxis()->SetTitle("Normalised Count");
	PY_D->GetYaxis()->LabelsOption("v");
	PY_D->GetYaxis()->SetTitleOffset(1);

	PY_D->GetXaxis()->SetTitle("N_{Ch}");
	PY_D->GetXaxis()->SetTitleOffset(1.25);
	PY_D->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_D->SetStats(kFALSE);

	PY_ND->SetMarkerStyle(20);
	PY_ND->SetMarkerSize(.75);
	PY_ND->SetMarkerColor(kRed);
	PY_ND->SetLineColor(kRed);

	PY_ND->GetYaxis()->SetRangeUser(0.0001,0.5);

	PY_ND->SetStats(kFALSE);

	HE_D->SetMarkerStyle(20);
	HE_D->SetMarkerSize(.75);
	HE_D->SetMarkerColor(kGreen);
	HE_D->SetLineColor(kGreen);

	HE_D->GetYaxis()->SetRangeUser(0.0001,0.5);

	HE_D->SetStats(kFALSE);

	HE_ND->SetMarkerStyle(20);
	HE_ND->SetMarkerSize(.75);
	HE_ND->SetMarkerColor(kViolet);
	HE_ND->SetLineColor(kViolet);

	HE_ND->GetYaxis()->SetRangeUser(0.0001,0.5);

	HE_ND->SetStats(kFALSE);

	c1->cd();
	PY_D->Draw("P");
	PY_ND->Draw("P same");
	HE_D->Draw("P same");
	HE_ND->Draw("P same");

	TLegend *leg = new TLegend(.5,.7,.9,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg->AddEntry(PY_D, "PYTHIA 8, all", "p");
	leg->AddEntry(PY_ND, "PYTHIA 8, non-diffractive", "p");
	leg->AddEntry(HE_D, "HERWIG 7, all", "p");
	leg->AddEntry(HE_ND, "HERWIG 7, non-diffractive", "p");

	leg->Draw("same");

	c1->Print("../output/nChar_MB_all.png", "png");
}
