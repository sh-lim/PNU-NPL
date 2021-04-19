void DrawAMPTvn(){

	const int nset = 3;
	const int norder = 2;

	string setname[nset] = {"p+Au", "d+Au", "^{3}He+Au"};

	TGraphErrors *gvn_on[nset][norder];
	TGraphErrors *gvn_off[nset][norder];

	TFile *infile = new TFile("outfile_AMPT_vn.root","read");

	for (int iset=0; iset<nset; iset++){
		for (int io=0; io<norder; io++){

			gvn_on[iset][io] = (TGraphErrors*)infile->Get(Form("gvn_on_set%d_order%d",iset,io+2));
			gvn_off[iset][io] = (TGraphErrors*)infile->Get(Form("gvn_off_set%d_order%d",iset,io+2));

			gvn_on[iset][io]->SetFillColorAlpha(io+1, 0.5);
			gvn_on[iset][io]->SetLineWidth(0);
			gvn_off[iset][io]->SetFillColorAlpha(io+1, 0.5);
			gvn_off[iset][io]->SetLineWidth(0);

		}
	}

	TCanvas *c3 = new TCanvas("c3","c3",1.1*3*400,400);
	c3->Divide(3,1);

	for (int iset=0; iset<nset; iset++){
		c3->cd(iset+1);

		gPad->SetMargin(0.14,0.05,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,-0.05,3,0.25);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("v_{n}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		gvn_on[iset][0]->Draw("e3");
		gvn_on[iset][1]->Draw("e3");

		TLegend *leg = new TLegend(0.4,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.05);
		leg->AddEntry("",Form("AMPT parton scattering on"),"h");
		leg->AddEntry("",Form("0-5%% %s 200 GeV",setname[iset].c_str()),"h");
		leg->AddEntry(gvn_on[iset][0],"v_{2}","F");
		leg->AddEntry(gvn_on[iset][1],"v_{3}","F");
		leg->Draw();

	}


	TCanvas *c3off = new TCanvas("c3off","c3off",1.1*3*400,400);
	c3off->Divide(3,1);

	for (int iset=0; iset<nset; iset++){
		c3off->cd(iset+1);

		gPad->SetMargin(0.14,0.03,0.12,0.03);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,-0.05,3,0.25);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);

		htmp->GetYaxis()->SetTitle("v_{n}");
		htmp->GetYaxis()->SetTitleSize(0.06);
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleOffset(1.1);

		gvn_off[iset][0]->Draw("e3");
		gvn_off[iset][1]->Draw("e3");

		TLegend *leg = new TLegend(0.4,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.05);
		leg->AddEntry("",Form("AMPT, parton scattering off"),"h");
		leg->AddEntry("",Form("0-5%% %s 200 GeV",setname[iset].c_str()),"h");
		leg->AddEntry(gvn_off[iset][0],"v_{2}","F");
		leg->AddEntry(gvn_off[iset][1],"v_{3}","F");
		leg->Draw();
	}


}
