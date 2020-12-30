#include "utility.h"
#include <math.h>

//--------------------------------------------------------------------
Float_t Length(Vector *v)
{
  return (Float_t)(sqrt((v->x)*(v->x) + (v->y)*(v->y) +(v->z)*(v->z)));
}

//--------------------------------------------------------------------
Vector *CrossProd(Vector *a, Vector *b, Vector *c)
{
  c->x = a->y*b->z - a->z*b->y;
  c->y = a->z*b->x - a->x*b->z;
  c->z = a->x*b->y - a->y*b->x;

  return c;
}

//--------------------------------------------------------------------
Float_t ScalProd(Vector *a, Vector *b)
{
  return a->x*b->x + a->y*b->y + a->z*b->z;
}

//--------------------------------------------------------------------
Int_t CheckIreg(Int_t oldv,Int_t newv)
{
  if(oldv == newv)
    return 0;

  if(newv-oldv == 1 || (newv==0&&oldv==3))
    return 1;
  
  return -1;
}

Int_t get_bin(Float_t alfa, Int_t nbins)
{
  return (Int_t)((alfa + PI)*nbins/(2*PI));
}
//---------------------------------------------------------------------
Float_t asy_error(Float_t n0, Float_t dn0, Float_t n1, Float_t dn1 )
{
  return  (n0+n1)? 2* sqrt(SQR(n1*dn0) + SQR(n0*dn1)) / SQR(n0+n1):0;
}
//---------------------------------------------------------------------
//Srat = (sqrt(n0*n1)-sqrt(n2*n3))/(sqrt(n0*n1)+sqrt(n2*n3))
Float_t Srat_error(Float_t n0, Float_t dn0, Float_t n1, Float_t dn1, Float_t n2, Float_t dn2, Float_t n3, Float_t dn3)
{
  //return   sqrt(SQR(dn0*n1*sqrt(n2*n3)/(sqrt(n1*n0)*SQR(sqrt(n2*n3)+sqrt(n0*n1)))) + 
  //	SQR(dn1*n0*sqrt(n2*n3)/(sqrt(n0*n1)*SQR(sqrt(n2*n3)+sqrt(n1*n0)))) +  
  //	SQR(dn2*n3*sqrt(n0*n1)/(sqrt(n3*n2)*SQR(sqrt(n0*n1)+sqrt(n2*n3)))) +  
  //	SQR(dn3*n2*sqrt(n0*n1)/(sqrt(n2*n3)*SQR(sqrt(n0*n1)+sqrt(n3*n2))))  );
  return  1./SQR(sqrt(n2*n3)+sqrt(n0*n1)) * 
    sqrt(SQR(dn0)*n1*n2*n3/n0 + SQR(dn1)*n0*n2*n3/n1 + SQR(dn2)*n0*n1*n3/n2 + SQR(dn3)*n0*n1*n2/n3);
}

Float_t SNGerr(Float_t asy, Float_t easy,  Float_t LT1, Float_t LT2, Float_t eta1, Float_t eta2, Float_t eLT, Float_t eEta, Float_t ePbAF)
{
  Float_t DLT2, M, ret, Deta, Dasy;

  M = asy*(LT1*eta1+LT2*eta2) - (LT1*eta1-LT2*eta2);

  DLT2 = eLT*eLT * SQR(eta1-eta2)*SQR(asy*asy-1)*(SQR(LT1)+SQR(LT2))/SQR(M*M);

  Deta = eEta * 4*(LT1*LT2)*SQR(asy)/(M*M);

  Dasy = easy * 2*LT2*(LT1*eta1+LT2*eta2)/(M*M);

  ret = sqrt(SQR(ePbAF) + DLT2 + SQR(Deta) + SQR(Dasy));

  //fprintf(stderr, "eLT %f, easy %f , deta %f, DLT %f;  ret %f  (M was %f)\n",eLT,  Dasy, Deta, sqrt(DLT2), ret, M);

  return ret;
}
 
//---------------------------------------------------------------------
Float_t W_Avar(Float_t a, Float_t da, Float_t b, Float_t db)
{
  Float_t wa, wb;

  wa = 1/(da*da);
  wb = 1/(db*db);

  return (a*wa + b*wb)/(wa+wb);

}
 
//---------------------------------------------------------------------
Double_t W_Avar(Double_t a, Double_t da, Double_t b, Double_t db, Double_t *dr)
{
  Double_t wa, wb;

  wa = 1/(da*da);
  wb = 1/(db*db);

  *dr = sqrt(1./(wa+wb));
  return (a*wa + b*wb)/(wa+wb);

}
//---------------------------------------------------------------------
Float_t W_Avar(Float_t a, Float_t da, Float_t b, Float_t db, Float_t *dr)
{
  Float_t wa, wb;

  wa = 1/(da*da);
  wb = 1/(db*db);

  *dr = sqrt(1./(wa+wb));
  return (a*wa + b*wb)/(wa+wb);

}

//---------------------------------------------------------------------
Float_t W_Avar(Float_t *a, Float_t *da, Int_t n, Float_t *ea)
{
  Float_t *wa, swa=0., sawa=0.;
  Int_t i;

  wa = new Float_t[n];

  for (i=0; i<n; i++)
    if (da[i] > 0.000001)
      {
	wa[i] = 1/(da[i] * da[i]);
	swa += wa[i];
	sawa += a[i] * wa[i];
      }

  *ea = sqrt(1./swa);

  return (swa!=0) ? sawa/swa : 0.;

}
//---------------------------------------------------------------------
Double_t W_Avar(Double_t *a, Double_t *da, Int_t n, Float_t *ea)
{
  Double_t *wa, swa=0., sawa=0.;
  Int_t i;

  wa = new Double_t[n];

  for (i=0; i<n; i++)
    if (da[i] > 0.000001)
      {
	wa[i] = 1/(da[i] * da[i]);
	swa += wa[i];
	sawa += a[i] * wa[i];
      }

  *ea = sqrt(1./swa);

  return (swa!=0) ? sawa/swa : 0.;

}
