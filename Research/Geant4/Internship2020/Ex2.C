#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void Ex2(){

	gStyle->SetOptFit(111);

	ifstream fdata;
	fdata.open("score.txt");

	vector<float> vec_score;
	float f_score;

	while ( fdata >> f_score ){
		vec_score.push_back(f_score);
	}

	//calculate mean
	float f_mean = 0;
	for (unsigned int ii=0; ii<vec_score.size(); ++ii){
		f_mean += vec_score[ii];
	}
	f_mean /= vec_score.size();

	//calculate std dev
	float f_std_dev = 0;
	for (unsigned int ii=0; ii<vec_score.size(); ++ii){
		f_std_dev += (vec_score[ii]-f_mean)*(vec_score[ii]-f_mean);
	}
	f_std_dev = sqrt(f_std_dev/(vec_score.size()-1));

	cout << "mean: " << f_mean << endl;
	cout << "sigma: " << f_std_dev << endl;

	//fill histogram
	TH1D *h_score = new TH1D("h_score",";score",100,0,100);
	for (unsigned int ii=0; ii<vec_score.size(); ++ii){
		h_score->Fill(vec_score[ii]);
	}

	TCanvas *c1 = new TCanvas("c1","c1");
	h_score->SetLineColor(1);
	h_score->SetLineWidth(2);
	h_score->Draw();

	TF1 *f_fit = new TF1("f_fit","gaus",0,100);
	h_score->Fit(f_fit,"R0Q");
	f_fit->Draw("same");


}
