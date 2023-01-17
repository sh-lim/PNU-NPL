void Draw(){

	const int nset = 5;
	const char *pname[nset] = {
		"Electron",
		"Proton",
		"kaon",
		"pion",
		"muon"
	};

	ifstream fdata;

	int tmp_bit;
	float tmp_edep, tmp_ebeam;

	TH2D *h2d_ebeam_edep[nset];
	
	for (int iset=0; iset<nset; iset++){

		h2d_ebeam_edep[iset] = new TH2D(Form("h2d_ebeam_edep_set%d",iset),"",200,0,20,100,0,20);

		fdata.open(pname[iset]);

		while ( fdata >> tmp_bit >> tmp_ebeam ){
			fdata >> tmp_bit >> tmp_edep;

			if ( tmp_edep>1 ){
				h2d_ebeam_edep[iset]->Fill(tmp_ebeam, tmp_edep);
			}
		}

		fdata.close();
	}

	TCanvas *c1 = new TCanvas("c1","c1",3*1.2*300,2*300);
	c1->Divide(3,2);
	for (int iset=0; iset<nset; iset++){
		c1->cd(iset+1);
		gPad->SetLogx();

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0.2,0,20,20);
		htmp->SetMinimum(0);
		htmp->GetXaxis()->SetTitle("p (GeV/c)");
		htmp->GetYaxis()->SetTitle("E_{dep} (MeV)");

		h2d_ebeam_edep[iset]->Draw("colz same");

		TLatex *tex = new TLatex(0.3, 2, pname[iset]); 
		tex->Draw();
	}



}
