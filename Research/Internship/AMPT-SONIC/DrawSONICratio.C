void DrawSONICratio(){

	const int nset = 3;
	const int nColor[3] = {1, 2, 4};

	string setname[nset] = {"p+Au", "d+Au", "^{3}He+Au"};

	TFile *infile[nset];
	infile[0] = new TFile("SONIC_Ratio_pAu.root","read");
	infile[1] = new TFile("SONIC_Ratio_dAu.root","read");
	infile[2] = new TFile("SONIC_Ratio_He3Au.root","read");

	TH1D *hratio[nset];
	TGraph *gratio[nset];

	for (int iset=0; iset<nset; iset++){

		hratio[iset] = (TH1D*)infile[iset]->Get("hpi");

		gratio[iset] = new TGraph;

		for (int ip=0; ip<hratio[iset]->GetNbinsX(); ip++){
			float xx = hratio[iset]->GetBinCenter(ip+1);
			float yy = hratio[iset]->GetBinContent(ip+1);

			gratio[iset]->SetPoint(ip, xx, yy);
		}

		gratio[iset]->SetLineColorAlpha(nColor[iset],0.5);
		gratio[iset]->SetFillColorAlpha(nColor[iset],0.5);
		gratio[iset]->SetLineWidth(5);

	}

	TCanvas *c3 = new TCanvas("c3","c3",1.1*400,400);
	{
		gPad->SetMargin(0.14,0.03,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.0,3.0,2.5);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("Ratio (0-20% / 60-100%)");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetLabelSize(0.04);

		TLegend *leg = new TLegend(0.2,0.15,0.5,0.35);
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


}
