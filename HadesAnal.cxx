#include "HadesAnal.h"
#include "TPaveText.h"
#include "TStyle.h"
#include "TH2F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TText.h"
#include "TMath.h"
#include "TRandom.h"
#include "TSystem.h"
#include "TMatrixD.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
//#include <random>
#include "TCanvas.h"
#include "TPad.h"
#include "TCutG.h"


#define SQR(x) ((x)*(x))
using namespace std;

Int_t   nentries;

HadesAnal *gHadesA;  
//HFilter *filter=new HFilter;


//--------------------------------------------------------------------
HadesAnal::HadesAnal(TTree *tree):InheritClass(tree)
{
  //gSystem->Load("libSymRun.so");
   gHadesA = this;

  nentries = Int_t(fChain->GetEntries());
  printf("Entries in the tree: %d\n",nentries);
  
  strcpy(theOutFileName,"HadesAnal.root");

  //!Open the nprun geometry
  if(!OpenGeometry())
    {
      printf("Error: The geometry can not be open!\n");
      return;
    }
 

  CreateHistos();
}

//--------------------------------------------------------------------

#include "CreateHistos.cxx"
#include "WriteHistos.cxx"

void HadesAnal::Init(void)
{
  //CreateHistos();
  //Reading kinematic files
  //TFile* fi = TFile::Open("cuts_mod5.root");

  char cname1[100];
  char cname2[100];

  //TFile* f1 = new TFile("matrices_agag_ckt.root");
  //  TFile* f1 = new TFile("matrices_agag.root");
  
  //heff3d_el= (TH3F*) f1->Get("heff3D_ele")->Clone();
  //hacc3d_el= (TH3F*) f1->Get("hacc3D_ele")->Clone();

  //heff3d_pos= (TH3F*) f1->Get("heff3D_pos")->Clone();
  //hacc3d_pos= (TH3F*) f1->Get("hacc3D_pos")->Clone();

  
    
  //sprintf(cname1,"cutg_mod5_%d",Pen);
  //fcut1_mod5  = (TCutG*)fi->Get(cname1)->Clone();
  // sprintf(cname2,"cutg2_mod5_%d",Pen);
  // fcut2_mod5  = (TCutG*)fi->Get(cname2)->Clone();
  //fi->Close();
  //delete fi;
   
}


//
//________________________________________________________________________
Int_t HadesAnal::ReadLine(FILE *fID, char *line)
{
  char buff[128];
  char ch;

  while (  fgets(buff, 127, fID) != NULL) 
    {
      ch = buff[0];
      if (ch != '!' && ch != '*' && ch != '#') // some comment characters 
	{
	  strcpy(line, buff);
	  return 1;
	}
    }
  return EOF;
}

//--------------------------------------------------------------------
HadesAnal::~HadesAnal()
{
  WriteHistos();

  //if(fcut1_mod5) delete fcut1_mod5;
 }

//--------------------------------------------------------------------
void HadesAnal::Loop(Char_t * file)
{
 
	    
  //    if(file == NULL)
  //	      {
  //		theOut=new TFile(theOutFileName,"recreate");
  //	      }


  //	    TTree TT("TT","TreeHades");

	   
	    // declare the tree structure
      
	    //TT.Branch("evnb",&evnb, "evnb/I" );
	    //TT.Branch("lep","TLorentzVector", &lvep);
	    //TT.Branch("lem","TLorentzVector", &lvem);
	    
	    
	    if (fChain == 0) return;

	    
	    for (Long_t event=0; event<nentries; event++) 
	      {
		if(!(event%100000))  
		  {
		    printf("Event: %ld\r",event);
		    fflush(stdout);
		  }
		LoadTree(event);
		fChain->GetEntry(event);
		//cout<< eventNum<<endl;
		
		if (Npart){
		  

		  for (int i=0;i<Npart;i++){
	 
		    TVector3 m3,vert;
		    TLorentzVector *lv = new TLorentzVector;
		    
		    m3.SetXYZ(Particles_fP_fX[i],Particles_fP_fY[i],Particles_fP_fZ[i]);
		    vert.SetXYZ(Particles_fV_fX[i],Particles_fV_fY[i],Particles_fV_fZ[i]);
		    
		    lv->SetPxPyPzE(Particles_fP_fX[i],Particles_fP_fY[i],Particles_fP_fZ[i],Particles_fE[i]);	 
	 
		    double theta=m3.Theta()*180./TMath::Pi();
		    int pid=Particles_pid[i];
		    int pin=Particles_parentIndex[i];


		    int gloW=Particles_wt[i];

	  

		    float th=lv->Theta()*180./TMath::Pi();;
		    float ph=lv->Phi()*180./TMath::Pi();;	  
		    float mom=lv->Rho()*1000;

		    //if(pid==9)thmom9_4pi->Fill(mom,th);
		    //if(pid==14)thmom14_4pi->Fill(mom,th);
		    //if(pid==2)thmom2_4pi->Fill(mom,th);
		    //if(pid==3)thmom3_4pi->Fill(mom,th);
		    //cout<<pid<<endl;
		    theta_p1->Fill(th);	    
		    
	    
		  }
		  
		}
	      
	    
      //if(peak_){
      //cout<<peak_mod[0]<<endl;
      //if (WriteTree) TT.Fill();
      //}
		//TT.Fill();
	      }//end event loop 


 
	    //TT.Write(); 
}

//------------------------------------------------------------------
Int_t HadesAnal::OpenGeometry()
{
    return 1;//OK
}


//double HadesAnal::ranGaus(double x0, double sigma)
//{


//  return ranVal.Gaus(x0,sigma);
//}



//void KRAnal::WriteHistos(void){
//}
