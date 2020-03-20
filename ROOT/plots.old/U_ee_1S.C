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

void U_ee_1S()
{
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	TFile *fileMB = TFile::Open("../data/MinBias.root");
	TFile *fileUps_ee = TFile::Open("../data/Upsilon_ee.root");

	TTreeReader readMB("tree", fileMB);
	TTreeReader readUps_ee("tree", fileUps_ee);

	TTreeReaderValue<Double_t> MB_nChar(readMB, "nChar");

	TTreeReaderValue<Double_t> Ups_ee_nChar(readUps_ee, "nChar");
	TTreeReaderValue<Double_t> Ups_ee_pT(readUps_ee, "p_pT");
	TTreeReaderValue<Double_t> Ups_ee_d1_pT(readUps_ee, "d1_pT");
	TTreeReaderValue<Double_t> Ups_ee_d1_eta(readUps_ee, "d1_eta");
	TTreeReaderValue<Double_t> Ups_ee_d2_pT(readUps_ee, "d2_pT");
	TTreeReaderValue<Double_t> Ups_ee_d2_eta(readUps_ee, "d2_eta");
	TTreeReaderValue<Double_t> Ups_ee_1S(readUps_ee, "Ups1S");
	TTreeReaderValue<Double_t> Ups_ee_2S(readUps_ee, "Ups2S");

	Int_t bins_own = 14;
	
	Double_t sumMB_nChar = 0;
	Double_t nMB = 0;

	while(readMB.Next())
	{
		if (*MB_nChar == 0)
			continue;
		else
		{
			sumMB_nChar += *MB_nChar;
			nMB++;
		}
	}
	readMB.Restart();

	Double_t meanMB_nChar = sumMB_nChar / nMB;

	Double_t nMB_bin_own[bins_own];
	for(int i; i < bins_own; i++)
	{
		nMB_bin_own[i] = 0;
	}

	while(readMB.Next())
	{
		if (*MB_nChar == 0)
			continue;
		Double_t current = *MB_nChar / meanMB_nChar;
		if (current < 0.25)
			nMB_bin_own[0]++;
		if (current >= 0.25 && current < 0.50)
			nMB_bin_own[1]++;
		if (current >= 0.50 && current < 0.75)
			nMB_bin_own[2]++;
		if (current >= 0.75 && current < 1.00)
			nMB_bin_own[3]++;
		if (current >= 1.00 && current < 1.25)
			nMB_bin_own[4]++;
		if (current >= 1.25 && current < 1.50)
			nMB_bin_own[5]++;
		if (current >= 1.50 && current < 1.75)
			nMB_bin_own[6]++;
		if (current >= 1.75 && current < 2.00)
			nMB_bin_own[7]++;
		if (current >= 2.00 && current < 2.25)
			nMB_bin_own[8]++;
		if (current >= 2.25 && current < 2.50)
			nMB_bin_own[9]++;
		if (current >= 2.50 && current < 2.75)
			nMB_bin_own[10]++;
		if (current >= 2.75 && current < 3.00)
			nMB_bin_own[11]++;
		if (current >= 3.00 && current < 4.00)
			nMB_bin_own[12]++;
		if (current >= 4.00)
			nMB_bin_own[13]++;
	}

	// ee channel
	Double_t nUps_ee_bin_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		nUps_ee_bin_own[i] = 0;

	Double_t nUps_ee = 0;
	
	while(readUps_ee.Next())
	{
		if (*Ups_ee_d1_pT > 0.2 && abs(*Ups_ee_d1_eta) < 1 && *Ups_ee_d2_pT > 0.2 && abs(*Ups_ee_d2_eta) < 1 && *Ups_ee_1S == 1)
		{
			Double_t current = *Ups_ee_nChar / meanMB_nChar;
			if (current < 0.25)
				nUps_ee_bin_own[0]++;
			if (current >= 0.25 && current < 0.50)
				nUps_ee_bin_own[1]++;
			if (current >= 0.50 && current < 0.75)
				nUps_ee_bin_own[2]++;
			if (current >= 0.75 && current < 1.00)
				nUps_ee_bin_own[3]++;
			if (current >= 1.00 && current < 1.25)
				nUps_ee_bin_own[4]++;
			if (current >= 1.25 && current < 1.50)
				nUps_ee_bin_own[5]++;
			if (current >= 1.50 && current < 1.75)
				nUps_ee_bin_own[6]++;
			if (current >= 1.75 && current < 2.00)
				nUps_ee_bin_own[7]++;
			if (current >= 2.00 && current < 2.25)
				nUps_ee_bin_own[8]++;
			if (current >= 2.25 && current < 2.50)
				nUps_ee_bin_own[9]++;
			if (current >= 2.50 && current < 2.75)
				nUps_ee_bin_own[10]++;
			if (current >= 2.75 && current < 3.00)
				nUps_ee_bin_own[11]++;
			if (current >= 3.00 && current < 4.00)
				nUps_ee_bin_own[12]++;
			if (current >= 4.00)
				nUps_ee_bin_own[13]++;
		}
		else 
			continue;
		nUps_ee++;
	}
	readUps_ee.Restart();
	
	Double_t meanUps_ee_bin_own[bins_own];
	Double_t corrUps_ee_bin_own[bins_own];

	for (int i = 0; i < bins_own; i++)
	{
		meanUps_ee_bin_own[i] = (nUps_ee / nMB) * nMB_bin_own[i];
		corrUps_ee_bin_own[i] = nUps_ee_bin_own[i] / meanUps_ee_bin_own[i];
	}

	// fill canvases
	TCanvas* c1 = new TCanvas("c1", "#Upsilon(1S) in e^{+}e^{-}", 800, 600);

	TH1D *h1 = new TH1D("h1", "#Upsilon(1S) in e^{+}e^{-}", 4000, 0, 4);

	h1->SetBinContent(125, corrUps_ee_bin_own[0]);
	h1->SetBinError(125, 0.1*corrUps_ee_bin_own[0]);
	h1->SetBinContent(375, corrUps_ee_bin_own[1]);
	h1->SetBinError(375, 0.1*corrUps_ee_bin_own[1]);
	h1->SetBinContent(625, corrUps_ee_bin_own[2]);
	h1->SetBinError(625, 0.1*corrUps_ee_bin_own[2]);
	h1->SetBinContent(875, corrUps_ee_bin_own[3]);
	h1->SetBinError(875, 0.1*corrUps_ee_bin_own[3]);
	h1->SetBinContent(1125, corrUps_ee_bin_own[4]);
	h1->SetBinError(1125, 0.1*corrUps_ee_bin_own[4]);
	h1->SetBinContent(1375, corrUps_ee_bin_own[5]);
	h1->SetBinError(1375, 0.1*corrUps_ee_bin_own[5]);
	h1->SetBinContent(1625, corrUps_ee_bin_own[6]);
	h1->SetBinError(1625, 0.1*corrUps_ee_bin_own[6]);
	h1->SetBinContent(1875, corrUps_ee_bin_own[7]);
	h1->SetBinError(1875, 0.1*corrUps_ee_bin_own[7]);
	h1->SetBinContent(2125, corrUps_ee_bin_own[8]);
	h1->SetBinError(2125, 0.1*corrUps_ee_bin_own[8]);
	h1->SetBinContent(2375, corrUps_ee_bin_own[9]);
	h1->SetBinError(2375, 0.1*corrUps_ee_bin_own[9]);
	h1->SetBinContent(2625, corrUps_ee_bin_own[10]);
	h1->SetBinError(2625, 0.1*corrUps_ee_bin_own[10]);
	h1->SetBinContent(2875, corrUps_ee_bin_own[11]);
	h1->SetBinError(2875, 0.1*corrUps_ee_bin_own[11]);
	h1->SetBinContent(3500, corrUps_ee_bin_own[12]);
	h1->SetBinError(3500, 0.1*corrUps_ee_bin_own[12]);

	h1->SetMarkerStyle(20);
	h1->SetMarkerSize(1);
	//h1->SetLineWidth(2);
	h1->SetLineColor(kBlue);
	h1->SetMarkerColor(kBlue);

	h1->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	h1->GetYaxis()->LabelsOption("v");
	h1->GetYaxis()->SetTitleOffset(1);

	h1->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	h1->GetXaxis()->SetTitleOffset(1.25);
	h1->GetYaxis()->SetRangeUser(0.,6.);

	h1->SetStats(kFALSE);

	TF1 *fit1 = new TF1("all_ee", "pol 2", 0, 4.5);
	fit1->SetLineColor(kBlue);
	h1->Fit(fit1);

	c1->cd();
	h1->Draw("P E1");

	TGraphErrors *ratio_1S = NULL;
	TGraphAsymmErrors *ratio_1S_err = NULL;

	gSystem->cd("../data");
	loadData(ratio_1S, ratio_1S_err, "dataPYTHIA_DCA0.5_noFDcorrEff_1S_0pt10.txt", "dataMeanPYTHIA_DCA0.5_noFDcorrEff_1S_0pt10.txt", 4);
	ratio_1S_err = LoadXYscanned("final_gcent_ups_1S_syst.txt");
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
	ratio_1S->GetYaxis()->SetRangeUser(0.,6.);

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

	TLegend *leg = new TLegend(.2,.7,.55,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, p_{T} > 0 GeV/c");
	leg->AddEntry(h1->DrawCopy("sameP"), "Pythia 8 STAR HF tune", "l");
	leg->AddEntry(ratio_1S, "STAR data", "l");

	leg->Draw("same");

	c1->cd();
	c1->Print("../output.general/Ups_ee_1S_500.png", "png");
}
