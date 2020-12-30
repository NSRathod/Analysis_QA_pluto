
void HadesAnal::CreateHistos(void)
{
  theta_p1=new TH1F("theta","theta",100,0,180);
  theta_p1->GetXaxis()->SetTitle("theta");
  theta_p1->GetYaxis()->SetTitle("counts");

}
