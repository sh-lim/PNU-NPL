void GenGaus(){

	gRandom = new TRandom3(0);

	TF1 *fgaus = new TF1("fgaus","gaus",0,100);
	fgaus->SetParameters(1,50,10);

	TH1D *h1 = new TH1D("h1","h1",100,0,100);

	ofstream fdata;
	fdata.open("score.txt");

	for (int ii=0; ii<10000; ii++){
		float val = fgaus->GetRandom();

		h1->Fill(val);

		cout << fixed << setprecision(1) << val << endl;
		fdata << fixed << setprecision(1) << val << endl;
	}

	h1->Draw();

	fdata.close();




}
