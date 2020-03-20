/*
 * LoadEventActivity.h
 *
 *  Created on: 3 lis 2017
 *      Author: Khaless
 */

#ifndef LOADEVENTACTIVITY_H_
#define LOADEVENTACTIVITY_H_

#include <iostream>

#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMatrixDSym.h"

#include "RooAbsReal.h"
#include "RooArgSet.h"

#include "PropagateErrors.h"

void loadData(TGraphErrors *&graph, TString name = "", TString name_mean = "", const Int_t Npoints = 1);
void loadData(TGraphErrors *&graph, TGraphAsymmErrors *&graph_syst, TString name = "", TString name_mean = "", const Int_t Npoints = 1);


void loadData(TGraphErrors *&graph, TString name, TString name_mean, const Int_t Npoints)
{

	Double_t mean_events = 0.0;
	Double_t mean_mult_min = 0.0;
	Double_t mean_mult_max = 0.0;
	Double_t mean_mult_cent = 0.0;
	Double_t mean_cent_min = 0.0;
	Double_t mean_cent_max = 0.0;
	Double_t mean_pt_min = 0.0;
	Double_t mean_pt_max = 0.0;
	Double_t mean_pt_cent = 0.0;
	Double_t mean_yield = 0.0;
	Double_t mean_stat = 0.0;
	Double_t mean_systp = 0.0;
	Double_t mean_systm = 0.0;

	Double_t data_events = 0.0;
	Double_t data_mult_min = 0.0;
	Double_t data_mult_max = 0.0;
	Double_t data_mult_cent = 0.0;
	Double_t data_cent_min = 0.0;
	Double_t data_cent_max = 0.0;
	Double_t data_pt_min = 0.0;
	Double_t data_pt_max = 0.0;
	Double_t data_pt_cent = 0.0;
	Double_t data_yield = 0.0;
	Double_t data_stat = 0.0;
	Double_t data_systp = 0.0;
	Double_t data_systm = 0.0;

	int line_offset = 1;
	const Int_t NpointsMean = 1;

	std::ifstream file;
	std::ifstream fileMean;
	string string;


	graph = new TGraphErrors(Npoints);
	//graph_syst = new TGraphAsymmErrors(Npoints);

	file.open(name, std::ifstream::in);
	fileMean.open(name_mean, std::ifstream::in);

	cout<<endl;

	if (!file) {
		cerr << "Couldn't open parameters file " << name << '!' << endl;
		return;
	} else cout << "Opened file " << name << '!' << endl;

	if (!fileMean) {
		cerr << "Couldn't open parameters file " << name_mean << '!' << endl;
		return;
	} else cout << "Opened file " << name_mean << '!' << endl;

	for (int i = 0; i < line_offset; ++i) {
		std::getline(fileMean, string);
		cout<<string;
	}
	for (int i = 0; i < line_offset; ++i) {
		std::getline(file, string);
		cout<<string;
	}

	cout<<endl;

	for (int i = 0; i < NpointsMean; ++i) {

		if(fileMean.eof()) break;

		fileMean>>mean_events;
		fileMean>>mean_mult_min;
		fileMean>>mean_mult_max;
		fileMean>>mean_mult_cent;
		fileMean>>mean_cent_min;
		fileMean>>mean_cent_max;
		fileMean>>mean_pt_min;
		fileMean>>mean_pt_max;
		fileMean>>mean_pt_cent;
		fileMean>>mean_yield;
		fileMean>>mean_stat;
		fileMean>>mean_systp;
		fileMean>>mean_systm;

		cout<<mean_events<<"\t";
		cout<<mean_mult_min<<"\t";
		cout<<mean_mult_max<<"\t";
		cout<<mean_mult_cent<<"\t";
		cout<<mean_cent_min<<"\t";
		cout<<mean_cent_max<<"\t";
		cout<<mean_pt_min<<"\t";
		cout<<mean_pt_max<<"\t";
		cout<<mean_pt_cent<<"\t";
		cout<<mean_yield<<"\t";
		cout<<mean_stat<<"\t";
		cout<<mean_systp<<"\t";
		cout<<mean_systm<<"\t";
		cout<<endl;

	}

	for (int i = 0; i < Npoints; ++i) {

		if(file.eof()) break;

		file>>data_events;
		file>>data_mult_min;
		file>>data_mult_max;
		file>>data_mult_cent;
		file>>data_cent_min;
		file>>data_cent_max;
		file>>data_pt_min;
		file>>data_pt_max;
		file>>data_pt_cent;
		file>>data_yield;
		file>>data_stat;
		file>>data_systp;
		file>>data_systm;

		cout<<data_events<<"\t";
		cout<<data_mult_min<<"\t";
		cout<<data_mult_max<<"\t";
		cout<<data_mult_cent<<"\t";
		cout<<data_cent_min<<"\t";
		cout<<data_cent_max<<"\t";
		cout<<data_pt_min<<"\t";
		cout<<data_pt_max<<"\t";
		cout<<data_pt_cent<<"\t";
		cout<<data_yield<<"\t";
		cout<<data_stat<<"\t";
		cout<<data_systp<<"\t";
		cout<<data_systm<<"\t";
		cout<<endl;

		double nMaxEv = 1e12;

		RooRealVar YieldBin("YieldBin","YieldBin", 0.0, 0.0, nMaxEv);
		RooRealVar YieldMean("YieldMean","YieldMean", 0.0, 0.0, nMaxEv);

		RooRealVar EventsBin("EventsBin","EventsBin", 0.0, 0.0, nMaxEv);
		RooRealVar EventsMean("EventsMean","EventsMean", 0.0, 0.0, nMaxEv);

		RooRealVar MultBin("MultBin","MultBin", 0.0, 0.0, nMaxEv);
		RooRealVar MultMean("MultMean","MultMean", 0.0, 0.0, nMaxEv);

		YieldBin.setVal(data_yield);
		YieldMean.setVal(mean_yield);
		EventsBin.setVal(data_events);
		EventsMean.setVal(mean_events);

		YieldBin.setError(data_stat);
		YieldMean.setError(mean_stat);
		EventsBin.setError(0.0);
		EventsMean.setError(0.0);
		EventsBin.setConstant(kTRUE);
		EventsMean.setConstant(kTRUE);

		MultBin.setVal(data_mult_cent);
		MultMean.setVal(mean_mult_cent);

		RooArgSet NormYield_argSet(YieldBin, YieldMean);
		RooArgSet NormMult_argSet(MultBin, MultMean);

		RooGenericPdf NormYield("NormYield", "Y/<Y>", "(YieldBin/YieldMean)*(EventsMean/EventsBin)", RooArgSet(YieldBin, YieldMean, EventsBin, EventsMean));
		//RooGenericPdf NormYield("NormYield", "Y/<Y>", "(YieldBin*EventsMean)/(YieldMean*EventsBin)", NormYield_argSet);
		RooGenericPdf NormMult("NormMult", "Mult/<Mult>", "MultBin/MultMean", NormMult_argSet);

		TMatrixDSym NormYield_covMat(2);
		TMatrixDSym NormMult_covMat(2);

		GetCovMat(NormYield_argSet, NormYield_covMat);

		double rho = YieldMean.getError()/YieldBin.getError()*(data_events/mean_events);
		//double rho = YieldMean.getError()/YieldBin.getError()*TMath::Sqrt(data_events/mean_events);
		//double rho = YieldMean.getError()/YieldBin.getError();
		//double rho = YieldBin.getError()/YieldMean.getError();
		//double rho = data_yield/mean_yield;
		rho = 0.0;

		NormYield_covMat(1,0) = rho*NormYield_covMat(1,0);
		NormYield_covMat(0,1) = rho*NormYield_covMat(0,1);

		NormYield_covMat.Print();

		double  normYield_val = NormYield.getVal();
		double  normMult_val = NormMult.getVal();

		double  normYield_err = getPropagatedError(NormYield, NormYield_argSet, NormYield_covMat);
		//double  normYield_err = getPropagatedErrorUncorr(NormYield, NormYield_argSet);
		//double kk = data_yield/data_events;
		//double nn = mean_yield/mean_events;
		double kk = data_yield;
		double nn = mean_yield;
		double variance = (kk+1)*(kk+2)/((nn+2)*(nn+3))-TMath::Power((kk+1)/(nn+2), 2.0);

		double sigma = TMath::Sqrt(variance);

		cout<<"rho = "<<rho<<endl;
		cout<<"Mult/<Mult> = "<<normMult_val<<"\tY/<Y> = "<<normYield_val<<" +\- "<<normYield_err<<" +\- "<<sigma<<endl;

		graph->SetPoint(i, normMult_val, normYield_val);
		graph->SetPointError(i, 0.0, normYield_err);
		//graph_syst->SetPoint(i, normMult_val, normYield_val);

		// systematic uncertainty propagation

		TMatrixDSym NormYield_covMat_syst_hi(2);

		YieldBin.setError(data_systp);
		YieldMean.setError(mean_systp);

		GetCovMat(NormYield_argSet, NormYield_covMat_syst_hi);

		NormYield_covMat_syst_hi(1,0) = rho*NormYield_covMat_syst_hi(1,0);
		NormYield_covMat_syst_hi(0,1) = rho*NormYield_covMat_syst_hi(0,1);

		double  normYield_syst_hi = getPropagatedError(NormYield, NormYield_argSet, NormYield_covMat_syst_hi);

		//graph_syst->SetPointEYhigh(i, normYield_syst_hi);

		//------

		TMatrixDSym NormYield_covMat_syst_lo(2);

		YieldBin.setError(data_systm);
		YieldMean.setError(mean_systm);

		GetCovMat(NormYield_argSet, NormYield_covMat_syst_lo);

		NormYield_covMat_syst_lo(1,0) = rho*NormYield_covMat_syst_lo(1,0);
		NormYield_covMat_syst_lo(0,1) = rho*NormYield_covMat_syst_lo(0,1);

		double  normYield_syst_lo = getPropagatedError(NormYield, NormYield_argSet, NormYield_covMat_syst_lo);

		//graph_syst->SetPointEYlow(i, normYield_syst_lo);

	}

	//graph->Draw("PA");

	cout<<"Loaded!!"<<endl;

}

void loadData(TGraphErrors *&graph, TGraphAsymmErrors *&graph_syst, TString name, TString name_mean, const Int_t Npoints)
{

	Double_t mean_events = 0.0;
	Double_t mean_mult_min = 0.0;
	Double_t mean_mult_max = 0.0;
	Double_t mean_mult_cent = 0.0;
	Double_t mean_cent_min = 0.0;
	Double_t mean_cent_max = 0.0;
	Double_t mean_pt_min = 0.0;
	Double_t mean_pt_max = 0.0;
	Double_t mean_pt_cent = 0.0;
	Double_t mean_yield = 0.0;
	Double_t mean_stat = 0.0;
	Double_t mean_systp = 0.0;
	Double_t mean_systm = 0.0;

	Double_t data_events = 0.0;
	Double_t data_mult_min = 0.0;
	Double_t data_mult_max = 0.0;
	Double_t data_mult_cent = 0.0;
	Double_t data_cent_min = 0.0;
	Double_t data_cent_max = 0.0;
	Double_t data_pt_min = 0.0;
	Double_t data_pt_max = 0.0;
	Double_t data_pt_cent = 0.0;
	Double_t data_yield = 0.0;
	Double_t data_stat = 0.0;
	Double_t data_systp = 0.0;
	Double_t data_systm = 0.0;

	int line_offset = 1;
	const Int_t NpointsMean = 1;

	std::ifstream file;
	std::ifstream fileMean;
	string string;


	graph = new TGraphErrors(Npoints);
	graph_syst = new TGraphAsymmErrors(Npoints);

	file.open(name, std::ifstream::in);
	fileMean.open(name_mean, std::ifstream::in);

	cout<<endl;

	if (!file) {
		cerr << "Couldn't open parameters file " << name << '!' << endl;
		return;
	} else cout << "Opened file " << name << '!' << endl;

	if (!fileMean) {
		cerr << "Couldn't open parameters file " << name_mean << '!' << endl;
		return;
	} else cout << "Opened file " << name_mean << '!' << endl;

	for (int i = 0; i < line_offset; ++i) {
		std::getline(fileMean, string);
		cout<<string;
	}
	for (int i = 0; i < line_offset; ++i) {
		std::getline(file, string);
		cout<<string;
	}

	cout<<endl;

	for (int i = 0; i < NpointsMean; ++i) {

		if(fileMean.eof()) break;

		fileMean>>mean_events;
		fileMean>>mean_mult_min;
		fileMean>>mean_mult_max;
		fileMean>>mean_mult_cent;
		fileMean>>mean_cent_min;
		fileMean>>mean_cent_max;
		fileMean>>mean_pt_min;
		fileMean>>mean_pt_max;
		fileMean>>mean_pt_cent;
		fileMean>>mean_yield;
		fileMean>>mean_stat;
		fileMean>>mean_systp;
		fileMean>>mean_systm;

		cout<<mean_events<<"\t";
		cout<<mean_mult_min<<"\t";
		cout<<mean_mult_max<<"\t";
		cout<<mean_mult_cent<<"\t";
		cout<<mean_cent_min<<"\t";
		cout<<mean_cent_max<<"\t";
		cout<<mean_pt_min<<"\t";
		cout<<mean_pt_max<<"\t";
		cout<<mean_pt_cent<<"\t";
		cout<<mean_yield<<"\t";
		cout<<mean_stat<<"\t";
		cout<<mean_systp<<"\t";
		cout<<mean_systm<<"\t";
		cout<<endl;

	}

	for (int i = 0; i < Npoints; ++i) {

		if(file.eof()) break;

		file>>data_events;
		file>>data_mult_min;
		file>>data_mult_max;
		file>>data_mult_cent;
		file>>data_cent_min;
		file>>data_cent_max;
		file>>data_pt_min;
		file>>data_pt_max;
		file>>data_pt_cent;
		file>>data_yield;
		file>>data_stat;
		file>>data_systp;
		file>>data_systm;

		cout<<data_events<<"\t";
		cout<<data_mult_min<<"\t";
		cout<<data_mult_max<<"\t";
		cout<<data_mult_cent<<"\t";
		cout<<data_cent_min<<"\t";
		cout<<data_cent_max<<"\t";
		cout<<data_pt_min<<"\t";
		cout<<data_pt_max<<"\t";
		cout<<data_pt_cent<<"\t";
		cout<<data_yield<<"\t";
		cout<<data_stat<<"\t";
		cout<<data_systp<<"\t";
		cout<<data_systm<<"\t";
		cout<<endl;

		double nMaxEv = 1e12;

		RooRealVar YieldBin("YieldBin","YieldBin", 0.0, 0.0, nMaxEv);
		RooRealVar YieldMean("YieldMean","YieldMean", 0.0, 0.0, nMaxEv);

		RooRealVar EventsBin("EventsBin","EventsBin", 0.0, 0.0, nMaxEv);
		RooRealVar EventsMean("EventsMean","EventsMean", 0.0, 0.0, nMaxEv);

		RooRealVar MultBin("MultBin","MultBin", 0.0, 0.0, nMaxEv);
		RooRealVar MultMean("MultMean","MultMean", 0.0, 0.0, nMaxEv);

		YieldBin.setVal(data_yield);
		YieldMean.setVal(mean_yield);
		EventsBin.setVal(data_events);
		EventsMean.setVal(mean_events);

		YieldBin.setError(data_stat);
		YieldMean.setError(mean_stat);
		EventsBin.setError(0.0);
		EventsMean.setError(0.0);
		EventsBin.setConstant(kTRUE);
		EventsMean.setConstant(kTRUE);

		MultBin.setVal(data_mult_cent);
		MultMean.setVal(mean_mult_cent);

		RooArgSet NormYield_argSet(YieldBin, YieldMean);
		RooArgSet NormMult_argSet(MultBin, MultMean);

		RooGenericPdf NormYield("NormYield", "Y/<Y>", "(YieldBin/YieldMean)*(EventsMean/EventsBin)", RooArgSet(YieldBin, YieldMean, EventsBin, EventsMean));
		//RooGenericPdf NormYield("NormYield", "Y/<Y>", "(YieldBin*EventsMean)/(YieldMean*EventsBin)", NormYield_argSet);
		RooGenericPdf NormMult("NormMult", "Mult/<Mult>", "MultBin/MultMean", NormMult_argSet);

		TMatrixDSym NormYield_covMat(2);
		TMatrixDSym NormMult_covMat(2);

		GetCovMat(NormYield_argSet, NormYield_covMat);

		double rho = YieldMean.getError()/YieldBin.getError()*(data_events/mean_events);
		//double rho = YieldMean.getError()/YieldBin.getError()*TMath::Sqrt(data_events/mean_events);
		//double rho = YieldMean.getError()/YieldBin.getError();
		//double rho = YieldBin.getError()/YieldMean.getError();
		//double rho = data_yield/mean_yield;
		rho = 0.0;

		NormYield_covMat(1,0) = rho*NormYield_covMat(1,0);
		NormYield_covMat(0,1) = rho*NormYield_covMat(0,1);

		NormYield_covMat.Print();

		double  normYield_val = NormYield.getVal();
		double  normMult_val = NormMult.getVal();

		double  normYield_err = getPropagatedError(NormYield, NormYield_argSet, NormYield_covMat);
		//double  normYield_err = getPropagatedErrorUncorr(NormYield, NormYield_argSet);
		//double kk = data_yield/data_events;
		//double nn = mean_yield/mean_events;
		double kk = data_yield;
		double nn = mean_yield;
		double variance = (kk+1)*(kk+2)/((nn+2)*(nn+3))-TMath::Power((kk+1)/(nn+2), 2.0);

		double sigma = TMath::Sqrt(variance);

		cout<<"rho = "<<rho<<endl;
		cout<<"Mult/<Mult> = "<<normMult_val<<"\tY/<Y> = "<<normYield_val<<" +\- "<<normYield_err<<" +\- "<<sigma<<endl;

		graph->SetPoint(i, normMult_val, normYield_val);
		graph->SetPointError(i, 0.0, normYield_err);
		graph_syst->SetPoint(i, normMult_val, normYield_val);

		// systematic uncertainty propagation

		TMatrixDSym NormYield_covMat_syst_hi(2);

		YieldBin.setError(data_systp);
		YieldMean.setError(mean_systp);

		GetCovMat(NormYield_argSet, NormYield_covMat_syst_hi);

		NormYield_covMat_syst_hi(1,0) = rho*NormYield_covMat_syst_hi(1,0);
		NormYield_covMat_syst_hi(0,1) = rho*NormYield_covMat_syst_hi(0,1);

		double  normYield_syst_hi = getPropagatedError(NormYield, NormYield_argSet, NormYield_covMat_syst_hi);

		graph_syst->SetPointEYhigh(i, normYield_syst_hi);

		//------

		TMatrixDSym NormYield_covMat_syst_lo(2);

		YieldBin.setError(data_systm);
		YieldMean.setError(mean_systm);

		GetCovMat(NormYield_argSet, NormYield_covMat_syst_lo);

		NormYield_covMat_syst_lo(1,0) = rho*NormYield_covMat_syst_lo(1,0);
		NormYield_covMat_syst_lo(0,1) = rho*NormYield_covMat_syst_lo(0,1);

		double  normYield_syst_lo = getPropagatedError(NormYield, NormYield_argSet, NormYield_covMat_syst_lo);

		graph_syst->SetPointEYlow(i, normYield_syst_lo);

	}

	//graph->Draw("PA");

	cout<<"Loaded!!"<<endl;

}

#endif /* LOADEVENTACTIVITY_H_ */
