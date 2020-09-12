void CheckProton(){

	/*
	auto run = KBRun::GetRun();
	run->SetInputFile("../","event");
	*/

	const float zref1 = -600.0;
	const float zref2 = -300.0;
	const float zref3 = 0.0;

	TH2D *hProton_xy_zref1 = new TH2D("hProton_xy_zref1","",200,-1000,1000,200,-1000,1000);

	TClonesArray *fMCTrack = new TClonesArray("KBMCTrack");
	TClonesArray *fMCPostTrack = new TClonesArray("KBMCTrack");

	TFile *infile = new TFile("example.mc.Al.Vac.root","read");
	//TFile *infile = new TFile("example.mc.Fe.root","read");
	TTree *T = (TTree*)infile->Get("event");

	TBranch *bMCTrack = (TBranch*)T->GetBranch("MCTrack");
	bMCTrack->SetAddress(&fMCTrack);

	TBranch *bMCPostTrack = (TBranch*)T->GetBranch("MCPostTrack");
	bMCPostTrack->SetAddress(&fMCPostTrack);

	int nentries = T->GetEntriesFast();

	int nProton = 0;

	for (int ien=0; ien<nentries; ien++){

		bMCTrack->GetEntry(ien);
		bMCPostTrack->GetEntry(ien);

		int nMCTrack = fMCTrack->GetEntriesFast();
		int nMCPostTrack = fMCPostTrack->GetEntriesFast();

		for (int itrk=0; itrk<nMCPostTrack; itrk++){

			KBMCTrack *track = (KBMCTrack*)fMCPostTrack->At(itrk);

			if ( track->GetPDG()!=2212 ) continue;

			float vx = track->GetVX(); 
			float vy = track->GetVY(); 
			float vz = track->GetVZ(); 

			float px = track->GetPX(); 
			float py = track->GetPY(); 
			float pz = track->GetPZ(); 

			if ( pz<0 ) continue;

			float xref1 = vx - px/pz*(vz - zref1);
			float yref1 = vy - py/pz*(vz - zref1);

			hProton_xy_zref1->Fill(xref1, yref1);

			nProton++;

		}//itrk


		fMCTrack->Clear();
		fMCPostTrack->Clear();

	}

	cout << nProton << endl;

	infile->Close();
	
	TCanvas *c1 = new TCanvas("c1","c1",1.2*500,500);
	gPad->SetLeftMargin(0.15);

	{
		TH1D *htmp = (TH1D*)hProton_xy_zref1;
		htmp->GetYaxis()->SetTitle("y (mm)");
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitle("x (mm)");
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleSize(0.05);
		hProton_xy_zref1->Draw("colz");
	}

	//return;

	//cout << hnHitPerMCTrack->Integral() << endl;

	/*
	//hnHitPerMCTrack->Draw();
	TFile *outfile = new TFile("outfile.root","recreate");
	hnHitPerMCTrack->Write();

	outfile->Close();
	*/

	//hnHitPerMCTrack->Draw();

}
