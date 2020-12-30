#include <stdio.h>
#include <string.h>
#include <math.h>   
#include "HadesAnal.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TClass.h"
#include "TClassTable.h"
#include "TCollection.h"
#include "TObject.h"
#include "TF1.h" 
#include "TMinuit.h"   
#include "TMath.h"
#include "TLine.h"
#include "TPaveLabel.h"
#include "TRandom3.h"
#include "TStopwatch.h"


extern void InitGui();
VoidFuncPtr_t initfuncs[] = { InitGui, 0 };

TROOT api("hades_analysis","hades",initfuncs);


int main(int argc, char **argv)
{

  TApplication theApp("App",0,0);
 
  TStopwatch timer; // for cpu usage information 
  timer.Start();
  
  HadesAnal * theSH = new HadesAnal();
  Int_t len;
  Char_t *file_name;

  if(argc == 2) 
    {
      len = strlen(argv[1]);
      file_name = new Char_t [len];
      strcpy(file_name, argv[1]);
    }
  else 
    file_name = NULL;

  gROOT->Macro("userHades.C"); 
  theSH->Init();
  theSH->Loop(file_name);

  delete theSH;

  timer.Stop();
  fprintf(stderr,"*********************************\n");
  return 0;
}


