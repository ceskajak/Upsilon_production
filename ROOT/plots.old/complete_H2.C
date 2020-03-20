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

void complete_H2()
{
	gStyle->SetCanvasColor(0);
   	gStyle->SetFrameBorderMode(0);
   	gStyle->SetStatBorderSize(1);
   	gStyle->SetFrameFillColor(0);
   	gStyle->SetTitleFillColor(0);
   	gStyle->SetPalette(1);
	gROOT->ForceStyle();

	TFile *fileMB = TFile::Open("../data/HE_MinBias_ND.root");
	TFile *fileUps_ee = TFile::Open("../data/HE_Upsilon_2.root");

	TTreeReader readMB("tree", fileMB);
	TTreeReader readUps_ee("tree", fileUps_ee);

	TTreeReaderValue<Int_t> MB_nChar(readMB, "nChar");

	TTreeReaderValue<Int_t> Ups_ee_nChar(readUps_ee, "nChar");
	TTreeReaderValue<Double_t> Ups_ee_pT(readUps_ee, "p_pT");
	TTreeReaderValue<Double_t> Ups_ee_d1_pT(readUps_ee, "d1_pT");
	TTreeReaderValue<Double_t> Ups_ee_d1_eta(readUps_ee, "d1_eta");
	TTreeReaderValue<Double_t> Ups_ee_d2_pT(readUps_ee, "d2_pT");
	TTreeReaderValue<Double_t> Ups_ee_d2_eta(readUps_ee, "d2_eta");
	TTreeReaderValue<Int_t> Ups_ee_1S(readUps_ee, "Ups1S");
	TTreeReaderValue<Int_t> Ups_ee_2S(readUps_ee, "Ups2S");

	// nastavime binovani
	Int_t bins_own = 14;
	Int_t bins_STAR = 5;
	
	// minbias celek a stredni hodnota
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

	// minbias distribuce init own
	Double_t nMB_bin_own[bins_own];

	for(int i = 0; i < bins_own; i++)
		nMB_bin_own[i] = 0;

	// minbias distribuce bin_own
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
	readMB.Restart();

	// minbias distribuce init STAR
	Double_t nMB_bin_STAR[bins_STAR];

	for(int i = 0; i < bins_STAR; i++)
		nMB_bin_STAR[i] = 0;

	// minbias distribuce bin_STAR
	while(readMB.Next())
	{
		if(*MB_nChar == 0)
			continue;

		Double_t current = *MB_nChar / meanMB_nChar;
		if (current < 1.00)
			nMB_bin_STAR[0]++;
		if (current >= 1.00 && current < 2.00)
			nMB_bin_STAR[1]++;
		if (current >= 2.00 && current < 3.00)
			nMB_bin_STAR[2]++;
		if (current >= 3.00 && current < 8.00)
			nMB_bin_STAR[3]++;
		if (current >= 8.00)
			nMB_bin_STAR[4]++;
	}
	
	// ups ee all own
	Double_t nUps_ee_all_bin_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		nUps_ee_all_bin_own[i] = 0;

	Double_t nUps_ee_all = 0;
	
	while(readUps_ee.Next())
	{
		if (*Ups_ee_nChar == 0)
			continue;
		else if (*Ups_ee_d1_pT > 0.2 && abs(*Ups_ee_d1_eta) < 1 && *Ups_ee_d2_pT > 0.2 && abs(*Ups_ee_d2_eta) < 1)
		{
			Double_t current = *Ups_ee_nChar / meanMB_nChar;
			if (current < 0.25)
				nUps_ee_all_bin_own[0]++;
			if (current >= 0.25 && current < 0.50)
				nUps_ee_all_bin_own[1]++;
			if (current >= 0.50 && current < 0.75)
				nUps_ee_all_bin_own[2]++;
			if (current >= 0.75 && current < 1.00)
				nUps_ee_all_bin_own[3]++;
			if (current >= 1.00 && current < 1.25)
				nUps_ee_all_bin_own[4]++;
			if (current >= 1.25 && current < 1.50)
				nUps_ee_all_bin_own[5]++;
			if (current >= 1.50 && current < 1.75)
				nUps_ee_all_bin_own[6]++;
			if (current >= 1.75 && current < 2.00)
				nUps_ee_all_bin_own[7]++;
			if (current >= 2.00 && current < 2.25)
				nUps_ee_all_bin_own[8]++;
			if (current >= 2.25 && current < 2.50)
				nUps_ee_all_bin_own[9]++;
			if (current >= 2.50 && current < 2.75)
				nUps_ee_all_bin_own[10]++;
			if (current >= 2.75 && current < 3.00)
				nUps_ee_all_bin_own[11]++;
			if (current >= 3.00 && current < 4.00)
				nUps_ee_all_bin_own[12]++;
			if (current >= 4.00)
				nUps_ee_all_bin_own[13]++;
		}
		else 
			continue;
		nUps_ee_all++;
	}
	readUps_ee.Restart();
	
	Double_t meanUps_ee_all_bin_own[bins_own];
	Double_t corrUps_ee_all_bin_own[bins_own];

	for (int i = 0; i < bins_own; i++)
	{
		meanUps_ee_all_bin_own[i] = (nUps_ee_all / nMB) * nMB_bin_own[i];
		corrUps_ee_all_bin_own[i] = nUps_ee_all_bin_own[i] / meanUps_ee_all_bin_own[i];
	}

	// ups ee all STAR
	Double_t nUps_ee_all_bin_STAR[bins_STAR];
	for (int i = 0; i < bins_STAR; i++)
		nUps_ee_all_bin_STAR[i] = 0;

	while(readUps_ee.Next())
	{
		if (*Ups_ee_nChar == 0)
			continue;
		else if (*Ups_ee_d1_pT > 0.2 && abs(*Ups_ee_d1_eta) < 1 && *Ups_ee_d2_pT > 0.2 && abs(*Ups_ee_d2_eta) < 1)
		{
			Double_t current = *Ups_ee_nChar / meanMB_nChar;
				if (current < 1.00)
					nUps_ee_all_bin_STAR[0]++;
				if (current >= 1.00 && current < 2.00)
					nUps_ee_all_bin_STAR[1]++;
				if (current >= 2.00 && current < 3.00)
					nUps_ee_all_bin_STAR[2]++;
				if (current >= 3.00 && current < 8.00)
					nUps_ee_all_bin_STAR[3]++;
				if (current >= 8.00)
					nUps_ee_all_bin_STAR[4]++;
		}
	}
	readUps_ee.Restart();
	
	Double_t meanUps_ee_all_bin_STAR[bins_STAR];
	Double_t corrUps_ee_all_bin_STAR[bins_STAR];

	for (int i = 0; i < bins_STAR; i++)
	{
		meanUps_ee_all_bin_STAR[i] = (nUps_ee_all / nMB) * nMB_bin_STAR[i];
		corrUps_ee_all_bin_STAR[i] = nUps_ee_all_bin_STAR[i] / meanUps_ee_all_bin_STAR[i];
	}

	// ups ee 1S own
	Double_t nUps_ee_1S_bin_own[bins_own];
	Double_t nUps_ee_1S_pT_bin_own[bins_own];

	for (int i = 0; i < bins_own; i++)
	{
		nUps_ee_1S_bin_own[i] = 0;
		nUps_ee_1S_pT_bin_own[i] = 0;
	}

	Double_t nUps_ee_1S = 0;
	Double_t nUps_ee_1S_pT = 0;
	
	while(readUps_ee.Next())
	{
		Bool_t high_pT = 0;
		if (*Ups_ee_pT > 4)
			high_pT = 1;

		if (*Ups_ee_nChar == 0)
			continue;
		else if (*Ups_ee_d1_pT > 0.2 && abs(*Ups_ee_d1_eta) < 1 && *Ups_ee_d2_pT > 0.2 && abs(*Ups_ee_d2_eta) < 1 && *Ups_ee_1S > 0)
		{
			Double_t current = *Ups_ee_nChar / meanMB_nChar;
			if (current < 0.25)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[0]++;
				else
					nUps_ee_1S_bin_own[0]++;
			}
			else if (current >= 0.25 && current < 0.50)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[1]++;
				else
					nUps_ee_1S_bin_own[1]++;
			}
			else if (current >= 0.50 && current < 0.75)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[2]++;
				else
					nUps_ee_1S_bin_own[2]++;
			}
			else if (current >= 0.75 && current < 1.00)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[3]++;
				else
					nUps_ee_1S_bin_own[3]++;
			}
			else if (current >= 1.00 && current < 1.25)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[4]++;
				else
					nUps_ee_1S_bin_own[4]++;
			}
			else if (current >= 1.25 && current < 1.50)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[5]++;
				else
					nUps_ee_1S_bin_own[5]++;
			}
			else if (current >= 1.50 && current < 1.75)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[6]++;
				else
					nUps_ee_1S_bin_own[6]++;
			}
			else if (current >= 1.75 && current < 2.00)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[7]++;
				else
					nUps_ee_1S_bin_own[7]++;
			}
			else if (current >= 2.00 && current < 2.25)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[8]++;
				else
					nUps_ee_1S_bin_own[8]++;
			}
			else if (current >= 2.25 && current < 2.50)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[9]++;
				else
					nUps_ee_1S_bin_own[9]++;
			}
			else if (current >= 2.50 && current < 2.75)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[10]++;
				else
					nUps_ee_1S_bin_own[10]++;
			}
			else if (current >= 2.75 && current < 3.00)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[11]++;
				else
					nUps_ee_1S_bin_own[11]++;
			}
			else if (current >= 3.00 && current < 4.00)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[12]++;
				else
					nUps_ee_1S_bin_own[12]++;
			}
			else if (current >= 4.00)
			{
				if (high_pT == 1)
					nUps_ee_1S_pT_bin_own[13]++;
				else 
					nUps_ee_1S_bin_own[13]++;
			}
		}
		else 
			continue;

		if (high_pT == 1)
			nUps_ee_1S_pT++;
		else
			nUps_ee_1S++;
	}
	readUps_ee.Restart();
	
	Double_t meanUps_ee_1S_bin_own[bins_own];
	Double_t corrUps_ee_1S_bin_own[bins_own];

	Double_t meanUps_ee_1S_pT_bin_own[bins_own];
	Double_t corrUps_ee_1S_pT_bin_own[bins_own];

	for (int i = 0; i < bins_own; i++)
	{
		meanUps_ee_1S_bin_own[i] = (nUps_ee_1S / nMB) * nMB_bin_own[i];
		corrUps_ee_1S_bin_own[i] = nUps_ee_1S_bin_own[i] / meanUps_ee_1S_bin_own[i];

		meanUps_ee_1S_pT_bin_own[i] = (nUps_ee_1S_pT / nMB) * nMB_bin_own[i];
		corrUps_ee_1S_pT_bin_own[i] = nUps_ee_1S_pT_bin_own[i] / meanUps_ee_1S_pT_bin_own[i];
	}

	// ups ee 1S STAR
	Double_t nUps_ee_1S_bin_STAR[bins_STAR];
	Double_t nUps_ee_1S_pT_bin_STAR[bins_STAR];

	for (int i = 0; i < bins_STAR; i++)
	{
		nUps_ee_1S_bin_STAR[i] = 0;
		nUps_ee_1S_pT_bin_STAR[i] = 0;
	}

	while(readUps_ee.Next())
	{
		if (*Ups_ee_nChar == 0)
			continue;
		else if (*Ups_ee_d1_pT > 0.2 && abs(*Ups_ee_d1_eta) < 1 && *Ups_ee_d2_pT > 0.2 && abs(*Ups_ee_d2_eta) < 1 && *Ups_ee_1S > 0)
		{
			Bool_t high_pT = 0;
			if (*Ups_ee_pT > 4)
				high_pT = 1;
			Double_t current = *Ups_ee_nChar / meanMB_nChar;
				if (current < 1.00)
				{
					if (high_pT == 1)
						nUps_ee_1S_pT_bin_STAR[0]++;
					else
						nUps_ee_1S_bin_STAR[0]++;
				}
				if (current >= 1.00 && current < 2.00)
				{
					if (high_pT == 1)
						nUps_ee_1S_pT_bin_STAR[1]++;
					else
						nUps_ee_1S_bin_STAR[1]++;
				}
				if (current >= 2.00 && current < 3.00)
				{
					if (high_pT == 1)
						nUps_ee_1S_pT_bin_STAR[2]++;
					else
						nUps_ee_1S_bin_STAR[2]++;
				}
				if (current >= 3.00 && current < 8.00)
				{
					if (high_pT == 1)
						nUps_ee_1S_pT_bin_STAR[3]++;
					else
						nUps_ee_1S_bin_STAR[3]++;
				}
				if (current >= 8.00)
				{
					if (high_pT == 1)
						nUps_ee_1S_pT_bin_STAR[4]++;
					else
						nUps_ee_1S_bin_STAR[4]++;
				}
		
		}
		else
			continue;
	}
	readUps_ee.Restart();
	
	Double_t meanUps_ee_1S_bin_STAR[bins_STAR];
	Double_t corrUps_ee_1S_bin_STAR[bins_STAR];

	Double_t meanUps_ee_1S_pT_bin_STAR[bins_STAR];
	Double_t corrUps_ee_1S_pT_bin_STAR[bins_STAR];

	for (int i = 0; i < bins_STAR; i++)
	{
		meanUps_ee_1S_bin_STAR[i] = (nUps_ee_1S / nMB) * nMB_bin_STAR[i];
		corrUps_ee_1S_bin_STAR[i] = nUps_ee_1S_bin_STAR[i] / meanUps_ee_1S_bin_STAR[i];

		meanUps_ee_1S_pT_bin_STAR[i] = (nUps_ee_1S_pT / nMB) * nMB_bin_STAR[i];
		corrUps_ee_1S_pT_bin_STAR[i] = nUps_ee_1S_pT_bin_STAR[i] / meanUps_ee_1S_pT_bin_STAR[i];
	}

	// ups ee 2S own
	Double_t nUps_ee_2S_bin_own[bins_own];

	for (int i = 0; i < bins_own; i++)
		nUps_ee_2S_bin_own[i] = 0;

	Double_t nUps_ee_2S = 0;
	
	while(readUps_ee.Next())
	{
		if (*Ups_ee_nChar == 0)
			continue;
		else if (*Ups_ee_d1_pT > 0.2 && abs(*Ups_ee_d1_eta) < 1 && *Ups_ee_d2_pT > 0.2 && abs(*Ups_ee_d2_eta) < 1 && *Ups_ee_2S > 0)
		{
			Double_t current = *Ups_ee_nChar / meanMB_nChar;
			if (current < 0.25)
				nUps_ee_2S_bin_own[0]++;
			else if (current >= 0.25 && current < 0.50)
					nUps_ee_2S_bin_own[1]++;
			else if (current >= 0.50 && current < 0.75)
					nUps_ee_2S_bin_own[2]++;
			else if (current >= 0.75 && current < 1.00)
					nUps_ee_2S_bin_own[3]++;
			else if (current >= 1.00 && current < 1.25)
					nUps_ee_2S_bin_own[4]++;
			else if (current >= 1.25 && current < 1.50)
					nUps_ee_2S_bin_own[5]++;
			else if (current >= 1.50 && current < 1.75)
					nUps_ee_2S_bin_own[6]++;
			else if (current >= 1.75 && current < 2.00)
					nUps_ee_2S_bin_own[7]++;
			else if (current >= 2.00 && current < 2.25)
					nUps_ee_2S_bin_own[8]++;
			else if (current >= 2.25 && current < 2.50)
					nUps_ee_2S_bin_own[9]++;
			else if (current >= 2.50 && current < 2.75)
					nUps_ee_2S_bin_own[10]++;
			else if (current >= 2.75 && current < 3.00)
					nUps_ee_2S_bin_own[11]++;
			else if (current >= 3.00 && current < 4.00)
					nUps_ee_2S_bin_own[12]++;
			else if (current >= 4.00)
					nUps_ee_2S_bin_own[13]++;
		}
		else 
			continue;
			nUps_ee_2S++;
	}
	readUps_ee.Restart();
	
	Double_t meanUps_ee_2S_bin_own[bins_own];
	Double_t corrUps_ee_2S_bin_own[bins_own];
	for (int i = 0; i < bins_own; i++)
	{
		meanUps_ee_2S_bin_own[i] = (nUps_ee_2S / nMB) * nMB_bin_own[i];
		corrUps_ee_2S_bin_own[i] = nUps_ee_2S_bin_own[i] / meanUps_ee_2S_bin_own[i];
	}

	// ups ee 2S STAR
	Double_t nUps_ee_2S_bin_STAR[bins_STAR];

	for (int i = 0; i < bins_STAR; i++)
		nUps_ee_2S_bin_STAR[i] = 0;

	while(readUps_ee.Next())
	{
		if (*Ups_ee_nChar == 0)
			continue;
		else if (*Ups_ee_d1_pT > 0.2 && abs(*Ups_ee_d1_eta) < 1 && *Ups_ee_d2_pT > 0.2 && abs(*Ups_ee_d2_eta) < 1 && *Ups_ee_2S > 0)
		{
			Double_t current = *Ups_ee_nChar / meanMB_nChar;
				if (current < 1.00)
					nUps_ee_2S_bin_STAR[0]++;
				if (current >= 1.00 && current < 2.00)
						nUps_ee_2S_bin_STAR[1]++;
				if (current >= 2.00 && current < 3.00)
						nUps_ee_2S_bin_STAR[2]++;
				if (current >= 3.00 && current < 8.00)
						nUps_ee_2S_bin_STAR[3]++;
				if (current >= 8.00)
						nUps_ee_2S_bin_STAR[4]++;
		}
		else
			continue;
	}
	readUps_ee.Restart();
	
	Double_t meanUps_ee_2S_bin_STAR[bins_STAR];
	Double_t corrUps_ee_2S_bin_STAR[bins_STAR];

	for (int i = 0; i < bins_STAR; i++)
	{
		meanUps_ee_2S_bin_STAR[i] = (nUps_ee_2S / nMB) * nMB_bin_STAR[i];
		corrUps_ee_2S_bin_STAR[i] = nUps_ee_2S_bin_STAR[i] / meanUps_ee_2S_bin_STAR[i];
	}

	// definuj biny own
	Double_t binning_own[bins_own];
	binning_own[0] = .125;
	binning_own[1] = .375;
	binning_own[2] = .625;
	binning_own[3] = .875;
	binning_own[4] = 1.125;
	binning_own[5] = 1.375;
	binning_own[6] = 1.625;
	binning_own[7] = 1.875;
	binning_own[8] = 2.125;
	binning_own[9] = 2.375;
	binning_own[10] = 2.625;
	binning_own[11] = 2.875;
	binning_own[12] = 3.500;
	binning_own[13] = 8.000;

	// definuj biny STAR
	Double_t binning_STAR[bins_STAR];
	binning_STAR[0] = .57;
	binning_STAR[1] = 1.34;
	binning_STAR[2] = 2.25;
	binning_STAR[3] = 3.3;
	binning_STAR[4] = 8.000;


	// definuj prazdne ex own
	Double_t x_err_own[bins_own];
	
	for (int i = 0; i < bins_own; i++)
		x_err_own[i] = 0;

	Double_t x_err_STAR[bins_STAR];
	
	for (int i = 0; i < bins_STAR; i++)
		x_err_STAR[i] = 0;

	// STAR prelim all
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
	ratio_all->GetYaxis()->SetRangeUser(0.,6.);

	// Ups all own
	Double_t y_err_ee_all_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		y_err_ee_all_own[i] = 0.25*corrUps_ee_all_bin_own[i];

	TGraphErrors *gr_ee_all_own = new TGraphErrors(bins_own, binning_own, corrUps_ee_all_bin_own, x_err_own , y_err_ee_all_own);
	gr_ee_all_own->RemovePoint((bins_own-1));

	gr_ee_all_own->SetTitle("");
	
	gr_ee_all_own->SetFillColor(kAzure);
	gr_ee_all_own->SetFillStyle(1001);

	gr_ee_all_own->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	gr_ee_all_own->GetYaxis()->LabelsOption("v");
	gr_ee_all_own->GetYaxis()->SetTitleOffset(1);
	gr_ee_all_own->GetYaxis()->SetTitleSize(0.04);
	gr_ee_all_own->GetYaxis()->SetRangeUser(0.,6.);

	gr_ee_all_own->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	gr_ee_all_own->GetXaxis()->SetTitleOffset(1.25);
	gr_ee_all_own->GetXaxis()->SetTitleSize(0.04);
	gr_ee_all_own->GetXaxis()->SetRangeUser(0.,3.5);

	TLegend *leg_ee_all_own = new TLegend(.15,.7,.6,.9);
	leg_ee_all_own->SetTextSize(0.03);
	leg_ee_all_own->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg_ee_all_own->AddEntry(gr_ee_all_own, "HERWIG 7, kT = 2 GeV", "f");
	leg_ee_all_own->AddEntry(ratio_all, "STAR Preliminary p_{T} > 0 GeV/c", "lep");

	TCanvas* c_ee_all_own = new TCanvas("c_ee_all_own", "#Upsilon(1S+2S) in e^{+}e^{-}", 800, 600);

	gr_ee_all_own->Draw("a3");

	ratio_all_err->Draw("samee2");
	ratio_all->Draw("samepe1");

	leg_ee_all_own->Draw("same");

	c_ee_all_own->Print("../output/all_own_HE2.png", "png");

	// Ups all STAR
	Double_t y_err_ee_all_STAR[bins_STAR];
	for (int i = 0; i < bins_STAR; i++)
		y_err_ee_all_STAR[i] = 0.25*corrUps_ee_all_bin_STAR[i];

	TGraphErrors *gr_ee_all_STAR = new TGraphErrors(bins_STAR, binning_STAR, corrUps_ee_all_bin_STAR, x_err_STAR , y_err_ee_all_STAR);
	gr_ee_all_STAR->RemovePoint((bins_own-1));

	gr_ee_all_STAR->SetTitle("");
	
	gr_ee_all_STAR->SetFillColor(kAzure);
	gr_ee_all_STAR->SetFillStyle(1001);

	gr_ee_all_STAR->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	gr_ee_all_STAR->GetYaxis()->LabelsOption("v");
	gr_ee_all_STAR->GetYaxis()->SetTitleOffset(1);
	gr_ee_all_STAR->GetYaxis()->SetTitleSize(0.04);
	gr_ee_all_STAR->GetYaxis()->SetRangeUser(0.,6.);

	gr_ee_all_STAR->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	gr_ee_all_STAR->GetXaxis()->SetTitleOffset(1.25);
	gr_ee_all_STAR->GetXaxis()->SetTitleSize(0.04);
	gr_ee_all_STAR->GetXaxis()->SetRangeUser(0.,3.5);

	TLegend *leg_ee_all_STAR = new TLegend(.15,.7,.6,.9);
	leg_ee_all_STAR->SetTextSize(0.03);
	leg_ee_all_STAR->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg_ee_all_STAR->AddEntry(gr_ee_all_STAR, "HERWIG 7, kT = 2 GeV", "f");
	leg_ee_all_STAR->AddEntry(ratio_all, "STAR Preliminary p_{T} > 0 GeV/c", "lep");

	TCanvas* c_ee_all_STAR = new TCanvas("c_ee_all_STAR", "#Upsilon(1S+2S) in e^{+}e^{-}", 800, 600);

	gr_ee_all_own->Draw("a3");

	ratio_all_err->Draw("samee2");
	ratio_all->Draw("samepe1");

	leg_ee_all_STAR->Draw("same");

	c_ee_all_STAR->Print("../output/all_STAR_HE2.png", "png");

	// STAR prelim 1S
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

	// Ups 1S own
	Double_t y_err_ee_1S_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		y_err_ee_1S_own[i] = 0.25*corrUps_ee_1S_bin_own[i];

	TGraphErrors *gr_ee_1S_own = new TGraphErrors(bins_own, binning_own, corrUps_ee_1S_bin_own, x_err_own , y_err_ee_1S_own);
	gr_ee_1S_own->RemovePoint((bins_own-1));

	gr_ee_1S_own->SetTitle("");
	
	gr_ee_1S_own->SetFillColor(kAzure);
	gr_ee_1S_own->SetFillStyle(1001);

	gr_ee_1S_own->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	gr_ee_1S_own->GetYaxis()->LabelsOption("v");
	gr_ee_1S_own->GetYaxis()->SetTitleOffset(1);
	gr_ee_1S_own->GetYaxis()->SetTitleSize(0.04);
	gr_ee_1S_own->GetYaxis()->SetRangeUser(0.,6.);

	gr_ee_1S_own->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	gr_ee_1S_own->GetXaxis()->SetTitleOffset(1.25);
	gr_ee_1S_own->GetXaxis()->SetTitleSize(0.04);
	gr_ee_1S_own->GetXaxis()->SetRangeUser(0.,3.5);

	TLegend *leg_ee_1S_own = new TLegend(.15,.7,.6,.9);
	leg_ee_1S_own->SetTextSize(0.03);
	leg_ee_1S_own->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg_ee_1S_own->AddEntry(gr_ee_1S_own, "HERWIG 7, kT = 2 GeV", "f");
	leg_ee_1S_own->AddEntry(ratio_1S, "STAR Preliminary p_{T} > 0 GeV/c", "lep");

	TCanvas* c_ee_1S_own = new TCanvas("c_ee_1S_own", "#Upsilon(1S+2S) in e^{+}e^{-}", 800, 600);

	gr_ee_1S_own->Draw("a3");

	ratio_1S_err->Draw("samee2");
	ratio_1S->Draw("samepe1");

	leg_ee_1S_own->Draw("same");

	c_ee_1S_own->Print("../output/1S_own_HE2.png", "png");

	// Ups 1S STAR
	Double_t y_err_ee_1S_STAR[bins_STAR];
	for (int i = 0; i < bins_STAR; i++)
		y_err_ee_1S_STAR[i] = 0.25*corrUps_ee_1S_bin_STAR[i];

	TGraphErrors *gr_ee_1S_STAR = new TGraphErrors(bins_STAR, binning_STAR, corrUps_ee_1S_bin_STAR, x_err_STAR , y_err_ee_1S_STAR);
	gr_ee_1S_STAR->RemovePoint((bins_own-1));

	gr_ee_1S_STAR->SetTitle("");
	
	gr_ee_1S_STAR->SetFillColor(kAzure);
	gr_ee_1S_STAR->SetFillStyle(1001);

	gr_ee_1S_STAR->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	gr_ee_1S_STAR->GetYaxis()->LabelsOption("v");
	gr_ee_1S_STAR->GetYaxis()->SetTitleOffset(1);
	gr_ee_1S_STAR->GetYaxis()->SetTitleSize(0.04);
	gr_ee_1S_STAR->GetYaxis()->SetRangeUser(0.,6.);

	gr_ee_1S_STAR->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	gr_ee_1S_STAR->GetXaxis()->SetTitleOffset(1.25);
	gr_ee_1S_STAR->GetXaxis()->SetTitleSize(0.04);
	gr_ee_1S_STAR->GetXaxis()->SetRangeUser(0.,3.5);

	TLegend *leg_ee_1S_STAR = new TLegend(.15,.7,.6,.9);
	leg_ee_1S_STAR->SetTextSize(0.03);
	leg_ee_1S_STAR->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg_ee_1S_STAR->AddEntry(gr_ee_1S_STAR, "HERWIG 7, kT = 2 GeV", "f");
	leg_ee_1S_STAR->AddEntry(ratio_1S, "STAR Preliminary p_{T} > 0 GeV/c", "lep");

	TCanvas* c_ee_1S_STAR = new TCanvas("c_ee_1S_STAR", "#Upsilon(1S+2S) in e^{+}e^{-}", 800, 600);

	gr_ee_1S_own->Draw("a3");

	ratio_1S_err->Draw("samee2");
	ratio_1S->Draw("samepe1");

	leg_ee_1S_STAR->Draw("same");

	c_ee_1S_STAR->Print("../output/1S_STAR_HE2.png", "png");

	// STAR prelim 1S pT
	TGraphErrors *ratio_1S_pT = NULL;
	TGraphAsymmErrors *ratio_1S_pT_err = NULL;

	gSystem->cd("../data");
	loadData(ratio_1S_pT, ratio_1S_pT_err, "dataPYTHIA_DCA0.5_noFDcorrEff_1S_4pt10.txt", "dataMeanPYTHIA_DCA0.5_noFDcorrEff_1S_4pt10.txt", 4);
	ratio_1S_err = LoadXYscanned("final_gcent_ups_1S_4pt10_syst.txt");
	gSystem->cd("../plots");
	
	ratio_1S_pT->SetMarkerStyle(20);
	ratio_1S_pT->SetLineColor(kRed);
	ratio_1S_pT->SetMarkerColor(kRed);
	ratio_1S_pT->SetMarkerSize(1);

	ratio_1S_pT_err->SetLineColor(kRed);
	ratio_1S_pT_err->SetFillColor(kRed);
	ratio_1S_pT_err->SetFillStyle(0);

	ratio_1S_pT->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	ratio_1S_pT->GetYaxis()->LabelsOption("v");
	ratio_1S_pT->GetYaxis()->SetTitleOffset(2);

	ratio_1S_pT->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	ratio_1S_pT->GetXaxis()->SetTitleOffset(1.25);
	ratio_1S_pT->GetYaxis()->SetRangeUser(0.,9.);

	// Ups 1S pT own
	Double_t y_err_ee_1S_pT_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		y_err_ee_1S_pT_own[i] = 0.25*corrUps_ee_1S_pT_bin_own[i];

	TGraphErrors *gr_ee_1S_pT_own = new TGraphErrors(bins_own, binning_own, corrUps_ee_1S_pT_bin_own, x_err_own , y_err_ee_1S_pT_own);
	gr_ee_1S_pT_own->RemovePoint((bins_own-1));

	gr_ee_1S_pT_own->SetTitle("");
	
	gr_ee_1S_pT_own->SetFillColor(kAzure);
	gr_ee_1S_pT_own->SetFillStyle(1001);

	gr_ee_1S_pT_own->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	gr_ee_1S_pT_own->GetYaxis()->LabelsOption("v");
	gr_ee_1S_pT_own->GetYaxis()->SetTitleOffset(1);
	gr_ee_1S_pT_own->GetYaxis()->SetTitleSize(0.04);
	gr_ee_1S_pT_own->GetYaxis()->SetRangeUser(0.,9.);

	gr_ee_1S_pT_own->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	gr_ee_1S_pT_own->GetXaxis()->SetTitleOffset(1.25);
	gr_ee_1S_pT_own->GetXaxis()->SetTitleSize(0.04);
	gr_ee_1S_pT_own->GetXaxis()->SetRangeUser(0.,3.5);

	TLegend *leg_ee_1S_pT_own = new TLegend(.15,.7,.6,.9);
	leg_ee_1S_pT_own->SetTextSize(0.03);
	leg_ee_1S_pT_own->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg_ee_1S_pT_own->AddEntry(gr_ee_1S_pT_own, "HERWIG 7, kT = 2 GeV", "f");
	leg_ee_1S_pT_own->AddEntry(ratio_1S_pT, "STAR Preliminary p_{T} > 4 GeV/c", "lep");

	TCanvas* c_ee_1S_pT_own = new TCanvas("c_ee_1S_pT_own", "#Upsilon(1S+2S) in e^{+}e^{-}", 800, 600);

	gr_ee_1S_pT_own->Draw("a3");

	ratio_1S_pT_err->Draw("samee2");
	ratio_1S_pT->Draw("samepe1");

	leg_ee_1S_pT_own->Draw("same");

	c_ee_1S_pT_own->Print("../output/1S_pT_own_HE2.png", "png");

	// Ups 1S pT STAR
	Double_t y_err_ee_1S_pT_STAR[bins_STAR];
	for (int i = 0; i < bins_STAR; i++)
		y_err_ee_1S_pT_STAR[i] = 0.25*corrUps_ee_1S_pT_bin_STAR[i];

	TGraphErrors *gr_ee_1S_pT_STAR = new TGraphErrors(bins_STAR, binning_STAR, corrUps_ee_1S_pT_bin_STAR, x_err_STAR , y_err_ee_1S_pT_STAR);
	gr_ee_1S_pT_STAR->RemovePoint((bins_own-1));

	gr_ee_1S_pT_STAR->SetTitle("");
	
	gr_ee_1S_pT_STAR->SetFillColor(kAzure);
	gr_ee_1S_pT_STAR->SetFillStyle(1001);

	gr_ee_1S_pT_STAR->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	gr_ee_1S_pT_STAR->GetYaxis()->LabelsOption("v");
	gr_ee_1S_pT_STAR->GetYaxis()->SetTitleOffset(1);
	gr_ee_1S_pT_STAR->GetYaxis()->SetTitleSize(0.04);
	gr_ee_1S_pT_STAR->GetYaxis()->SetRangeUser(0.,9.);

	gr_ee_1S_pT_STAR->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	gr_ee_1S_pT_STAR->GetXaxis()->SetTitleOffset(1.25);
	gr_ee_1S_pT_STAR->GetXaxis()->SetTitleSize(0.04);
	gr_ee_1S_pT_STAR->GetXaxis()->SetRangeUser(0.,3.5);

	TLegend *leg_ee_1S_pT_STAR = new TLegend(.15,.7,.6,.9);
	leg_ee_1S_pT_STAR->SetTextSize(0.03);
	leg_ee_1S_pT_STAR->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg_ee_1S_pT_STAR->AddEntry(gr_ee_1S_pT_STAR, "HERWIG 7, kT = 2 GeV", "f");
	leg_ee_1S_pT_STAR->AddEntry(ratio_1S_pT, "STAR Preliminary p_{T} > 0 GeV/c", "lep");

	TCanvas* c_ee_1S_pT_STAR = new TCanvas("c_ee_1S_STAR", "#Upsilon(1S+2S) in e^{+}e^{-}", 800, 600);

	gr_ee_1S_pT_STAR->Draw("a3");

	ratio_1S_pT_err->Draw("samee2");
	ratio_1S_pT->Draw("samepe1");

	leg_ee_1S_pT_own->Draw("same");

	c_ee_1S_pT_STAR->Print("../output/1S_pT_STAR_HE2.png", "png");

	// Ups 2S own
	Double_t y_err_ee_2S_own[bins_own];
	for (int i = 0; i < bins_own; i++)
		y_err_ee_2S_own[i] = 0.25*corrUps_ee_2S_bin_own[i];

	TH1D *hist_1S_own = new TH1D("hist_1S_own", "", 4000, 0, 4);
	for (int i = 0; i < bins_own; i++)
	{
		hist_1S_own->SetBinContent((binning_own[i]*1000), corrUps_ee_1S_bin_own[i]);
		hist_1S_own->SetBinError((binning_own[i]*1000), y_err_ee_1S_own[i]);
	}

	hist_1S_own->SetMarkerStyle(20);
	hist_1S_own->SetMarkerSize(1);
	hist_1S_own->SetLineColor(kBlue);
	hist_1S_own->SetMarkerColor(kBlue);

	hist_1S_own->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	hist_1S_own->GetYaxis()->LabelsOption("v");
	hist_1S_own->GetYaxis()->SetTitleSize(0.04);
	hist_1S_own->GetYaxis()->SetTitleOffset(1);

	hist_1S_own->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	hist_1S_own->GetXaxis()->SetTitleOffset(1.25);
	hist_1S_own->GetXaxis()->SetTitleSize(0.04);
	hist_1S_own->GetXaxis()->SetRangeUser(0.,6.);

	hist_1S_own->SetStats(kFALSE);

	TH1D *hist_2S_own = new TH1D("hist_2S_own", "", 4000, 0, 4);
	for (int i = 0; i < bins_own; i++)
	{
		hist_2S_own->SetBinContent(((binning_own[i]*1000)+50), corrUps_ee_2S_bin_own[i]);
		hist_2S_own->SetBinError(((binning_own[i]*1000)+50), y_err_ee_2S_own[i]);
	}

	hist_2S_own->SetMarkerStyle(20);
	hist_2S_own->SetMarkerSize(1);
	hist_2S_own->SetLineColor(kRed);
	hist_2S_own->SetMarkerColor(kRed);

	hist_2S_own->GetYaxis()->SetTitle("N_{#Upsilon}^{bin}/<N_{#Upsilon}>");
	hist_2S_own->GetYaxis()->LabelsOption("v");
	hist_2S_own->GetYaxis()->SetTitleSize(0.04);
	hist_2S_own->GetYaxis()->SetTitleOffset(1);

	hist_2S_own->GetXaxis()->SetTitle("N_{ch}/<N_{ch}>");
	hist_2S_own->GetXaxis()->SetTitleOffset(1.25);
	hist_2S_own->GetXaxis()->SetTitleSize(0.04);
	hist_2S_own->GetXaxis()->SetRangeUser(0.,6.);

	hist_2S_own->SetStats(kFALSE);

	TCanvas* c_ee_2S_own = new TCanvas("c_ee_2S_own", "#Upsilon(2S+2S) in e^{+}e^{-}", 800, 600);

	TLegend *leg_ee_2S_own = new TLegend(.15,.7,.6,.9);
	leg_ee_2S_own->SetTextSize(0.03);
	leg_ee_2S_own->SetHeader("p+p@500 GeV, |#eta| < 1");
	leg_ee_2S_own->AddEntry(hist_1S_own, "HERWIG 7, kT = 2 GeV, #Upsilon(1S)", "p");
	leg_ee_2S_own->AddEntry(hist_2S_own, "HERWIG 7, kT = 2 GeV,  #Upsilon(2S)", "p");

	hist_1S_own->Draw("P E1");
	hist_2S_own->Draw("same P E1");
	leg_ee_2S_own->Draw("same");
	c_ee_2S_own->Print("../output/2S_own_HE2.png", "png");

	// Ups 2S STAR
	Double_t y_err_ee_2S_STAR[bins_STAR];
	for (int i = 0; i < bins_STAR; i++)
		y_err_ee_2S_STAR[i] = 0.25*corrUps_ee_2S_bin_STAR[i];

	TCanvas* c_ee_2S_STAR = new TCanvas("c_ee_2S_STAR", "#Upsilon(2S+2S) in e^{+}e^{-}", 800, 600);


	c_ee_2S_STAR->Print("../output/2S_STAR_HE2.png", "png");
}
