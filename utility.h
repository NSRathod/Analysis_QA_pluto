#ifndef utility_h
#define utility_h

#include <TROOT.h>

typedef struct 
{
  Float_t x, y, z;
} Vector;

const Float_t PI=3.1415;

#define SQR(x) ((x)*(x))

Float_t Length(Vector *v);
Vector *CrossProd(Vector *a, Vector *b, Vector *c);
Float_t ScalProd(Vector *a, Vector *b);
Int_t CheckIreg(Int_t oldv,Int_t newv);
Int_t get_bin(Float_t alfa, Int_t nbins);
Float_t asy_error(Float_t n0, Float_t dn0, Float_t n1, Float_t dn1 );
Float_t Srat_error(Float_t n0, Float_t dn0, Float_t n1, Float_t dn1, Float_t n2, Float_t dn2, Float_t n3, Float_t dn3);
Float_t SNGerr(Float_t asy, Float_t easy,  Float_t LT1, Float_t LT2, Float_t eta1, Float_t eta2, Float_t eLT, Float_t eEta, Float_t ePbAF);
Float_t W_Avar(Float_t *a, Float_t *da, Int_t n, Float_t *ea);
Double_t W_Avar(Double_t *a, Double_t *da, Int_t n, Float_t *ea);
Double_t W_Avar(Double_t a, Double_t da, Double_t b, Double_t db, Double_t *dr);
Float_t W_Avar(Float_t a, Float_t da, Float_t b, Float_t db, Float_t *dr);
#endif
