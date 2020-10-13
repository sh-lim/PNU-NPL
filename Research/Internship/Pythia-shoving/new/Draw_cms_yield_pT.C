#include "Style.h"

void Draw_cms_yield_pT(){

	gStyle->SetOptStat(0);

	TFile *infile;
		
	const Int_t nfiles = 2;	

	string cfigNames1[nfiles] = {"cfig1_cms_dp_pT","cifg1_cms_ds_pT"};
	string cfigNames2_pre[nfiles] = {"cfig2_pre_cms_dp_pT","cifg2_pre_cms_ds_pT"};
	string cfigNames2[nfiles] = {"cfig2_cms_dp_pT","cfig2_cms_ds_pT"};

	string fileNames[nfiles] = {"outfile_hist_pp13TeV_set00_grp003_2_pT_try000.root","outfile_hist_pp13TeV_set00_grp004_2_pT_try000.root"};

	TCanvas *cfig1[nfiles];
	TCanvas *cfig2_pre[nfiles];
	TCanvas *cfig2[nfiles];
	TCanvas *cfig3;
	TCanvas *cfig4;

	const float const_pi = TMath::Pi();

	const int npt = 8;
	const float ptbin[npt+1] = {0.2, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 6.0};

	const int nmult = 3;
	const float multbin[nmult+1] = {0, 10, 20, 100};

	const int nMarker[npt] = {20, 21, 24, 25, 26, 27, 28};
	const int nColor[npt] = {1, 2, 4, 4, 5, 6, 8};

	TH2D *h2d_same_mid[nmult][npt];
	TH2D *h2d_mixed_mid[nmult][npt];
	TH2D *h2d_div_mid[nmult][npt];

	TH1D *hntrig_same_mid[nmult];
	TH1D *hntrig_mixed_mid[nmult];

	TH1D *h1d_deta_div_long_mid[nmult][npt][2];
	TH1D *h1d_deta_div_short_mid[nmult][npt][2];

	TH1D *h1d_dphi_div_long_mid[nmult][npt][2];
	TH1D *h1d_dphi_div_short_mid[nmult][npt][2];
	TH1D *h1d_dphi_div_sub_mid[nmult][npt];

	TH1D *h1d_dphi_zyam_long_mid[nmult][npt];
	TH1D *h1d_dphi_zyam_sub_mid[nmult][npt];

	TF1 *f1d_dphi_short_mid[nmult][npt];
	TF1 *f1d_dphi_long_mid[nmult][npt];
	TF1 *f1d_dphi_sub_mid[nmult][npt];

	TH1D *h1d_Yassociated_pT_mid[nfiles][nmult];
	TH1D *h1d_Yassociated_pT_jet_mid[nfiles][nmult];

	for (int i=0; i<nfiles; i++){

	infile = new TFile(fileNames[i].c_str(), "read");

	for (int imult=0; imult<nmult; imult++){
		h1d_Yassociated_pT_mid[i][imult] = new TH1D(Form("h1d_Yassociated_pT_mid_mult%02d",imult),"",npt,ptbin);
		h1d_Yassociated_pT_jet_mid[i][imult] = new TH1D(Form("h1d_Yassociated_pT_jet_mid_mult%02d",imult),"",npt,ptbin);
	}


	for (int imult=0; imult<nmult; imult++){
		hntrig_same_mid[imult] = (TH1D*)infile->Get(Form("hntrig_same_mult%02d",imult));
		hntrig_mixed_mid[imult] = (TH1D*)infile->Get(Form("hntrig_mixed_mult%02d",imult));
	
	for (int ipt=0; ipt<npt; ipt++){

			h2d_same_mid[imult][ipt] = (TH2D*)infile->Get(Form("h2d_same_dphi_deta_mult%02d_pt%02d",imult,ipt));
			h2d_mixed_mid[imult][ipt] = (TH2D*)infile->Get(Form("h2d_mixed_dphi_deta_mult%02d_pt%02d",imult,ipt));

			h2d_same_mid[imult][ipt]->RebinX(6);
			h2d_mixed_mid[imult][ipt]->RebinX(6);
			h2d_same_mid[imult][ipt]->RebinY(2);
			h2d_mixed_mid[imult][ipt]->RebinY(2);

			float ntrig_same_mid= hntrig_same_mid[imult]->Integral(hntrig_same_mid[imult]->FindBin(ptbin[ipt]+0.1), hntrig_same_mid[imult]->FindBin(ptbin[ipt+1]-0.1));
			float ntrig_mixed_mid = hntrig_mixed_mid[imult]->Integral(hntrig_mixed_mid[imult]->FindBin(ptbin[ipt]+0.1), hntrig_mixed_mid[imult]->FindBin(ptbin[ipt+1]-0.1));

			float nnorm_mixed_mid = h2d_mixed_mid[imult][ipt]->GetBinContent(h2d_mixed_mid[imult][ipt]->FindBin(0,0));
			float nscale_same_mid = ntrig_same_mid;
			float nscale_mixed_mid = ntrig_mixed_mid;

			nnorm_mixed_mid /= ntrig_mixed_mid;
			nnorm_mixed_mid /= h2d_mixed_mid[imult][ipt]->GetXaxis()->GetBinWidth(1);
			nnorm_mixed_mid /= h2d_mixed_mid[imult][ipt]->GetYaxis()->GetBinWidth(1);

			nscale_same_mid *= h2d_same_mid[imult][ipt]->GetXaxis()->GetBinWidth(1);
			nscale_same_mid *= h2d_same_mid[imult][ipt]->GetYaxis()->GetBinWidth(1);

			nscale_mixed_mid *= h2d_mixed_mid[imult][ipt]->GetXaxis()->GetBinWidth(1);
			nscale_mixed_mid *= h2d_mixed_mid[imult][ipt]->GetYaxis()->GetBinWidth(1);

			h2d_same_mid[imult][ipt]->Scale(1./nscale_same_mid);
			h2d_mixed_mid[imult][ipt]->Scale(1./nscale_mixed_mid);
	
			h2d_div_mid[imult][ipt] = (TH2D*)h2d_same_mid[imult][ipt]->Clone(Form("h2d_div_dphi_deta_mult%02d_pt%02d",imult,ipt));
			h2d_div_mid[imult][ipt]->Divide(h2d_mixed_mid[imult][ipt]);
			h2d_div_mid[imult][ipt]->Scale(nnorm_mixed_mid);

			//1D projection, negative eta 
			int etabin_min_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(-5.0+0.001);
			int etabin_max_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(-2.0-0.001);

			h1d_dphi_div_long_mid[imult][ipt][0] = (TH1D*)h2d_div_mid[imult][ipt]->ProjectionX(Form("h1d_dphi_div_long_mid_mult%02d_pt%02d",imult,ipt),etabin_min_mid,etabin_max_mid);

			//1D projection, positive eta 
			etabin_min_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(+2.0+0.001);
			etabin_max_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(+5.0-0.001);

			h1d_dphi_div_long_mid[imult][ipt][1] = (TH1D*)h2d_div_mid[imult][ipt]->ProjectionX(Form("h1d_dphi_div_long_mid_mult%02d_pt%02d_1",imult,ipt),etabin_min_mid,etabin_max_mid);

			h1d_dphi_div_long_mid[imult][ipt][0]->Add(h1d_dphi_div_long_mid[imult][ipt][1]);
			h1d_dphi_div_long_mid[imult][ipt][0]->Scale(1./6.0*h2d_div_mid[imult][ipt]->GetYaxis()->GetBinWidth(1));

			etabin_min_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(-1.0+0.0001);
			etabin_max_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(+1.0+0.0001);

			h1d_dphi_div_short_mid[imult][ipt][0] = (TH1D*)h2d_div_mid[imult][ipt]->ProjectionX(Form("h1d_dphi_div_short_mid_mult%02d_pt%02d",imult,ipt),etabin_min_mid,etabin_max_mid);
			h1d_dphi_div_short_mid[imult][ipt][0]->Scale(1./2.0*h2d_div_mid[imult][ipt]->GetYaxis()->GetBinWidth(1));

			//f1d_dphi_short_mid[imult][ipt] = new TF1("f1","[0]*( 1+ 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) + 2*[4]*cos(4*x) + 2*[5]*cos(5*x))",-const_pi/2,3*const_pi/2);
			//h1d_dphi_div_short_mid[imult][ipt][0]->Fit(f1d_dphi_short_mid[imult][ipt],"R0Q");

			f1d_dphi_long_mid[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) + 2*[4]*cos(4*x) + 2*[5]*cos(5*x))",-const_pi/2,3*const_pi/2);
			h1d_dphi_div_long_mid[imult][ipt][0]->Fit(f1d_dphi_long_mid[imult][ipt],"R0Q");

			h1d_dphi_div_sub_mid[imult][ipt] = (TH1D*)h1d_dphi_div_short_mid[imult][ipt][0]->Clone(Form("h1d_dphi_div_sub_mid_%d_%d",imult,ipt));
			h1d_dphi_div_sub_mid[imult][ipt]->Add(h1d_dphi_div_long_mid[imult][ipt][0], -1);
			
			f1d_dphi_sub_mid[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x))",0.6,3*const_pi/2);
			h1d_dphi_div_sub_mid[imult][ipt]->Fit(f1d_dphi_sub_mid[imult][ipt],"R0Q");

//return;
			//ZYAM subtraction
			float zyam = f1d_dphi_long_mid[imult][ipt]->GetMinimum(-const_pi/2,3*const_pi/2);
			float zyam_x = f1d_dphi_long_mid[imult][ipt]->GetMinimumX(-const_pi/2,3*const_pi/2);
			float Y_associated_mid = 0.0; 
			float Y_associated_mid_err = 0.0; 

			h1d_dphi_zyam_long_mid[imult][ipt] = (TH1D*)h1d_dphi_div_long_mid[imult][ipt][0]->Clone(Form("h1d_dphi_zyam_long_mid_mult%02d_pt%02d",imult,ipt));

			for (int iphi=0; iphi<h1d_dphi_zyam_long_mid[imult][ipt]->GetNbinsX(); iphi++){
				float val_mid = h1d_dphi_zyam_long_mid[imult][ipt]->GetBinContent(iphi+1);
				h1d_dphi_zyam_long_mid[imult][ipt]->SetBinContent(iphi+1, val_mid-zyam);

				//associated yield |dphi|<1.2
				float dphi_mid = h1d_dphi_zyam_long_mid[imult][ipt]->GetBinCenter(iphi+1); 
				float ddphi_mid = h1d_dphi_zyam_long_mid[imult][ipt]->GetBinWidth(iphi+1);
				
				//if ( fabs(dphi_mid)<1.2 ){
				if ( fabs(dphi_mid)<fabs(zyam_x) ){
					Y_associated_mid += h1d_dphi_zyam_long_mid[imult][ipt]->GetBinContent(iphi+1)*ddphi_mid;
					Y_associated_mid_err += h1d_dphi_zyam_long_mid[imult][ipt]->GetBinError(iphi+1)*h1d_dphi_zyam_long_mid[imult][ipt]->GetBinError(iphi+1)*ddphi_mid*ddphi_mid;
				}
			}

			float dpt_mid = ptbin[ipt+1] - ptbin[ipt];
			h1d_Yassociated_pT_mid[i][imult]->SetBinContent(ipt+1,Y_associated_mid/dpt_mid); 
			h1d_Yassociated_pT_mid[i][imult]->SetBinError(ipt+1,sqrt(Y_associated_mid_err)/dpt_mid); 

			zyam = f1d_dphi_sub_mid[imult][ipt]->GetMinimum(1,3*const_pi/2);
			zyam_x = f1d_dphi_sub_mid[imult][ipt]->GetMinimumX(1,3*const_pi/2);
			Y_associated_mid = 0.0; 
			Y_associated_mid_err = 0.0; 

			h1d_dphi_zyam_sub_mid[imult][ipt] = (TH1D*)h1d_dphi_div_sub_mid[imult][ipt]->Clone(Form("h1d_dphi_zyam_sub_mid_mult%02d_pt%02d",imult,ipt));

			for (int iphi=0; iphi<h1d_dphi_zyam_sub_mid[imult][ipt]->GetNbinsX(); iphi++){
				float val_mid = h1d_dphi_zyam_sub_mid[imult][ipt]->GetBinContent(iphi+1);
				h1d_dphi_zyam_sub_mid[imult][ipt]->SetBinContent(iphi+1, val_mid-zyam);

				//associated yield |dphi|<1.2
				float dphi_mid = h1d_dphi_zyam_sub_mid[imult][ipt]->GetBinCenter(iphi+1); 
				float ddphi_mid = h1d_dphi_zyam_sub_mid[imult][ipt]->GetBinWidth(iphi+1);
				
				if ( fabs(dphi_mid)<1.5 ){
				//if ( fabs(dphi_mid)<fabs(zyam_x) ){
					Y_associated_mid += h1d_dphi_zyam_sub_mid[imult][ipt]->GetBinContent(iphi+1)*ddphi_mid;
					Y_associated_mid_err += h1d_dphi_zyam_sub_mid[imult][ipt]->GetBinError(iphi+1)*h1d_dphi_zyam_sub_mid[imult][ipt]->GetBinError(iphi+1)*ddphi_mid*ddphi_mid;
				}
			}

			h1d_Yassociated_pT_jet_mid[i][imult]->SetBinContent(ipt+1,Y_associated_mid/dpt_mid); 
			h1d_Yassociated_pT_jet_mid[i][imult]->SetBinError(ipt+1,sqrt(Y_associated_mid_err)/dpt_mid); 


			//cout << imult << " " << ipt << " " << h1d_Yassociated_pT_mid[i][imult]->GetBinContent(ipt+1) << endl;
		}//ipt
	}//imult

	cfig1[i] = new TCanvas(cfigNames1[i].c_str(), cfigNames1[i].c_str(), 1.1*250*8, 250*2);
	cfig1[i]->Divide(8,3);

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){
			cfig1[i]->cd(imult*npt+ipt+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);
			gPad->SetPhi(135);

			htmp = (TH1D*)h2d_same_mid[imult][ipt]; 
			SetHistoStyle("","","",14,12);
			h2d_div_mid[imult][ipt]->SetAxisRange(-4.0+0.01,4.0-0.01,"Y");
			h2d_div_mid[imult][ipt]->GetYaxis()->SetTitle("|#Delta#eta|");
			h2d_div_mid[imult][ipt]->GetYaxis()->CenterTitle();
			h2d_div_mid[imult][ipt]->GetYaxis()->SetTitleOffset(5.);
			h2d_div_mid[imult][ipt]->GetXaxis()->SetTitle("|#Delta#phi|");
			h2d_div_mid[imult][ipt]->GetXaxis()->CenterTitle();
			h2d_div_mid[imult][ipt]->GetXaxis()->SetTitleOffset(5.0);
			h2d_div_mid[imult][ipt]->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}");
			h2d_div_mid[imult][ipt]->GetZaxis()->CenterTitle();
			h2d_div_mid[imult][ipt]->GetZaxis()->SetTitleOffset(7.0);

			float ymax_mid = h2d_div_mid[imult][ipt]->GetMaximum();
			float ymin_mid = h2d_div_mid[imult][ipt]->GetMinimum();
			//h2d_div_mid[imult][ipt]->SetMaximum(ymin_mid + (0.8-0.2*ipt)*(ymax_mid-ymin_mid));
			h2d_div_mid[imult][ipt]->Draw("surf1");

			TLegend *leg = new TLegend(0.05,0.8,0.5,0.98);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextFont(43);
			leg->SetTextSize(14);
			leg->AddEntry("","PYTHIA8 pp #sqrt{s}=13 TeV","h");
			leg->AddEntry("",Form("%d#leqN_{trk}<%d",int(multbin[imult]),int(multbin[imult+1])),"h");
			leg->AddEntry("",Form("%g<p_{T}<%g GeV/c",ptbin[ipt],ptbin[ipt+1]),"h");
			//leg->Draw();
		}
	}

	//continue;

	cfig2_pre[i] = new TCanvas(cfigNames2_pre[i].c_str(), cfigNames2_pre[i].c_str(), 1.1*250*8, 250*2);
	cfig2_pre[i]->Divide(8,3);

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			cfig2_pre[i]->cd(imult*npt+ipt+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);
			gPad->SetRightMargin(0.01);

			float ymax_mid = TMath::Max(h1d_dphi_div_short_mid[imult][ipt][0]->GetMaximum(), h1d_dphi_div_long_mid[imult][ipt][0]->GetMaximum());
			float ymin_mid = h1d_dphi_div_sub_mid[imult][ipt]->GetMinimum();

			htmp = (TH1D*)gPad->DrawFrame(-const_pi/2,0,const_pi*3/2,1.1*ymax_mid);
			SetHistoStyle("|#Delta#phi|","#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}","",14,12);
			htmp->GetYaxis()->SetTitleOffset(5.0);
			htmp->GetXaxis()->SetTitleOffset(2.0);

			h1d_dphi_div_short_mid[imult][ipt][0]->SetMarkerStyle(24);
			h1d_dphi_div_short_mid[imult][ipt][0]->SetMarkerSize(0.8);
			h1d_dphi_div_short_mid[imult][ipt][0]->SetMarkerColor(1);
			h1d_dphi_div_short_mid[imult][ipt][0]->Draw("same");

			h1d_dphi_div_sub_mid[imult][ipt]->SetMarkerStyle(24);
			h1d_dphi_div_sub_mid[imult][ipt]->SetMarkerSize(0.8);
			h1d_dphi_div_sub_mid[imult][ipt]->SetMarkerColor(4);
			h1d_dphi_div_sub_mid[imult][ipt]->Draw("same");

			h1d_dphi_div_long_mid[imult][ipt][0]->SetMarkerStyle(24);
			h1d_dphi_div_long_mid[imult][ipt][0]->SetMarkerSize(0.8);
			h1d_dphi_div_long_mid[imult][ipt][0]->SetMarkerColor(2);
			h1d_dphi_div_long_mid[imult][ipt][0]->Draw("same");

			f1d_dphi_sub_mid[imult][ipt]->SetLineWidth(3);
			f1d_dphi_sub_mid[imult][ipt]->SetLineStyle(2);
			f1d_dphi_sub_mid[imult][ipt]->SetLineColor(4);
			f1d_dphi_sub_mid[imult][ipt]->Draw("same");

			f1d_dphi_long_mid[imult][ipt]->SetLineWidth(3);
			f1d_dphi_long_mid[imult][ipt]->SetLineStyle(2);
			f1d_dphi_long_mid[imult][ipt]->SetLineColor(2);
			f1d_dphi_long_mid[imult][ipt]->Draw("same");

			float zyam_x = f1d_dphi_sub_mid[imult][ipt]->GetMinimumX(-const_pi/2,const_pi/2);

			TLegend *leg = new TLegend(0.25,0.73,0.65,0.95);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextFont(43);
			leg->SetTextSize(14);
			leg->AddEntry("","Pythia8 pp 13 TeV","h");
			leg->AddEntry("",Form("%d#leqN_{trk}<%d",int(multbin[imult]),int(multbin[imult+1])),"h");
			leg->AddEntry("",Form("%g<p_{T}<%g GeV/c",ptbin[ipt],ptbin[ipt+1]),"h");
			leg->AddEntry("",Form("#Delta #phi_{ZYAM}=%4.2f",fabs(zyam_x)),"h");
			//leg->Draw();

		}
	}

	//continue;

	cfig2[i] = new TCanvas(cfigNames2[i].c_str(), cfigNames2[i].c_str(), 1.1*250*8, 250*2);
	cfig2[i]->Divide(8,3);
	
	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			cfig2[i]->cd(imult*npt+ipt+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);
			gPad->SetRightMargin(0.01);

			float ymax_mid = h1d_dphi_zyam_sub_mid[imult][ipt]->GetMaximum();
			float ymin_mid = h1d_dphi_zyam_long_mid[imult][ipt]->GetMinimum();

			htmp = (TH1D*)gPad->DrawFrame(-const_pi/2,-0.1*ymax_mid,const_pi*3/2,1.05*ymax_mid);
			SetHistoStyle("|#Delta#phi|","#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi} - C_{ZYAM}","",14,12);
			htmp->GetYaxis()->SetTitleOffset(5.0);
			htmp->GetXaxis()->SetTitleOffset(2.0);

			h1d_dphi_zyam_sub_mid[imult][ipt]->SetMarkerStyle(24);
			h1d_dphi_zyam_sub_mid[imult][ipt]->SetMarkerSize(0.8);
			h1d_dphi_zyam_sub_mid[imult][ipt]->SetMarkerColor(4);
			h1d_dphi_zyam_sub_mid[imult][ipt]->SetLineColor(4);
			h1d_dphi_zyam_sub_mid[imult][ipt]->Draw("same");

			h1d_dphi_zyam_long_mid[imult][ipt]->SetMarkerStyle(24);
			h1d_dphi_zyam_long_mid[imult][ipt]->SetMarkerSize(0.8);
			h1d_dphi_zyam_long_mid[imult][ipt]->SetMarkerColor(2);
			h1d_dphi_zyam_long_mid[imult][ipt]->SetLineColor(2);
			h1d_dphi_zyam_long_mid[imult][ipt]->Draw("same");

			TLegend *leg = new TLegend(0.25,0.78,0.65,0.95);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextFont(43);
			leg->SetTextSize(14);
			leg->AddEntry("","Pythia8 pp 13 TeV","h");
			leg->AddEntry("",Form("%d#leqN_{trk}<%d",int(multbin[imult]),int(multbin[imult+1])),"h");
			leg->AddEntry("",Form("%g<p_{T}<%g GeV/c",ptbin[ipt],ptbin[ipt+1]),"h");
			//leg->Draw();

		}
	}
	}//ifile

//	return;

#if 1
	cfig3 = new TCanvas("cfig3_cms_pT","cfig_cms_pT",1.1*2*500, 500);
	cfig3->Divide(2,1);

	cfig3->cd(1);
	SetPadStyle();
	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,4,0.05);
	SetHistoStyle("p_{T} (GeV/c)","Associated yield/(GeV/c)","",20,16);


	for (int imult=0; imult<nmult; imult++){
		std::cout<<h1d_Yassociated_pT_mid[0][imult]<<std::endl;
		h1d_Yassociated_pT_mid[0][imult]->SetMarkerStyle(21);
		h1d_Yassociated_pT_mid[0][imult]->SetLineColor(nColor[imult]);
		h1d_Yassociated_pT_mid[0][imult]->SetLineWidth(2);
		h1d_Yassociated_pT_mid[0][imult]->SetMarkerColor(nColor[imult]);
		h1d_Yassociated_pT_mid[0][imult]->Draw("p e0 same");
	}

	cfig3->cd(2);
	SetPadStyle();
	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,4,0.05);
	SetHistoStyle("p_{T} (GeV/c)","Associated yield/(GeV/c)","",20,16);
	for (int imult=0; imult<nmult; imult++){
		std::cout<<h1d_Yassociated_pT_mid[1][imult]<<std::endl;
		h1d_Yassociated_pT_mid[1][imult]->SetMarkerStyle(24);
		h1d_Yassociated_pT_mid[1][imult]->SetLineColor(nColor[imult]);
		h1d_Yassociated_pT_mid[1][imult]->SetLineWidth(2);
		h1d_Yassociated_pT_mid[1][imult]->SetMarkerColor(nColor[imult]);
		h1d_Yassociated_pT_mid[1][imult]->Draw("p e0 same");
	}
	
	{
		TLegend *leg = new TLegend(0.2,0.65,0.65,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(18);
		leg->AddEntry("","Pythia8 pp #sqrt{s}=13 TeV","h");
		leg->AddEntry("","Multiplicity>100","h");
		leg->AddEntry("","Short range (|#Delta#eta|<1.0)","h");
		leg->AddEntry(""," - Long range (|#Delta#eta|>2.0)","h");
		leg->AddEntry(h1d_Yassociated_pT_mid[0][0],"Default","PL");
		leg->AddEntry(h1d_Yassociated_pT_mid[1][0],"String shoving","PL");
		//leg->Draw();
	}

	cfig4 = new TCanvas("cfig4_cms_pT","cfig4_cms_pT",1.1*2*500, 500);
	cfig4->Divide(2,1);

	cfig4->cd(1);
	SetPadStyle();
	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,4,0.5);
	SetHistoStyle("p_{T} (GeV/c)","Associated yield/(GeV/c)","",20,16);

	for (int imult=0; imult<nmult; imult++){
		std::cout<<h1d_Yassociated_pT_jet_mid[0][imult]<<std::endl;
		h1d_Yassociated_pT_jet_mid[0][imult]->SetMarkerStyle(21);
		h1d_Yassociated_pT_jet_mid[0][imult]->SetLineColor(nColor[imult]);
		h1d_Yassociated_pT_jet_mid[0][imult]->SetLineWidth(2);
		h1d_Yassociated_pT_jet_mid[0][imult]->SetMarkerColor(nColor[imult]);
		h1d_Yassociated_pT_jet_mid[0][imult]->Draw("p e0 same");
	}

	cfig4->cd(2);
	SetPadStyle();
	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,4,0.5);
	SetHistoStyle("p_{T} (GeV/c)","Associated yield/(GeV/c)","",20,16);

	for (int imult=0; imult<nmult; imult++){
		std::cout<<h1d_Yassociated_pT_jet_mid[1][imult]<<std::endl;
		h1d_Yassociated_pT_jet_mid[1][imult]->SetMarkerStyle(24);
		h1d_Yassociated_pT_jet_mid[1][imult]->SetLineColor(nColor[imult]);
		h1d_Yassociated_pT_jet_mid[1][imult]->SetLineWidth(2);
		h1d_Yassociated_pT_jet_mid[1][imult]->SetMarkerColor(nColor[imult]);
		h1d_Yassociated_pT_jet_mid[1][imult]->Draw("p e0 same");
	}
	
	{
		TLegend *leg = new TLegend(0.2,0.65,0.65,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(18);
		leg->AddEntry("","Pythia8 pp #sqrt{s}=13 TeV","h");
		leg->AddEntry("","Multiplicity>100","h");
		leg->AddEntry("","Short range (|#Delta#eta|<1.0)","h");
		leg->AddEntry(""," - Long range (|#Delta#eta|>2.0)","h");
		leg->AddEntry(h1d_Yassociated_pT_mid[0][0],"Default","PL");
		leg->AddEntry(h1d_Yassociated_pT_mid[1][0],"String shoving","PL");
		//leg->Draw();
	}
#endif


/*	cfig3[i]->cd(2);
	SetPadStyle();

	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,150,0.05);
	SetHistoStyle("Multiplicity","Associated yield/(GeV/c)","",20,16);

	{
		TLegend *leg = new TLegend(0.2,0.65,0.65,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(18);
		leg->AddEntry("","Pythia8 pp 13 TeV","h");

		for (int ipt=0; ipt<npt; ipt++){
			h1d_Yassociated_mult_mid[ipt]->SetMarkerStyle(nMarker[ipt]);
			h1d_Yassociated_mult_mid[ipt]->SetLineColor(nColor[ipt]);
			h1d_Yassociated_mult_mid[ipt]->SetMarkerColor(nColor[ipt]);
			h1d_Yassociated_mult_mid[ipt]->Draw("p e0 same");
			leg->AddEntry(h1d_Yassociated_mult_mid[ipt],Form("%g<p_{T}<%g (GeV/c)",ptbin[ipt],ptbin[ipt+1]),"PL");
		}
		leg->Draw();

	}*/

//	}//ifile
	}//void

