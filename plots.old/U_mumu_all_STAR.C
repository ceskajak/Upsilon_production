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

void U_mumu_all_STAR()
{
	TFile *fileMB = TFile::Open("../data/MinBias.root");
	TFile *fileUps_mumu = TFile::Open("../data/Upsilon_mumu.root");

	TTreeReader readMB("tree", fileMB);
	TTreeReader readUps_mumu("tree", fileUps_mumu);

	TTreeReaderValue<Double_t> MB_nChar(readMB, "nChar");

	TTreeReaderValue<Double_t> Ups_mumu_nChar(readUps_mumu, "nChar");
	TTreeReaderValue<Double_t> Ups_mumu_pT(readUps_mumu, "p_pT");
	TTreeReaderValue<Double_t> Ups_mumu_d1_pT(readUps_mumu, "d1_pT");
	TTreeReaderValue<Double_t> Ups_mumu_d1_eta(readUps_mumu, "d1_eta");
	TTreeReaderValue<Double_t> Ups_mumu_d2_pT(readUps_mumu, "d2_pT");
	TTreeReaderValue<Double_t> Ups_mumu_d2_eta(readUps_mumu, "d2_eta");
	TTreeReaderValue<Double_t> Ups_mumu_1S(readUps_mumu, "Ups1S");
	TTreeReaderValue<Double_t> Ups_mumu_2S(readUps_mumu, "Ups2S");

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

	// mumu channel
	Double_t nUps_mumu_bin_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		nUps_mumu_bin_own[i] = 0;

	Double_t nUps_mumu = 0;

	while(readUps_mumu.Next())
	{
		if (*Ups_mumu_d1_pT > 0.2 && abs(*Ups_mumu_d1_eta) < 1 && *Ups_mumu_d2_pT > 0.2 && abs(*Ups_mumu_d2_eta) < 1)
		{
			Double_t current = *Ups_mumu_nChar / meanMB_nChar;
			if (current < 1.0)
				nUps_mumu_bin_own[0]++;
			if (current >= 1.0 && current < 2.0)
				nUps_mumu_bin_own[1]++;
			if (current >= 2.0 && current < 3.0)
				nUps_mumu_bin_own[2]++;
			if (current >= 3.0 && current < 8.0)
				nUps_mumu_bin_own[3]++;
			if (current >= 8.0)
				nUps_mumu_bin_own[4]++;
		}
		else 
			continue;
		nUps_mumu++;
	}
	readUps_mumu.Restart();
	
	Double_t meanUps_mumu_bin_own[bins_own];
	Double_t corrUps_mumu_bin_own[bins_own];

	for (int i = 0; i < bins_own; i++)
	{
		meanUps_mumu_bin_own[i] = (nUps_mumu / nMB) * nMB_bin_own[i];
		corrUps_mumu_bin_own[i] = nUps_mumu_bin_own[i] / meanUps_mumu_bin_own[i];
	}

	// fill canvases
	TCanvas* c2 = new TCanvas("c2", "#Upsilon(1S+2S) in #mu^{+}#mu^{-}", 800, 600);

	TH1D *h2 = new TH1D("h2", "#Upsilon(1S+2S) in #mu^{+}#mu^{-}", 4000, 0, 4);

	h2->SetBinContent(570, corrUps_mumu_bin_own[0]);
	h2->SetBinError(570, 0.1*corrUps_mumu_bin_own[0]);
	h2->SetBinContent(1340, corrUps_mumu_bin_own[1]);
	h2->SetBinError(1340, 0.1*corrUps_mumu_bin_own[1]);
	h2->SetBinContent(2250, corrUps_mumu_bin_own[2]);
	h2->SetBinError(2250, 0.1*corrUps_mumu_bin_own[2]);
	h2->SetBinContent(3300, corrUps_mumu_bin_own[3]);
	h2->SetBinError(3300, 0.1*corrUps_mumu_bin_own[3]);

	h2->SetMarkerStyle(20);
	h2->SetMarkerSize(1);
	//h2->SetLineWidth(2);
	h2->SetLineColor(kBlue);
	h2->SetMarkerColor(kBlue);

	h2->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	h2->GetYaxis()->LabelsOption("v");
	h2->GetYaxis()->SetTitleOffset(1);

	h2->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	h2->GetXaxis()->SetTitleOffset(1.25);
	h2->GetYaxis()->SetRangeUser(0.,7.);

	h2->SetStats(kFALSE);

	TF1 *fit2 = new TF1("all_mumu", "pol 2", 0, 4.5);
	fit2->SetLineColor(kBlue);
	h2->Fit(fit2);

	c2->cd();
	h2->Draw("P E1");

	TGraphErrors *ratio_all = NULL;
	TGraphAsymmErrors *ratio_all_err = NULL;

	gSystem->cd("../data");
	loadData(ratio_all, ratio_all_err, "dataPYTHIA_DCA0.5_noFDcorrEff_1S+2S+3S_0pt10.txt", "dataMeanPYTHIA_DCA0.5_noFDcorrEff_1S+2S+3S_0pt10.txt", 4);
	ratio_all_err = LoadXYscanned("final_gcent_ups_1S2S3S_syst.txt");
	gSystem->cd("../plots");

	ratio_all->SetMarkerStyle(20);
	ratio_all->SetLineColor(kRed);
	ratio_all->SetMarkerColor(kRed);
	ratio_all->SetMarkerSize(1);

	ratio_all_err->SetLineColor(kRed);
	ratio_all_err->SetFillColor(kRed);
	ratio_all_err->SetFillStyle(0);

	ratio_all->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	ratio_all->GetYaxis()->LabelsOption("v");
	ratio_all->GetYaxis()->SetTitleOffset(2);

	ratio_all->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	ratio_all->GetXaxis()->SetTitleOffset(1.25);
	ratio_all->GetYaxis()->SetRangeUser(0.,7.);

	ratio_all_err->Draw("samee2");
	ratio_all->Draw("samepe1");

	TLegend *leg = new TLegend(.2,.7,.55,.9);
	leg->SetTextSize(0.035);
	leg->SetHeader("p+p@500 GeV, p_{T} > 0 GeV/c");
	leg->AddEntry(h2->DrawCopy("sameP"), "Pythia 8 STAR HF tune", "l");
	leg->AddEntry(ratio_all, "STAR data", "l");

	leg->Draw("same");

	c2->cd();
	c2->Print("../output.general/Ups_mumu_all_STAR_500.png", "png");
}
