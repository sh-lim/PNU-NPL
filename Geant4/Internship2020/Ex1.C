#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void Ex1(){

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

}
