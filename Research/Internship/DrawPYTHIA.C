void DrawPYTHIA(){

	TFile *infile = new TFile("outfile_ScanPYTHIA.root","read");

	TH1D *h1Np = (TH1D*)infile->Get("h1Np");
	TH2D *h2EtaPt = (TH2D*)infile->Get("h2EtaPt");

	TH1D *h1Eta = (TH1D*)h2EtaPt->ProjectionX("h1Eta");

	int etamin = h1Eta->FindBin(-0.8+0.001);
	int etamax = h1Eta->FindBin(+0.8-0.001);

	TH1D *h1Pt = (TH1D*)h2EtaPt->ProjectionY("h1Pt",etamin,etamax);

	TFile *infile1 = new TFile("HEPData-ins1395253-v1-Table_1.root","read");
	TGraphErrors *gALICE1 = (TGraphErrors*)((TDirectoryFile*)infile1->Get("Table 1"))->Get("Graph1D_y1");
	TGraphErrors *gALICE2 = (TGraphErrors*)((TDirectoryFile*)infile1->Get("Table 1"))->Get("Graph1D_y2");

	TFile *infile2 = new TFile("HEPData-ins1395253-v1-Table_2.root","read");
	TGraphErrors *gALICE3 = (TGraphErrors*)((TDirectoryFile*)infile2->Get("Table 2"))->Get("Graph1D_y1");

	float nevent = h1Np->Integral();

	h1Eta->Sumw2();
	float scaler = 1./(nevent*h1Eta->GetBinWidth(1));
	h1Eta->Scale(scaler);

	h1Pt->Sumw2();
	scaler = 1./(nevent*h1Pt->GetBinWidth(1)*1.6*TMath::TwoPi());
	h1Pt->Scale(scaler);
	for (int ii=0; ii<h1Pt->GetNbinsX(); ii++){
		float xx = h1Pt->GetBinCenter(ii+1);
		h1Pt->SetBinContent(ii+1, h1Pt->GetBinContent(ii+1)/xx);
		h1Pt->SetBinError(ii+1, h1Pt->GetBinError(ii+1)/xx);
	}

	TCanvas *c1 = new TCanvas("c1","c1",1.2*2*500,500);
	c1->Divide(2,1);

	{
		c1->cd(1);
		gPad->SetTicks();
		gPad->SetLeftMargin(0.13);
		gPad->SetRightMargin(0.02);
		gPad->SetBottomMargin(0.12);
		gPad->SetTopMargin(0.02);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(-5,3,5,13);
		htmp->GetXaxis()->SetTitle("#eta");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleOffset(1.1);
		htmp->GetYaxis()->SetTitle("dN/d#eta");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetLabelSize(0.04);

		h1Eta->SetLineColor(1);
		h1Eta->SetMarkerColor(1);
		h1Eta->SetMarkerStyle(24);
		h1Eta->Draw("p same");

		gALICE1->SetMarkerStyle(20);
		gALICE1->SetMarkerColor(1);
		gALICE1->SetLineColor(1);
		gALICE1->Draw("p");

		gALICE2->SetMarkerStyle(21);
		gALICE2->SetMarkerColor(2);
		gALICE2->SetLineColor(2);
		gALICE2->Draw("p");

		TLegend *leg = new TLegend(0.6,0.73,0.9,0.93);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.04);
		leg->AddEntry("","pp 13 TeV","h");
		leg->AddEntry(h1Eta,"PYTHIA8","P");
		leg->AddEntry(gALICE1,"ALICE, INEL","P");
		leg->AddEntry(gALICE2,"ALICE, INEL>0","P");
		leg->Draw();
	}

	{
		c1->cd(2);
		gPad->SetTicks();
		gPad->SetLeftMargin(0.15);
		gPad->SetRightMargin(0.02);
		gPad->SetBottomMargin(0.12);
		gPad->SetTopMargin(0.02);
		gPad->SetLogy();

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,1e-6,10,100);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleOffset(1.1);
		htmp->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}} #frac{d^{2}N}{d#etadp_{T}} (GeV^{-2})");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetLabelSize(0.04);

		h1Pt->SetLineColor(1);
		h1Pt->SetMarkerColor(1);
		h1Pt->SetMarkerStyle(24);
		h1Pt->Draw("p same");

		gALICE3->SetMarkerStyle(20);
		gALICE3->SetMarkerColor(1);
		gALICE3->SetLineColor(1);
		gALICE3->Draw("p");

		TLegend *leg = new TLegend(0.6,0.73,0.9,0.93);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.04);
		leg->AddEntry("","pp 13 TeV","h");
		leg->AddEntry("","|#eta|<0.8","h");
		leg->AddEntry(h1Pt,"PYTHIA8","P");
		leg->AddEntry(gALICE3,"ALICE, INEL>0","P");
		leg->Draw();

	}


}
