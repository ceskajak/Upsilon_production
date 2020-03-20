/*
 * save.h
 *
 *  Created on: 16-12-2013
 *      Author: Khaless
 */

#ifndef SAVE_H_
#define SAVE_H_

#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TH1.h>

/*
Int_t save(TCanvas *cnv, const char **names, Int_t n, const TString png="png", const TString eps="",
		const TString pdf="", const TString gif="");
*/
Int_t save(TCanvas *cnv, const char **names, Int_t n, const TString png="png", const TString eps="",
		const TString pdf="", const TString gif="")	{

	if(n==0)
	{
		cnv->cd()->SaveAs(Form("%s.png", names[0]));
		return 1;
	}

	for (int i = 0; i < n; ++i) {


		if(png == "png")	cnv->cd(i+1)->SaveAs(Form("%s.png", names[i]));
		if(eps == "eps")	cnv->cd(i+1)->SaveAs(Form("%s.eps", names[i]));
		if(pdf == "pdf")	cnv->cd(i+1)->SaveAs(Form("%s.pdf", names[i]));
		if(gif == "gif")	cnv->cd(i+1)->SaveAs(Form("%s.gif", names[i]));

	}


	return 1;
}
//---------------------------------
Int_t save(TCanvas *cnv, const TString *names, Int_t n, const TString png="png", const TString eps="",
		const TString pdf="", const TString gif="")	{

	if(n==0)
	{
		cnv->cd()->SaveAs(Form("%s.png", names[0].Data()));
		return 1;
	}

	for (int i = 0; i < n; ++i) {


		if(png == "png")	cnv->cd(i+1)->SaveAs(Form("%s.png", names[i].Data()));
		if(eps == "eps")	cnv->cd(i+1)->SaveAs(Form("%s.eps", names[i].Data()));
		if(pdf == "pdf")	cnv->cd(i+1)->SaveAs(Form("%s.pdf", names[i].Data()));
		if(gif == "gif")	cnv->cd(i+1)->SaveAs(Form("%s.gif", names[i].Data()));

	}


	return 1;
}
//---------------------------------
Int_t saveRoot(TH1F **obj, const char **names, const Int_t n, const char *file_name)	{

	TFile *file = new TFile(file_name, "recreate");

	for (int i = 0; i < n; ++i) {
		if (names != NULL) obj[i]->Write(names[i]);
		else obj[i]->Write(names[i]);
	}

	//file->Close();

	return 1;
}

#endif /* SAVE_H_ */
