void fakedatatest1(){
  //TString dir = "/home/jryu/Desktop";
  TString dir = "./";
  dir.Append("/FakeData/");
  dir.ReplaceAll("/./","/");
  auto T = new TTree("T","Fake Data");
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

   T->SetBranchAddress("Ep",&Ep);
   T->SetBranchAddress("dE",&dE);
   TH1F *hEp0= new TH1F("Ep0.1GeV","Ep distribution",100,-3,100);
   TH1F *hEp1= new TH1F("Ep1GeV","Ep distribution",100,-3,100);
   TH1F *hEp2= new TH1F("Ep2GeV","Ep distribution",100,-3,100);
   TH1F *hEp3= new TH1F("Ep3GeV","Ep distribution",100,-3,100);
   TH1F *hEp4= new TH1F("Ep4GeV","Ep distribution",100,-3,100);
   TH1F *hEp5= new TH1F("Ep5GeV","Ep distribution",100,-3,100);
   TH1F *hEp6= new TH1F("Ep10GeV","Ep distribution",100,-3,100);
   TH1F *hEp7= new TH1F("Ep25GeV","Ep distribution",100,-3,100);
   TH1F *hEp8= new TH1F("Ep50GeV","Ep distribution",100,-3,100);
   TH1F *hEp9= new TH1F("Ep100GeV","Ep distribution",100,-3,100);
   Long64_t nentries = T->GetEntries();
   for (Long64_t i=0;i<nentries;i++) {
     T->GetEntry(i);
     double e = 0.001;
     if (abs(Ep-0.1)<e)
       hEp0->Fill(dE);
     if (abs(int(Ep-1))<e)
       hEp1->Fill(dE);
     if (abs(int(Ep-2))<e)
       hEp2->Fill(dE);
     if (abs(int(Ep-3))<e)
       hEp3->Fill(dE);
     if (abs(int(Ep-4))<e)
       hEp4->Fill(dE);
     if (abs(int(Ep-5))<e)
       hEp5->Fill(dE);
     if (abs(int(Ep-10))<e)
       hEp6->Fill(dE);
     if (abs(int(Ep-25))<e)
       hEp7->Fill(dE);
     if (abs(int(Ep-50))<e)
       hEp8->Fill(dE);
     if (abs(int(Ep-100))<e)
       hEp9->Fill(dE);
   }
   //TF1 *landau1 = new TF1 ("landau1". "TMath::Landau(x,[0],[1],0)",-5,100);")
   //landau1->SetParameters(,);
   
   T->Print();
}
