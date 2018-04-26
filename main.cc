//G.Yang Apr.25 2018

#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TTree.h>
#include <TVector3.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TStopwatch.h>
#include <TPolyMarker3D.h>
#include <string>
#include <iostream>
#include <fstream>
#include "TSystem.h"

#include "THEIALoop.hh"


int main(int argc, char* argv[])
{
   gSystem->Load("libTree");

   //TChain * chain = new TChain("h1","");
   //chain->Add("input/combined.root");
   TFile* f = new TFile("input/combined.root");
   //TTree* tree = chain;   
   TTree* tree = (TTree*)f->Get("h1");

   std::cout<<"preparing.."<<std::endl;
   THEIA* sLoop = new THEIA(tree);
   //sLoop->LoadFile(tree);     
   //sLoop->Init(tree);
   sLoop->prepareOutput("outputTest.root");

   TString atmFlux("input/hondaFluxTruncated.txt");
   TSpline5** atmSpline = sLoop->LoadAtmFlux(atmFlux);

   TString duneFlux("input/g4lbne_FHC_FD.root");
   TSpline5** duneSpline = sLoop->LoadDuneFlux(duneFlux);   


   for (int i = 0; i < 4; i++) atmSpline[i]->SetNpx(1000);
   for (int i = 0; i < 8; i++) duneSpline[i]->SetNpx(1000);
   
   
   TCanvas * c1 = new TCanvas();
   atmSpline[2]->Draw();
   c1->SetLogy();

   TCanvas * c2 = new TCanvas();
   duneSpline[6]->Draw();

   c1->SaveAs("atmSpline.png");
   c2->SaveAs("duneSpline.png");
   
   
   //   Long64_t nentries = tree->GetEntries();

   //   std::cout<<"ready to loop"<<std::endl;

   //   Int_t NofEvent = 100;
   //   sLoop->LoopAndWrite(NofEvent, true);   

} 

