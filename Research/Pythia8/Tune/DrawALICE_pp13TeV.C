void DrawALICE_pp13TeV(){

	TFile *infile = new TFile("HEPData-ins1395253-v1-root.root","read");

	{
		TDirectoryFile *tdf = (TDirectoryFile*)infile->Get("Table 1");
		TGraphAsymmErrors *gFig1A = (TGraphAsymmErrors*)tdf->Get("Graph1D_y1");
		TGraphAsymmErrors *gFig1B = (TGraphAsymmErrors*)tdf->Get("Graph1D_y2");

		TCanvas *c1 = new TCanvas("c1","c1",1.1*500,500);
		gPad->SetMargin(0.15,0.03,0.13,0.03);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(-2.5,4.5,2.5,9.0);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitle("#eta");
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("#LTdN_{ch}/d#eta#GT");

		gFig1A->SetMarkerColor(2);
		gFig1A->SetMarkerStyle(20);
		gFig1A->SetLineColor(2);

		gFig1B->SetMarkerColor(1);
		gFig1B->SetMarkerStyle(21);
		gFig1B->SetLineColor(1);

		gFig1A->Draw("pe");
		gFig1B->Draw("pe");

	}

}
