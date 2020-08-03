void Draw(){

	int np;
	int p_id[1000];
	float p_pt[1000], p_eta[1000], p_phi[1000];

	TH2D *hmult_mid_fwd = new TH2D("hmult_mid_fwd","",100,0,100,100,0,100);

	TH1D *htrk_pt_pi = new TH1D("htrk_pt_pi","",100,0,10);
	TH1D *htrk_pt_ka = new TH1D("htrk_pt_ka","",100,0,10);
	TH1D *htrk_pt_pr = new TH1D("htrk_pt_pr","",100,0,10);

	TH1D *htrk_eta_pi = new TH1D("htrk_eta_pi","",100,-5.0,5.0);
	TH1D *htrk_eta_ka = new TH1D("htrk_eta_ka","",100,-5.0,5.0);
	TH1D *htrk_eta_pr = new TH1D("htrk_eta_pr","",100,-5.0,5.0);

	for (int ii=0; ii<5; ii++){

		TFile *infile = new TFile(Form("outfile_pp13TeV_set05_grp000_%05d.root",ii),"read");
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

		int nentries = T->GetEntries();

		for (int ien=0; ien<nentries; ien++){

			T->GetEntry(ien);

			int nmult_mid = 0, nmult_fwd = 0;

			for (int ip=0; ip<np; ip++){
				if ( fabs(p_eta[ip])<1.0 && p_pt[ip]>0.2 ){
					nmult_mid++;

				}else if ( fabs(p_eta[ip])>3.0 && fabs(p_eta[ip])<5.0 ){
					nmult_fwd++;
				}
			}//ip

			for (int ip=0; ip<np; ip++){
				if ( p_pt[ip]>0.2 ){

					if ( abs(p_id[ip])==211 ){
						htrk_eta_pi->Fill(p_eta[ip]);
						if ( fabs(p_eta[ip])<1.0 ){
							htrk_pt_pi->Fill(p_pt[ip]);
						}
					}else if ( abs(p_id[ip])==321 ){
						htrk_eta_ka->Fill(p_eta[ip]);
						if ( fabs(p_eta[ip])<1.0 ){
							htrk_pt_ka->Fill(p_pt[ip]);
						}
					}else if ( abs(p_id[ip])==2212 ){
						htrk_eta_pr->Fill(p_eta[ip]);
						if ( fabs(p_eta[ip])<1.0 ){
							htrk_pt_pr->Fill(p_pt[ip]);
						}
					}

				}//p_pt[ip]>0.2
			}//ip

			hmult_mid_fwd->Fill(nmult_mid, nmult_fwd);

		}//ien

	}//ii

	TCanvas *c1 = new TCanvas("c1","c1",1.2*300*3,2*300);
	c1->Divide(3,2);
	
	c1->cd(1);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	hmult_mid_fwd->Draw("colz");
	hmult_mid_fwd->GetXaxis()->SetTitle("N_{ch}, |#eta|<1 && p_{T}>0.2 GeV/c");
	hmult_mid_fwd->GetYaxis()->SetTitle("N_{ch}, 3<|#eta|<5");

	c1->cd(2);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetLogy();
	TH1D *hprojx = (TH1D*)hmult_mid_fwd->ProjectionX("hprojx");
	hprojx->SetLineColor(1);
	hprojx->Draw();

	c1->cd(3);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetLogy();
	TH1D *hprojy = (TH1D*)hmult_mid_fwd->ProjectionY("hprojy");
	hprojy->SetLineColor(1);
	hprojy->Draw();

	c1->cd(4);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	gPad->SetLogy();
	htrk_pt_pi->GetYaxis()->SetTitle("1/N_{evt} dN/dp_{T}");
	htrk_pt_pi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	htrk_pt_pi->Scale(1./htrk_pt_pi->GetBinWidth(1)/hmult_mid_fwd->GetEntries());
	htrk_pt_pi->SetLineColor(1);
	htrk_pt_pi->Draw();

	htrk_pt_ka->Scale(1./htrk_pt_ka->GetBinWidth(1)/hmult_mid_fwd->GetEntries());
	htrk_pt_ka->SetLineColor(2);
	htrk_pt_ka->Draw("same");

	htrk_pt_pr->Scale(1./htrk_pt_pr->GetBinWidth(1)/hmult_mid_fwd->GetEntries());
	htrk_pt_pr->SetLineColor(4);
	htrk_pt_pr->Draw("same");

	{
		TLegend *leg = new TLegend(0.15,0.15,0.6,0.3);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.04);
		leg->AddEntry(htrk_pt_pi,"#pi^{+} + #pi^{-}","L");
		leg->AddEntry(htrk_pt_ka,"K^{+} + K^{-}","L");
		leg->AddEntry(htrk_pt_pr,"p + #bar{p}","L");
		leg->Draw();
	}

	c1->cd(5);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	htrk_eta_pi->GetYaxis()->SetTitle("1/N_{evt} dN/d#eta");
	htrk_eta_pi->GetXaxis()->SetTitle("#eta");
	htrk_eta_pi->GetXaxis()->CenterTitle();
	htrk_eta_pi->Scale(1./htrk_eta_pi->GetBinWidth(1)/hmult_mid_fwd->GetEntries());
	htrk_eta_pi->SetLineColor(1);
	htrk_eta_pi->SetMinimum(0);
	htrk_eta_pi->SetMaximum(3.0);
	htrk_eta_pi->Draw();

	htrk_eta_ka->Scale(1./htrk_eta_ka->GetBinWidth(1)/hmult_mid_fwd->GetEntries());
	htrk_eta_ka->SetLineColor(2);
	htrk_eta_ka->Draw("same");

	htrk_eta_pr->Scale(1./htrk_eta_pr->GetBinWidth(1)/hmult_mid_fwd->GetEntries());
	htrk_eta_pr->SetLineColor(4);
	htrk_eta_pr->Draw("same");

	{
		TLegend *leg = new TLegend(0.15,0.78,0.6,0.93);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.04);
		leg->AddEntry(htrk_pt_pi,"#pi^{+} + #pi^{-}","L");
		leg->AddEntry(htrk_pt_ka,"K^{+} + K^{-}","L");
		leg->AddEntry(htrk_pt_pr,"p + #bar{p}","L");
		leg->Draw();
	}

	TH1D *htrk_pt_ka_pi = (TH1D*)htrk_pt_ka->Clone("htrk_pt_ka");
	TH1D *htrk_pt_pr_pi = (TH1D*)htrk_pt_pr->Clone("htrk_pt_pr");

	htrk_pt_ka_pi->Divide(htrk_pt_pi);
	htrk_pt_pr_pi->Divide(htrk_pt_pi);

	c1->cd(6);
	gPad->SetRightMargin(0.05);
	gPad->SetTopMargin(0.05);
	
	htrk_pt_ka_pi->GetYaxis()->SetTitle("Ratio");
	htrk_pt_ka_pi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	htrk_pt_ka_pi->SetMinimum(0);
	htrk_pt_ka_pi->SetMaximum(1.0);
	htrk_pt_ka_pi->Draw();

	htrk_pt_pr_pi->Draw("same");

	{
		TLegend *leg = new TLegend(0.15,0.83,0.6,0.93);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.04);
		leg->AddEntry(htrk_pt_ka,"(K^{+} + K^{-})/(#pi^{+} + #pi^{-})","L");
		leg->AddEntry(htrk_pt_pr,"(p + #bar{p})/(#pi^{+} + #pi^{-})","L");
		leg->Draw();
	}


	TFile *outfile = new TFile("outfile.root","recreate");

	hmult_mid_fwd->Write();

	outfile->Close();

}
