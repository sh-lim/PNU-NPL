#include "Style.h"

void Draw_sub(){

	const int nset = 2;
	const int refbin = 1;

	TFile *infile3 = new TFile("outfile_fig3.root","read");
	TFile *infile4 = new TFile("outfile_fig4.root","read");

	TH1D *h1d_YA_long[nset];
	TH1D *h1d_YA_sub[nset];
	TH1D *h1d_YA_LMsub[nset];

	for (int iset=0; iset<nset; iset++){
		h1d_YA_long[iset] = (TH1D*)infile3->Get(Form("h1d_YA_mid_set%d",iset));
		h1d_YA_sub[iset] = (TH1D*)infile4->Get(Form("h1d_YA_mid_set%d",iset));

		h1d_YA_LMsub[iset] = (TH1D*)h1d_YA_long[iset]->Clone(Form("h1d_YA_LMsub_set%d",iset));
		h1d_YA_LMsub[iset]->Reset();
	}


	/*
	TCanvas *c0 = new TCanvas("c0","c0",1.1*500, 500);
	SetPadStyle();
	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,120,0.5);
	SetHistoStyle("N_{ch}","Associated yield/(GeV/c)","",24,20);

	h1d_YA_sub[0]->Draw("p e0 same");
	h1d_YA_sub[1]->Draw("p e0 same");
	*/

	TCanvas *c1 = new TCanvas("c1","c1",1.1*500, 500);
	SetPadStyle();
	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,120,0.05);
	SetHistoStyle("N_{ch}","Associated yield/(GeV/c)","",24,20);

	//h1d_YA_long[0]->Draw("p e0 same");
	h1d_YA_long[1]->Draw("p e0 same");

	for (int ii=(refbin+1); ii<12; ii++){
		float YA_S_LM = h1d_YA_sub[1]->GetBinContent(refbin+1);
		float YA_S_HM = h1d_YA_sub[1]->GetBinContent(ii+1);
		float SF_S = YA_S_HM / YA_S_LM;

		cout << YA_S_LM << " " << YA_S_HM << " " << SF_S << endl;

		float YA_L_LM = h1d_YA_long[1]->GetBinContent(refbin+1);
		float YA_L_HM = h1d_YA_long[1]->GetBinContent(ii+1);

		float YA_L_LM_err = h1d_YA_long[1]->GetBinError(refbin+1);
		float YA_L_HM_err = h1d_YA_long[1]->GetBinError(ii+1);

		h1d_YA_LMsub[1]->SetBinContent(ii+1, YA_L_HM - YA_L_LM*SF_S);
		h1d_YA_LMsub[1]->SetBinError(ii+1, sqrt(YA_L_HM_err*YA_L_HM_err + YA_L_LM_err*YA_L_LM_err*SF_S*SF_S));

	}

	TFile *infile = new TFile("HEPData-ins1397173-v1-Table_35.root","read");
	TDirectoryFile *tdf = (TDirectoryFile*)infile->Get("Table 35");
	tdf->ls();
	TGraphAsymmErrors *gCMS = (TGraphAsymmErrors*)tdf->Get("Graph1D_y1");
	gCMS->SetFillColorAlpha(kGray,0.5);
	gCMS->SetLineWidth(0);
	gCMS->Draw("3");

	h1d_YA_LMsub[1]->SetMarkerStyle(20);
	h1d_YA_LMsub[1]->SetMarkerColor(1);
	h1d_YA_LMsub[1]->SetLineColor(1);
	h1d_YA_LMsub[1]->Draw("p e0 same");

	{
		TLegend *leg = new TLegend(0.2,0.6,0.65,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(20);
		leg->AddEntry("","pp #sqrt{s}=13 TeV","h");
		leg->AddEntry("","1.0<p_{T}<2.0 GeV/c","h");
		leg->AddEntry("","|#Delta#eta|>2.0","h");
		leg->AddEntry(h1d_YA_long[1],"Pythia8 string shoving","PL");
		leg->AddEntry(h1d_YA_LMsub[1],"LM (10#leqN_{ch}<20) subtracted","PL");
		leg->AddEntry(gCMS,"CMS, PRL 116, 172302","F");
		leg->Draw();
	}

}
