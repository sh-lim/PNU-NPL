void ScanPYTHIA(){

	int np;
	int p_id[1000];
	float p_pt[1000], p_eta[1000], p_phi[1000];

	TH1D *h1Np = new TH1D("h1Np","",500,0,500);
	TH2D *h2EtaPt = new TH2D("h2EtaPt","",100,-5,5,100,0,10);

	TFile *infile = new TFile("outfile_pp13TeV_set00_grp000_00000.root","read");

	TTree *T = (TTree*)infile->Get("T");

	T->SetBranchAddress("np",&np);
	T->SetBranchAddress("p_id",p_id);
	T->SetBranchAddress("p_pt",p_pt);
	T->SetBranchAddress("p_eta",p_eta);
	T->SetBranchAddress("p_phi",p_phi);

	int nentries = T->GetEntries();

	for (int ien=0; ien<nentries; ien++){

		T->GetEntry(ien);

		h1Np->Fill(np);

		for (int ip=0; ip<np; ip++){

			h2EtaPt->Fill(p_eta[ip], p_pt[ip]);

		}//ip

	}//ien

	TFile *outfile = new TFile("outfile_ScanPYTHIA.root","recreate");

	h1Np->Write();
	h2EtaPt->Write();

	outfile->Close();

}
