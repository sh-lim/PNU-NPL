void Read(){

	gStyle->SetOptFit(1);


	ifstream flist;
	flist.open("score.txt");

	int i_index = 0;
	float f_score = -999;
	vector<float> vec_score;

	TTree *T = new TTree("T","score");
	T->Branch("index",&i_index,"index/I");
	T->Branch("score",&f_score,"score/F");

	while ( flist >> f_score ){

		T->Fill();

		vec_score.push_back(f_score);

		i_index++;
	}


	TH1D *hscore = new TH1D("hscore","Score distribution;Score",100,0,100);

	for (unsigned int ii=0; ii<vec_score.size(); ++ii){

		hscore->Fill(vec_score[ii]);

	}

	TCanvas *c1 = new TCanvas("c1","c1",1.2*500,500);

	hscore->Draw();

	TF1 *fscore = new TF1("fscore","gaus",0,100);
	hscore->Fit(fscore,"RQ");
	fscore->Draw("same");


	TFile *outfile = new TFile("score.root","recreate");
	T->Write();
	outfile->Close();

}
