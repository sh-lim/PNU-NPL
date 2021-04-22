void DrawAMPTvn(){

	const int nset = 3;
	const int norder = 2;

	string setname[nset] = {"p+Au", "d+Au", "^{3}He+Au"};

	TGraphErrors *gvn[nset][norder];
	TGraphErrors *gvn_on[nset][norder];
	TGraphErrors *gvn_off[nset][norder];

	TFile *infile = new TFile("outfile_AMPT_vn.root","read");

	TFile *infileS[nset];
	infileS[0] = new TFile("SONIC_v2v3_pAu.root","read");
	infileS[1] = new TFile("SONIC_v2v3_dAu.root","read");
	infileS[2] = new TFile("SONIC_v2v3_He3Au.root","read");

	TFile *infilePHENIX = new TFile("outfile_PHENIX_v2v3.root","read");

	TGraphAsymmErrors *gdata_v2_sys[nset];
	TGraphAsymmErrors *gdata_v3_sys[nset];

	TGraphErrors *gdata_v2[nset];
	TGraphErrors *gdata_v3[nset];

	for (int iset=0; iset<nset; iset++){
		gdata_v2_sys[iset] = (TGraphAsymmErrors*)infilePHENIX->Get(Form("gv2_sys_set%d",iset));
		gdata_v3_sys[iset] = (TGraphAsymmErrors*)infilePHENIX->Get(Form("gv3_sys_set%d",iset));
		gdata_v2[iset] = (TGraphErrors*)infilePHENIX->Get(Form("gv2_set%d",iset));
		gdata_v3[iset] = (TGraphErrors*)infilePHENIX->Get(Form("gv3_set%d",iset));
	}


	for (int iset=0; iset<nset; iset++){
		for (int io=0; io<norder; io++){

			gvn_on[iset][io] = (TGraphErrors*)infile->Get(Form("gvn_on_set%d_order%d",iset,io+2));
			gvn_off[iset][io] = (TGraphErrors*)infile->Get(Form("gvn_off_set%d_order%d",iset,io+2));

			gvn_on[iset][io]->SetFillColorAlpha(1+3*io, 0.5);
			gvn_on[iset][io]->SetLineWidth(0);
			gvn_off[iset][io]->SetFillColorAlpha(1, 0.5);
			gvn_off[iset][io]->SetLineWidth(0);

		}

		gvn[iset][0] = (TGraphErrors*)infileS[iset]->Get("v2_SONIC");
		gvn[iset][1] = (TGraphErrors*)infileS[iset]->Get("v3_SONIC");

		gvn[iset][0]->SetLineColorAlpha(1, 0.5);
		gvn[iset][1]->SetLineColorAlpha(4, 0.5);

		gvn[iset][0]->SetLineWidth(5);
		gvn[iset][1]->SetLineWidth(5);

		gvn[iset][0]->SetLineStyle(9);
		gvn[iset][1]->SetLineStyle(9);
	}

	TCanvas *c3 = new TCanvas("c3","c3",1.1*3*400,400);
	c3->Divide(3,1);

	for (int iset=0; iset<nset; iset++){
		c3->cd(iset+1);

		gPad->SetMargin(0.14,0.05,0.12,0.03);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,-0.02,3,0.25);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.045);

		htmp->GetYaxis()->SetTitle("v_{n}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.045);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		gvn_on[iset][0]->Draw("e3");
		gvn_on[iset][1]->Draw("e3");

		gdata_v2_sys[iset]->Draw("2");
		gdata_v3_sys[iset]->Draw("2");

		gdata_v2[iset]->Draw("P");
		gdata_v3[iset]->Draw("P");

		TLegend *leg = new TLegend(0.2,0.6,0.5,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.045);
		leg->AddEntry("",Form("0-5%% %s 200 GeV",setname[iset].c_str()),"h");
		leg->AddEntry(gdata_v2[iset],"v_{2}, PHENIX","P");
		leg->AddEntry(gdata_v3[iset],"v_{3}, PHENIX","P");
		leg->AddEntry(gvn_on[iset][0],"v_{2}, AMPT","F");
		leg->AddEntry(gvn_on[iset][1],"v_{3}, AMPT","F");
		leg->Draw();

	}

	TCanvas *c1 = new TCanvas("c1","c1",1.1*3*400,400);
	c1->Divide(3,1);

	for (int iset=0; iset<nset; iset++){
		c1->cd(iset+1);

		gPad->SetMargin(0.14,0.05,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,-0.02,3,0.25);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.045);

		htmp->GetYaxis()->SetTitle("v_{n}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.045);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		gvn[iset][0]->Draw("");
		gvn[iset][1]->Draw("");

		gdata_v2_sys[iset]->Draw("2");
		gdata_v3_sys[iset]->Draw("2");

		gdata_v2[iset]->Draw("P");
		gdata_v3[iset]->Draw("P");

		TLegend *leg = new TLegend(0.2,0.6,0.5,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.045);
		leg->AddEntry("",Form("0-5%% %s 200 GeV",setname[iset].c_str()),"h");
		leg->AddEntry(gdata_v2[iset],"v_{2}, PHENIX","P");
		leg->AddEntry(gdata_v3[iset],"v_{3}, PHENIX","P");
		leg->AddEntry(gvn[iset][0],"v_{2}, SONIC","L");
		leg->AddEntry(gvn[iset][1],"v_{3}, SONIC","L");
		leg->Draw();
	}

	TCanvas *c4 = new TCanvas("c4","c4",1.1*3*400,400);
	c4->Divide(3,1);

	for (int iset=0; iset<nset; iset++){
		c4->cd(iset+1);

		gPad->SetMargin(0.14,0.05,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,-0.01,3,0.25);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.045);
		htmp->GetXaxis()->SetTitleOffset(1.15);

		htmp->GetYaxis()->SetTitle("v_{2}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.045);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		gvn[iset][0]->Draw("");
		gvn_on[iset][0]->Draw("e3");
		gdata_v2_sys[iset]->Draw("2");
		gdata_v2[iset]->Draw("P");

		TLegend *leg = new TLegend(0.2,0.7,0.7,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.045);
		leg->AddEntry("",Form("0-5%% %s 200 GeV",setname[iset].c_str()),"h");
		leg->AddEntry(gdata_v2[iset],"PHENIX","P");
		leg->AddEntry(gvn[iset][0],"SONIC","L");
		leg->AddEntry(gvn_on[iset][0],"AMPT","F");
		leg->Draw();

	}

	TCanvas *c5 = new TCanvas("c5","c5",1.1*3*400,400);
	c5->Divide(3,1);

	for (int iset=0; iset<nset; iset++){
		c5->cd(iset+1);

		gPad->SetMargin(0.14,0.05,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,-0.01,3,0.15);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitleOffset(1.15);
		htmp->GetXaxis()->SetLabelSize(0.045);

		htmp->GetYaxis()->SetTitle("v_{3}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.045);
		htmp->GetYaxis()->SetTitleOffset(1.1);
		htmp->GetYaxis()->SetNdivisions(7,9,1);

		gvn[iset][1]->Draw("");
		gvn_on[iset][1]->Draw("e3");
		gdata_v3_sys[iset]->Draw("2");
		gdata_v3[iset]->Draw("P");

		TLegend *leg = new TLegend(0.2,0.7,0.7,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.045);
		leg->AddEntry("",Form("0-5%% %s 200 GeV",setname[iset].c_str()),"h");
		leg->AddEntry(gdata_v3[iset],"PHENIX","P");
		leg->AddEntry(gvn[iset][1],"SONIC","L");
		leg->AddEntry(gvn_on[iset][1],"AMPT","F");
		leg->Draw();

	}


	/*
	TCanvas *c3off = new TCanvas("c3off","c3off",1.1*3*400,400);
	c3off->Divide(3,1);

	for (int iset=0; iset<nset; iset++){
		c3off->cd(iset+1);

		gPad->SetMargin(0.14,0.03,0.12,0.03);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,-0.05,3,0.25);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("v_{n}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		gvn_off[iset][0]->Draw("e3");
		gvn_off[iset][1]->Draw("e3");

		TLegend *leg = new TLegend(0.4,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.05);
		leg->AddEntry("",Form("AMPT, parton scattering off"),"h");
		leg->AddEntry("",Form("0-5%% %s 200 GeV",setname[iset].c_str()),"h");
		leg->AddEntry(gvn_off[iset][0],"v_{2}","F");
		leg->AddEntry(gvn_off[iset][1],"v_{3}","F");
		leg->Draw();
	}
	*/


}
