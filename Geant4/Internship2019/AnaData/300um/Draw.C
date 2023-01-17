void Draw(){

	gStyle->SetPalette(55);

	double hagedornPar[5] = {1.39570961407454881e-02,-1.61541865766719001e-01,8.87993993087939915e-02,6.95224923745161760e-01,-8.32200469029351275e+00}; //RUN9 NEW
	TF1 *fhagedorn = new TF1("fhagedorn", "[0]*(exp([1]*x-[2]*x*x)+(x/[3]))^[4]", 0.01, 20.0);
	fhagedorn->SetParameters(hagedornPar);

	//fhagedorn->Draw();
	//return;

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

		h2d_ebeam_edep[iset] = new TH2D(Form("h2d_ebeam_edep_set%d",iset),"",2000,0,20,1000,0,1000);

		fdata.open(pname[iset]);

		while ( fdata >> tmp_bit >> tmp_ebeam ){
			fdata >> tmp_bit >> tmp_edep;

			//float weight = fhagedorn->Eval(tmp_ebeam)/fhagedorn->Eval(0.1);

			if ( tmp_edep>0.01 && tmp_ebeam>0.2 ){
				h2d_ebeam_edep[iset]->Fill(tmp_ebeam, tmp_edep*1000);
				//h2d_ebeam_edep[iset]->Fill(tmp_ebeam, tmp_edep*1000, weight);
			}
		}

		fdata.close();
	}

	TCanvas *c1 = new TCanvas("c1","c1",3*1.2*300,2*300);
	c1->Divide(3,2);
	for (int iset=0; iset<nset; iset++){
		c1->cd(iset+1);
		gPad->SetLogx();

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0.2,0,20,800);
		htmp->SetMinimum(0);
		htmp->GetXaxis()->SetTitle("p (GeV/c)");
		htmp->GetYaxis()->SetTitle("E_{dep} (MeV)");

		h2d_ebeam_edep[iset]->SetMaximum(8);
		h2d_ebeam_edep[iset]->Draw("colz same");

		TLatex *tex = new TLatex(0.3, 2, pname[iset]); 
		tex->Draw();
	}



}
