#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"

#include <vector>
#include <iostream>
using namespace std;

void mcAnaTestBeam(const char* inFile = "./example.mc.root")
{
	//gSystem->Load("/home/ckim/work/testbench/kebi-1/tools/install/lib/libRaveBase.so.0");
	//gSystem->Load("/home/ckim/work/testbench/kebi-1/build/libKEBI.so");
	//cout <<"KEBI loaded!" <<endl;

	//Constants, Enumerations
	enum pIDorder { pro, neu, gam, ele, pos, deu, ELS };
	enum pIDindex { Proton = 2212, Neutron = 2112, Gamma = 22, Electron=11, Positron=-11, Deuteron=1000010020 };
	enum {forward, recoil};

	const float zCollimator = -600.;
	const float xRoomEnd = 1500.;
	const float yRoomEnd = 1500.;
	const float zRoomEnd = 4200.;
	const float pIDmass[] = {938.272, 939.565, 0, 0.511, 0.511, 1875.613};

	//-------------------------------------------

	//Link input
	TFile* F = TFile::Open(inFile);
	if (!F || F->IsZombie()) { cout <<Form("Cannot open %s: stop.\n", inFile); return; }

	TTree* T = (TTree*)F->Get("event");
	//TClonesArray* MCTrack = nullptr;
	TClonesArray* MCPostTrack = nullptr;
	//T->SetBranchAddress("MCTrack", &MCTrack);
	T->SetBranchAddress("MCPostTrack", &MCPostTrack);

	//-------------------------------------------

	// Containers
	TH2F* H2_postTN = new TH2F("H2_postTN", "", 1000,0.5,1000.5, 1000,0.5,1000.5);
	H2_postTN->SetTitle(";TotalPostTracks/Event;RecoilPostTracks/Event");
	H2_postTN->Sumw2();

	TH1F* H1_postTC[2];
	const char* LABEL[7] = {"p", "n", "#gamma", "e-", "e+", "deuteron", "ELSE"};
	for (int a=0; a<2; a++)
	{
		H1_postTC[a] = new TH1F(Form("H1_postTComp_%i", a), "", 7, 0, 7);
		H1_postTC[a]->SetTitle(Form("Composition of post tracks %s", (a==0)?"":"(recoiled)"));
		for (int b=0; b<H1_postTC[a]->GetNbinsX(); b++) H1_postTC[a]->GetXaxis()->SetBinLabel(b+1, LABEL[b]);
		H1_postTC[a]->Sumw2();
	}

	TH2F* H2_protonXY[4]; //At 300,  0, -300, -600
	for (int a=0; a<4; a++)
	{
		const char* probeZ = "";
		if      (a==0) probeZ = "+300"; 
		else if (a==1) probeZ = "0 (target)"; 
		else if (a==2) probeZ = "-300 (start counter)"; 
		else if (a==3) probeZ = "-600 (collimator)";

		H2_protonXY[a] = new TH2F(Form("protonXY_%i", a), "", 2000,-1000,1000, 2000,-1000,1000);
		H2_protonXY[a]->SetTitle(Form("Forward protons at z = %s;x;y", probeZ));
		H2_protonXY[a]->Sumw2();
	}

	//-------------------------------------------

	int nTotalPostTracks[2] = {0};
	const int nEvents = T->GetEntries();
	for (int a=0; a<nEvents; a++)
	{
		MCPostTrack->Clear();
		T->GetEntry(a);

		int nPostTrackRecoil = 0;
		const int nPostTrack = MCPostTrack->GetEntries();
		for (int b=0; b<nPostTrack; b++)
		{
			auto postT = (KBMCTrack*)MCPostTrack->At(b);

			const Int_t   tPDG = postT->GetPDG();
			const Double_t tPX = postT->GetPX();
			const Double_t tPY = postT->GetPY();
			const Double_t tPZ = postT->GetPZ();
			const Double_t tP  = TMath::Sqrt(tPX*tPX + tPY*tPY + tPZ*tPZ);

			const Double_t tVX = postT->GetVX();
			const Double_t tVY = postT->GetVY();
			const Double_t tVZ = postT->GetVZ();

			int index = 0;
			if      (tPDG == Proton)   index = pro;
			else if (tPDG == Neutron)  index = neu;
			else if (tPDG == Gamma)    index = gam;
			else if (tPDG == Electron) index = ele;
			else if (tPDG == Positron) index = pos;
			else if (tPDG == Deuteron) index = deu;
			else index = ELS;

			if (tVZ > zCollimator)
			{
				H1_postTC[forward]->Fill(index);

				if (tPDG == Proton)
				{
					//if ( (abs(tVX) == xRoomEnd) || (abs(tVY) == yRoomEnd) ) continue;

					const float slopeX = tVX/(zRoomEnd * 2);
					const float slopeY = tVY/(zRoomEnd * 2);
					H2_protonXY[0]->Fill(slopeX * (zRoomEnd + 300), slopeY * (zRoomEnd + 300));
					H2_protonXY[1]->Fill(slopeX * zRoomEnd, slopeY * zRoomEnd);
					H2_protonXY[2]->Fill(slopeX * (zRoomEnd - 300), slopeY * (zRoomEnd - 300));
					H2_protonXY[3]->Fill(slopeX * (zRoomEnd - 600), slopeY * (zRoomEnd - 600));
				}
			}
			else
			{
				nPostTrackRecoil++;
				H1_postTC[recoil]->Fill(index);
			}

		}//b, PostTrack

		nTotalPostTracks[forward] += (nPostTrack - nPostTrackRecoil);
		nTotalPostTracks[recoil]  += (nPostTrackRecoil);
		H2_postTN->Fill(nPostTrack, nPostTrackRecoil);
	}//a, nEvents
	//for (int a=0; a<2; a++) H1_postTC[a]->Scale(1/(float)nTotalPostTracks[a]);

	TCanvas* c1 = new TCanvas("c1", "", 1600, 900);
	c1->Divide(2, 2); 
	c1->cd(1)->SetGrid(); H2_postTN->Draw("colz");
	c1->cd(2);
	gPad->SetLogy();
	gPad->SetGrid();
	//H1_postTC[0]->GetYaxis()->SetRangeUser(0, 1);
	H1_postTC[0]->Draw("hist e");
	c1->cd(4);
	gPad->SetLogy();
	gPad->SetGrid();
	//H1_postTC[1]->GetYaxis()->SetRangeUser(0, 1);
	H1_postTC[1]->Draw("hist e");

	TCanvas* c2 = new TCanvas("c2", "", 1600, 900);
	c2->Divide(2, 2);

	for (int a=0; a<4; a++)
	{
		c2->cd(a+1);
		H2_protonXY[a]->Rebin2D(10);
		H2_protonXY[a]->Draw("colz");
	}

	return;
}//Main
