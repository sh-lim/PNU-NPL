#include "Style.h"

void Draw_cms_yield_subs_2D(){

	gStyle->SetOptStat(0);

	TFile *infile;
		
	const Int_t nfiles = 2;	
	
	string cfigNames1[nfiles] = {"cfig1_cms_dp", "cfig1_cms_ds"};
	string cfigNames2_pre[nfiles] = {"cifg2_pre_cms_dp", "cfig2_pre_cms_ds"};
	string cfigNames2[nfiles] = {"cfig2_cms_dp", "cfig2_cms_ds"};
	string cfigNames3[nfiles] = {"cfig3_cms_dp", "cfig3_cms_ds"};

	//mid rapidity for try000, default pythia for grp000, default shoving for grp 001
	string fileNames[nfiles] = {"outfile_hist_pp13TeV_set00_grp000_try000.root", "outfile_hist_pp13TeV_set00_grp001_try000.root"};

	TCanvas *cfig1[nfiles];
	TCanvas *cfig2_pre[nfiles];
	TCanvas *cfig2[nfiles];
	TCanvas *cfig3[nfiles];

	for(int i=0; i<2; i++){

	infile = new TFile(fileNames[i].c_str(), "read");

	const float const_pi = TMath::Pi();

	const int npt = 1;
	const float ptbin[npt+1] = {1.0, 2.0};

	const int nmult = 12;

	const int nMarker[nmult] = {20, 21, 24, 25};
	const int nColor[nmult] = {1, 2, 4, 8};

	TH2D *h2d_same_mid[nmult][npt];
	TH2D *h2d_mixed_mid[nmult][npt];
	TH2D *h2d_div_mid[nmult][npt];

	TH1D *hntrig_mid;
	TH1D *hntrig_mixed_mid;

	TH1D *h1d_deta_div_mid[nmult][npt];
	TH1D *h1d_dphi_div_mid[nmult][npt];

	TH1D *h1d_dphi_zyam_mid[nmult][npt];

	TF1 *f1d_dphi_mid[nmult][npt];

	TH1D *h1d_Yassociated_pT_mid[nmult];
	TH1D *h1d_Yassociated_mult_mid[npt];

	for (int imult=0; imult<nmult; imult++){
		h1d_Yassociated_pT_mid[imult] = new TH1D(Form("h1d_Yassociated_pT_mid_mult%02d",imult),"",npt,ptbin);
	}

	for (int ipt=0; ipt<npt; ipt++){
		h1d_Yassociated_mult_mid[ipt] = new TH1D(Form("h1d_Yassociated_mult_mid_pt%02d",ipt),"",nmult,0,10*nmult);
	}
	
	hntrig_mid = (TH1D*)infile->Get("hntrig_mid");
	hntrig_mixed_mid = (TH1D*)infile->Get("hntrig_mixed_mid");

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			h2d_same_mid[imult][ipt] = (TH2D*)infile->Get(Form("h2d_same_dphi_deta_m%02d",imult));
			h2d_mixed_mid[imult][ipt] = (TH2D*)infile->Get(Form("h2d_mixed_dphi_deta_m%02d",imult));

			h2d_same_mid[imult][ipt]->RebinX(4);
			h2d_mixed_mid[imult][ipt]->RebinX(4);
			h2d_same_mid[imult][ipt]->RebinY(2);
			h2d_mixed_mid[imult][ipt]->RebinY(2);

			float ntrig_same_mid = hntrig_mid->Integral(hntrig_mid->FindBin(10*imult+0.1), hntrig_mid->FindBin(10*(imult+1)-0.1));
			float ntrig_mixed_mid = hntrig_mixed_mid->Integral(hntrig_mixed_mid->FindBin(10*imult+0.1), hntrig_mixed_mid->FindBin(10*(imult+1)-0.1));

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
			
			h2d_div_mid[imult][ipt] = (TH2D*)h2d_same_mid[imult][ipt]->Clone(Form("h2d_div_dphi_deta_m%02d",imult));
			h2d_div_mid[imult][ipt]->Divide(h2d_mixed_mid[imult][ipt]);
			h2d_div_mid[imult][ipt]->Scale(nnorm_mixed_mid);

//			h2d_div_mid[imult][ipt]->RebinX(4);
//			h2d_div_mid[imult][ipt]->RebinY(4);

			//1D projection, negative eta 
			int etabin_min_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(-5.0+0.001);
			int etabin_max_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(-2.0-0.001);

			h1d_dphi_div_mid[imult][ipt] = (TH1D*)h2d_div_mid[imult][ipt]->ProjectionX(Form("h1d_dphi_div_mid_mult%02d_pt%02d",imult,ipt),etabin_min_mid,etabin_max_mid);	

			//1D projection, positive eta 
			etabin_min_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(+2.0+0.001);
			etabin_max_mid = h2d_div_mid[imult][ipt]->GetYaxis()->FindBin(+5.0-0.001);

			TH1D *htmp_div_mid = (TH1D*)h2d_div_mid[imult][ipt]->ProjectionX(Form("h1d_dphi_div_mid_mult%02d_pt%02d_1",imult,ipt),etabin_min_mid,etabin_max_mid);

			h1d_dphi_div_mid[imult][ipt]->Add(htmp_div_mid);

			float ddeta_mid = h2d_same_mid[imult][ipt]->GetYaxis()->GetBinWidth(1);
			float deta_mid = 6.0;
			h1d_dphi_div_mid[imult][ipt]->Scale(ddeta_mid/deta_mid);
			
			//fit w/ Fourier series
			//f1d_dphi[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x))",-const_pi/2,3*const_pi/2);
			f1d_dphi_mid[imult][ipt] = new TF1("f1","[0]*( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x))",-const_pi/2,1*const_pi/2);
			h1d_dphi_div_mid[imult][ipt]->Fit(f1d_dphi_mid[imult][ipt],"R0Q");

			//ZYAM subtraction
			float zyam = f1d_dphi_mid[imult][ipt]->GetMinimum(-const_pi/2,const_pi/2);
			float zyam_x = f1d_dphi_mid[imult][ipt]->GetMinimumX(-const_pi/2,const_pi/2);
			float Y_associated_mid = 0.0; 
			float Y_associated_mid_err = 0.0; 

			h1d_dphi_zyam_mid[imult][ipt] = (TH1D*)h1d_dphi_div_mid[imult][ipt]->Clone(Form("h1d_dphi_zyam_mid_mult%02d_pt%02d",imult,ipt));
			for (int iphi=0; iphi<h1d_dphi_zyam_mid[imult][ipt]->GetNbinsX(); iphi++){
				float val_mid = h1d_dphi_zyam_mid[imult][ipt]->GetBinContent(iphi+1);
				h1d_dphi_zyam_mid[imult][ipt]->SetBinContent(iphi+1, val_mid-zyam);

				//associated yield |dphi|<1.2
				float dphi_mid = h1d_dphi_zyam_mid[imult][ipt]->GetBinCenter(iphi+1); 
				float ddphi_mid = h1d_dphi_zyam_mid[imult][ipt]->GetBinWidth(iphi+1);

				//if ( fabs(dphi)<1.2 ){
				if ( fabs(dphi_mid)<fabs(zyam_x) ){
					Y_associated_mid += h1d_dphi_zyam_mid[imult][ipt]->GetBinContent(iphi+1)*ddphi_mid;
					Y_associated_mid_err += h1d_dphi_zyam_mid[imult][ipt]->GetBinError(iphi+1)*h1d_dphi_zyam_mid[imult][ipt]->GetBinError(iphi+1)*ddphi_mid*ddphi_mid;
				}
			}

//			h1d_Yassociated_pT[imult]->SetBinContent(ipt+1,Y_associated); 
//			h1d_Yassociated_pT[imult]->SetBinError(ipt+1,sqrt(Y_associated_err)); 

			h1d_Yassociated_mult_mid[ipt]->SetBinContent(imult+1,Y_associated_mid); 
			h1d_Yassociated_mult_mid[ipt]->SetBinError(imult+1,sqrt(Y_associated_mid_err)); 

		}//ipt
	}//imult

#if 0
	cfig1[i] = new TCanvas(cfigNames1[i].c_str(), cfigNames1[i].c_str(), 1.1*300*5, 300*4);
	cfig1[i]->Divide(5,4);

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){
			cfig1[i]->cd(imult*npt+ipt+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);
			gPad->SetPhi(135);

			htmp = (TH1D*)h2d_div_mid[imult][ipt]; 
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
			h2d_div_mid[imult][ipt]->SetMaximum(ymin_mid + (0.8-0.2*ipt)*(ymax_mid-ymin_mid));
			h2d_div_mid[imult][ipt]->Draw("surf1");

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

	cfig2_pre[i] = new TCanvas(cfigNames2_pre[i].c_str(), cfigNames2_pre[i].c_str(), 1.1*300*5, 300*4);
	cfig2_pre[i]->Divide(5,4);


	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			cfig2_pre[i]->cd(imult*npt+ipt+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);

			float ymax_mid = h1d_dphi_div_mid[imult][ipt]->GetMaximum();
			float ymin_mid = h1d_dphi_div_mid[imult][ipt]->GetMinimum();

			htmp = (TH1D*)gPad->DrawFrame(-const_pi/2,ymin_mid-0.05*(ymax_mid-ymin_mid),const_pi*3/2,ymax_mid+0.05*(ymax_mid-ymin_mid));
			SetHistoStyle("|#Delta#phi|","#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}","",14,12);
			htmp->GetYaxis()->SetTitleOffset(7.0);
			htmp->GetXaxis()->SetTitleOffset(5.0);

			h1d_dphi_div_mid[imult][ipt]->SetMarkerStyle(24);
			h1d_dphi_div_mid[imult][ipt]->SetMarkerSize(1.0);
			h1d_dphi_div_mid[imult][ipt]->Draw("same");

			f1d_dphi_mid[imult][ipt]->SetLineWidth(3);
			f1d_dphi_mid[imult][ipt]->SetLineStyle(2);
			f1d_dphi_mid[imult][ipt]->Draw("same");

			float zyam_x = f1d_dphi_mid[imult][ipt]->GetMinimumX(-const_pi/2,const_pi/2);

			TLegend *leg = new TLegend(0.25,0.73,0.65,0.95);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextFont(43);
			leg->SetTextSize(14);
			leg->AddEntry("","Pythia8 pp 13 TeV","h");
			leg->AddEntry("",Form("%d#leqN_{trk}<%d",int(10*imult),int(10*(imult+1))),"h");
			leg->AddEntry("",Form("%g<p_{T}<%g GeV/c",ptbin[ipt],ptbin[ipt+1]),"h");
			leg->AddEntry("",Form("#Delta #phi_{ZYAM}=%4.2f",fabs(zyam_x)),"h");
			leg->Draw();

		}
	}

	cfig2[i] = new TCanvas(cfigNames2[i].c_str(), cfigNames2[i].c_str(), 1.1*300*5, 300*4);
	cfig2[i]->Divide(5,4);

	for (int imult=0; imult<nmult; imult++){
		for (int ipt=0; ipt<npt; ipt++){

			cfig2[i]->cd(imult*npt+ipt+1);
			SetPadStyle();
			gPad->SetLeftMargin(0.23);

			float ymax_mid = h1d_dphi_zyam_mid[imult][ipt]->GetMaximum();
			float ymin_mid = h1d_dphi_zyam_mid[imult][ipt]->GetMinimum();

			htmp = (TH1D*)gPad->DrawFrame(-const_pi/2,-0.05*ymax_mid,const_pi*3/2,1.05*ymax_mid);
			SetHistoStyle("|#Delta#phi|","#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi} - C_{ZYAM}","",14,12);
			htmp->GetYaxis()->SetTitleOffset(7.0);
			htmp->GetXaxis()->SetTitleOffset(5.0);

			h1d_dphi_zyam_mid[imult][ipt]->SetMarkerStyle(24);
			h1d_dphi_zyam_mid[imult][ipt]->SetMarkerSize(1.0);
			h1d_dphi_zyam_mid[imult][ipt]->Draw("same");

			TLegend *leg = new TLegend(0.25,0.78,0.65,0.95);
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
#endif
//	cfig3[i] = new TCanvas(cfigNames3[i].c_str(), cfigNames3[i].c_str(),1.1*2*400, 400);
//	cfig3[i]->Divide(2,1);

	cfig3[i] = new TCanvas(cfigNames3[i].c_str(), cfigNames3[i].c_str(),1.1*1*400, 400);
/*
	cfig3->cd(1);
	SetPadStyle();

	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,4,0.05);
	SetHistoStyle("p_{T} (GeV/c)","Associated yield/(GeV/c)","",20,16);

	{
		TLegend *leg = new TLegend(0.2,0.65,0.65,0.95);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextFont(43);
		leg->SetTextSize(18);
		leg->AddEntry("","Pythia8 pp 13 TeV","h");

		for (int imult=0; imult<nmult; imult++){
			h1d_Yassociated_pT[imult]->SetMarkerStyle(nMarker[imult]);
			h1d_Yassociated_pT[imult]->SetLineColor(nColor[imult]);
			h1d_Yassociated_pT[imult]->SetMarkerColor(nColor[imult]);
			h1d_Yassociated_pT[imult]->Draw("p same");
			leg->AddEntry(h1d_Yassociated_pT[imult],Form("%d#leqN_{trk}<%d",int(multbin[imult]),int(multbin[imult+1])),"PL");
		}
		leg->Draw();
	}
*/
	cfig3[i]->cd(2);
	
	SetPadStyle();

	htmp = (TH1D*)gPad->DrawFrame(0,-0.01,120,0.05);

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
	}
	}
}

