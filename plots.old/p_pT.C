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

void p_pT()
{
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	TFile *filePY_Ups = TFile::Open("../data/PY_Upsilon_ee.root");
	TFile *fileHE_Ups2 = TFile::Open("../data/HE_Upsilon_2.root");
	TFile *fileHE_Ups4 = TFile::Open("../data/HE_Upsilon_4.root");
	TFile *fileHE_Ups20 = TFile::Open("../data/HE_Upsilon_20.root");

	TTreeReader readPY_Ups("tree", filePY_Ups);
	TTreeReader readHE_Ups2("tree", fileHE_Ups2);
	TTreeReader readHE_Ups4("tree", fileHE_Ups4);
	TTreeReader readHE_Ups20("tree", fileHE_Ups20);

	TTreeReaderValue<Double_t> PY_p_pT(readPY_Ups, "p_pT");
	TTreeReaderValue<Double_t> HE_p_pT2(readHE_Ups2, "p_pT");
	TTreeReaderValue<Double_t> HE_p_pT4(readHE_Ups4, "p_pT");
	TTreeReaderValue<Double_t> HE_p_pT20(readHE_Ups20, "p_pT");

	TH1D *PY = new TH1D("PY", "", 140, 0, 70);
	while(readPY_Ups.Next())
	{
		if (*PY_p_pT == 0)
			continue;
		else
		{
			PY->Fill(*PY_p_pT);
		}
	}
	PY->Scale(1/(PY->GetEntries()));

	TH1D *HE2 = new TH1D("HE2", "", 140, 0, 70);
	while(readHE_Ups2.Next())
	{
		if (*HE_p_pT2 == 0)
			continue;
		else
		{
			HE2->Fill(*HE_p_pT2);
		}
	}
	HE2->Scale(1/(HE2->GetEntries()));

	TH1D *HE4 = new TH1D("HE4", "", 140, 0, 70);
	while(readHE_Ups4.Next())
	{
		if (*HE_p_pT4 == 0)
			continue;
		else
		{
			HE4->Fill(*HE_p_pT4);
		}
	}
	HE4->Scale(1/(HE4->GetEntries()));

	TH1D *HE20 = new TH1D("HE20", "", 140, 0, 70);
	while(readHE_Ups20.Next())
	{
		if (*HE_p_pT20 == 0)
			continue;
		else
		{
			HE20->Fill(*HE_p_pT20);
		}
	}
	HE20->Scale(1/(HE20->GetEntries()));

	TCanvas* c1 = new TCanvas("c1", "p_pT Ups spectrum", 800, 600);
	c1->SetLogy();

	PY->SetMarkerStyle(20);
	PY->SetMarkerSize(.75);
	PY->SetLineColor(kBlue);
	PY->SetMarkerColor(kBlue);

	PY->GetYaxis()->SetTitle("Normalised Count");
	PY->GetYaxis()->LabelsOption("v");
	PY->GetYaxis()->SetTitleOffset(1);

	PY->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	PY->GetXaxis()->SetTitleOffset(1.25);
	PY->GetYaxis()->SetRangeUser(0.00001,.5);

	PY->SetStats(kFALSE);

	HE2->SetMarkerStyle(20);
	HE2->SetMarkerSize(.75);
	HE2->SetLineColor(kRed);
	HE2->SetMarkerColor(kRed);

	HE2->GetYaxis()->SetTitle("Normalised Count");
	HE2->GetYaxis()->LabelsOption("v");
	HE2->GetYaxis()->SetTitleOffset(1);

	HE2->GetXaxis()->SetTitleOffset(1.25);
	HE2->GetYaxis()->SetRangeUser(0.00001,.5);

	HE2->SetStats(kFALSE);

	HE4->SetMarkerStyle(20);
	HE4->SetMarkerSize(.75);
	HE4->SetLineColor(kGreen);
	HE4->SetMarkerColor(kGreen);

	HE4->GetYaxis()->SetTitle("Normalised Count");
	HE4->GetYaxis()->LabelsOption("v");
	HE4->GetYaxis()->SetTitleOffset(1);

	HE4->GetXaxis()->SetTitleOffset(1.25);
	HE4->GetYaxis()->SetRangeUser(0.00001,.5);

	HE4->SetStats(kFALSE);

	HE20->SetMarkerStyle(20);
	HE20->SetMarkerSize(.75);
	HE20->SetLineColor(kViolet);
	HE20->SetMarkerColor(kViolet);

	HE20->GetYaxis()->SetTitle("Normalised Count");
	HE20->GetYaxis()->LabelsOption("v");
	HE20->GetYaxis()->SetTitleOffset(1);

	HE20->GetXaxis()->SetTitleOffset(1.25);
	HE20->GetYaxis()->SetRangeUser(0.00001,.5);

	HE20->SetStats(kFALSE);

	c1->cd();
	PY->Draw("P");
	HE2->Draw("P same");
	HE4->Draw("P same");
	HE20->Draw("P same");

	TLegend *leg = new TLegend(.5,.58,.9,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg->AddEntry(PY->DrawCopy("same"), "PYTHIA 8 STAR HF Tune", "p");
	leg->AddEntry(HE2->DrawCopy("same"), "HERWIG 7, k_{T} = 2 GeV", "p");
	leg->AddEntry(HE4->DrawCopy("same"), "HERWIG 7, k_{T} = 4 GeV", "p");
	leg->AddEntry(HE20->DrawCopy("same"), "HERWIG 7, k_{T} = 20 GeV", "p");

	leg->Draw("same");

	c1->cd();
	c1->Print("../output/p_pT_Ups.png", "png");
}
