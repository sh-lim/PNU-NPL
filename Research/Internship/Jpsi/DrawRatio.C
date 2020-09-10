void DrawRatio(){

	const bool bSAVE = false;

	int np;
	int p_id[1000];
	float p_pt[1000], p_eta[1000], p_phi[1000];
	bool p_charge[1000];

	TH1D *hmult_jpsi = new TH1D("hmult_jpsi","",50,0,100);
	TH1D *hmult_psip = new TH1D("hmult_psip","",50,0,100);

	hmult_jpsi->Sumw2();
	hmult_psip->Sumw2();

	TH1D *hnjpsi = new TH1D("hnjpsi","",10,0,10);
	TH1D *hnpsip = new TH1D("hnpsip","",10,0,10);

	for (int ii=0; ii<1; ii++){

		TFile *infile = new TFile(Form("outfile_pp13TeV_set04_grp000_%05d.root",ii),"read");
		//TFile *infile = new TFile(Form("outfile_pp13TeV_set04_grp002.root"),"read");
		if ( infile->IsOpen() ){
			cout << "OPEN: " << infile->GetName() << endl;
		}else{
			cout << "SKIP: " << infile->GetName() << endl;
			continue;
		}
		TTree *T = (TTree*)infile->Get("T");

		T->SetBranchAddress("np",&np);
		T->SetBranchAddress("p_id",p_id);
		T->SetBranchAddress("p_pt",p_pt);
		T->SetBranchAddress("p_eta",p_eta);
		T->SetBranchAddress("p_phi",p_phi);
		T->SetBranchAddress("p_charge",p_charge);

		int nentries = T->GetEntries();

		for (int ien=0; ien<nentries; ien++){

			T->GetEntry(ien);

			int nmult = 0;

			for (int ip=0; ip<np; ip++){
				if ( p_charge[ip] ){
					nmult++;
				}
			}

			int njpsi = 0, npsip = 0;

			for (int ip=0; ip<np; ip++){
				if ( p_id[ip]==443 ){
					njpsi++;
				}else if ( p_id[ip]==100443 ){
					npsip++;
				}
			}

			hnjpsi->Fill(njpsi);
			hnpsip->Fill(npsip);

			if ( njpsi>0 ){
				hmult_jpsi->Fill(nmult, njpsi);
			}
			if ( npsip>0 ){
				hmult_psip->Fill(nmult, npsip);
			}

		}//ien

	}//ii


	TCanvas *c0 = new TCanvas("c0","c0",1.1*3*400,1*400);
	c0->Divide(3,1);

	c0->cd(1);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.14);
	gPad->SetLeftMargin(0.14);
	gPad->SetLogy();

	{
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.5,5,2.0*hnjpsi->GetMaximum());
		htmp->GetXaxis()->SetTitle("N_{#psi} per event");
		htmp->GetXaxis()->SetTitleSize(0.06);
		htmp->GetXaxis()->SetLabelSize(0.05);

		htmp->GetYaxis()->SetTitle("N_{event}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.05);

		hnjpsi->SetLineWidth(2);
		hnjpsi->SetLineColor(1);
		hnjpsi->Draw("same");

		hnpsip->SetLineWidth(2);
		hnpsip->SetLineColor(2);
		hnpsip->Draw("same");
	}

	c0->cd(2);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.14);
	gPad->SetLeftMargin(0.18);

	{
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0.,50,1.2*hmult_jpsi->GetMaximum());
		htmp->GetXaxis()->SetTitle("N_{ch} per event");
		htmp->GetXaxis()->SetTitleSize(0.06);
		htmp->GetXaxis()->SetLabelSize(0.05);

		htmp->GetYaxis()->SetTitle("N_{event}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.05);

		hmult_jpsi->SetMarkerStyle(24);
		hmult_jpsi->SetLineWidth(2);
		hmult_jpsi->SetLineColor(1);
		hmult_jpsi->Draw("p same");

		hmult_psip->SetMarkerStyle(24);
		hmult_psip->SetLineWidth(2);
		hmult_psip->SetLineColor(2);
		hmult_psip->Draw("p same");
	}

	c0->cd(3);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetBottomMargin(0.14);
	gPad->SetLeftMargin(0.14);

	TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,50,1);
	htmp->GetXaxis()->SetTitle("N_{ch} per event");
	htmp->GetXaxis()->SetTitleSize(0.06);
	htmp->GetXaxis()->SetLabelSize(0.05);

	htmp->GetYaxis()->SetTitle("#psi(2S) / J/#psi");
	htmp->GetYaxis()->SetTitleSize(0.06);
	htmp->GetYaxis()->SetLabelSize(0.05);

	TH1D *hmult_ratio = (TH1D*)hmult_psip->Clone("hmult_ratio");
	hmult_ratio->Divide(hmult_jpsi);

	hmult_ratio->SetMarkerStyle(24);
	hmult_ratio->SetLineWidth(2);
	hmult_ratio->SetLineColor(1);
	hmult_ratio->Draw("same");

	if ( bSAVE ){
		TFile *outfile = new TFile("outfile_first.root", "recreate");
		hmult_ratio->Write();
		outfile->Close();
	}


}
