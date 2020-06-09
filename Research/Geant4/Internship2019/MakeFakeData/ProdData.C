void ProdData(){

	gRandom = new TRandom3(0);

	float const_conv = 3.87 / 1.66;

	ifstream fdata;
	fdata.open("data_Si.txt");

	float tmp_e, tmp_dedx; //MeV

	float energy[100], dedx[100]; 

	int count = 0;

	while ( fdata >> tmp_e >> tmp_dedx ){

		energy[count] = tmp_e / 1000.; //GeV 
		dedx[count] = tmp_dedx * const_conv; //MeV 

		count++;

	}

	TCanvas *c1 = new TCanvas("c1","c1",400,400);
	gPad->SetLogx();
	TH1D *htmp = (TH1D*)gPad->DrawFrame(0.0005, 0, 200, 500);

	TGraph *gdedx = new TGraph(count, energy, dedx);
	gdedx->SetMarkerStyle(20);
	gdedx->SetMarkerColor(1);
	gdedx->Draw("p");

	TSpline3 *sp3 = new TSpline3("sp3",gdedx);
	sp3->SetLineColor(2);
	sp3->SetLineWidth(2);

	sp3->Draw("same");

	cout << "0.1 GeV, dE/dx= " << sp3->Eval(0.1) << " MeV" << endl; 
	cout << "1.0 GeV, dE/dx= " << sp3->Eval(1.0) << " MeV" << endl; 

	TF1 *fLandau0 = new TF1("fLandau0","TMath::Landau(x, [0], [1], 0)",0,5*sp3->Eval(0.1));
	fLandau0->SetParameters(sp3->Eval(0.1), 0.2*sp3->Eval(0.1));

	TF1 *fLandau1 = new TF1("fLandau1","TMath::Landau(x, [0], [1], 0)",0,5*sp3->Eval(1.0));
	fLandau1->SetParameters(sp3->Eval(1.0), 0.2*sp3->Eval(1.0));

	TCanvas *c2 = new TCanvas("c2","c2",400,400);
	fLandau0->Draw();

	TCanvas *c3 = new TCanvas("c3","c3",400,400);
	fLandau1->Draw();


	const int nset = 10;
	float beam_e[nset] = {0.1, 1, 2, 3, 4, 5, 10, 25, 50, 100};

	TH1D *hdedx[nset];

	for (int iset=0; iset<nset; iset++){
	//for (int iset=0; iset<1; iset++){

		TF1 *fLandau = new TF1("fLandau","TMath::Landau(x, [0], [1], 0)",0,10*sp3->Eval(beam_e[iset]));
		fLandau->SetParameters(sp3->Eval(beam_e[iset]), 0.2*sp3->Eval(beam_e[iset]));

		hdedx[iset] = new TH1D(Form("hdedx_set%d",iset),"",100,0,10*sp3->Eval(beam_e[iset])); 

		TString fname = Form("FakeData2/Si_1cm_energy_%g_GeV.txt",beam_e[iset]);
		ofstream fout;
		fout.open(fname.Data());

		for (int ii=0; ii<100000; ii++){
			float val_rand = fLandau->GetRandom();
			hdedx[iset]->Fill(val_rand);

			fout << val_rand << endl;
		}

		fout.close();

	}//iset

	TCanvas *c4 = new TCanvas("c4","c4",200*5,200);
	c4->Divide(5,2);

	for (int iset=0; iset<nset; iset++){
	//for (int iset=0; iset<1; iset++){
		c4->cd(iset+1);
		hdedx[iset]->Draw();
	}

	TTree *T = new TTree("T","T");



}
