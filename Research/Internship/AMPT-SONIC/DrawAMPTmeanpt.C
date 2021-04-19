void DrawAMPTmeanpt(){

	const int nset = 3;
	const int nColor[3] = {1, 2, 4};

	string setname[nset] = {"p+Au", "d+Au", "^{3}He+Au"};

	TFile *infile = new TFile("outfile_AMPT_meanpt.root","read");

	TProfile *hon_meanpt[nset];
	TProfile *hon_meanpt_sT[nset];

	TProfile *hoff_meanpt[nset];
	TProfile *hoff_meanpt_sT[nset];

	for (int iset=0; iset<nset; iset++){

		hon_meanpt[iset] = (TProfile*)infile->Get(Form("hon_meanpt_set%d",iset));
		hon_meanpt_sT[iset] = (TProfile*)infile->Get(Form("hon_meanpt_sT_set%d",iset));

		hoff_meanpt[iset] = (TProfile*)infile->Get(Form("hoff_meanpt_set%d",iset));
		hoff_meanpt_sT[iset] = (TProfile*)infile->Get(Form("hoff_meanpt_sT_set%d",iset));

	}

	TCanvas *c1 = new TCanvas("c1","c1",1.1*400,400);

	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.4,100,0.8);
		htmp->GetXaxis()->SetTitle("dN_{ch}/d#eta|_{#eta=0}");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("#LTp_{T}#GT");
		htmp->GetYaxis()->SetTitleSize(0.055);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		TLegend *leg = new TLegend(0.6,0.15,0.9,0.4);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","AMPT 200 GeV","h");
		leg->AddEntry("","parton scattering on","h");

		for (int iset=0; iset<nset; iset++){
			hon_meanpt[iset]->SetMarkerStyle(24);
			hon_meanpt[iset]->SetLineColor(nColor[iset]);
			hon_meanpt[iset]->SetMarkerColor(nColor[iset]);
			hon_meanpt[iset]->SetLineWidth(2);
			hon_meanpt[iset]->Draw("p same");
			leg->AddEntry(hon_meanpt[iset],setname[iset].c_str(),"P");
		}//iset
		leg->Draw();
	}//jj

	TCanvas *c2 = new TCanvas("c2","c2",1.1*400,400);

	{
		gPad->SetMargin(0.14,0.05,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.4,100,0.8);
		htmp->GetXaxis()->SetTitle("dN_{ch}/d#eta|_{#eta=0}/#LTS_{T}#GT");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("#LTp_{T}#GT");
		htmp->GetYaxis()->SetTitleSize(0.055);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		TLegend *leg = new TLegend(0.6,0.15,0.9,0.4);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","AMPT 200 GeV","h");
		leg->AddEntry("","parton scattering on","h");

		for (int iset=0; iset<nset; iset++){
			hon_meanpt_sT[iset]->SetMarkerStyle(24);
			hon_meanpt_sT[iset]->SetLineColor(nColor[iset]);
			hon_meanpt_sT[iset]->SetMarkerColor(nColor[iset]);
			hon_meanpt_sT[iset]->SetLineWidth(2);
			hon_meanpt_sT[iset]->Draw("p same");
			leg->AddEntry(hon_meanpt_sT[iset],setname[iset].c_str(),"P");
		}//iset
		leg->Draw();
	}//jj

	TCanvas *c3 = new TCanvas("c3","c3",1.1*400,400);

	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.4,100,0.8);
		htmp->GetXaxis()->SetTitle("dN_{ch}/d#eta|_{#eta=0}");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("#LTp_{T}#GT");
		htmp->GetYaxis()->SetTitleSize(0.055);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		TLegend *leg = new TLegend(0.6,0.15,0.9,0.4);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","AMPT 200 GeV","h");
		leg->AddEntry("","parton scattering off","h");

		for (int iset=0; iset<nset; iset++){
			hoff_meanpt[iset]->SetMarkerStyle(24);
			hoff_meanpt[iset]->SetLineColor(nColor[iset]);
			hoff_meanpt[iset]->SetMarkerColor(nColor[iset]);
			hoff_meanpt[iset]->SetLineWidth(2);
			hoff_meanpt[iset]->Draw("p same");
			leg->AddEntry(hoff_meanpt[iset],setname[iset].c_str(),"P");
		}//iset
		leg->Draw();
	}//jj

	TCanvas *c4 = new TCanvas("c4","c4",1.1*400,400);

	{
		gPad->SetMargin(0.14,0.05,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.4,100,0.8);
		htmp->GetXaxis()->SetTitle("dN_{ch}/d#eta|_{#eta=0}/#LTS_{T}#GT");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("#LTp_{T}#GT");
		htmp->GetYaxis()->SetTitleSize(0.055);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		TLegend *leg = new TLegend(0.6,0.15,0.9,0.4);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","AMPT 200 GeV","h");
		leg->AddEntry("","parton scattering off","h");

		for (int iset=0; iset<nset; iset++){
			hoff_meanpt_sT[iset]->SetMarkerStyle(24);
			hoff_meanpt_sT[iset]->SetLineColor(nColor[iset]);
			hoff_meanpt_sT[iset]->SetMarkerColor(nColor[iset]);
			hoff_meanpt_sT[iset]->SetLineWidth(2);
			hoff_meanpt_sT[iset]->Draw("p same");
			leg->AddEntry(hoff_meanpt_sT[iset],setname[iset].c_str(),"P");
		}//iset
		leg->Draw();
	}//jj

}
