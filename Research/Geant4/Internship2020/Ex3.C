#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void Ex3(){

	gStyle->SetOptFit(111);

	TFile *infile = new TFile("score.root","read");

	TTree *T = (TTree*)infile->Get("T");

	float f_score;
	int i_index;

	T->SetBranchAddress("score",&f_score);
	T->SetBranchAddress("index",&i_index);

	unsigned int nentries = T->GetEntries();

	TH1D *h_score = new TH1D("h_score",";score",100,0,100);
	for (int ien=0; ien<nentries; ien++){
		T->GetEntry(ien);

		h_score->Fill(f_score);
	}


	TCanvas *c1 = new TCanvas("c1","c1");
	h_score->SetLineColor(1);
	h_score->SetLineWidth(2);
	h_score->Draw();

	TF1 *f_fit = new TF1("f_fit","gaus",0,100);
	h_score->Fit(f_fit,"R0Q");
	f_fit->Draw("same");


}
