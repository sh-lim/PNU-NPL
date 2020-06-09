void AnaData(){

	gStyle->SetOptStat(0);


	//configuration 
	const int nset = 10;

	const char *const_mname = "Si"; //material name
	const char *const_pname = "Proton"; //particle name
	const float const_thick = 1.0;
	const float const_energy[nset] = {0.1, 1, 2, 3, 4, 5, 10, 25, 50, 100};

	//define histogram
	TH1D *hedep[nset];
	for (int iset=0; iset<nset; iset++){
		hedep[iset] = new TH1D(Form("hedep_%s_%s_%g_%g",const_mname,const_pname,const_thick,const_energy[iset]),"",200,0,100);
	}//iset

	//read file
	ifstream fdata;
	char fname[300];
	for (int iset=0; iset<nset; iset++){
		sprintf(fname, "FakeData/%s_%dcm_energy_%g_GeV.txt",const_mname,int(const_thick),const_energy[iset]);
		cout << "Read: " << fname << endl;

		fdata.open(fname);

		float tmp_edep;
		while ( fdata >> tmp_edep ){
			hedep[iset]->Fill(tmp_edep);
		}//while

		fdata.close();
	}//iset

	
	//draw & fit
	TCanvas *c1 = new TCanvas("c1","c1",300*4, 250*3);
	c1->Divide(4,3);

	TF1 *fedep[nset];
	float par_mpv[nset];
	float par_mpv_err[nset];

	for (int iset=0; iset<nset; iset++){
		c1->cd(iset+1);
		gPad->SetRightMargin(0.05);
		gPad->SetLeftMargin(0.15);
		gPad->SetTopMargin(0.02);
		gPad->SetBottomMargin(0.13);
		hedep[iset]->GetXaxis()->SetLabelSize(0.05);
		hedep[iset]->GetXaxis()->SetTitleSize(0.06);
		hedep[iset]->GetXaxis()->SetTitle("E_{dep} (MeV)");
		hedep[iset]->GetYaxis()->SetLabelSize(0.05);
		hedep[iset]->GetYaxis()->SetTitleSize(0.06);
		hedep[iset]->GetYaxis()->SetTitleOffset(1.3);
		hedep[iset]->GetYaxis()->SetTitle("Counts / 0.5 MeV");
		hedep[iset]->SetLineWidth(2);
		hedep[iset]->SetLineColor(1);
		hedep[iset]->Draw();

		fedep[iset] = new TF1("fedep","[0]*TMath::Landau(x,[1],[2],0)",0,100);

		fedep[iset]->SetParameter(1, hedep[iset]->GetBinCenter(hedep[iset]->GetMaximumBin()));
		fedep[iset]->SetParameter(2, hedep[iset]->GetRMS());
		hedep[iset]->Fit(fedep[iset],"R0");
		fedep[iset]->Draw("same");

		par_mpv[iset] = fedep[iset]->GetParameter(1);
		par_mpv_err[iset] = fedep[iset]->GetParError(1);

		TLegend *leg = new TLegend(0.4,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.06);
		leg->AddEntry("",Form("%s, E=%g GeV",const_pname,const_energy[iset]),"");
		leg->AddEntry("",Form("%s, %g cm",const_mname,const_thick),"");
		leg->Draw();
	}//iset

	TGraphErrors *gedep = new TGraphErrors(nset, const_energy, par_mpv, 0, par_mpv_err); 
	gedep->SetMarkerStyle(20);
	gedep->SetMarkerColor(1);
	gedep->SetMarkerSize(1.0);
	gedep->SetLineColor(1);
	gedep->SetLineWidth(3);

	TCanvas *c2 = new TCanvas("c2","c2",600,500);
	gPad->SetRightMargin(0.05);
	gPad->SetLeftMargin(0.15);
	gPad->SetTopMargin(0.03);
	gPad->SetBottomMargin(0.15);
	gPad->SetLogx();
	
	TH1D *htmp = (TH1D*)gPad->DrawFrame(0.05,0,200,25);
	htmp->GetXaxis()->SetLabelSize(0.05);
	htmp->GetXaxis()->SetTitleSize(0.06);
	htmp->GetXaxis()->SetTitleOffset(1.1);
	htmp->GetXaxis()->SetTitle("E_{beam} (GeV)");
	htmp->GetYaxis()->SetLabelSize(0.05);
	htmp->GetYaxis()->SetTitleSize(0.06);
	htmp->GetYaxis()->SetTitleOffset(1.0);
	htmp->GetYaxis()->SetTitle("MPV E_{dep} (MeV)");

	gedep->Draw("C");

	{
		TLegend *leg = new TLegend(0.5,0.75,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.05);
		leg->AddEntry("",Form("%s, %g cm",const_mname,const_thick),"");
		leg->AddEntry(gedep,"Proton","L");
		leg->Draw();
	}
	

}
