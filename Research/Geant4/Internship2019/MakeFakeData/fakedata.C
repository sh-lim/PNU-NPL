void fakedata(){
  TString dir = "./";
  dir.Append("/FakeData/");
  dir.ReplaceAll("/./","/");
  TTree *T = new TTree("T","Fake Data");
  Float_t Ep, dE;
  int Eps[9] = {1, 2, 3, 4, 5, 10, 25, 50, 100};
  T->Branch("Ep",&Ep);
  T->Branch("dE",&dE);
  char line[10];
  FILE *in;
  Ep=0.1;
  in=fopen(Form("%sSi_1cm_energy_0.1_GeV.txt",dir.Data()), "r");
  while (fgets(line,10,in)) {
     sscanf(&line[0],"%f", &dE);
     T->Fill();
  }
  int i;
  for(i=0;i<9;i++){
    Ep = Eps[i];
    in=fopen(Form("%sSi_1cm_energy_%d_GeV.txt",dir.Data(), int(Ep)), "r");
    while (fgets(line,10,in)) {
       sscanf(&line[0],"%f", &dE);
       T->Fill();
    }
  }
  int s, o;
TH1F *hEp[10];
TF1 *fLandau[10];
hEp[0] = new TH1F("Ep0.1GeV", "Ep distribution",200,0,100);
int k[10]={1, 1, 2, 3, 4, 5, 10, 25, 50, 100};
for (s=1; s<10; s++)
{
  o=k[s];
  hEp[s]=new TH1F(Form("Ep%dGeV", o), "Ep distribution",200,0,100);
}
for (s=1; s<10; s++)
{
hEp[s]->GetXaxis()->SetRange(0, 100);
}
   T->SetBranchAddress("Ep",&Ep);
   T->SetBranchAddress("dE",&dE);
   /*TH1F *hEp0= new TH1F("Ep0.1GeV","Ep distribution",100,-3,100);
   TH1F *hEp1= new TH1F("Ep1GeV","Ep distribution",100,-3,100);
   TH1F *hEp2= new TH1F("Ep2GeV","Ep distribution",100,-3,100);
   TH1F *hEp3= new TH1F("Ep3GeV","Ep distribution",100,-3,100);
   TH1F *hEp4= new TH1F("Ep4GeV","Ep distribution",100,-3,100);
   TH1F *hEp5= new TH1F("Ep5GeV","Ep distribution",100,-3,100);
   TH1F *hEp6= new TH1F("Ep10GeV","Ep distribution",100,-3,100);
   TH1F *hEp7= new TH1F("Ep25GeV","Ep distribution",100,-3,100);
   TH1F *hEp8= new TH1F("Ep50GeV","Ep distribution",100,-3,100);
   TH1F *hEp9= new TH1F("Ep100GeV","Ep distribution",100,-3,100);
*/
   Long64_t nentries = T->GetEntries();
   for (Long64_t i=0;i<nentries;i++) {
     T->GetEntry(i);
     double e = 0.001;
     if (abs(Ep-0.1)<e)
       hEp[0]->Fill(dE);
     if (abs(Ep-1)<e)
       hEp[1]->Fill(dE);
     if (abs(Ep-2)<e)
       hEp[2]->Fill(dE);
     if (abs(Ep-3)<e)
       hEp[3]->Fill(dE);
     if (abs(Ep-4)<e)
       hEp[4]->Fill(dE);
     if (abs(Ep-5)<e)
       hEp[5]->Fill(dE);
     if (abs(Ep-10)<e)
       hEp[6]->Fill(dE);
     if (abs(Ep-25)<e)
       hEp[7]->Fill(dE);
     if (abs(Ep-50)<e)
       hEp[8]->Fill(dE);
     if (abs(Ep-100)<e)
       hEp[9]->Fill(dE);
   }
//   TF1 *landau1 = new TF1 ("landau1". "TMath::Landau(x,[0],[1],0)",-5,100);")
//   landau1->SetParameters(,);
int j;
TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);


 for (j=1; j<11; j++)
 {
	 fLandau[j-1] = new TF1("landau","landau",0,100);
   hEp[j-1]->Fit(fLandau[j-1], "0");
 }


/*hEp[0]->Fit("landau","","",2, 80);
   TF1 *f=hEp[0]->GetFunction("landau");
*/
  c1->Divide(5,2);
   for (j=1; j<11; j++)
   {
     c1->cd(j);
     hEp[j-1]->Draw();
		 fLandau[j-1]->Draw("same");
   }
    c1->SaveAs("c1.jpeg");
//    printf("NDF = %d\n", f->GetNDF());
  //  printf("CS = %f\n", f->GetChisquare());
return;
for (j=1; j<11; j++)
{
 TF1 *f = hEp[j-1]->GetFunction("landau");
 printf("NDF = %d\n", f->GetNDF());
 printf("Chisquare = %f\n", f->GetChisquare());
}
/*
for (j=1; j<11; j++)
{
TF1 *f = hEp[j-1]->GetFunction("landau");
f->GetNDF()
f->GetChisquare()

}*/
 T->Print();
}
