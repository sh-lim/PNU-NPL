#include "Style.h"

void Draw_atlas(const bool bSAVE=false){

	TLegendEntry *le;

	const int nset = 2;
	const int nColor[nset] = {2, 4};
	const float const_pi = TMath::Pi();

	TFile *infile_v22[nset];
	TFile *infile_v33[nset];

	TFile *infile_v22_pT[nset];
	TFile *infile_v33_pT[nset];

	TFile *infile_fit[nset];

	infile_v22[0] = new TFile("outfile_v22_mult_pp13TeV_set05set06_grp000_try000.root","read");
	infile_v22[1] = new TFile("outfile_v22_mult_pp13TeV_set05_grp003_try000.root","read");

	infile_v33[0] = new TFile("outfile_v33_mult_pp13TeV_set05set06_grp000_try000.root","read");
	infile_v33[1] = new TFile("outfile_v33_mult_pp13TeV_set05_grp003_try000.root","read");

	infile_v22_pT[0] = new TFile("outfile_v22_pT_pp13TeV_set05set06_grp000_try001.root","read");
	infile_v22_pT[1] = new TFile("outfile_v22_pT_pp13TeV_set05_grp003_try001.root","read");

	infile_v33_pT[0] = new TFile("outfile_v33_pT_pp13TeV_set05set06_grp000_try001.root","read");
	infile_v33_pT[1] = new TFile("outfile_v33_pT_pp13TeV_set05_grp003_try001.root","read");

	infile_fit[0] = new TFile("outfile_template_fit_pp13TeV_set00_grp000_try010.root","read");
	infile_fit[1] = new TFile("outfile_template_fit_pp13TeV_set00_grp001_try010.root","read");

	TGraphErrors *gv22[nset];
	TGraphErrors *gv33[nset];

	TGraphErrors *gv22_pT[nset];
	TGraphErrors *gv33_pT[nset];

	TH1D *hHM[nset];
	TH1D *hLM[nset];
	TF1 *fPED[nset];
	TF1 *fFLOW[nset];
	TH1D *hFIT[nset];

	for (int iset=0; iset<nset; iset++){
		gv22[iset] = (TGraphErrors*)infile_v22[iset]->Get("gv22_sub_nref_3");
		gv33[iset] = (TGraphErrors*)infile_v33[iset]->Get("gv33_sub_nref_3");

		gv22_pT[iset] = (TGraphErrors*)infile_v22_pT[iset]->Get("gv22_sub_nref_3");
		gv33_pT[iset] = (TGraphErrors*)infile_v33_pT[iset]->Get("gv33_sub_nref_3");

		gv22[iset]->SetLineColor(nColor[iset]);
		gv33[iset]->SetLineColor(nColor[iset]);

		gv22_pT[iset]->SetLineColor(nColor[iset]);
		gv33_pT[iset]->SetLineColor(nColor[iset]);

		hHM[iset] = (TH1D*)infile_fit[iset]->Get("hHM_mult8");
		hLM[iset] = (TH1D*)infile_fit[iset]->Get("hLM_mult8");
		fPED[iset] = (TF1*)infile_fit[iset]->Get("fPED_mult8");
		fFLOW[iset] = (TF1*)infile_fit[iset]->Get("fFLOW_mult8");
		hFIT[iset] = (TH1D*)infile_fit[iset]->Get("hFIT_mult8");
	}

	ifstream fdata;
	float tmp_xx, tmp_yy;
	int tmp_ind;

	fdata.open("ATLAS-v22-mult.txt");
	TGraphErrors *gdata_v22_mult = new TGraphErrors;
	tmp_ind = 0;
	while ( fdata >> tmp_xx >> tmp_yy ){
		cout << tmp_xx << " " << tmp_yy << endl;
		gdata_v22_mult->SetPoint(tmp_ind, tmp_xx, tmp_yy/1000.);
		tmp_ind++;
	}
	fdata.close();

	fdata.open("ATLAS-v22-pT.txt");
	TGraphErrors *gdata_v22_pT = new TGraphErrors;
	tmp_ind = 0;
	while ( fdata >> tmp_xx >> tmp_yy ){
		cout << tmp_xx << " " << tmp_yy << endl;
		gdata_v22_pT->SetPoint(tmp_ind, tmp_xx, tmp_yy);
		tmp_ind++;
	}
	fdata.close();

	fdata.open("ATLAS-v33-mult.txt");
	TGraphErrors *gdata_v33_mult = new TGraphErrors;
	tmp_ind = 0;
	while ( fdata >> tmp_xx >> tmp_yy ){
		cout << tmp_xx << " " << tmp_yy << endl;
		gdata_v33_mult->SetPoint(tmp_ind, tmp_xx, tmp_yy/1000.);
		tmp_ind++;
	}
	fdata.close();

	fdata.open("ATLAS-v33-pT.txt");
	TGraphErrors *gdata_v33_pT = new TGraphErrors;
	tmp_ind = 0;
	while ( fdata >> tmp_xx >> tmp_yy ){
		cout << tmp_xx << " " << tmp_yy << endl;
		gdata_v33_pT->SetPoint(tmp_ind, tmp_xx, tmp_yy);
		tmp_ind++;
	}
	fdata.close();
	

	TCanvas *c3 = new TCanvas("c3","c3",1.1*500,500);
	SetPadStyle();
	gPad->SetBottomMargin(0.13);
	gPad->SetLeftMargin(0.16);

	htmp = (TH1D*)gPad->DrawFrame(0,-0.003,140,0.016);
	SetHistoStyle("N_{ch}","v_{22}","",24,20);
	htmp->GetXaxis()->SetTitleOffset(1.0);
	htmp->GetYaxis()->SetTitleOffset(1.6);

	{
		TLine *line = new TLine(0,0,140,0);
		line->SetLineWidth(2);
		line->SetLineStyle(2);
		line->SetLineColor(1);
		line->Draw();
	}

	gdata_v22_mult->SetMarkerStyle(20);
	gdata_v22_mult->Draw("P");
	gv22[0]->Draw("c");
	gv22[1]->Draw("c");

	{
		TLegend *leg = new TLegend(0.45,0.55,0.85,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(20);
		le = leg->AddEntry("","pp #sqrt{s}=13 TeV","");
		le = leg->AddEntry("","Template fit, LM 0#leqN_{ch}<20","");
		le = leg->AddEntry("","0.5<p_{T}^{Trig}, p_{T}^{Assoc}<5.0 GeV/c","");
		le = leg->AddEntry("","0<|#eta^{Trig}|, |#eta^{Assoc}|<2.5","");
		le = leg->AddEntry(gdata_v22_mult,"ATLAS","P");
		le = leg->AddEntry(gv22[0],"PYTHIA8 default","L");
		le = leg->AddEntry(gv22[1],"PYTHIA8 string shoving","L");
		leg->Draw();
	}

	TCanvas *c3_ = new TCanvas("c3_","c3_",1.1*500,500);
	SetPadStyle();
	gPad->SetBottomMargin(0.13);
	gPad->SetLeftMargin(0.16);

	htmp = (TH1D*)gPad->DrawFrame(0,-0.003,5,0.016);
	SetHistoStyle("p_{T}^{Trig} (GeV/c)","v_{22}","",24,20);
	htmp->GetXaxis()->SetTitleOffset(1.0);
	htmp->GetYaxis()->SetTitleOffset(1.6);

	{
		TLine *line = new TLine(0,0,5,0);
		line->SetLineWidth(2);
		line->SetLineStyle(2);
		line->SetLineColor(1);
		line->Draw();
	}

	gdata_v22_pT->SetMarkerStyle(20);
	gdata_v22_pT->Draw("P");
	gv22_pT[0]->Draw("c");
	gv22_pT[1]->Draw("c");

	{
		TLegend *leg = new TLegend(0.45,0.55,0.85,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(20);
		le = leg->AddEntry("","pp #sqrt{s}=13 TeV","");
		le = leg->AddEntry("","Template fit, LM 0#leqN_{ch}<20","");
		le = leg->AddEntry("","0.5<p_{T}^{Assoc}<5.0 GeV/c","");
		le = leg->AddEntry("","0<|#eta^{Trig}|, |#eta^{Assoc}|<2.5","");
		le = leg->AddEntry(gdata_v22_mult,"ATLAS","P");
		le = leg->AddEntry(gv22[0],"PYTHIA8 default","L");
		le = leg->AddEntry(gv22[1],"PYTHIA8 string shoving","L");
		leg->Draw();
	}

	//return;

	TCanvas *c4 = new TCanvas("c4","c4",1.1*500,500);
	SetPadStyle();
	gPad->SetBottomMargin(0.13);
	gPad->SetLeftMargin(0.16);

	htmp = (TH1D*)gPad->DrawFrame(0,-0.0005,140,0.0025);
	SetHistoStyle("N_{ch}","v_{33}","",24,20);
	htmp->GetXaxis()->SetTitleOffset(1.0);
	htmp->GetYaxis()->SetTitleOffset(1.6);

	{
		TLine *line = new TLine(0,0,140,0);
		line->SetLineWidth(2);
		line->SetLineStyle(2);
		line->SetLineColor(1);
		line->Draw();
	}

	gdata_v33_mult->SetMarkerStyle(20);
	gdata_v33_mult->Draw("P");
	gv33[0]->Draw("c");
	gv33[1]->Draw("c");

	{
		TLegend *leg = new TLegend(0.45,0.55,0.85,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(20);
		le = leg->AddEntry("","p+p #sqrt{s}=13 TeV","");
		le = leg->AddEntry("","Template fit, LM 0#leqN_{ch}<20","");
		le = leg->AddEntry("","0.5<p_{T}^{Trig}, p_{T}^{Assoc}<5.0 GeV/c","");
		le = leg->AddEntry("","0<|#eta^{Trig}|, |#eta^{Assoc}|<2.5","");
		le = leg->AddEntry(gdata_v22_mult,"ATLAS","P");
		le = leg->AddEntry(gv22[0],"PYTHIA8 default","L");
		le = leg->AddEntry(gv22[1],"PYTHIA8 string shoving","L");
		leg->Draw();
	}

	TCanvas *c4_ = new TCanvas("c4_","c4_",1.1*500,500);
	SetPadStyle();
	gPad->SetBottomMargin(0.13);
	gPad->SetLeftMargin(0.16);

	htmp = (TH1D*)gPad->DrawFrame(0,-0.0005,5,0.0025);
	SetHistoStyle("p_{T}^{Trig} (GeV/c)","v_{33}","",24,20);
	htmp->GetXaxis()->SetTitleOffset(1.0);
	htmp->GetYaxis()->SetTitleOffset(1.6);

	{
		TLine *line = new TLine(0,0,5,0);
		line->SetLineWidth(2);
		line->SetLineStyle(2);
		line->SetLineColor(1);
		line->Draw();
	}

	gdata_v33_pT->SetMarkerStyle(20);
	gdata_v33_pT->Draw("P");
	gv33_pT[0]->Draw("c");
	gv33_pT[1]->Draw("c");

	{
		TLegend *leg = new TLegend(0.45,0.55,0.85,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(20);
		le = leg->AddEntry("","pp #sqrt{s}=13 TeV","");
		le = leg->AddEntry("","Template fit, LM 0#leqN_{ch}<20","");
		le = leg->AddEntry("","0.5<p_{T}^{Assoc}<5.0 GeV/c","");
		le = leg->AddEntry("","0<|#eta^{Trig}|, |#eta^{Assoc}|<2.5","");
		le = leg->AddEntry(gdata_v22_mult,"ATLAS","P");
		le = leg->AddEntry(gv22[0],"PYTHIA8 default","L");
		le = leg->AddEntry(gv22[1],"PYTHIA8 string shoving","L");
		leg->Draw();
	}

	TCanvas *c5[nset];

	for (int iset=0; iset<nset; iset++){
		c5[iset] = new TCanvas(Form("c5_set%d",iset),Form("c5_set%d",iset),1.1*500,500);
		SetPadStyle();
		gPad->SetBottomMargin(0.13);
		gPad->SetLeftMargin(0.16);

		float max = hHM[iset]->GetMaximum();
		float min = hHM[iset]->GetMinimum();

		htmp = (TH1D*)gPad->DrawFrame(-const_pi/2, min-0.05*(max-min), 3*const_pi/2, max+0.05*(max-min));
		SetHistoStyle("#Delta#phi (rad)","Per trigger yield","",24,20);
		hHM[iset]->Draw("p same");
		hLM[iset]->Draw("p same");
		fPED[iset]->Draw("same");
		fFLOW[iset]->Draw("same");
		hFIT[iset]->Draw("same");

		{
			TLegend *leg = new TLegend(0.18,0.4,0.55,0.95);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextFont(43);
			leg->SetTextSize(20);
			le = leg->AddEntry("","pp #sqrt{s}=13 TeV","");
			if ( iset==0 ){
				le = leg->AddEntry("","PYTHIA8 default","");
			}else{
				le = leg->AddEntry("","PYTHIA8 string shoving","");
			}
			le = leg->AddEntry("","Template fit","");
			le = leg->AddEntry("","0.5<p_{T}^{Assoc}<5.0 GeV/c","");
			le = leg->AddEntry("","0<|#eta^{Trig}|, |#eta^{Assoc}|<2.5","");
			le = leg->AddEntry(hHM[iset],"HM 80#leqN_{ch}<90","P");
			le = leg->AddEntry(hLM[iset],"Scaled LM 0#leqN_{ch}<20","P");
			le = leg->AddEntry(fPED[iset],"Pedestal","L");
			le = leg->AddEntry(fFLOW[iset],"Flow","L");
			le = leg->AddEntry(hFIT[iset],"Total fit","L");
			leg->Draw();
		}

	}


	if ( bSAVE ){
		c3->cd();
		c3->SaveAs("v22-mult.png");
		c3_->cd();
		c3_->SaveAs("v22-pT.png");
		c4->cd();
		c4->SaveAs("v33-mult.png");
		c4_->cd();
		c4_->SaveAs("v33-pT.png");

		/*
		TFile *outfile = new TFile("outfile_PYTHIA8_pp13TeV_template_fit.root","recreate");
		gdata_v22_pT->Write("gdata_v22_pT");
		gdata_v33_pT->Write("gdata_v33_pT");
		gdata_v22_mult->Write("gdata_v22_mult");
		gdata_v33_mult->Write("gdata_v33_mult");
		gv22_pT[0]->Write("gv22_pT_PYTHIA");
		gv22_pT[1]->Write("gv22_pT_PYTHIA_shoving");
		gv33_pT[0]->Write("gv33_pT_PYTHIA");
		gv33_pT[1]->Write("gv33_pT_PYTHIA_shoving");

		gv22[0]->Write("gv22_mult_PYTHIA");
		gv22[1]->Write("gv22_mult_PYTHIA_shoving");
		gv33[0]->Write("gv33_mult_PYTHIA");
		gv33[1]->Write("gv33_mult_PYTHIA_shoving");
		*/
	}

}
