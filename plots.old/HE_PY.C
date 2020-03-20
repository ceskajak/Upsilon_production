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

void HE_PY()
{
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	TFile *fileHE_MB = TFile::Open("../data/HE_MinBias_ND.root");
	TFile *filePY_MB = TFile::Open("../data/PY_MinBias.root");
	TFile *fileHE_Ups_ee = TFile::Open("../data/HE_Upsilon_4.root");
	TFile *filePY_Ups_ee = TFile::Open("../data/PY_Upsilon_ee.root");

	TTreeReader readHE_MB("tree", fileHE_MB);
	TTreeReader readPY_MB("tree", filePY_MB);
	TTreeReader readHE_Ups_ee("tree", fileHE_Ups_ee);
	TTreeReader readPY_Ups_ee("tree", filePY_Ups_ee);

	TTreeReaderValue<Int_t> HE_MB_nChar(readHE_MB, "nChar");

	TTreeReaderValue<Double_t> PY_MB_nChar(readPY_MB, "nChar");

	TTreeReaderValue<Int_t> HE_Ups_ee_nChar(readHE_Ups_ee, "nChar");
	TTreeReaderValue<Double_t> HE_Ups_ee_pT(readHE_Ups_ee, "p_pT");
	TTreeReaderValue<Double_t> HE_Ups_ee_d1_pT(readHE_Ups_ee, "d1_pT");
	TTreeReaderValue<Double_t> HE_Ups_ee_d1_eta(readHE_Ups_ee, "d1_eta");
	TTreeReaderValue<Double_t> HE_Ups_ee_d2_pT(readHE_Ups_ee, "d2_pT");
	TTreeReaderValue<Double_t> HE_Ups_ee_d2_eta(readHE_Ups_ee, "d2_eta");
	TTreeReaderValue<Int_t> HE_Ups_ee_1S(readHE_Ups_ee, "Ups1S");
	TTreeReaderValue<Int_t> HE_Ups_ee_2S(readHE_Ups_ee, "Ups2S");

	TTreeReaderValue<Double_t> PY_Ups_ee_nChar(readPY_Ups_ee, "nChar");
	TTreeReaderValue<Double_t> PY_Ups_ee_pT(readPY_Ups_ee, "p_pT");
	TTreeReaderValue<Double_t> PY_Ups_ee_d1_pT(readPY_Ups_ee, "d1_pT");
	TTreeReaderValue<Double_t> PY_Ups_ee_d1_eta(readPY_Ups_ee, "d1_eta");
	TTreeReaderValue<Double_t> PY_Ups_ee_d2_pT(readPY_Ups_ee, "d2_pT");
	TTreeReaderValue<Double_t> PY_Ups_ee_d2_eta(readPY_Ups_ee, "d2_eta");
	TTreeReaderValue<Double_t> PY_Ups_ee_1S(readPY_Ups_ee, "Ups1S");
	TTreeReaderValue<Double_t> PY_Ups_ee_2S(readPY_Ups_ee, "Ups2S");

	Int_t bins_own = 5;
	
	Double_t sumHE_MB_nChar = 0;
	Double_t nHE_MB = 0;

	Double_t sumPY_MB_nChar = 0;
	Double_t nPY_MB = 0;

	while(readHE_MB.Next())
	{
		if (*HE_MB_nChar == 0)
			continue;
		else
		{
			sumHE_MB_nChar += *HE_MB_nChar;
			nHE_MB++;
		}
	}
	readHE_MB.Restart();

	Double_t meanHE_MB_nChar = sumHE_MB_nChar / nHE_MB;

	Double_t nHE_MB_bin_own[bins_own];
	for(int i; i < bins_own; i++)
	{
		nHE_MB_bin_own[i] = 0;
	}

	while(readHE_MB.Next())
	{
		if (*HE_MB_nChar == 0)
			continue;
		Double_t current = *HE_MB_nChar / meanHE_MB_nChar;
		if (current < 1.0)
			nHE_MB_bin_own[0]++;
		if (current >= 1.0 && current < 2.0)
			nHE_MB_bin_own[1]++;
		if (current >= 2.0 && current < 3.0)
			nHE_MB_bin_own[2]++;
		if (current >= 3.0 && current < 8.0)
			nHE_MB_bin_own[3]++;
		if (current >= 8.0)
			nHE_MB_bin_own[4]++;
	}

	// ee channel
	Double_t nHE_Ups_ee_bin_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		nHE_Ups_ee_bin_own[i] = 0;

	Double_t nHE_Ups_ee = 0;
	
	while(readHE_Ups_ee.Next())
	{
		if (*HE_Ups_ee_d1_pT > 0.2 && abs(*HE_Ups_ee_d1_eta) < 1 && *HE_Ups_ee_d2_pT > 0.2 && abs(*HE_Ups_ee_d2_eta) < 1 && *HE_Ups_ee_1S != 0 && *HE_Ups_ee_pT > 4)
		{
			Double_t current = *HE_Ups_ee_nChar / meanHE_MB_nChar;
			if (current < 1.0)
				nHE_Ups_ee_bin_own[0]++;
			if (current >= 1.0 && current < 2.0)
				nHE_Ups_ee_bin_own[1]++;
			if (current >= 2.0 && current < 3.0)
				nHE_Ups_ee_bin_own[2]++;
			if (current >= 3.0 && current < 8.0)
				nHE_Ups_ee_bin_own[3]++;
			if (current >= 8.00)
				nHE_Ups_ee_bin_own[4]++;
		}
		else 
			continue;
		nHE_Ups_ee++;
	}
	readHE_Ups_ee.Restart();
	
	Double_t meanHE_Ups_ee_bin_own[bins_own];
	Double_t corrHE_Ups_ee_bin_own[bins_own];

	for (int i = 0; i < bins_own; i++)
	{
		meanHE_Ups_ee_bin_own[i] = (nHE_Ups_ee / nHE_MB) * nHE_MB_bin_own[i];
		corrHE_Ups_ee_bin_own[i] = nHE_Ups_ee_bin_own[i] / meanHE_Ups_ee_bin_own[i];
	}

	while(readPY_MB.Next())
	{
		if (*PY_MB_nChar == 0)
			continue;
		else
		{
			sumPY_MB_nChar += *PY_MB_nChar;
			nPY_MB++;
		}
	}
	readPY_MB.Restart();

	Double_t meanPY_MB_nChar = sumPY_MB_nChar / nPY_MB;

	Double_t nPY_MB_bin_own[bins_own];
	for(int i; i < bins_own; i++)
	{
		nPY_MB_bin_own[i] = 0;
	}

	while(readPY_MB.Next())
	{
		if (*PY_MB_nChar == 0)
			continue;
		Double_t current = *PY_MB_nChar / meanPY_MB_nChar;
		if (current < 1.0)
			nPY_MB_bin_own[0]++;
		if (current >= 1.0 && current < 2.0)
			nPY_MB_bin_own[1]++;
		if (current >= 2.0 && current < 3.0)
			nPY_MB_bin_own[2]++;
		if (current >= 3.0 && current < 8.0)
			nPY_MB_bin_own[3]++;
		if (current >= 8.0)
			nPY_MB_bin_own[4]++;
	}

	// ee channel
	Double_t nPY_Ups_ee_bin_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		nPY_Ups_ee_bin_own[i] = 0;

	Double_t nPY_Ups_ee = 0;
	
	while(readPY_Ups_ee.Next())
	{
		if (*PY_Ups_ee_d1_pT > 0.2 && abs(*PY_Ups_ee_d1_eta) < 1 && *PY_Ups_ee_d2_pT > 0.2 && abs(*PY_Ups_ee_d2_eta) < 1 && *PY_Ups_ee_1S != 0 && *PY_Ups_ee_pT > 4)
		{
			Double_t current = *PY_Ups_ee_nChar / meanPY_MB_nChar;
			if (current < 1.0)
				nPY_Ups_ee_bin_own[0]++;
			if (current >= 1.0 && current < 2.0)
				nPY_Ups_ee_bin_own[1]++;
			if (current >= 2.0 && current < 3.0)
				nPY_Ups_ee_bin_own[2]++;
			if (current >= 3.0 && current < 8.0)
				nPY_Ups_ee_bin_own[3]++;
			if (current >= 8.00)
				nPY_Ups_ee_bin_own[4]++;
		}
		else 
			continue;
		nPY_Ups_ee++;
	}
	readPY_Ups_ee.Restart();
	
	Double_t meanPY_Ups_ee_bin_own[bins_own];
	Double_t corrPY_Ups_ee_bin_own[bins_own];

	for (int i = 0; i < bins_own; i++)
	{
		meanPY_Ups_ee_bin_own[i] = (nPY_Ups_ee / nPY_MB) * nPY_MB_bin_own[i];
		corrPY_Ups_ee_bin_own[i] = nPY_Ups_ee_bin_own[i] / meanPY_Ups_ee_bin_own[i];
	}

	// fill canvases
	TCanvas* c1 = new TCanvas("c1", "", 800, 600);

	TH1D *h1 = new TH1D("h1", "", 4000, 0, 4);
	TH1D *h2 = new TH1D("h2", "", 4000, 0, 4);

	h1->SetBinContent(570, corrHE_Ups_ee_bin_own[0]);
	h1->SetBinError(570, 0.15*corrHE_Ups_ee_bin_own[0]);
	h1->SetBinContent(1340, corrHE_Ups_ee_bin_own[1]);
	h1->SetBinError(1340, 0.20*corrHE_Ups_ee_bin_own[1]);
	h1->SetBinContent(2250, corrHE_Ups_ee_bin_own[2]);
	h1->SetBinError(2250, 0.25*corrHE_Ups_ee_bin_own[2]);
	h1->SetBinContent(3300, corrHE_Ups_ee_bin_own[3]);
	h1->SetBinError(3300, 0.30*corrHE_Ups_ee_bin_own[3]);

	h2->SetBinContent(570, corrPY_Ups_ee_bin_own[0]);
	h2->SetBinError(570, 0.1*corrPY_Ups_ee_bin_own[0]);
	h2->SetBinContent(1340, corrPY_Ups_ee_bin_own[1]);
	h2->SetBinError(1340, 0.1*corrPY_Ups_ee_bin_own[1]);
	h2->SetBinContent(2250, corrPY_Ups_ee_bin_own[2]);
	h2->SetBinError(2250, 0.1*corrPY_Ups_ee_bin_own[2]);
	h2->SetBinContent(3300, corrPY_Ups_ee_bin_own[3]);
	h2->SetBinError(3300, 0.1*corrPY_Ups_ee_bin_own[3]);

	h1->SetMarkerStyle(20);
	h1->SetMarkerSize(1);
	//h1->SetLineWidth(2);
	h1->SetLineColor(kGreen);
	h1->SetMarkerColor(kGreen);

	h1->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	h1->GetYaxis()->LabelsOption("v");
	h1->GetYaxis()->SetTitleOffset(1);

	h1->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	h1->GetXaxis()->SetTitleOffset(1.25);
	h1->GetYaxis()->SetRangeUser(0.,9.);

	h1->SetStats(kFALSE);

	h2->SetMarkerStyle(20);
	h2->SetMarkerSize(1);
	//h1->SetLineWidth(2);
	h2->SetLineColor(kBlue);
	h2->SetMarkerColor(kBlue);
	h2->GetYaxis()->SetRangeUser(0.,9.);
	h2->SetStats(kFALSE);

	c1->cd();
	h1->Draw("P E1");
	h2->Draw("P E1 same");

	TGraphErrors *ratio_1S = NULL;
	TGraphAsymmErrors *ratio_1S_err = NULL;

	gSystem->cd("../data");
	loadData(ratio_1S, ratio_1S_err, "dataPYTHIA_DCA0.5_noFDcorrEff_1S_4pt10.txt", "dataMeanPYTHIA_DCA0.5_noFDcorrEff_1S_4pt10.txt", 4);
	ratio_1S_err = LoadXYscanned("final_gcent_ups_1S_4pt10_syst.txt");
	gSystem->cd("../plots");

	ratio_1S->SetMarkerStyle(20);
	ratio_1S->SetLineColor(kRed);
	ratio_1S->SetMarkerColor(kRed);
	ratio_1S->SetMarkerSize(1);

	ratio_1S_err->SetLineColor(kRed);
	ratio_1S_err->SetFillColor(kRed);
	ratio_1S_err->SetFillStyle(0);

	ratio_1S->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	ratio_1S->GetYaxis()->LabelsOption("v");
	ratio_1S->GetYaxis()->SetTitleOffset(2);

	ratio_1S->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	ratio_1S->GetXaxis()->SetTitleOffset(1.25);
	ratio_1S->GetYaxis()->SetRangeUser(0.,9.);

	ratio_1S_err->Draw("samee2");
	ratio_1S->Draw("samepe1");

	/*
	TGraph *g1 = new TGraph();
	for (int i = 1; i <= h1->GetNbinsX(); i++)
 		if (h1->GetBinContent(i) != 0.0)
 			g1->SetPoint(g1->GetN(), h1->GetBinCenter(i), h1->GetBinContent(i));

	g1->SetLineColor(kBlue);
	g1->SetLineWidth(2);
	if (g1->GetN() > 1) g1->Draw("C");
	*/

	TLegend *leg = new TLegend(.2,.75,.65,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, p_{T} > 0 GeV/c");
	leg->AddEntry(h2, "PYTHIA 8 STAR HF Tune", "p");
	leg->AddEntry(h1, "HERWIG 7, k_{T} = 4 GeV", "p");
	leg->AddEntry(ratio_1S, "STAR Preliminary p_{T} > 4 GeV/c", "p");

	leg->Draw("same");

	c1->cd();
	c1->Print("../output/complete_pT.png", "png");
}
