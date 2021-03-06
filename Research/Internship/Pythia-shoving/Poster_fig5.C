#include "Style.h"

void Poster_fig5(){

	const bool bSAVE = false;

	gStyle->SetOptStat(0);

	TFile *infile;
	TFile *infiles[2];
		
	const Int_t nfiles = 2;
	
	string cfigNames1[nfiles] = {"cfig1_cms_dp", "cfig1_cms_ds"};
	string cfigNames2_pre[nfiles] = {"cifg2_pre_cms_dp", "cfig2_pre_cms_ds"};
	string cfigNames3_pre[nfiles] = {"cifg3_pre_cms_dp", "cfig3_pre_cms_ds"};
	string cfigNames2[nfiles] = {"cfig2_cms_dp", "cfig2_cms_ds"};
	string cfigNames3[nfiles] = {"cfig3_cms_dp", "cfig3_cms_ds"};

	//mid rapidity for try000, default pythia for grp000, default shoving for grp 001
	string fileNames[nfiles] = {"outfile_hist_pp13TeV_set00_grp000_try000.root", "outfile_hist_pp13TeV_set00_grp001_try000.root"};

	TCanvas *cfig1[nfiles];
	TCanvas *cfig2_pre[nfiles];
	TCanvas *cfig3_pre[nfiles];
	TCanvas *cfig2[nfiles];
	TCanvas *cfig3;

	const float const_pi = TMath::Pi();

	const int npt = 1;
	const float ptbin[npt+1] = {1.0, 2.0};

	const int nmult = 12;
	//const float multbin[nmult+1] = {0, 35, 80, 105, 150};

	const int nMarker[nmult] = {20, 21, 24, 25};
	const int nColor[nmult] = {1, 2, 4, 8};
	

	TH2D *h2d_same_mid[nmult][npt];
	TH2D *h2d_mixed_mid[nmult][npt];

	TH1D *hntrig_mid;
	TH1D *hntrig_mixed_mid;

	TH1D *h1d_deta_same_mid[nmult][npt];
	TH1D *h1d_deta_mixed_mid[nmult][npt];

	//TH1D *h1d_dphi_same_mid[nmult][npt];
	//TH1D *h1d_dphi_mixed_mid[nmult][npt];

	TH1D *h1d_mixed_dphi_long_mid[nmult][npt][2];
	TH1D *h1d_mixed_dphi_short_mid[nmult][npt][2];

	TH1D *h1d_same_dphi_long_mid[nmult][npt][2];
	TH1D *h1d_same_dphi_short_mid[nmult][npt][2];

	TH1D *h1d_same_dphi_subs_mid[nmult][npt];
	TH1D *h1d_dphi_zyam_subs_mid[nmult][npt];

	TF1 *f1d_dphi_short_mid[nmult][npt];
	TF1 *f1d_dphi_long_mid[nmult][npt];
	TF1 *f1d_dphi_subs_mid[nmult][npt];
	
	TH1D *h1d_Yassociated_mult_mid[nfiles][npt];
	
	cfig3 = new TCanvas("cfig3","cfig3",1.1*500*2,500);
	cfig3->Divide(2,1);

	for(int i=0; i<2; i++){

	infiles[i] = new TFile(fileNames[i].c_str(), "read");
	infile = infiles[i];


	for (int ipt=0; ipt<npt; ipt++){
		std::cout<<"GEN HIST " << i <<std::endl;
		h1d_Yassociated_mult_mid[i][ipt] = new TH1D(Form("h1d_Yassociated_mult_mid_pt_%d_%02d",i,ipt),"",nmult,0,10*nmult);
	}

	hntrig_mid = (TH1D*)infile->Get("hntrig_mid");
	hntrig_mixed_mid = (TH1D*)infile->Get("hntrig_mixed_mid");

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			float ntrig_mid= hntrig_mid->Integral(hntrig_mid->FindBin(10*imult+0.1), hntrig_mid->FindBin(10*(imult+1)-0.1));
			float ntrig_mixed_mid = hntrig_mixed_mid->Integral(hntrig_mixed_mid->FindBin(10*imult+0.1), hntrig_mixed_mid->FindBin(10*(imult+1)-0.1));

			h2d_same_mid[imult][ipt] = (TH2D*)infile->Get(Form("h2d_same_dphi_deta_m%02d",imult));
			h2d_mixed_mid[imult][ipt] = (TH2D*)infile->Get(Form("h2d_mixed_dphi_deta_m%02d",imult));

			h2d_same_mid[imult][ipt]->RebinX(4);
			h2d_mixed_mid[imult][ipt]->RebinX(4);

			h2d_same_mid[imult][ipt]->Scale(1./ntrig_mid);
			h2d_mixed_mid[imult][ipt]->Scale(1./ntrig_mixed_mid);

			h2d_same_mid[imult][ipt]->Divide(h2d_mixed_mid[imult][ipt]);

			float nnorm_mixed_mid = h2d_mixed_mid[imult][ipt]->GetBinContent(h2d_mixed_mid[imult][ipt]->FindBin(0,0));
			nnorm_mixed_mid /= h2d_mixed_mid[imult][ipt]->GetYaxis()->GetBinWidth(1);
			nnorm_mixed_mid /= h2d_mixed_mid[imult][ipt]->GetXaxis()->GetBinWidth(1);
			h2d_same_mid[imult][ipt]->Scale(nnorm_mixed_mid);

			//normalization
			//h2d_same_mid[imult][ipt]->RebinY(4);
			//h2d_mixed_mid[imult][ipt]->RebinY(4);


			int etabin_min_mid = h2d_same_mid[imult][ipt]->GetYaxis()->FindBin(-5.0+0.0001);
			int etabin_max_mid = h2d_same_mid[imult][ipt]->GetYaxis()->FindBin(-2.0-0.0001);
		
			h1d_same_dphi_long_mid[imult][ipt][0] = (TH1D*)h2d_same_mid[imult][ipt]->ProjectionX(Form("h1d_same_dphi_long_mid_mult%02d_pt%02d_0",imult,ipt),etabin_min_mid,etabin_max_mid);

			etabin_min_mid = h2d_same_mid[imult][ipt]->GetYaxis()->FindBin(+2.0+0.0001);
			etabin_max_mid = h2d_same_mid[imult][ipt]->GetYaxis()->FindBin(+5.0-0.0001);
			
			h1d_same_dphi_long_mid[imult][ipt][1] = (TH1D*)h2d_same_mid[imult][ipt]->ProjectionX(Form("h1d_same_dphi_long_mid_mult%02d_pt%02d_1",imult,ipt),etabin_min_mid,etabin_max_mid);

			h1d_same_dphi_long_mid[imult][ipt][0]->Add(h1d_same_dphi_long_mid[imult][ipt][1]);
			h1d_same_dphi_long_mid[imult][ipt][0]->Scale(1./6.0*h2d_same_mid[imult][ipt]->GetYaxis()->GetBinWidth(1));


			etabin_min_mid = h2d_same_mid[imult][ipt]->GetYaxis()->FindBin(-1.0+0.0001);
			etabin_max_mid = h2d_same_mid[imult][ipt]->GetYaxis()->FindBin(+1.0-0.0001);
	
			h1d_same_dphi_short_mid[imult][ipt][0] = (TH1D*)h2d_same_mid[imult][ipt]->ProjectionX(Form("h1d_same_dphi_short_mid_mult%02d_pt%02d",imult,ipt),etabin_min_mid,etabin_max_mid);
			h1d_same_dphi_short_mid[imult][ipt][0]->Scale(1./2.0*h2d_same_mid[imult][ipt]->GetYaxis()->GetBinWidth(1));


			//TH1D *htmp_same_mid = (TH1D*)h2d_same_mid[imult][ipt]->ProjectionX(Form("h1d_same_dphi_subs_mid_mult%02d_pt%02d_1",imult,ipt),etabin_min_mid,etabin_max_mid);
			//TH1D *htmp_mixed_mid = (TH1D*)h2d_mixed_mid[imult][ipt]->ProjectionX(Form("h1d_dphi_mixed_mid_mult%02d_pt%02d_1",imult,ipt),etabin_min_mid,etabin_max_mid);

			h1d_same_dphi_subs_mid[imult][ipt] = (TH1D*)h1d_same_dphi_short_mid[imult][ipt][0]->Clone(Form("h1d_same_dphi_short_mid_%d_%d",imult,ipt));
			h1d_same_dphi_subs_mid[imult][ipt]->Add(h1d_same_dphi_long_mid[imult][ipt][0], -1);

			//fit w/ Fourier series
			//f1d_dphi[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x))",-const_pi/2,3*const_pi/2);
			//f1d_dphi_mid[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x))",-const_pi/2,1*const_pi/2);
			f1d_dphi_short_mid[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) + 2*[4]*cos(4*x) + 2*[5]*cos(5*x))",-const_pi/2,3*const_pi/2);
			h1d_same_dphi_short_mid[imult][ipt][0]->Fit(f1d_dphi_short_mid[imult][ipt],"R0Q");

			f1d_dphi_long_mid[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) + 2*[4]*cos(4*x) + 2*[5]*cos(5*x))",-const_pi/2,3*const_pi/2);
			h1d_same_dphi_long_mid[imult][ipt][0]->Fit(f1d_dphi_long_mid[imult][ipt],"R0Q");

			f1d_dphi_subs_mid[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) + 2*[4]*cos(4*x) + 2*[5]*cos(5*x))",-const_pi/2,3*const_pi/2);
			h1d_same_dphi_subs_mid[imult][ipt]->Fit(f1d_dphi_subs_mid[imult][ipt],"R0Q");

			//ZYAM subtraction
			float zyam = f1d_dphi_subs_mid[imult][ipt]->GetMinimum(-const_pi/2,3*const_pi/2);
			float zyam_x = f1d_dphi_subs_mid[imult][ipt]->GetMinimumX(-const_pi/2,3*const_pi/2);
			float Y_associated_mid = 0.0; 
			float Y_associated_mid_err = 0.0; 

			h1d_dphi_zyam_subs_mid[imult][ipt] = (TH1D*)h1d_same_dphi_subs_mid[imult][ipt]->Clone(Form("h1d_dphi_zyam_short_mid_mult%02d_pt%02d",imult,ipt));
			for (int iphi=0; iphi<h1d_dphi_zyam_subs_mid[imult][ipt]->GetNbinsX(); iphi++){
				float val_mid = h1d_dphi_zyam_subs_mid[imult][ipt]->GetBinContent(iphi+1);
				h1d_dphi_zyam_subs_mid[imult][ipt]->SetBinContent(iphi+1, val_mid-zyam);

				//associated yield |dphi|<1.2
				float dphi_mid = h1d_dphi_zyam_subs_mid[imult][ipt]->GetBinCenter(iphi+1); 
				float ddphi_mid = h1d_dphi_zyam_subs_mid[imult][ipt]->GetBinWidth(iphi+1);

				if ( fabs(dphi_mid)<1.2 ){
					Y_associated_mid += h1d_dphi_zyam_subs_mid[imult][ipt]->GetBinContent(iphi+1)*ddphi_mid;
					Y_associated_mid_err += h1d_dphi_zyam_subs_mid[imult][ipt]->GetBinError(iphi+1)*h1d_dphi_zyam_subs_mid[imult][ipt]->GetBinError(iphi+1)*ddphi_mid*ddphi_mid;
				}
			}

			h1d_Yassociated_mult_mid[i][ipt]->SetBinContent(imult+1,Y_associated_mid); 
			h1d_Yassociated_mult_mid[i][ipt]->SetBinError(imult+1,sqrt(Y_associated_mid_err)); 
			
		}//ipt
	}//imult
	
	

#if 1
	/*
	cfig1[i] = new TCanvas(cfigNames1[i].c_str(), cfigNames1[i].c_str(), 1.1*300*4, 300*4);
	cfig1[i]->Divide(5,4);

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){
			cfig1[i]->cd(imult*npt+ipt+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);
			gPad->SetPhi(135);

			htmp = (TH1D*)h2d_same_mid[imult][ipt]; 
			SetHistoStyle("","","",14,12);
			h2d_same_mid[imult][ipt]->SetAxisRange(-4.0+0.01,4.0-0.01,"Y");
			h2d_same_mid[imult][ipt]->GetYaxis()->SetTitle("|#Delta#eta|");
			h2d_same_mid[imult][ipt]->GetYaxis()->CenterTitle();
			h2d_same_mid[imult][ipt]->GetYaxis()->SetTitleOffset(5.);
			h2d_same_mid[imult][ipt]->GetXaxis()->SetTitle("|#Delta#phi|");
			h2d_same_mid[imult][ipt]->GetXaxis()->CenterTitle();
			h2d_same_mid[imult][ipt]->GetXaxis()->SetTitleOffset(5.0);
			h2d_same_mid[imult][ipt]->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}");
			h2d_same_mid[imult][ipt]->GetZaxis()->CenterTitle();
			h2d_same_mid[imult][ipt]->GetZaxis()->SetTitleOffset(7.0);

			float ymax_mid = h2d_same_mid[imult][ipt]->GetMaximum();
			float ymin_mid = h2d_same_mid[imult][ipt]->GetMinimum();
			h2d_same_mid[imult][ipt]->SetMaximum(ymin_mid + (0.8-0.2*ipt)*(ymax_mid-ymin_mid));
			h2d_same_mid[imult][ipt]->Draw("surf1");

			TLegend *leg = new TLegend(0.05,0.8,0.5,0.98);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextFont(43);
			leg->SetTextSize(14);
			leg->AddEntry("","Pythia8 pp 13 TeV","h");
			leg->AddEntry("",Form("%d#leqN_{trk}<%d",int(10*imult),int(10*(imult+1))),"h");
			leg->AddEntry("",Form("%g<p_{T}<%g GeV/c",ptbin[ipt],ptbin[ipt+1]),"h");
			leg->Draw();
		}
	}
	*/


	cfig2_pre[i] = new TCanvas(cfigNames2_pre[i].c_str(), cfigNames2_pre[i].c_str(), 1.1*300*4, 300*3);
	cfig2_pre[i]->Divide(4,3);

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			cfig2_pre[i]->cd(imult+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);
			gPad->SetTopMargin(0.10);

			float ymax_mid = h1d_same_dphi_short_mid[imult][ipt][0]->GetMaximum();
			float ymin_mid = h1d_same_dphi_short_mid[imult][ipt][0]->GetMinimum();

			htmp = (TH1D*)gPad->DrawFrame(-const_pi/2,ymin_mid-0.05*(ymax_mid-ymin_mid),const_pi*3/2,ymax_mid+0.05*(ymax_mid-ymin_mid));
			SetHistoStyle("|#Delta#phi|","#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}","",14,12);
			htmp->GetYaxis()->SetTitleOffset(7.0);
			htmp->GetXaxis()->SetTitleOffset(5.0);

			h1d_same_dphi_short_mid[imult][ipt][0]->SetMarkerStyle(24);
			h1d_same_dphi_short_mid[imult][ipt][0]->SetMarkerSize(1.0);
			h1d_same_dphi_short_mid[imult][ipt][0]->Draw("same");

			f1d_dphi_short_mid[imult][ipt]->SetLineWidth(3);
			f1d_dphi_short_mid[imult][ipt]->SetLineStyle(2);
			f1d_dphi_short_mid[imult][ipt]->SetLineColor(1);
			f1d_dphi_short_mid[imult][ipt]->Draw("same");

			h1d_same_dphi_long_mid[imult][ipt][0]->SetMarkerStyle(24);
			h1d_same_dphi_long_mid[imult][ipt][0]->SetMarkerSize(1.0);
			h1d_same_dphi_long_mid[imult][ipt][0]->SetMarkerColor(2);
			h1d_same_dphi_long_mid[imult][ipt][0]->Draw("same");

			f1d_dphi_long_mid[imult][ipt]->SetLineWidth(3);
			f1d_dphi_long_mid[imult][ipt]->SetLineStyle(2);
			f1d_dphi_long_mid[imult][ipt]->Draw("same");

		}
	}

	/*
	cfig3_pre[i] = new TCanvas(cfigNames3_pre[i].c_str(), cfigNames3_pre[i].c_str(), 1.1*300*4, 300*3);
	cfig3_pre[i]->Divide(4,3);

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			cfig3_pre[i]->cd(imult+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);
			gPad->SetTopMargin(0.10);

			float ymax_mid = h1d_same_dphi_subs_mid[imult][ipt]->GetMaximum();
			float ymin_mid = h1d_same_dphi_subs_mid[imult][ipt]->GetMinimum();

			htmp = (TH1D*)gPad->DrawFrame(-const_pi/2,ymin_mid-0.05*(ymax_mid-ymin_mid),const_pi*3/2,ymax_mid+0.05*(ymax_mid-ymin_mid));
			SetHistoStyle("|#Delta#phi|","#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}","",14,12);
			htmp->GetYaxis()->SetTitleOffset(7.0);
			htmp->GetXaxis()->SetTitleOffset(5.0);

			h1d_same_dphi_subs_mid[imult][ipt]->SetMarkerStyle(24);
			h1d_same_dphi_subs_mid[imult][ipt]->SetMarkerSize(1.0);
			h1d_same_dphi_subs_mid[imult][ipt]->Draw("same");

			f1d_dphi_subs_mid[imult][ipt]->SetLineWidth(3);
			f1d_dphi_subs_mid[imult][ipt]->SetLineStyle(2);
			f1d_dphi_subs_mid[imult][ipt]->SetLineColor(1);
			f1d_dphi_subs_mid[imult][ipt]->Draw("same");
		}
	}
	*/

	/*
	cfig2[i] = new TCanvas(cfigNames2[i].c_str(), cfigNames3[i].c_str(), 1.1*300*4, 300*3);
	cfig2[i]->Divide(4,3);
	
	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			cfig2[i]->cd(imult*npt+ipt+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);

			float ymax_mid = h1d_dphi_zyam_subs_mid[imult][ipt]->GetMaximum();
			float ymin_mid = h1d_dphi_zyam_subs_mid[imult][ipt]->GetMinimum();

			htmp = (TH1D*)gPad->DrawFrame(-const_pi/2,-0.05*ymax_mid,const_pi*3/2,1.05*ymax_mid);
			SetHistoStyle("|#Delta#phi|","#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi} - C_{ZYAM}","",14,12);
			htmp->GetYaxis()->SetTitleOffset(7.0);
			htmp->GetXaxis()->SetTitleOffset(5.0);

			h1d_dphi_zyam_subs_mid[imult][ipt]->SetMarkerStyle(24);
			h1d_dphi_zyam_subs_mid[imult][ipt]->SetMarkerSize(1.0);
			h1d_dphi_zyam_subs_mid[imult][ipt]->Draw("same");
		}
	}
	*/
	
	cfig3->cd(i+1);
	SetPadStyle();
	gPad->SetLeftMargin(0.18);

	{
		TH1D *htmp_short = (TH1D*)h1d_same_dphi_short_mid[8][0][0]->Clone(Form("htmp_short_%d",i));
		htmp_short->SetMarkerStyle(20);
		htmp_short->SetLineColor(1);

		TH1D *htmp_long = (TH1D*)h1d_same_dphi_long_mid[8][0][0]->Clone(Form("htmp_long_%d",i));
		htmp_long->SetMarkerStyle(24);
		htmp_long->SetLineColor(2);

		float ymax_mid = htmp_short->GetMaximum();
		float ymin_mid = htmp_short->GetMinimum();
		htmp = (TH1D*)gPad->DrawFrame(-const_pi/2,ymin_mid-0.1*(ymax_mid-ymin_mid),const_pi*3/2,ymax_mid+0.1*(ymax_mid-ymin_mid));
		SetHistoStyle("|#Delta#phi|","#frac{1}{N_{trig}} #frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}","",24,20);
		htmp->GetYaxis()->SetTitleOffset(1.5);

		htmp_short->Draw("same");
		htmp_long->Draw("same");

		TLegend *leg = new TLegend(0.45,0.65,0.95,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(18);
		leg->AddEntry("","pp #sqrt{s}=13 TeV","");
		if ( i==0 ){
			leg->AddEntry("","PYTHIA8 default","");
		}else{
			leg->AddEntry("","PYTHIA8 string shoving","");
		}
		leg->AddEntry("","80<N_{ch}#leq90","");
		leg->AddEntry("","1.0<p_{T}<2.0 GeV/c","");
		leg->AddEntry(htmp_short,"Short-range (|#Delta#eta|<1.0)","P");
		leg->AddEntry(htmp_long,"Long-range (2.0<|#Delta#eta|<5.0)","P");
		leg->Draw();
	}
#endif

	}


	/*
	TCanvas *cfig4 = new TCanvas("cifg4_cms_ShortRange","cfig4_cms_ShortRange",1.1*500, 500);

	SetPadStyle();
	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,120,0.5);
	SetHistoStyle("N_{ch}","Associated yield/(GeV/c)","",24,20);

	for (int ipt=0; ipt<npt; ipt++){
		std::cout<<h1d_Yassociated_mult_mid[0][ipt]<<std::endl;
		h1d_Yassociated_mult_mid[0][ipt]->SetMarkerStyle(21);
		h1d_Yassociated_mult_mid[0][ipt]->SetLineColor(4);
		h1d_Yassociated_mult_mid[0][ipt]->SetLineWidth(2);
		h1d_Yassociated_mult_mid[0][ipt]->SetMarkerColor(4);
		h1d_Yassociated_mult_mid[0][ipt]->Draw("p e0 same");
	}

	for (int ipt=0; ipt<npt; ipt++){
		std::cout<<h1d_Yassociated_mult_mid[1][ipt]<<std::endl;
		h1d_Yassociated_mult_mid[1][ipt]->SetMarkerStyle(25);
		h1d_Yassociated_mult_mid[1][ipt]->SetLineColor(2);
		h1d_Yassociated_mult_mid[1][ipt]->SetLineWidth(2);
		h1d_Yassociated_mult_mid[1][ipt]->SetMarkerColor(2);
		h1d_Yassociated_mult_mid[1][ipt]->Draw("p e0 same");
	}

	{
		TLegend *leg = new TLegend(0.2,0.6,0.65,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(20);
		leg->AddEntry("","PYTHIA8 pp #sqrt{s}=13 TeV","h");
		leg->AddEntry("","1.0<p_{T}<2.0 GeV/c","h");
		leg->AddEntry("","Short range (|#Delta#eta|<1.0)","h");
		leg->AddEntry(""," - Long range (|#Delta#eta|>2.0)","h");
		leg->AddEntry(h1d_Yassociated_mult_mid[0][0],"Defalut","PL");
		leg->AddEntry(h1d_Yassociated_mult_mid[1][0],"String shoving","PL");
		leg->Draw();
	}
	*/



//============================================================//

}
