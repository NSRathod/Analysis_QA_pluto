void HadesAnal::WriteHistos(void)
{
  
  float x1,x2,y1,y2;
  x1=0.52; y1=0.8;x2=0.7;y2=0.87;
   TPaveText *t1,*t2; 

  f = new TFile("hades_histos.root","recreate");
  //if (!f || !f->IsOpen()){
  //f=new TFile("SymulHe3_histos.root","recreate");
  //}

  //  TCanvas *c1=new TCanvas("lambdaPluto","lambdaPluto");
  //c1->Divide(2,2);
  //c1->Write();


  theta_p1->Write();

  
    f->Close();
    f->Write();
  
}
