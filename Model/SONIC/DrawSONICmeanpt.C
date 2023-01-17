void DrawSONICmeanpt(){

	const int nset = 3;
	const int nColor[3] = {1, 2, 4};

	const float cut[nset] = {40, 55, 70};

	string setname[nset] = {"p+Au", "d+Au", "^{3}He+Au"};

	TFile *infile[3];
	infile[0] = new TFile("SONIC_meanpT_pAu.root","read");
	infile[1] = new TFile("SONIC_meanpT_dAu.root","read");
	infile[2] = new TFile("SONIC_meanpT_He3Au.root","read");

	TFile *infile_sT[3];
	infile_sT[0] = new TFile("SONIC_meanpT_ST_pAu.root","read");
	infile_sT[1] = new TFile("SONIC_meanpT_ST_dAu.root","read");
	infile_sT[2] = new TFile("SONIC_meanpT_ST_He3Au.root","read");

	TProfile *h_meanpt[nset];
	TProfile *h_meanpt_sT[nset];

	for (int iset=0; iset<nset; iset++){
		h_meanpt[iset] = (TProfile*)infile[iset]->Get("p");
		h_meanpt_sT[iset] = (TProfile*)infile_sT[iset]->Get("p");

		for (int ip=0; ip<h_meanpt[iset]->GetNbinsX(); ip++){
			if ( h_meanpt[iset]->GetBinCenter(ip+1)<cut[iset] ){
				continue;
			}
			h_meanpt[iset]->SetBinContent(ip+1, 0);
		}//ip
	}//iset

	TCanvas *c1 = new TCanvas("c1","c1",1.1*400,400);

	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.4,80,0.75);
		htmp->GetXaxis()->SetTitle("dN_{ch}/d#eta|_{#eta=0}");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("#LTp_{T}#GT");
		htmp->GetYaxis()->SetTitleSize(0.055);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		TLegend *leg = new TLegend(0.6,0.15,0.9,0.35);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","SONIC 200 GeV","h");

		for (int iset=0; iset<nset; iset++){
			h_meanpt[iset]->SetMarkerStyle(24);
			h_meanpt[iset]->SetLineColor(nColor[iset]);
			h_meanpt[iset]->SetMarkerColor(nColor[iset]);
			h_meanpt[iset]->SetLineWidth(2);
			h_meanpt[iset]->Draw("p same");
			leg->AddEntry(h_meanpt[iset],setname[iset].c_str(),"P");
		}//iset
		leg->Draw();
	}//jj

	TCanvas *c2 = new TCanvas("c2","c2",1.1*400,400);

	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.4,80,0.75);
		htmp->GetXaxis()->SetTitle("dN_{ch}/d#eta|_{#eta=0}/#LTS_{T}#GT");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("#LTp_{T}#GT");
		htmp->GetYaxis()->SetTitleSize(0.055);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		TLegend *leg = new TLegend(0.6,0.15,0.9,0.35);
		leg->SetTextSize(0.045);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","SONIC 200 GeV","h");

		for (int iset=0; iset<nset; iset++){
			h_meanpt_sT[iset]->SetMarkerStyle(24);
			h_meanpt_sT[iset]->SetLineColor(nColor[iset]);
			h_meanpt_sT[iset]->SetMarkerColor(nColor[iset]);
			h_meanpt_sT[iset]->SetLineWidth(2);
			h_meanpt_sT[iset]->Draw("p same");
			leg->AddEntry(h_meanpt_sT[iset],setname[iset].c_str(),"P");
		}//iset
		leg->Draw();
	}//jj

}
