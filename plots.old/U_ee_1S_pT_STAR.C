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

void U_ee_1S_pT_STAR()
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

	Int_t bins_own = 5;
	
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
		if (current < 1.0)
			nMB_bin_own[0]++;
		if (current >= 1.0 && current < 2.0)
			nMB_bin_own[1]++;
		if (current >= 2.0 && current < 3.0)
			nMB_bin_own[2]++;
		if (current >= 3.0 && current < 8.0)
			nMB_bin_own[3]++;
		if (current >= 8.0)
			nMB_bin_own[4]++;
	}

	// ee channel
	Double_t nUps_ee_bin_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		nUps_ee_bin_own[i] = 0;

	Double_t nUps_ee = 0;
	
	while(readUps_ee.Next())
	{
		if (*Ups_ee_d1_pT > 0.2 && abs(*Ups_ee_d1_eta) < 1 && *Ups_ee_d2_pT > 0.2 && abs(*Ups_ee_d2_eta) < 1 && *Ups_ee_pT > 4 && *Ups_ee_1S == 1)
		{
			Double_t current = *Ups_ee_nChar / meanMB_nChar;
			if (current < 1.0)
				nUps_ee_bin_own[0]++;
			if (current >= 1.0 && current < 2.0)
				nUps_ee_bin_own[1]++;
			if (current >= 2.0 && current < 3.0)
				nUps_ee_bin_own[2]++;
			if (current >= 3.0 && current < 8.0)
				nUps_ee_bin_own[3]++;
			if (current >= 8.00)
				nUps_ee_bin_own[4]++;
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

	h1->SetBinContent(570, corrUps_ee_bin_own[0]);
	h1->SetBinError(570, 0.1*corrUps_ee_bin_own[0]);
	h1->SetBinContent(1340, corrUps_ee_bin_own[1]);
	h1->SetBinError(1340, 0.1*corrUps_ee_bin_own[1]);
	h1->SetBinContent(2250, corrUps_ee_bin_own[2]);
	h1->SetBinError(2250, 0.1*corrUps_ee_bin_own[2]);
	h1->SetBinContent(3300, corrUps_ee_bin_own[3]);
	h1->SetBinError(3300, 0.1*corrUps_ee_bin_own[3]);

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
	h1->GetYaxis()->SetRangeUser(0.,9.);

	h1->SetStats(kFALSE);

	TF1 *fit1 = new TF1("all_ee", "pol 2", 0, 4.5);
	fit1->SetLineColor(kBlue);
	h1->Fit(fit1);

	c1->cd();
	h1->Draw("P E1");

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

	TLegend *leg = new TLegend(.2,.7,.55,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, p_{T} > 4 GeV/c");
	leg->AddEntry(h1->DrawCopy("sameP"), "Pythia 8 STAR HF tune", "l");
	leg->AddEntry(ratio_1S, "STAR data", "l");

	leg->Draw("same");

	c1->cd();
	c1->Print("../output.general/Ups_ee_1S_pT_STAR_500.png", "png");
}
