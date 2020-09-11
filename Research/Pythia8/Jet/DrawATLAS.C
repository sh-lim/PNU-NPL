void DrawATLAS(){

	const int nset = 4;
	const int nMarker[nset] = {20, 21, 24, 25};
	const int nColor[nset] = {1, 2, 4, 6};
	const int jetpT[nset+1] = {25, 40 ,60 ,80, 110};

	TFile *infileZ[nset];
	TFile *infileJT[nset];

	TGraphAsymmErrors *gZ[nset];
	TGraphAsymmErrors *gJT[nset];

	for (int iset=0; iset<nset; iset++){
		infileZ[iset] = new TFile(Form("HEPData-ins929691-v1-Table_%d.root",iset+1),"read");
		infileJT[iset] = new TFile(Form("HEPData-ins929691-v1-Table_%d.root",iset+21),"read");
		TDirectoryFile *tdf = (TDirectoryFile*)infileZ[iset]->Get(Form("Table %d",iset+1));
		gZ[iset] = (TGraphAsymmErrors*)tdf->Get("Graph1D_y1");

		tdf = (TDirectoryFile*)infileJT[iset]->Get(Form("Table %d",iset+21));
		gJT[iset] = (TGraphAsymmErrors*)tdf->Get("Graph1D_y1");
	}

	TCanvas *c1 = new TCanvas("c1","c1",1.1*500,500);
	gPad->SetMargin(0.15,0.03,0.13,0.03);
	gPad->SetLogy();
	gPad->SetLogx();
	{

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0.005,0.01,1.0,2000);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitle("z");
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("F(z)");

		TLegend *leg = new TLegend(0.2,0.2,0.6,0.4);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.04);

		for (int iset=0; iset<nset; iset++){
			gZ[iset]->SetMarkerStyle(nMarker[iset]);
			gZ[iset]->SetMarkerColor(nColor[iset]);
			gZ[iset]->SetLineColor(nColor[iset]);
			gZ[iset]->Draw("P");
			leg->AddEntry(gZ[iset], Form("%d GeV<p_{T, jet}<%d GeV", jetpT[iset], jetpT[iset+1]),"P");
		}
		leg->Draw();

	}


	TCanvas *c2 = new TCanvas("c2","c2",1.1*500,500);
	gPad->SetMargin(0.15,0.03,0.13,0.03);
	{

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,3,20);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitle("p_{T}^{rel} (GeV)");
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("f(p_{T}^{rel})");

		TLegend *leg = new TLegend(0.5,0.6,0.9,0.8);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.04);

		for (int iset=0; iset<nset; iset++){
			gJT[iset]->SetMarkerStyle(nMarker[iset]);
			gJT[iset]->SetMarkerColor(nColor[iset]);
			gJT[iset]->SetLineColor(nColor[iset]);
			gJT[iset]->Draw("P");
			leg->AddEntry(gJT[iset], Form("%d GeV<p_{T, jet}<%d GeV", jetpT[iset], jetpT[iset+1]),"P");
		}
		leg->Draw();

	}

}
