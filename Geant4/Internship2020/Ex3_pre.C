#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void Ex3_pre(){

	ifstream fdata;
	fdata.open("score.txt");

	int i_index = 0;
	float f_score;

	TTree *T = new TTree("T","score");
	T->Branch("index",&i_index,"index/I");
	T->Branch("score",&f_score,"score/F");

	while ( fdata >> f_score ){
		T->Fill();
		i_index++;
	}


	TFile *outfile = new TFile("score.root","recreate");
	T->Write();
	outfile->Close();


}
