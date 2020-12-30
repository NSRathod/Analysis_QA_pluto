
int BChain(char*ClassName="myClass"){
#include <string> 
 using namespace std;
TTimeStamp ts;
printf("%s\n",ts.AsString());

gROOT->Reset();



TChain * fchain = new TChain("data","HadesAnal");

//gSystem->Load("libSymRun.so");
//printf("Library libSymRun.so has been loaded\n");

if(ClassName=="myClass"){
  cout<<"Class: "<<ClassName<<endl;
	}


 char name[200];
 char name2[200];
 string name1;
 ifstream tfil;
 string str1, str,str2,str3;
 size_t pos;
 string mypath="/home/ciepal/Main/HADES/pluto/KSI/root_analiza_Lam1520";
 //size_t s1,s2;   
 string s1;



 tfil.open("FileList.dat");
  if (!tfil){
    cout<< "No TFile List !! " <<endl;
    return;
  }
  while(!tfil.eof() ){
       tfil>>name;
       str=name;
       
       //pos = str.find("dst6_m"); 
       
       //str1 = str.substr (pos);   
       //str2 = str1.substr (6,2); 
       //str3 = str1.substr (9,4);
       //cout << "---> "<< str2<<" "<<str3 << endl;
  
      
  //int rnb = atoi (str3.c_str());
  //int mnb = atoi (str2.c_str());
  //cout<<" "<<mnb<<endl;

  //if (mnb==10){
    //s1=mypath+str;
    //cout<<"----->> "<<s1<<endl;
    //name2=s1.c_str();
    //s1.copy(name2, 200);


  fchain->Add(name);	
  cout<<name<<"  "<<fchain->GetEntries()<<endl;;
     
  //}
  }
  tfil.close();

fchain->MakeClass(ClassName);

TString A(ClassName);
A.Append(".C");

TString H(ClassName);
H.Append(".h");

TString B(ClassName);
B.Append(".cxx");

TString C("mv -f ");
C.Append(A);
C.Append(" ");
C.Append(B);

 char info1[100];

gSystem->Exec(C.Data());

 sprintf(info1,"File: %s has been renamed to %s\n",A.Data(),B.Data());
 cout<<info1<<endl;


ofstream Inherit;
 Inherit.open("ClassName.h");
 Inherit<<"//This file has been created automatically by BChain.C\n //"<<ts.AsString()<<"\n\n";
 Inherit<<"#include \""<<H.Data()<<"\"\n";
 Inherit<<"#define InheritClass "<<ClassName<<"\n";
 cout<<"File: ClassName.h has been created\n";
 Inherit.close();

 ofstream MakeBase;
 MakeBase.open("make-chain");
 MakeBase<<"#"<< ts.AsString()<<"\n";
 MakeBase<<"# This file has been created automatically by BChain.C \n ";
 MakeBase<<" ECBBaseCXX = "<<B.Data()<<"\n";
 MakeBase<<" ECBBaseH   = "<<H.Data()<<"\n";
 cout<<"File: make-chain has been created\n";
 MakeBase.close();


//It here is tricky but since there is an error in root it must be persistently done.
TString exec;
exec.Append("/bin/cat ");
exec.Append(H);
exec.Append("  | sed s/'_ '/' '/ >_.h && mv -f _.h ");
exec.Append(H);
exec.Append(";");

gSystem->Exec(exec.Data());

 cout<< "File: "<<B.Data() <<" has been corrected \n";
return 0;
}
