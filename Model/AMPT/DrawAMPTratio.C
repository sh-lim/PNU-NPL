void DrawAMPTratio(){

	const int nset = 3;
	const int nColor[3] = {1, 2, 4};

	string setname[nset] = {"p+Au", "d+Au", "^{3}He+Au"};

	TFile *infile = new TFile("outfile_AMPT_ratio.root","read");

	TFile *infileS[nset];
	infileS[0] = new TFile("SONIC_Ratio_pAu.root","read");
	infileS[1] = new TFile("SONIC_Ratio_dAu.root","read");
	infileS[2] = new TFile("SONIC_Ratio_He3Au.root","read");

	TGraphErrors *gon_ratio[nset];
	TGraphErrors *goff_ratio[nset];

	for (int iset=0; iset<nset; iset++){

		gon_ratio[iset] = (TGraphErrors*)infile->Get(Form("gon_ratio_set%d",iset));
		goff_ratio[iset] = (TGraphErrors*)infile->Get(Form("goff_ratio_set%d",iset));

		gon_ratio[iset]->SetFillColorAlpha(nColor[iset],0.5);
		goff_ratio[iset]->SetFillColorAlpha(nColor[iset],0.5);
		goff_ratio[iset]->SetFillStyle(3244);

	}

	TH1D *hratio[nset];
	TGraph *gratio[nset];

	for (int iset=0; iset<nset; iset++){

		hratio[iset] = (TH1D*)infileS[iset]->Get("hpi");
		gratio[iset] = new TGraph;

		for (int ip=0; ip<hratio[iset]->GetNbinsX(); ip++){
			float xx = hratio[iset]->GetBinCenter(ip+1);
			float yy = hratio[iset]->GetBinContent(ip+1);

			gratio[iset]->SetPoint(ip, xx, yy);
		}

		gratio[iset]->SetLineColorAlpha(nColor[iset],0.5);
		gratio[iset]->SetFillColorAlpha(nColor[iset],0.5);
		gratio[iset]->SetLineStyle(9);
		gratio[iset]->SetLineWidth(5);

	}

	TCanvas *c0 = new TCanvas("c0","c0",1.1*400,400);
	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.0,3.0,2.5);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.045);

		htmp->GetYaxis()->SetTitle("Ratio (0-20% / 60-100%)");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetLabelSize(0.04);

		TLegend *leg = new TLegend(0.18,0.7,0.58,0.9);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","SONIC 200 GeV","h");


		for (int iset=0; iset<nset; iset++){
			gratio[iset]->Draw("");
			leg->AddEntry(gratio[iset],setname[iset].c_str(),"L");
		}//iset
		leg->Draw();
	}//jj

	TCanvas *c1 = new TCanvas("c1","c1",1.1*400,400);
	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.0,3.0,2.5);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.045);

		htmp->GetYaxis()->SetTitle("Ratio (0-20% / 60-100%)");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetLabelSize(0.04);

		TLegend *leg = new TLegend(0.18,0.7,0.58,0.9);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","SONIC 200 GeV","h");

		TLegend *leg1 = new TLegend(0.18,0.15,0.48,0.4);
		leg1->SetTextSize(0.045);
		leg1->SetFillStyle(0);
		leg1->SetBorderSize(0);
		leg1->AddEntry("","AMPT 200 GeV","h");
		leg1->AddEntry("","parton scattering on","h");


		for (int iset=0; iset<nset; iset++){
			gratio[iset]->Draw("");
			gon_ratio[iset]->Draw("e3");
			leg->AddEntry(gratio[iset],setname[iset].c_str(),"L");
			leg1->AddEntry(gon_ratio[iset],setname[iset].c_str(),"F");
		}//iset
		leg->Draw();
		leg1->Draw();
	}//jj

	TCanvas *c3 = new TCanvas("c3","c3",1.1*400,400);
	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.0,3.0,1.2);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.045);

		htmp->GetYaxis()->SetTitle("Ratio (0-20% / 60-100%)");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetLabelSize(0.045);

		TLegend *leg = new TLegend(0.18,0.15,0.8,0.4);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","AMPT 200 GeV","h");
		leg->SetNColumns(3);


		for (int iset=0; iset<nset; iset++){
			gon_ratio[iset]->Draw("e3");
			goff_ratio[iset]->Draw("e3");
			leg->AddEntry("",setname[iset].c_str(),"");
			leg->AddEntry(gon_ratio[iset],"parton scattering on","F");
			leg->AddEntry(goff_ratio[iset],"off","F");
		}//iset
		leg->Draw();
	}//jj

	return;


	TCanvas *c4 = new TCanvas("c4","c4",1.1*400,400);
	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.0,3.0,2.5);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.045);

		htmp->GetYaxis()->SetTitle("Ratio (0-20% / 60-100%)");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetLabelSize(0.045);

		TLegend *leg = new TLegend(0.2,0.15,0.5,0.4);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","AMPT 200 GeV","h");
		leg->AddEntry("","parton scattering off","h");


		for (int iset=0; iset<nset; iset++){
			goff_ratio[iset]->Draw("e3");
			leg->AddEntry(goff_ratio[iset],setname[iset].c_str(),"F");
		}//iset
		leg->Draw();
	}//jj

}
