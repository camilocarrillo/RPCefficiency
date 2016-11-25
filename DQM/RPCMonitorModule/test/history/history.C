#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

#define max_range 100
#define min_range 80

float GetMean_0(TH1F * histo){
  float mean=0;
  for(int bin=2; bin<=histo->GetNbinsX(); bin++){
    mean=mean+float(bin)*float(histo->GetBinContent(bin));
  }
  
  float denominator = float(histo->Integral())-float(histo->GetBinContent(1));
  //cout<<"First Bin="<<histo->GetBinContent(1)<<endl;
  //cout<<"Zero Bin="<<histo->GetBinContent(0)<<endl;
  if(denominator>0) mean=2.*mean/(denominator);

  return mean;
  
}


float Denominator(float eff,float err){
  if(err!=0) return eff*(1-eff)/(err*err);
  else cout<<"crash in Numerator err = 0"<<endl;
  return 0;
}

float Numerator(float eff, float err){
  if(err!=0) return eff*Denominator(eff,err);
  else cout<<"crash in Denumerator err = 0"<<endl;
  return 0;
}

float WheelError(TFile * file,int wheel){
  TH1F * efficiency;
  if(wheel==-2) efficiency = (TH1F*) (file->Get("AzimutalDistroWm2"));
  if(wheel==-1) efficiency = (TH1F*) (file->Get("AzimutalDistroWm1"));
  if(wheel==0) efficiency = (TH1F*) (file->Get("AzimutalDistroW0"));
  if(wheel==1) efficiency = (TH1F*) (file->Get("AzimutalDistroW1"));
  if(wheel==2) efficiency = (TH1F*) (file->Get("AzimutalDistroW2"));
  
  float numerator=0;
  float denominator=0;
  float eff,err;

  for(int k=1;k<=12;k++){
    eff = efficiency->GetBinContent(k); 
    err = efficiency->GetBinError(k);
    if(err!=0){
      numerator=numerator+Numerator(eff,err);
      denominator=denominator+Denominator(eff,err);
    }
  }
  
  if(denominator!=0){
    //cout<<"returning "<<numerator/denominator<<endl;
      float effi=numerator/denominator;
      float erro=sqrt(effi*(1.-effi)/denominator);
      return erro;
  }else{
    //cout<<"returning -1"<<endl;
    return -0.01;
  }
}

float BarrelEfficiency(TFile * file){
    TH1F * efficiency[5];
    efficiency[0] = (TH1F*) (file->Get("AzimutalDistroWm2"));
    efficiency[1] = (TH1F*) (file->Get("AzimutalDistroWm1"));
    efficiency[2] = (TH1F*) (file->Get("AzimutalDistroW0"));
    efficiency[3] = (TH1F*) (file->Get("AzimutalDistroW1"));
    efficiency[4] = (TH1F*) (file->Get("AzimutalDistroW2"));
    
    float numerator=0;
    float denominator=0;
    float eff,err;
    
    for(int wheel=0;wheel<=4;wheel++){
	for(int k=1;k<=12;k++){
	    eff = efficiency[wheel]->GetBinContent(k); 
	    err = efficiency[wheel]->GetBinError(k);
	    if(err!=0){
		numerator=numerator+Numerator(eff,err);
		denominator=denominator+Denominator(eff,err);
	    }
	}
    }
    
    if(denominator!=0){
	//cout<<"returning "<<numerator/denominator<<endl;
	return numerator/denominator;
    }else{
	//cout<<"returning -1"<<endl;
	return -0.01;
    }
}



float WheelEfficiency(TFile * file,int wheel){
  TH1F * efficiency;
  if(wheel==-2) efficiency = (TH1F*) (file->Get("AzimutalDistroWm2"));
  if(wheel==-1) efficiency = (TH1F*) (file->Get("AzimutalDistroWm1"));
  if(wheel==0) efficiency = (TH1F*) (file->Get("AzimutalDistroW0"));
  if(wheel==1) efficiency = (TH1F*) (file->Get("AzimutalDistroW1"));
  if(wheel==2) efficiency = (TH1F*) (file->Get("AzimutalDistroW2"));
  
  float numerator=0;
  float denominator=0;
  float eff,err;

  for(int k=1;k<=12;k++){
    eff = efficiency->GetBinContent(k); 
    err = efficiency->GetBinError(k);
    if(err!=0){
      numerator=numerator+Numerator(eff,err);
      denominator=denominator+Denominator(eff,err);
    }
  }
  
  if(denominator!=0){
    //cout<<"returning "<<numerator/denominator<<endl;
    return numerator/denominator;
  }else{
    //cout<<"returning -1"<<endl;
    return -0.01;
  }

}

float EndCapEfficiency(TFile * file){

  TH1F * efficiencyR2[8];
  TH1F * efficiencyR3[8];
  

  efficiencyR2[0] = (TH1F*) (file->Get("GregDistroD1R2"));
  efficiencyR3[0] = (TH1F*) (file->Get("GregDistroD1R3"));
  
  efficiencyR2[1] = (TH1F*) (file->Get("GregDistroD2R2"));
  efficiencyR3[1] = (TH1F*) (file->Get("GregDistroD2R3"));
  
  efficiencyR2[2] = (TH1F*) (file->Get("GregDistroD3R2"));
  efficiencyR3[2] = (TH1F*) (file->Get("GregDistroD3R3"));
  
  efficiencyR2[3] = (TH1F*) (file->Get("GregDistroD4R2"));
  efficiencyR3[3] = (TH1F*) (file->Get("GregDistroD4R3"));
  
  efficiencyR2[4] = (TH1F*) (file->Get("GregDistroDm1R2"));
  efficiencyR3[4] = (TH1F*) (file->Get("GregDistroDm1R3"));
  
  efficiencyR2[5] = (TH1F*) (file->Get("GregDistroDm2R2"));
  efficiencyR3[5] = (TH1F*) (file->Get("GregDistroDm2R3"));
  
  efficiencyR2[6] = (TH1F*) (file->Get("GregDistroDm3R2"));
  efficiencyR3[6] = (TH1F*) (file->Get("GregDistroDm3R3"));
  
  efficiencyR2[7] = (TH1F*) (file->Get("GregDistroDm4R2"));
  efficiencyR3[7] = (TH1F*) (file->Get("GregDistroDm4R3"));


  float numerator=0;
  float denominator=0;
  float eff1,err1,eff2,err2;

  for(int index=0;index<8;index++){
      for(int k=1;k<=36;k++){
	  eff1 = efficiencyR2[index]->GetBinContent(k);
	  err1 = efficiencyR2[index]->GetBinError(k);
	  
	  eff2 = efficiencyR3[index]->GetBinContent(k);
	  err2 = efficiencyR3[index]->GetBinError(k);
	  
	  if(err1!=0 && err2!=0){
	      numerator=numerator+Numerator(eff1,err1)+Numerator(eff2,err2);
	      denominator=denominator+Denominator(eff1,err1)+Denominator(eff2,err2);
	  } 
      }
  }
      
  if(denominator!=0){
      cout<<"returning "<<numerator/denominator<<endl;
      return numerator/denominator;
  }else{
      return -0.01;
  }
}


float RingEfficiency(TFile * file,int ring){

  TH1F * efficiency[4];
  
  if(ring==2){
      efficiency[0] = (TH1F*) (file->Get("GregDistroD1R2"));
      efficiency[1] = (TH1F*) (file->Get("GregDistroD2R2"));
      efficiency[2] = (TH1F*) (file->Get("GregDistroD3R2"));
      efficiency[3] = (TH1F*) (file->Get("GregDistroD4R2"));
  }
  if(ring==-2){
      efficiency[0] = (TH1F*) (file->Get("GregDistroDm1R2"));
      efficiency[1] = (TH1F*) (file->Get("GregDistroDm2R2"));
      efficiency[2] = (TH1F*) (file->Get("GregDistroDm3R2"));
      efficiency[3] = (TH1F*) (file->Get("GregDistroDm4R2"));
  }
  if(ring==3){
      efficiency[0] = (TH1F*) (file->Get("GregDistroD1R3"));
      efficiency[1] = (TH1F*) (file->Get("GregDistroD2R3"));
      efficiency[2] = (TH1F*) (file->Get("GregDistroD3R3"));
      efficiency[3] = (TH1F*) (file->Get("GregDistroD4R3"));
  }
  if(ring==-3){
      efficiency[0] = (TH1F*) (file->Get("GregDistroDm1R3"));
      efficiency[1] = (TH1F*) (file->Get("GregDistroDm2R3"));
      efficiency[2] = (TH1F*) (file->Get("GregDistroDm3R3"));
      efficiency[3] = (TH1F*) (file->Get("GregDistroDm4R3"));
  }

  float numerator=0;
  float denominator=0;
  float eff1,err1,eff2,err2;

  for(int index=0;index<4;index++){
      for(int k=1;k<=36;k++){
	  eff1 = efficiency[index]->GetBinContent(k);
	  err1 = efficiency[index]->GetBinError(k);
	  if(err1!=0){
	      numerator=numerator+Numerator(eff1,err1);
	      denominator=denominator+Denominator(eff1,err1);
	  } 
      }
  }
      
  if(denominator!=0){
      cout<<"returning "<<numerator/denominator<<endl;
      return numerator/denominator;
  }else{
      return -0.01;
  }
}



float DiskEfficiency(TFile * file,int disk){

  cout<<"computing efficiency for disk "<<disk<<endl;
  
  TH1F * efficiencyR2;
  TH1F * efficiencyR3;

  if(disk==1){                  
    efficiencyR2 = (TH1F*) (file->Get("GregDistroD1R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroD1R3"));
  }

  if(disk==2){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroD2R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroD2R3"));
  }
  if(disk==3){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroD3R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroD3R3"));
  }
  if(disk==4){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroD4R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroD4R3"));
  }
  if(disk==-1){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroDm1R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroDm1R3"));
  }
  if(disk==-2){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroDm2R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroDm2R3"));
  }
  if(disk==-3){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroDm3R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroDm3R3"));
  }
  if(disk==-4){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroDm4R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroDm4R3"));
  }

  float numerator=0;
  float denominator=0;
  float eff1,err1,eff2,err2;

  for(int k=1;k<=36;k++){

    //cout<<"reading "<<eff1<<" +/-"<<err1<<" "<<eff2<<" +/- "<<err2<<endl;
    
    eff1 = efficiencyR2->GetBinContent(k);
    err1 = efficiencyR2->GetBinError(k);

    eff2 = efficiencyR3->GetBinContent(k);
    err2 = efficiencyR3->GetBinError(k);
    
    if(err1!=0 && err2!=0){
      numerator=numerator+Numerator(eff1,err1)+Numerator(eff2,err2);
      denominator=denominator+Denominator(eff1,err1)+Denominator(eff2,err2);
    } 
    //cout<<"\t for k = "<<k<<" numerator = "<<numerator<<" denominator = "<<denominator<<endl;
  }

  if(denominator!=0){
    cout<<"returning "<<numerator/denominator<<endl;
    return numerator/denominator;
  }else{
    return -0.01;
  }
}

float DiskError(TFile * file,int disk){

  cout<<"computing efficiency for disk "<<disk<<endl;
  
  TH1F * efficiencyR2;
  TH1F * efficiencyR3;

  if(disk==1){                  
    efficiencyR2 = (TH1F*) (file->Get("GregDistroD1R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroD1R3"));
  }

  if(disk==2){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroD2R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroD2R3"));
  }
  if(disk==3){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroD3R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroD3R3"));
  }
  if(disk==4){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroD4R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroD4R3"));
  }
  if(disk==-1){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroDm1R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroDm1R3"));
  }
  if(disk==-2){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroDm2R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroDm2R3"));
  }
  if(disk==-3){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroDm3R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroDm3R3"));
  }
  if(disk==-4){
    efficiencyR2 = (TH1F*) (file->Get("GregDistroDm4R2"));
    efficiencyR3 = (TH1F*) (file->Get("GregDistroDm4R3"));
  }

  float numerator=0;
  float denominator=0;
  float eff1,err1,eff2,err2;

  for(int k=1;k<=36;k++){

    //cout<<"reading "<<eff1<<" +/-"<<err1<<" "<<eff2<<" +/- "<<err2<<endl;
    
    eff1 = efficiencyR2->GetBinContent(k);
    err1 = efficiencyR2->GetBinError(k);

    eff2 = efficiencyR3->GetBinContent(k);
    err2 = efficiencyR3->GetBinError(k);
    
    if(err1!=0 && err2!=0){
      numerator=numerator+Numerator(eff1,err1)+Numerator(eff2,err2);
      denominator=denominator+Denominator(eff1,err1)+Denominator(eff2,err2);
    } 
    //cout<<"\t for k = "<<k<<" numerator = "<<numerator<<" denominator = "<<denominator<<endl;
  }

  if(denominator!=0){
    cout<<"returning "<<numerator/denominator<<endl;
    float effi=numerator/denominator;
    float erro=sqrt(effi*(1.-effi)/denominator);
    return erro;
  }else{
    return -0.01;
  }
}

void setHistoCorrelation(TH2F * histo,string titleY){
  histo->GetXaxis()->SetTitle("pressure(mbar)");
  histo->GetYaxis()->SetTitle(titleY.c_str());
  histo->SetMarkerStyle(21);
  histo->SetMarkerColor(2);
  histo->Draw();
}

void setHisto(TH1F * histo){
  histo->GetXaxis()->LabelsOption("v");
  histo->GetXaxis()->SetLabelSize(0.033);
  histo->SetMarkerStyle(21);
  histo->SetMarkerColor(2);
  histo->Draw("P");         
}

void setHistoV(TH1F * histo){
  histo->GetXaxis()->LabelsOption("v");
  histo->GetXaxis()->SetLabelSize(0.033);
  histo->SetMarkerStyle(18);
  histo->SetMarkerColor(2);
  histo->SetMaximum(max_range/100.);
  histo->SetMinimum(min_range/100.);
  histo->Draw("P");         
}

void setHistoSameV(TH1F * histo,int color){
  histo->GetXaxis()->LabelsOption("v");
  histo->GetXaxis()->SetLabelSize(0.033);
  histo->SetMarkerStyle(18);
  histo->SetMarkerColor(color);
  histo->SetMaximum(max_range/100.);
  histo->SetMinimum(min_range/100.);
  histo->Draw("Psame");         
}

void setHistonormalized(TH1F * histo,int sty){
  histo->GetXaxis()->LabelsOption("v");
  histo->GetXaxis()->SetLabelSize(0.033);
  histo->SetMarkerStyle(sty);
  histo->SetMarkerColor(2);
  histo->DrawNormalized("P");         
}

void setHistosame(TH1F * histo, int sty){
  histo->GetXaxis()->LabelsOption("v");
  histo->GetXaxis()->SetLabelSize(0.033);
  histo->SetMarkerStyle(sty);
  histo->SetMarkerColor(2);
  histo->DrawNormalized("Psame");         
}


float CLSEndCap(TFile * file){
  TH1F * allCLS[9];
  allCLS[0]= (TH1F*) (file->Get("CLSStation1Ring2_A"));
  allCLS[1]= (TH1F*) (file->Get("CLSStation1Ring2_B"));
  allCLS[2]= (TH1F*) (file->Get("CLSStation1Ring2_C"));
  allCLS[3]= (TH1F*) (file->Get("CLSStation234Ring2_A"));
  allCLS[4]= (TH1F*) (file->Get("CLSStation234Ring2_B"));
  allCLS[5]= (TH1F*) (file->Get("CLSStation234Ring2_C"));
  allCLS[6]= (TH1F*) (file->Get("CLSStation1234Ring3_A"));
  allCLS[7]= (TH1F*) (file->Get("CLSStation1234Ring3_B"));
  allCLS[8]= (TH1F*) (file->Get("CLSStation1234Ring3_C"));
  
  TH1F * CLSE = new TH1F ("CLSE","Cluster Size for all the endcap",10,0.5,10.5);
  for(int k=0;k<9;k++) CLSE->Add(allCLS[k]);
  float mean = CLSE->GetMean();
  delete CLSE;
  return mean;
}

float RMSCLSEndCap(TFile * file){
  TH1F * allCLS[9];
  allCLS[0]= (TH1F*) (file->Get("CLSStation1Ring2_A"));
  allCLS[1]= (TH1F*) (file->Get("CLSStation1Ring2_B"));
  allCLS[2]= (TH1F*) (file->Get("CLSStation1Ring2_C"));
  allCLS[3]= (TH1F*) (file->Get("CLSStation234Ring2_A"));
  allCLS[4]= (TH1F*) (file->Get("CLSStation234Ring2_B"));
  allCLS[5]= (TH1F*) (file->Get("CLSStation234Ring2_C"));
  allCLS[6]= (TH1F*) (file->Get("CLSStation1234Ring3_A"));
  allCLS[7]= (TH1F*) (file->Get("CLSStation1234Ring3_B"));
  allCLS[8]= (TH1F*) (file->Get("CLSStation1234Ring3_C"));
  
  TH1F * CLSE = new TH1F ("CLS","Cluster Size for all the endcap",10,0.5,10.5);
  for(int k=0;k<9;k++) CLSE->Add(allCLS[k]);
  float rms=CLSE->GetRMS();
  delete CLSE;
  return rms;
}


float masked(TFile * file){
  float total=0;
  TH1F * allmasked[10];
  
  allmasked[0]= (TH1F*) (file->Get("GlobMaskedWheel_-2near"));
  allmasked[1]= (TH1F*) (file->Get("GlobMaskedWheel_-1near"));
  allmasked[2]= (TH1F*) (file->Get("GlobMaskedWheel_0near"));
  allmasked[3]= (TH1F*) (file->Get("GlobMaskedWheel_1near"));
  allmasked[4]= (TH1F*) (file->Get("GlobMaskedWheel_2near"));
  allmasked[5]= (TH1F*) (file->Get("GlobMaskedWheel_2far"));
  allmasked[6]= (TH1F*) (file->Get("GlobMaskedWheel_-2far"));
  allmasked[7]= (TH1F*) (file->Get("GlobMaskedWheel_-1far"));
  allmasked[8]= (TH1F*) (file->Get("GlobMaskedWheel_0far"));
  allmasked[9]= (TH1F*) (file->Get("GlobMaskedWheel_1far"));

  for(int i=0;i<10;i++) total = total + allmasked[i]->Integral();

  total = (total/1020);

  std::cout<<total<<std::endl;
  
  delete allmasked[0];

  return total;
}

float maskedendcap(TFile * file){

  float total=0;
  TH1F * allmasked[16];
  
  allmasked[0]= (TH1F*) (file->Get("GlobMaskedDisk_4near"));
  allmasked[1]= (TH1F*) (file->Get("GlobMaskedDisk_3near"));  
  allmasked[2]= (TH1F*) (file->Get("GlobMaskedDisk_2near"));  
  allmasked[3]= (TH1F*) (file->Get("GlobMaskedDisk_1near"));  
  allmasked[4]= (TH1F*) (file->Get("GlobMaskedDisk_m4near")); 
  allmasked[5]= (TH1F*) (file->Get("GlobMaskedDisk_m3near")); 
  allmasked[6]= (TH1F*) (file->Get("GlobMaskedDisk_m2near")); 
  allmasked[7]= (TH1F*) (file->Get("GlobMaskedDisk_m1near")); 
  allmasked[8]= (TH1F*) (file->Get("GlobMaskedDisk_4far"));  
  allmasked[9]= (TH1F*) (file->Get("GlobMaskedDisk_3far"));  
  allmasked[10]= (TH1F*) (file->Get("GlobMaskedDisk_2far"));  
  allmasked[11]= (TH1F*) (file->Get("GlobMaskedDisk_1far"));  
  allmasked[12]= (TH1F*) (file->Get("GlobMaskedDisk_m4far")); 
  allmasked[13]= (TH1F*) (file->Get("GlobMaskedDisk_m3far")); 
  allmasked[14]=(TH1F*) (file->Get("GlobMaskedDisk_m2far")); 
  allmasked[15]=(TH1F*) (file->Get("GlobMaskedDisk_m1far")); 
  for(int i=0;i<16;i++) total = total + allmasked[i]->Integral();

  total = (total/(1296+36*12));

  std::cout<<total<<std::endl;
  
  delete allmasked[0];

  return total;
}

void history(){
  //gROOT->Reset();
  gStyle->SetOptStat(0);
 

  ifstream fileruns;
  ofstream allinfo;

  //--hvth info
  
  map<string,float> hvbarrelinfo;
  map<string,int> thbarrelinfo;
  map<string,float> hvendcapinfo;
  map<string,int> thendcapinfo;

  map<string,float> pressureinfo;

  ifstream hvthbarrel;
  ifstream hvthendcap;
  ifstream pressure;

  allinfo.open("allinfo.txt");

  //const int N=416;
  const int N=5;

  //Input txt files

  //hvthbarrel.open("hvthbarrel.txt");
  //hvthendcap.open("hvthendcap.txt");
  system("cat pressure.txt | awk \'{print $1}\' > runslist.txt");
  pressure.open("pressure.txt");
  fileruns.open("runslist.txt");
  
  string Run;
  float hv=0;
  float press=0;
  int th=0;
  int n =0;
  
  //cout<<"Reading hv barrel"<<endl;
  /*while(!hvthbarrel.eof() && n<N){
    hvthbarrel >>Run >>hv >>th;
    if(Run.size()==0) continue;
    std::cout<<Run<<" "<<hv<<" "<<th<<" "<<n<<std::endl;  
    hvbarrelinfo[Run]=hv;
    thbarrelinfo[Run]=th;
    n++;
  }
  */
  n=0;
  
  //cout<<"Reading hv endcap"<<endl;
  /*
  while(!hvthendcap.eof() && n<N){
    hvthendcap >>Run >>hv >>th;
    if(Run.size()==0) continue;
    std::cout<<Run<<" "<<hv<<" "<<th<<" "<<n<<std::endl;  
    hvendcapinfo[Run]=hv;
    thendcapinfo[Run]=th;
    n++;
  }
  */

  n=0;
  
  //cout<<"Reading pressure"<<endl;
  while(!pressure.eof() && n<N){
    pressure >>Run >>press;
    if(Run.size()==0) continue;
    std::cout<<Run<<" "<<press<<" "<<n<<std::endl;  
    pressureinfo[Run]=press;
    n++;
  }
  
  //  system("rm runslist.txt");


  cout<<"All files were read"<<endl;
  
  map<string,int> durationinfo;
  
  map<string,float> channelcubarrelinfo;
  map<string,float> cubarrelinfo;
  map<string,float> errorcubarrelinfo;
  map<string,float> sensorstpbarrelinfo;
  map<string,float> tpbarrelinfo;
  map<string,float> errortpbarrelinfo;

  map<string,float> channelcuendcapinfo;
  map<string,float> cuendcapinfo;
  map<string,float> errorcuendcapinfo;
  map<string,float> sensorstpendcapinfo;
  map<string,float> tpendcapinfo;
  map<string,float> errortpendcapinfo;

  ifstream cutp;

  float cu=0;
  float tp=0;

  cutp.open("cutp.txt");

  n=0;
  while(!cutp.eof() && n<N){
    cutp >>Run >>durationinfo[Run] 
	 >>channelcubarrelinfo[Run] >>cubarrelinfo[Run] >>errorcubarrelinfo[Run] 
	 >>sensorstpbarrelinfo[Run] >>tpbarrelinfo[Run] >>errortpbarrelinfo[Run] 
	 >>channelcuendcapinfo[Run] >>cuendcapinfo[Run] >>errorcuendcapinfo[Run] 
	 >>sensorstpendcapinfo[Run] >>tpendcapinfo[Run] >>errortpendcapinfo[Run];
    
    //std::cout<<Run<<" "<<cubarrelinfo[Run]<<" "<<errorcubarrelinfo[Run]<<" "<<tpbarrelinfo[Run]<<" "<<errortpbarrelinfo[Run]<<std::endl;
    n++;
  }
  
  TH1F * EventsH = new TH1F("EventsH","Number of events History",N,0,N);
  TH1F * durationH = new TH1F("durationH","Duration of each run in seconds",N,0,N);
  
  TH1F * CentralEffBarrelH = new TH1F("CentralEffBarrelH","Barrel all rolls average",N,0,N);
  TH1F * CentralEffBarrelH_black_masked = new TH1F("CentralEffBarrelH_black_masked","Barrel good rolls Average",N,0,N);
  TH1F * Barrel_masked = new TH1F("Barrel_masked","% rolls not excluded",N,0,N);

  TH1F * DistributionEfficiencyPerRunBarrel = new TH1F("DistributionEfficiencyPerRunBarrel","Distribution Efficiency Per Run Barrel",10,90,100);
  TH1F * DistributionEfficiencyPerRunBarrel2 = new TH1F("DistributionEfficiencyPerRunBarrel2","Distribution Efficiency Per Run Barrel 2",10,90,100);
  
  TH1F * EfficiencyPerLayer1H = new TH1F("EfficiencyPerLayer1H","EfficiencyPerLayer1H" ,N,0,N);
  TH1F * EfficiencyPerLayer2H = new TH1F("EfficiencyPerLayer2H","EfficiencyPerLayer2H" ,N,0,N);
  TH1F * EfficiencyPerLayer3H = new TH1F("EfficiencyPerLayer3H","EfficiencyPerLayer3H" ,N,0,N);
  TH1F * EfficiencyPerLayer4H = new TH1F("EfficiencyPerLayer4H","EfficiencyPerLayer4H" ,N,0,N);
  TH1F * EfficiencyPerLayer5H = new TH1F("EfficiencyPerLayer5H","EfficiencyPerLayer5H" ,N,0,N);
  TH1F * EfficiencyPerLayer6H = new TH1F("EfficiencyPerLayer6H","EfficiencyPerLayer6H" ,N,0,N);

  TH1F * EfficiencyPerRingm3 = new TH1F("EfficiencyPerRingm3","EfficiencyPerRingm3" ,N,0,N);
  TH1F * EfficiencyPerRingm2 = new TH1F("EfficiencyPerRingm2","EfficiencyPerRingm2" ,N,0,N);
  TH1F * EfficiencyPerRing2 = new TH1F("EfficiencyPerRing2","EfficiencyPerRing2" ,N,0,N);
  TH1F * EfficiencyPerRing3 = new TH1F("EfficiencyPerRing3","EfficiencyPerRing3" ,N,0,N);

  TH1F * CentralEffBarrelInt = new TH1F("CentralEffBarrelInt","Fiducial Barrel Efficiency (split)" ,N,0,N);
  TH1F * CentralEffBarrelWm2H = new TH1F("CentralEffBarrelWm2H","Fiducial Efficiency" ,N,0,N);
  TH1F * CentralEffBarrelWm1H = new TH1F("CentralEffBarrelWm1H","Fiducial Efficiency Wheel -1" ,N,0,N);
  TH1F * CentralEffBarrelW0H = new TH1F("CentralEffBarrelW0H","Fiducial Efficiency Wheel 0" ,N,0,N);
  TH1F * CentralEffBarrelW1H = new TH1F("CentralEffBarrelW1H","Fiducial Efficiency Wheel 1" ,N,0,N);
  TH1F * CentralEffBarrelW2H = new TH1F("CentralEffBarrelW2H","Fiducial Efficiency Wheel 2" ,N,0,N);
  
  TH1F * CentralEffEndCapH = new TH1F("CentralEffEndCapH","EndCap all rolls average",N,0,N);
  TH1F * CentralEffEndCapH_black_masked = new TH1F("CentralEffEndCapH_black_masked","EndCap good rolls average",N,0,N);
  TH1F * EndCap_masked = new TH1F("EndCap_masked","% rolls not excluded",N,0,N);

  TH1F * CentralEffEndCapInt = new TH1F("CentralEffEndCapInt","Fiducial EndCap Efficiency (split)",N,0,N);
  TH1F * CentralEffEndCapDm4H = new TH1F("CentralEffEndCapDm4H","Fiducial Efficiency EndCap",N,0,N);
  TH1F * CentralEffEndCapDm3H = new TH1F("CentralEffEndCapDm3H","Fiducial Efficiency EndCap",N,0,N);
  TH1F * CentralEffEndCapDm2H = new TH1F("CentralEffEndCapDm2H","Fiducial Efficiency EndCap",N,0,N);
  TH1F * CentralEffEndCapDm1H = new TH1F("CentralEffEndCapDm1H","Fiducial Efficiency EndCap",N,0,N);
  TH1F * CentralEffEndCapD1H = new TH1F("CentralEffEndCapD1H","Fiducial Efficiency EndCap",N,0,N);
  TH1F * CentralEffEndCapD2H = new TH1F("CentralEffEndCapD2H","Fiducial Efficiency EndCap",N,0,N);
  TH1F * CentralEffEndCapD3H = new TH1F("CentralEffEndCapD3H","Fiducial Efficiency EndCap",N,0,N);
  TH1F * CentralEffEndCapD4H = new TH1F("CentralEffEndCapD4H","Fiducial Efficiency EndCap",N,0,N);
  
  TH1F * DoubleGapBarrelH = new TH1F("DoubleGapBarrelH","Double Gap Mean Efficiency Barrel",N,0,N);
  TH1F * DoubleGapEndCapH = new TH1F("DoubleGapEndCapH","Double Gap Mean Efficiency EndCap",N,0,N);
  TH1F * DoubleGapBarrelH_0 = new TH1F("DoubleGapBarrelH_0","Double Gap Mean Efficiency Barrel without masked rolls",N,0,N);
  TH1F * DoubleGapEndCapH_0 = new TH1F("DoubleGapEndCapH_0","Double Gap Mean Efficiency EndCap without masked rolls",N,0,N);
  TH1F * bxbarrelH = new TH1F("bxbarrelH","Mean Bunch Crossing Barrel (error bars Mean RMS)",N,0,N);
  TH1F * bxendcapH = new TH1F("bxendcapH","Mean Bunch Crossing EndCap (error bars Mean RMS)",N,0,N);
  TH1F * rmsbxbarrelH = new TH1F("rmsbxbarrelH","RMS Bunch Crossing Barrel",N,0,N);
  TH1F * rmsbxendcapH = new TH1F("rmsbxendcapH","RMS Bunch Crossing EndCap",N,0,N);
  TH1F * CLSH = new TH1F("CLSH","Cluster Size for the Barrel (error bars Mean RMS)",N,0,N);
  TH1F * CLSHE = new TH1F("CLSHE","Cluster Size for the EndCap (error bars Mean RMS)",N,0,N);
  TH1F * pressureH = new TH1F("pressureH","Pressure History",N,0,N);
  TH1F * hvbarrelH = new TH1F("hvbarrelH","High Voltage for the Barrel",N,0,N);
  TH1F * thbarrelH = new TH1F("thbarrelH","Threshold for the the Barrel",N,0,N);
  TH1F * hvendcapH = new TH1F("hvendcapH","High Voltage for the EndCap",N,0,N);
  TH1F * thendcapH = new TH1F("thendcapH","Threshold for the EndCap",N,0,N);
  TH1F * maskedH = new TH1F("maskedH","Average Percentage of strips without data per roll in the Barrel",N,0,N);
  TH1F * maskedendcapH = new TH1F("maskedendcapH","Average Percentage of strips without data per roll in the End Cap",N,0,N);
  TH1F * sensorstpbarrelH = new TH1F("sensorstpbarrelH","Number of sensors in barrel for average temperature",N,0,N);
  TH1F * tpbarrelH = new TH1F("tpbarrelH","Average temperature for the barrel",N,0,N);
  TH1F * sensorstpendcapH = new TH1F("sensorstpendcapH","Number of sensors in endcap for average temperature",N,0,N);
  TH1F * tpendcapH = new TH1F("tpendcapH","Average temperature for the endcap",N,0,N);
  TH1F * channelcubarrelH = new TH1F("channelcubarrelH","Number of channels in barrel for the average current",N,0,N);
  TH1F * cubarrelH = new TH1F("cubarrelH","Average current for the barrel",N,0,N);
  TH1F * cuendcapH = new TH1F("cuendcapH","Average current for the endcap",N,0,N);
  TH1F * channelcuendcapH = new TH1F("channelcuendcapH","Number of channels in endcap for the average current",N,0,N);

  TH2F * correlation_Pressure_Efficiency = new TH2F("correlation_Pressure_Efficiency","correlation_Pressure_Efficiency",100,945,980,100,90,100);
  
  TH2F * correlation_Pressure_Efficiency_Barrel = new TH2F("correlation_Pressure_Efficiency_Barrel","correlation_Pressure_Efficiency_Barrel",100,945,980,100,90,100);
  TH2F * correlation_Pressure_Efficiency_Barrel2 = new TH2F("correlation_Pressure_Efficiency_Barrel2","correlation_Pressure_Efficiency_Barrel2",100,945,980,100,90,100);

  TH2F * correlation_Pressure_Efficiency_Barrel_Wheelm2 = new TH2F("correlation_Pressure_Efficiency_Barrel_Wheelm2","correlation_Pressure_Efficiency_Barrel_Wheelm2",100,945,980,100,0.9,1.0);
  TH2F * correlation_Pressure_Efficiency_Barrel_Wheelm1 = new TH2F("correlation_Pressure_Efficiency_Barrel_Wheelm1","correlation_Pressure_Efficiency_Barrel_Wheelm1",100,945,980,100,0.9,1.0);
  TH2F * correlation_Pressure_Efficiency_Barrel_Wheel0  = new TH2F("correlation_Pressure_Efficiency_Barrel_Wheel0","correlation_Pressure_Efficiency_Barrel_Wheel0",100,945,980,100,0.9,1.0);
  TH2F * correlation_Pressure_Efficiency_Barrel_Wheelp1 = new TH2F("correlation_Pressure_Efficiency_Barrel_Wheelp1","correlation_Pressure_Efficiency_Barrel_Wheelp1",100,945,980,100,0.9,1.0);
  TH2F * correlation_Pressure_Efficiency_Barrel_Wheelp2 = new TH2F("correlation_Pressure_Efficiency_Barrel_Wheelp2","correlation_Pressure_Efficiency_Barrel_Wheelp2",100,945,980,100,0.9,1.0);


  TH2F * correlation_Pressure_Efficiency_EndCap = new TH2F("correlation_Pressure_Efficiency_EndCap","correlation_Pressure_Efficiency_EndCap",100,945,980,100,90,100);
  TH2F * correlation_Pressure_Efficiency_EndCap2 = new TH2F("correlation_Pressure_Efficiency_EndCap2","correlation_Pressure_Efficiency_EndCap2",100,945,980,100,90,100);


  TH2F * correlation_Pressure_ClusterSize = new TH2F("correlation_Pressure_ClusterSize","correlation_Pressure_ClusterSize",100,945,980,100,1.3,2.5);
  TH2F * correlation_Pressure_ClusterSize_Barrel = new TH2F("correlation_Pressure_ClusterSize_Barrel","correlation_Pressure_ClusterSize_Barrel",100,945,980,100,1.3,2.5);
  TH2F * correlation_Pressure_ClusterSize_EndCap = new TH2F("correlation_Pressure_ClusterSize_EndCap","correlation_Pressure_ClusterSize_EndCap",100,945,980,100,1.3,2.5);
  
  TH2F * correlation_Pressure_ClusterSize_Barrel2 = new TH2F("correlation_Pressure_ClusterSize_Barrel2","correlation_Pressure_ClusterSize_Barrel2",100,945,980,100,1.3,2.5);
  TH2F * correlation_Pressure_ClusterSize_EndCap2 = new TH2F("correlation_Pressure_ClusterSize_EndCap2","correlation_Pressure_ClusterSize_EndCap2",100,945,980,100,1.3,2.5);

  TH2F * correlation_Efficiency_ClusterSize_Barrel = new TH2F("correlation_Efficiency_ClusterSize_Barrel","correlation_Efficiency_ClusterSize_Barrel",100,90,100,100,1.3,2.5);
  TH2F * correlation_Efficiency_ClusterSize_EndCap = new TH2F("correlation_Efficiency_ClusterSize_EndCap","correlation_Efficiency_ClusterSize_EndCap",100,90,100,100,1.3,2.5);
  
    std::cout<<"Before the while "<<std::endl;

  int counter = 0;
  string run;

  int index=1;

  while(!fileruns.eof() && counter < N){
    getline(fileruns,run);
    std::cout<<" In run = "<<run<<std::endl;
    if(run.size()==0) continue;
    //TFile * theFile = new TFile(("/afs/cern.ch/user/c/carrillo/workspace/efficiencynoptt/_RPCMonitor_Run2016B-v2_RAW/"+run+"/efficiency-"+run+".root").c_str());
    //TFile * secFile = new TFile(("/afs/cern.ch/user/c/carrillo/workspace/efficiencynoptt/_RPCMonitor_Run2016B-v2_RAW/"+run+"/secefficiency-"+run+".root").c_str());
    
    //TFile * theFile = new TFile(("/afs/cern.ch/user/c/carrillo/workspace/efficiency/_RPCMonitor_Run2016B-v2_RAW/"+run+"/efficiency-"+run+".root").c_str());
    //TFile * secFile = new TFile(("/afs/cern.ch/user/c/carrillo/workspace/efficiency/_RPCMonitor_Run2016B-v2_RAW/"+run+"/secefficiency-"+run+".root").c_str());

    TFile * theFile = new TFile(("/afs/cern.ch/user/c/carrillo/workspace/efficiencycls/_RPCMonitor_Run2016B-v2_RAW/"+run+"/efficiency-"+run+".root").c_str());
    TFile * secFile = new TFile(("/afs/cern.ch/user/c/carrillo/workspace/efficiencycls/_RPCMonitor_Run2016B-v2_RAW/"+run+"/secefficiency-"+run+".root").c_str());

    if(!theFile) continue;
    if(!secFile) continue;
    
    cout<<"Both Files exsit"<<endl;

    //Set Run Axis

    //    if(index%5==0){
    if(index%1==0){
      EventsH->GetXaxis()->SetBinLabel(index,run.c_str());
      durationH->GetXaxis()->SetBinLabel(index,run.c_str());

      EfficiencyPerLayer1H->GetXaxis()->SetBinLabel(index,run.c_str());
      EfficiencyPerLayer2H->GetXaxis()->SetBinLabel(index,run.c_str());
      EfficiencyPerLayer3H->GetXaxis()->SetBinLabel(index,run.c_str());
      EfficiencyPerLayer4H->GetXaxis()->SetBinLabel(index,run.c_str());
      EfficiencyPerLayer5H->GetXaxis()->SetBinLabel(index,run.c_str());
      EfficiencyPerLayer6H->GetXaxis()->SetBinLabel(index,run.c_str());

      EfficiencyPerRingm3->GetXaxis()->SetBinLabel(index,run.c_str());
      EfficiencyPerRingm2->GetXaxis()->SetBinLabel(index,run.c_str());
      EfficiencyPerRing2->GetXaxis()->SetBinLabel(index,run.c_str());
      EfficiencyPerRing3->GetXaxis()->SetBinLabel(index,run.c_str());

      CentralEffBarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffBarrelH_black_masked->GetXaxis()->SetBinLabel(index,run.c_str());
      Barrel_masked->GetXaxis()->SetBinLabel(index,run.c_str());

      CentralEffBarrelInt->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffBarrelWm2H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffBarrelWm1H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffBarrelW0H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffBarrelW1H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffBarrelW2H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffEndCapH->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffEndCapH_black_masked->GetXaxis()->SetBinLabel(index,run.c_str());
      EndCap_masked->GetXaxis()->SetBinLabel(index,run.c_str());
      
      CentralEffEndCapDm1H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffEndCapDm2H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffEndCapDm3H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffEndCapDm4H->GetXaxis()->SetBinLabel(index,run.c_str());

      CentralEffEndCapInt->GetXaxis()->SetBinLabel(index,run.c_str());
      
      CentralEffEndCapD1H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffEndCapD2H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffEndCapD3H->GetXaxis()->SetBinLabel(index,run.c_str());
      CentralEffEndCapD4H->GetXaxis()->SetBinLabel(index,run.c_str());
      
      DoubleGapBarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      DoubleGapEndCapH->GetXaxis()->SetBinLabel(index,run.c_str());
      DoubleGapBarrelH_0->GetXaxis()->SetBinLabel(index,run.c_str());
      DoubleGapEndCapH_0->GetXaxis()->SetBinLabel(index,run.c_str());
      bxbarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      bxendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
      rmsbxbarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      rmsbxendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
      CLSH->GetXaxis()->SetBinLabel(index,run.c_str());
      CLSHE->GetXaxis()->SetBinLabel(index,run.c_str());
      thbarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      hvbarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      pressureH->GetXaxis()->SetBinLabel(index,run.c_str());
      thendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
      hvendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
      maskedH->GetXaxis()->SetBinLabel(index,run.c_str());
      maskedendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
      
      sensorstpbarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      tpbarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      
      sensorstpendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
      tpendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
    	       
      channelcubarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      cubarrelH->GetXaxis()->SetBinLabel(index,run.c_str());
      
      channelcuendcapH->GetXaxis()->SetBinLabel(index,run.c_str());    
      cuendcapH->GetXaxis()->SetBinLabel(index,run.c_str());
    }

    pressure.close();
    
    TH1F * Statistics = (TH1F*) (theFile->Get("DQMData/Muons/MuonSegEff/Statistics"));
    EventsH->SetBinContent(index,Statistics->GetBinContent(1));

    //if(Statistics->GetBinContent(1)<500000) continue;
    counter++;

    durationH->SetBinContent(index,durationinfo[run]);

    TH1F * EfficiencyPerLayer = (TH1F*) (secFile->Get("EfficiencyPerLayer"));
    
    EfficiencyPerLayer1H->SetBinContent(index,EfficiencyPerLayer->GetBinContent(1)/100);
    EfficiencyPerLayer2H->SetBinContent(index,EfficiencyPerLayer->GetBinContent(2)/100);
    EfficiencyPerLayer3H->SetBinContent(index,EfficiencyPerLayer->GetBinContent(3)/100);
    EfficiencyPerLayer4H->SetBinContent(index,EfficiencyPerLayer->GetBinContent(4)/100);
    EfficiencyPerLayer5H->SetBinContent(index,EfficiencyPerLayer->GetBinContent(5)/100);
    EfficiencyPerLayer6H->SetBinContent(index,EfficiencyPerLayer->GetBinContent(6)/100);

    EfficiencyPerLayer1H->SetBinError(index,EfficiencyPerLayer->GetBinError(1)/100);
    EfficiencyPerLayer2H->SetBinError(index,EfficiencyPerLayer->GetBinError(2)/100);
    EfficiencyPerLayer3H->SetBinError(index,EfficiencyPerLayer->GetBinError(3)/100);
    EfficiencyPerLayer4H->SetBinError(index,EfficiencyPerLayer->GetBinError(4)/100);
    EfficiencyPerLayer5H->SetBinError(index,EfficiencyPerLayer->GetBinError(5)/100);
    EfficiencyPerLayer6H->SetBinError(index,EfficiencyPerLayer->GetBinError(6)/100);

    EfficiencyPerRingm3->SetBinContent(index,RingEfficiency(secFile,-3));
    EfficiencyPerRingm2->SetBinContent(index,RingEfficiency(secFile,-2));
    EfficiencyPerRing2->SetBinContent(index,RingEfficiency(secFile,2));
    EfficiencyPerRing3->SetBinContent(index,RingEfficiency(secFile,3));
    
    TH1F * CentralEffBarrel = (TH1F*) (secFile->Get("CentralEffBarrel"));
    TH1F * CentralEffBarrel_black = (TH1F*) (secFile->Get("CentralEffBarrel_black"));
    TH1F * CentralEffBarrel_black_masked = (TH1F*) (secFile->Get("CentralEffBarrel_black_masked"));

    CentralEffBarrelH->SetBinContent(index,CentralEffBarrel->GetMean());
    CentralEffBarrelH->SetBinError(index,CentralEffBarrel->GetRMS()/sqrt(CentralEffBarrel->GetEntries()));

    CentralEffBarrelH_black_masked->SetBinContent(index,CentralEffBarrel_black_masked->GetMean());
    CentralEffBarrelH_black_masked->SetBinError(index,CentralEffBarrel_black_masked->GetRMS()/sqrt(CentralEffBarrel->GetEntries()));


    Barrel_masked->SetBinContent(index,1020-(CentralEffBarrel->GetEntries()-CentralEffBarrel_black_masked->GetEntries()));

    /*
    if(atoi(run.c_str())<178985){
      cout<<" 2011"<<endl;
      Barrel_masked->SetBinContent(index,1020-41+CentralEffBarrel_black->GetEntries()-CentralEffBarrel_black_masked->GetEntries());
    }else{
      cout<<" 2012"<<endl;
      Barrel_masked->SetBinContent(index,1020-54+CentralEffBarrel_black->GetEntries()-CentralEffBarrel_black_masked->GetEntries());
    }
    */


    CentralEffBarrelInt->SetBinContent(index,BarrelEfficiency(secFile));
    CentralEffBarrelWm2H->SetBinContent(index,WheelEfficiency(secFile,-2));
    CentralEffBarrelWm1H->SetBinContent(index,WheelEfficiency(secFile,-1));
    CentralEffBarrelW0H->SetBinContent(index,WheelEfficiency(secFile,0));
    CentralEffBarrelW1H->SetBinContent(index,WheelEfficiency(secFile,1));
    CentralEffBarrelW2H->SetBinContent(index,WheelEfficiency(secFile,2));

    CentralEffBarrelWm2H->SetBinError(index,WheelError(secFile,-2));
    CentralEffBarrelWm1H->SetBinError(index,WheelError(secFile,-1));
    CentralEffBarrelW0H->SetBinError(index,WheelError(secFile,0));
    CentralEffBarrelW1H->SetBinError(index,WheelError(secFile,1));
    CentralEffBarrelW2H->SetBinError(index,WheelError(secFile,2));

    TH1F * CentralEffEndCap = (TH1F*) (secFile->Get("CentralEffEndCap"));
    CentralEffEndCapH->SetBinContent(index,CentralEffEndCap->GetMean());
    CentralEffEndCapH->SetBinError(index,CentralEffEndCap->GetRMS()/sqrt(CentralEffEndCap->GetEntries()));

    TH1F * CentralEffEndCap_black = (TH1F*) (secFile->Get("CentralEffEndCap_black"));

    TH1F * CentralEffEndCap_black_masked = (TH1F*) (secFile->Get("CentralEffEndCap_black_masked"));

    CentralEffEndCapH_black_masked->SetBinContent(index,CentralEffEndCap_black_masked->GetMean());
    CentralEffEndCapH_black_masked->SetBinError(index,CentralEffEndCap_black_masked->GetRMS()/sqrt(CentralEffEndCap_black_masked->GetEntries()));


    EndCap_masked->SetBinContent(index,1152-(CentralEffEndCap->GetEntries()-CentralEffEndCap_black_masked->GetEntries()));

    /*if(atoi(run.c_str())<178985){
      EndCap_masked->SetBinContent(index,1152-72+CentralEffEndCap_black->GetEntries()-CentralEffEndCap_black_masked->GetEntries());
      }else{
      EndCap_masked->SetBinContent(index,1152-115+CentralEffEndCap_black->GetEntries()-CentralEffEndCap_black_masked->GetEntries());
      }
    */


    CentralEffEndCapInt->SetBinContent(index,EndCapEfficiency(secFile));
    CentralEffEndCapDm4H->SetBinContent(index,DiskEfficiency(secFile,-4));
    CentralEffEndCapDm3H->SetBinContent(index,DiskEfficiency(secFile,-3));
    CentralEffEndCapDm2H->SetBinContent(index,DiskEfficiency(secFile,-2));
    CentralEffEndCapDm1H->SetBinContent(index,DiskEfficiency(secFile,-1));
    CentralEffEndCapD1H->SetBinContent(index,DiskEfficiency(secFile,1));
    CentralEffEndCapD2H->SetBinContent(index,DiskEfficiency(secFile,2));
    CentralEffEndCapD3H->SetBinContent(index,DiskEfficiency(secFile,3));
    CentralEffEndCapD4H->SetBinContent(index,DiskEfficiency(secFile,4));

    CentralEffEndCapDm4H->SetBinError(index,DiskError(secFile,-4));
    CentralEffEndCapDm3H->SetBinError(index,DiskError(secFile,-3));
    CentralEffEndCapDm2H->SetBinError(index,DiskError(secFile,-2));
    CentralEffEndCapDm1H->SetBinError(index,DiskError(secFile,-1));
    CentralEffEndCapD1H->SetBinError(index,DiskError(secFile,1));
    CentralEffEndCapD2H->SetBinError(index,DiskError(secFile,2));
    CentralEffEndCapD3H->SetBinError(index,DiskError(secFile,3));
    CentralEffEndCapD4H->SetBinError(index,DiskError(secFile,4));

    TH1F * DoubleGapBarrel = (TH1F*) (secFile->Get("DoubleGapBarrel"));
    DoubleGapBarrelH->SetBinContent(index,DoubleGapBarrel->GetMean());
    DoubleGapBarrelH_0->SetBinContent(index,GetMean_0(DoubleGapBarrel));

    TH1F * DoubleGapEndCap = (TH1F*) (secFile->Get("DoubleGapEndCap"));
    DoubleGapEndCapH->SetBinContent(index,DoubleGapEndCap->GetMean());
    DoubleGapEndCapH_0->SetBinContent(index,GetMean_0(DoubleGapEndCap));

    TH2F * bxbarrel = (TH2F*) (secFile->Get("BXBarrel"));
    bxbarrelH->SetBinContent(index,bxbarrel->ProjectionX("_px")->GetMean());
    bxbarrelH->SetBinError(index,bxbarrel->ProjectionX("_px")->GetRMS());

    rmsbxbarrelH->SetBinContent(index,bxbarrel->ProjectionX("_px")->GetRMS());
    
    TH2F * bxendcap = (TH2F*) (secFile->Get("BXEndCap"));
    bxendcapH->SetBinContent(index,bxendcap->ProjectionX("_px")->GetMean());
    bxendcapH->SetBinError(index,bxendcap->ProjectionX("_px")->GetRMS());
    
    rmsbxendcapH->SetBinContent(index,bxendcap->ProjectionX("_px")->GetRMS());
    
    TH1F * CLS = (TH1F*) (secFile->Get("CLS"));
    CLSH->SetBinContent(index,CLS->GetMean());
    //CLSH->SetBinError(index,CLS->GetRMS());
    
    //Cluster Size EndCap
    CLSHE->SetBinContent(index,CLSEndCap(secFile));
    //CLSHE->SetBinError(index,RMSCLSEndCap(secFile));
    
    hvbarrelH->SetBinContent(index,hvbarrelinfo[run]);
    thbarrelH->SetBinContent(index,thbarrelinfo[run]);

    pressureH->SetBinContent(index,pressureinfo[run]);

    hvendcapH->SetBinContent(index,hvendcapinfo[run]);
    thendcapH->SetBinContent(index,thendcapinfo[run]);
    
    maskedH->SetBinContent(index,masked(secFile));
    maskedendcapH->SetBinContent(index,maskedendcap(secFile));
    
    if(tpbarrelinfo[run]!=0){
      if(sensorstpbarrelinfo[run]>250){
	tpbarrelH->SetBinContent(index,tpbarrelinfo[run]);
	tpbarrelH->SetBinError(index,errortpbarrelinfo[run]);
      }
      sensorstpbarrelH->SetBinContent(index,sensorstpbarrelinfo[run]);
    }
    
    if(tpendcapinfo[run]!=0){
      if(sensorstpendcapinfo[run]>50){
	tpendcapH->SetBinContent(index,tpendcapinfo[run]);
	tpendcapH->SetBinError(index,errortpendcapinfo[run]);
      }
      sensorstpendcapH->SetBinContent(index,sensorstpendcapinfo[run]);
    }
    	       
    if(cubarrelinfo[run]!=0){
      if(channelcubarrelinfo[run]>430){
	cubarrelH->SetBinContent(index,cubarrelinfo[run]);
	cubarrelH->SetBinError(index,errorcubarrelinfo[run]);
      }
      channelcubarrelH->SetBinContent(index,channelcubarrelinfo[run]);
    }

    if(cuendcapinfo[run]!=0){
      if(channelcuendcapinfo[run]>170){
	cuendcapH->SetBinContent(index,cuendcapinfo[run]);
	cuendcapH->SetBinError(index,errorcuendcapinfo[run]);
      }
      channelcuendcapH->SetBinContent(index,channelcuendcapinfo[run]);
    }

    float thepressure = pressureinfo[run];
    
    //cout<<"----- Filling "<<WheelEfficiency(secFile,-2)<<" "<<thepressure<<endl;
    correlation_Pressure_Efficiency_Barrel_Wheelm2->Fill(thepressure,WheelEfficiency(secFile,-2));
    correlation_Pressure_Efficiency_Barrel_Wheelm1->Fill(thepressure,WheelEfficiency(secFile,-1));
    correlation_Pressure_Efficiency_Barrel_Wheel0->Fill(thepressure,WheelEfficiency(secFile,0));
    correlation_Pressure_Efficiency_Barrel_Wheelp1->Fill(thepressure,WheelEfficiency(secFile,1));
    correlation_Pressure_Efficiency_Barrel_Wheelp2->Fill(thepressure,WheelEfficiency(secFile,2));

    if(atoi(run.c_str())>191277 && atoi(run.c_str())<191720){
      correlation_Pressure_Efficiency_Barrel->Fill(thepressure,CentralEffBarrel_black_masked->GetMean()); 
      correlation_Pressure_Efficiency_EndCap->Fill(thepressure,CentralEffEndCap_black_masked->GetMean()); 
      correlation_Pressure_ClusterSize_Barrel->Fill(thepressure,CLS->GetMean());   
      correlation_Pressure_ClusterSize_EndCap->Fill(thepressure,CLSEndCap(secFile));

    }else{
      correlation_Pressure_Efficiency_Barrel2->Fill(thepressure,CentralEffBarrel_black_masked->GetMean()); 
      correlation_Pressure_Efficiency_EndCap2->Fill(thepressure,CentralEffEndCap_black_masked->GetMean()); 
      correlation_Pressure_ClusterSize_Barrel2->Fill(thepressure,CLS->GetMean());   
      correlation_Pressure_ClusterSize_EndCap2->Fill(thepressure,CLSEndCap(secFile));
    }
    
    correlation_Pressure_Efficiency->Fill(thepressure,CentralEffBarrel->GetMean()); 
    correlation_Pressure_Efficiency->Fill(thepressure,CentralEffEndCap->GetMean()); 
    correlation_Pressure_ClusterSize->Fill(thepressure,CLS->GetMean()); 
    correlation_Pressure_ClusterSize->Fill(thepressure,CLSEndCap(secFile)); 

    correlation_Efficiency_ClusterSize_Barrel->Fill(CentralEffBarrel->GetMean(),CLS->GetMean());
    correlation_Efficiency_ClusterSize_EndCap->Fill(CentralEffEndCap->GetMean(),CLSEndCap(secFile));
    
    allinfo<<run<<" "<<pressureinfo[run]<<" "<<CentralEffBarrel->GetMean()<<" "<<CentralEffEndCap->GetMean()<<" "<<CLS->GetMean()<<" "<<" "<<CLSEndCap(secFile)<<" "<<masked(secFile)<<" "<<maskedendcap(secFile)<<endl;
    
    delete theFile;
    index++;
  }
  
  //cout<<"counter="<<counter<<endl;

  TCanvas * Ca0 = new TCanvas("Ca0","History",1000,600);

  Ca0->SetFillColor(kWhite);

  setHistoCorrelation(correlation_Pressure_Efficiency,"Efficiency(%)");        Ca0->SaveAs("correlation_Pressure_Efficiency.png");  Ca0->Clear();
  
  correlation_Efficiency_ClusterSize_Barrel->SetMarkerStyle(21);
  correlation_Efficiency_ClusterSize_Barrel->SetMarkerColor(2);
  correlation_Efficiency_ClusterSize_Barrel->SetMarkerColor(kBlue);
  setHistoCorrelation(correlation_Efficiency_ClusterSize_Barrel,"Efficiency Vs Cluster Size(%)");        Ca0->SaveAs("correlation_Efficiency_ClusterSize_Barrel.png");  Ca0->Clear();

  correlation_Efficiency_ClusterSize_EndCap->SetMarkerStyle(21);
  correlation_Efficiency_ClusterSize_EndCap->SetMarkerColor(2);
  correlation_Efficiency_ClusterSize_EndCap->SetMarkerColor(kBlue);
  setHistoCorrelation(correlation_Efficiency_ClusterSize_EndCap,"Efficiency Vs Cluster Size(%)");        Ca0->SaveAs("correlation_Efficiency_ClusterSize_EndCap.png");  Ca0->Clear();
  
  correlation_Pressure_Efficiency_Barrel->GetXaxis()->SetTitle("pressure(mbar)");
  correlation_Pressure_Efficiency_Barrel->GetYaxis()->SetTitle("Efficiency_Barrel(%)");
  correlation_Pressure_Efficiency_Barrel->SetMarkerStyle(21);
  correlation_Pressure_Efficiency_Barrel->SetMarkerColor(2);
  correlation_Pressure_Efficiency_Barrel2->SetMarkerStyle(21);
  correlation_Pressure_Efficiency_Barrel2->SetMarkerColor(kBlue);
  correlation_Pressure_Efficiency_Barrel->Draw();
  correlation_Pressure_Efficiency_Barrel2->Draw("same");
  Ca0->SaveAs("correlation_Pressure_Efficiency_Barrel.png");  Ca0->Clear();
  

  setHistoCorrelation(correlation_Pressure_Efficiency_Barrel_Wheelm2,"Efficiency(%)"); Ca0->SaveAs("correlation_Pressure_Efficiency_Barrel_Wheelm2.png");  Ca0->Clear();
  setHistoCorrelation(correlation_Pressure_Efficiency_Barrel_Wheelm1,"Efficiency(%)"); Ca0->SaveAs("correlation_Pressure_Efficiency_Barrel_Wheelm1.png");  Ca0->Clear();
  setHistoCorrelation(correlation_Pressure_Efficiency_Barrel_Wheel0,"Efficiency(%)"); Ca0->SaveAs("correlation_Pressure_Efficiency_Barrel_Wheel0.png");  Ca0->Clear();
  setHistoCorrelation(correlation_Pressure_Efficiency_Barrel_Wheelp1,"Efficiency(%)"); Ca0->SaveAs("correlation_Pressure_Efficiency_Barrel_Wheelp1.png");  Ca0->Clear();
  setHistoCorrelation(correlation_Pressure_Efficiency_Barrel_Wheelp2,"Efficiency(%)"); Ca0->SaveAs("correlation_Pressure_Efficiency_Barrel_Wheelp2.png");  Ca0->Clear();

  correlation_Pressure_Efficiency_EndCap->GetXaxis()->SetTitle("pressure(mbar)");
  correlation_Pressure_Efficiency_EndCap->GetYaxis()->SetTitle("Efficiency_EndCap(%)");
  correlation_Pressure_Efficiency_EndCap->SetMarkerStyle(21);
  correlation_Pressure_Efficiency_EndCap->SetMarkerColor(2);
  correlation_Pressure_Efficiency_EndCap2->SetMarkerStyle(21);
  correlation_Pressure_Efficiency_EndCap2->SetMarkerColor(kBlue);
  correlation_Pressure_Efficiency_EndCap->Draw();
  correlation_Pressure_Efficiency_EndCap2->Draw("same");
  Ca0->SaveAs("correlation_Pressure_Efficiency_EndCap.png");  Ca0->Clear();
  
  setHistoCorrelation(correlation_Pressure_ClusterSize,"cls");		       Ca0->SaveAs("correlation_Pressure_ClusterSize.png"); Ca0->Clear();

  correlation_Pressure_ClusterSize_Barrel->GetXaxis()->SetTitle("Atmospheric Pressure(mbar)");
  correlation_Pressure_ClusterSize_Barrel->GetYaxis()->SetTitle("Cluster Size Barrel(strips)");

  correlation_Efficiency_ClusterSize_Barrel->GetXaxis()->SetTitle("Efficiency Barrel(%)");
  correlation_Efficiency_ClusterSize_Barrel->GetYaxis()->SetTitle("Cluster Size Barrel(strips)");

  correlation_Efficiency_ClusterSize_EndCap->GetXaxis()->SetTitle("Efficiency EndCap (%)");
  correlation_Efficiency_ClusterSize_EndCap->GetYaxis()->SetTitle("Cluster Size EndCap(strips)");

  correlation_Pressure_ClusterSize_Barrel->SetMarkerStyle(21);
  correlation_Pressure_ClusterSize_Barrel->SetMarkerColor(2);
  correlation_Pressure_ClusterSize_Barrel2->SetMarkerStyle(21);
  correlation_Pressure_ClusterSize_Barrel2->SetMarkerColor(kBlue);
  correlation_Pressure_ClusterSize_Barrel->Draw();
  correlation_Pressure_ClusterSize_Barrel2->Draw("same");
  Ca0->SaveAs("correlation_Pressure_ClusterSize_Barrel.png");  Ca0->Clear();

  correlation_Pressure_ClusterSize_EndCap->GetXaxis()->SetTitle("Atmospheric Pressure(mbar)");
  correlation_Pressure_ClusterSize_EndCap->GetYaxis()->SetTitle("Cluster Size EndCap(strips)");
  correlation_Pressure_ClusterSize_EndCap->SetMarkerStyle(21);
  correlation_Pressure_ClusterSize_EndCap->SetMarkerColor(2);
  correlation_Pressure_ClusterSize_EndCap2->SetMarkerStyle(21);
  correlation_Pressure_ClusterSize_EndCap2->SetMarkerColor(kBlue);
  correlation_Pressure_ClusterSize_EndCap->Draw();
  correlation_Pressure_ClusterSize_EndCap2->Draw("same");
  Ca0->SaveAs("correlation_Pressure_ClusterSize_EndCap.png");  Ca0->Clear();
  
  EventsH->GetYaxis()->SetTitle("Number of Events per run");
  setHisto(EventsH);
  Ca0->SetGrid();
  Ca0->SaveAs("EventsH.png");
  Ca0->Clear();

  durationH->GetYaxis()->SetTitle("Duration of the run (s)");
  setHisto(durationH);
  Ca0->SetGrid();
  Ca0->SaveAs("durationH.png");
  Ca0->Clear();

  CentralEffBarrelH->GetYaxis()->SetTitle("Eff #pm RMS / sqrt N (%), all rolls");
  setHisto(CentralEffBarrelH);
  CentralEffBarrelH->SetMinimum(min_range);
  CentralEffBarrelH->SetMaximum(max_range);
  Ca0->SetGrid();
  Ca0->SaveAs("CentralEffBarrelH.png");
  Ca0->Clear();

  CentralEffBarrelH_black_masked->GetYaxis()->SetTitle("Eff #pm RMS / sqrt N (%), good rolls");
  CentralEffBarrelH_black_masked->GetYaxis()->SetTitleSize(0.04);
  setHisto(CentralEffBarrelH_black_masked);
  CentralEffBarrelH_black_masked->SetMinimum(min_range);
  CentralEffBarrelH_black_masked->SetMaximum(max_range);
  Ca0->SetGrid();
  Ca0->SaveAs("CentralEffBarrelH_black_masked.png");
  Ca0->Clear();

  Barrel_masked->SetTitle("good rolls in the Barrel");
  Barrel_masked->GetYaxis()->SetTitleSize(0.04);
  Barrel_masked->GetYaxis()->SetTitle("good rolls");
  setHisto(Barrel_masked);
  Barrel_masked->SetMinimum(900);
  Barrel_masked->SetMaximum(1020);
  Barrel_masked->SetMarkerStyle(34);
  Barrel_masked->SetMarkerColor(1);
  Barrel_masked->Draw("same");
  Ca0->SetGrid();
  Ca0->SaveAs("Barrel_masked.png");
  Ca0->Clear();

  
  EfficiencyPerLayer1H->GetYaxis()->SetTitle("Mean Efficiency %");
  
  setHistoV(CentralEffBarrelInt); CentralEffBarrelInt->SetMarkerStyle(19); CentralEffBarrelInt->SetMarkerSize(2.5);
  setHistoSameV(EfficiencyPerLayer1H,4); 
  setHistoSameV(EfficiencyPerLayer2H,5);
  setHistoSameV(EfficiencyPerLayer3H,6);
  setHistoSameV(EfficiencyPerLayer4H,7);
  setHistoSameV(EfficiencyPerLayer5H,8);
  setHistoSameV(EfficiencyPerLayer6H,10);
  
  TLegend *leg2 = new TLegend(0.8,0.41,0.93,0.11);
  leg2->AddEntry(EfficiencyPerLayer1H,"Layer 1","p");
  leg2->AddEntry(EfficiencyPerLayer2H,"Layer 2","p");
  leg2->AddEntry(EfficiencyPerLayer3H,"Layer 3","p");
  leg2->AddEntry(EfficiencyPerLayer4H,"Layer 4","p");
  leg2->AddEntry(EfficiencyPerLayer5H,"Layer 5","p");
  leg2->AddEntry(EfficiencyPerLayer6H,"Layer 6","p");
  leg2->AddEntry(CentralEffBarrelInt,"All Barrel","p");
  leg2->Draw("same");
  Ca0->SetGrid();
  Ca0->SaveAs("EfficiencyPerLayerH.png");
  Ca0->Clear();
  leg2->Delete();
  
  CentralEffBarrelInt->GetYaxis()->SetTitle("Mean Efficiency %");
  
  setHistoV(CentralEffBarrelInt); CentralEffBarrelInt->SetMarkerStyle(19); CentralEffBarrelInt->SetMarkerSize(2.5);
  setHistoSameV(CentralEffBarrelWm2H,4);
  setHistoSameV(CentralEffBarrelWm1H,5);
  setHistoSameV(CentralEffBarrelW0H,6);
  setHistoSameV(CentralEffBarrelW1H,7);
  setHistoSameV(CentralEffBarrelW2H,8);
  
  TLegend *leg3 = new TLegend(0.8,0.41,0.93,0.11);
  leg3->AddEntry(CentralEffBarrelWm2H,"wheel -2","p");
  leg3->AddEntry(CentralEffBarrelWm1H,"wheel -1","p");
  leg3->AddEntry(CentralEffBarrelW0H,"wheel 0","p");
  leg3->AddEntry(CentralEffBarrelW1H,"wheel +1","p");
  leg3->AddEntry(CentralEffBarrelW2H,"wheel +2","p");
  leg3->AddEntry(CentralEffBarrelInt,"All Barrel","p");
  leg3->Draw("same");
  Ca0->SetGrid();
  Ca0->SaveAs("CentralEffBarrelWH.png");
  Ca0->Clear();
  leg3->Delete();
  
  CentralEffEndCapH->GetYaxis()->SetTitle("Eff #pm RMS / sqrt N (%), all rolls");
  setHisto(CentralEffEndCapH);
  CentralEffEndCapH->SetMinimum(min_range);
  CentralEffEndCapH->SetMaximum(max_range);
  Ca0->SetGrid();
  Ca0->SaveAs("CentralEffEndCapH.png");
  Ca0->Clear();

  CentralEffEndCapH_black_masked->GetYaxis()->SetTitle("Eff #pm RMS / sqrt N (%), good rolls");
  CentralEffEndCapH_black_masked->GetYaxis()->SetTitleSize(0.04);
  setHisto(CentralEffEndCapH_black_masked);
  CentralEffEndCapH_black_masked->SetMinimum(min_range);
  CentralEffEndCapH_black_masked->SetMaximum(max_range);
  Ca0->SetGrid();
  Ca0->SaveAs("CentralEffEndCapH_black_masked.png");
  Ca0->Clear();

  EndCap_masked->SetTitle("good rolls EndCaps");
  EndCap_masked->GetYaxis()->SetTitleSize(0.04);
  EndCap_masked->GetYaxis()->SetTitle("good rolls");
  setHisto(EndCap_masked);
  EndCap_masked->SetMinimum(900);
  EndCap_masked->SetMaximum(1152);
  EndCap_masked->SetMarkerStyle(34);
  EndCap_masked->SetMarkerColor(1);
  EndCap_masked->Draw("same");
  Ca0->SetGrid();
  Ca0->SaveAs("EndCap_masked.png");
  Ca0->Clear();

  setHistoV(CentralEffEndCapInt); CentralEffEndCapInt->SetMarkerStyle(19); CentralEffEndCapInt->SetMarkerSize(2.5);
  setHistoSameV(CentralEffEndCapDm4H,3);
  setHistoSameV(CentralEffEndCapDm3H,4);
  setHistoSameV(CentralEffEndCapDm2H,5);
  setHistoSameV(CentralEffEndCapDm1H,6);
  setHistoSameV(CentralEffEndCapD1H,7);
  setHistoSameV(CentralEffEndCapD2H,8);
  setHistoSameV(CentralEffEndCapD3H,9);
  setHistoSameV(CentralEffEndCapD4H,10);
  
  TLegend *leg4 = new TLegend(0.8,0.41,0.93,0.11);
  leg4->AddEntry(CentralEffEndCapDm4H,"disk -4","p");
  leg4->AddEntry(CentralEffEndCapDm3H,"disk -3","p");
  leg4->AddEntry(CentralEffEndCapDm2H,"disk -2","p");
  leg4->AddEntry(CentralEffEndCapDm1H,"disk -1","p");
  leg4->AddEntry(CentralEffEndCapD1H,"disk 1","p");
  leg4->AddEntry(CentralEffEndCapD2H,"disk 2","p");
  leg4->AddEntry(CentralEffEndCapD3H,"disk 3","p");
  leg4->AddEntry(CentralEffEndCapD4H,"disk 4","p");
  leg4->AddEntry(CentralEffEndCapInt,"All EndCap","p");
  
  leg4->Draw("same");
  Ca0->SetGrid();
  Ca0->SaveAs("CentralEffEndCapDH.png");
  Ca0->Clear();
  leg4->Delete();

  setHistoV(CentralEffEndCapInt); CentralEffEndCapInt->SetMarkerStyle(19); CentralEffEndCapInt->SetMarkerSize(2.5);
  setHistoSameV(EfficiencyPerRingm3,3);
  setHistoSameV(EfficiencyPerRingm2,4);
  setHistoSameV(EfficiencyPerRing2,5);
  setHistoSameV(EfficiencyPerRing3,6);
  
  TLegend *leg6 = new TLegend(0.8,0.41,0.93,0.11);
  leg6->AddEntry(EfficiencyPerRingm3,"ring -3","p");
  leg6->AddEntry(EfficiencyPerRingm2,"ring -2","p");
  leg6->AddEntry(EfficiencyPerRing2,"ring 2","p");
  leg6->AddEntry(EfficiencyPerRing3,"ring 3","p");
  leg6->AddEntry(CentralEffEndCapInt,"All EndCap","p");
  
  leg6->Draw("same");
  Ca0 ->SetGrid();
  Ca0->SaveAs("EfficiencyPerRingH.png");
  Ca0->Clear();
  leg6->Delete();

  
  DoubleGapBarrelH->GetYaxis()->SetTitle("Mean Efficiency %");
  setHisto(DoubleGapBarrelH);
  Ca0->SetGrid();
  Ca0->SaveAs("DoubleGapBarrelH.png");
  Ca0->Clear();
  
  DoubleGapEndCapH->GetYaxis()->SetTitle("Mean Efficiency %");
  setHisto(DoubleGapEndCapH);
  Ca0->SetGrid();
  Ca0->SaveAs("DoubleGapEndCapH.png");
  Ca0->Clear();

  DoubleGapBarrelH_0->GetYaxis()->SetTitle("Mean Efficiency %");
  setHisto(DoubleGapBarrelH_0);
  Ca0->SetGrid();
  Ca0->SaveAs("DoubleGapBarrelH_0.png");
  Ca0->Clear();
  
  DoubleGapEndCapH_0->GetYaxis()->SetTitle("Mean Efficiency %");
  setHisto(DoubleGapEndCapH_0);
  Ca0->SetGrid();
  Ca0->SaveAs("DoubleGapEndCapH_0.png");
  Ca0->Clear();

  bxendcapH->GetYaxis()->SetTitle("Mean BX (bx units)");
  //bxendcapH->SetMinimum(-10);
  //bxendcapH->SetMaximum(10);
  setHisto(bxendcapH);
  Ca0->SetGrid();
  Ca0->SaveAs("bxendcapH.png");
  Ca0->Clear();

  bxbarrelH->GetYaxis()->SetTitle("Mean BX (bx units)");
  //bxbarrelH->SetMinimum(-10)2A;
  //bxbarrelH->SetMaximum(10);
  setHisto(bxbarrelH);
  Ca0->SetGrid();
  Ca0->SaveAs("bxbarrelH.png");
  Ca0->Clear();

  rmsbxendcapH->GetYaxis()->SetTitle("RMS of the Mean BX Distribution (bx units)");
  //rmsbxendcapH->SetMinimum(-10);
  //rmsbxendcapH->SetMaximum(10);
  setHisto(rmsbxendcapH);
  Ca0->SetGrid();
  Ca0->SaveAs("rmsbxendcapH.png");
  Ca0->Clear();
 
  rmsbxbarrelH->GetYaxis()->SetTitle("RMS of the Mean BX Distribution (bx units)");
  //rmsbxbarrelH->SetMinimum(-10);
  //rmsbxbarrelH->SetMaximum(10);
  setHisto(rmsbxbarrelH);
  Ca0->SetGrid();
  Ca0->SaveAs("rmsbxbarrelH.png");
  Ca0->Clear();

  CLSH->GetYaxis()->SetTitle("Mean Cluster Size Barrel (strips)");
  setHisto(CLSH);
  CLSH->SetMaximum(3.5);
  CLSH->SetMinimum(0.5);
  Ca0->SetGrid();
  Ca0->SaveAs("CLSH.png");
  Ca0->Clear();

  CLSHE->GetYaxis()->SetTitle("Mean Cluster Size EndCap (strips)");
  setHisto(CLSHE);
  CLSHE->SetMaximum(3.5);
  CLSHE->SetMinimum(0.5);
  Ca0->SetGrid();
  Ca0->SaveAs("CLSHE.png");
  Ca0->Clear();

  pressureH->GetYaxis()->SetTitle("pressure(mbar)");
  setHisto(pressureH);
  pressureH->SetMaximum(1000);
  pressureH->SetMinimum(940);
  Ca0->SetGrid();
  Ca0->SaveAs("pressureH.png");
  Ca0->Clear();

  hvbarrelH->GetYaxis()->SetTitle("High Voltage (kV)");
  setHisto(hvbarrelH);
  Ca0->SetGrid();
  Ca0->SaveAs("hvbarrelH.png");
  Ca0->Clear();

  hvendcapH->GetYaxis()->SetTitle("High Voltage (kV)");
  setHisto(hvendcapH);
  Ca0->SetGrid();
  Ca0->SaveAs("hvendcapH.png");
  Ca0->Clear();

  thendcapH->GetYaxis()->SetTitle("Threshold(mV)");
  setHisto(thendcapH);
  Ca0->SetGrid();
  Ca0->SaveAs("thendcapH.png");
  Ca0->Clear();

  thbarrelH->GetYaxis()->SetTitle("Threshold(mV)");
  setHisto(thbarrelH);
  Ca0->SetGrid();
  Ca0->SaveAs("thbarrelH.png");
  Ca0->Clear();

  maskedH->GetYaxis()->SetTitle("%");
  setHisto(maskedH);
  Ca0->SetGrid();
  Ca0->SaveAs("maskedH.png");
  Ca0->Clear();

  maskedendcapH->GetYaxis()->SetTitle("%");
  setHisto(maskedendcapH);
  Ca0->SetGrid();
  Ca0->SaveAs("maskedendcapH.png");
  Ca0->Clear();
  

  //--Temeperature and Current ---

  sensorstpbarrelH->GetYaxis()->SetTitle("Number of sensors");
  setHisto(sensorstpbarrelH);
  Ca0->SetGrid();
  Ca0->SaveAs("sensorstpbarrelH.png");
  Ca0->Clear();

  tpbarrelH->GetYaxis()->SetTitle("Celsius");
  setHisto(tpbarrelH);
  tpbarrelH->SetMinimum(17);
  tpbarrelH->SetMaximum(23);
  Ca0->SetGrid();
  Ca0->SaveAs("tpbarrelH.png");
  Ca0->Clear();

  sensorstpendcapH->GetYaxis()->SetTitle("Number of sensors");
  setHisto(sensorstpendcapH);
  Ca0->SetGrid();
  Ca0->SaveAs("sensorstpendcapH.png");
  Ca0->Clear();

  tpendcapH->GetYaxis()->SetTitle("Celsius");
  setHisto(tpendcapH);
  tpendcapH->SetMinimum(17);
  tpendcapH->SetMaximum(23);
  Ca0->SetGrid();
  Ca0->SaveAs("tpendcapH.png");
  Ca0->Clear();
	  
  channelcubarrelH->GetYaxis()->SetTitle("Number of channels");
  setHisto(channelcubarrelH);
  Ca0->SetGrid();
  Ca0->SaveAs("channelcubarrelH.png");
  Ca0->Clear();

  cubarrelH->GetYaxis()->SetTitle("uA");
  setHisto(cubarrelH);
  Ca0->SetGrid();
  Ca0->SaveAs("cubarrelH.png");
  Ca0->Clear();

  channelcuendcapH->GetYaxis()->SetTitle("Number of channels");
  setHisto(channelcuendcapH);
  Ca0->SetGrid();
  Ca0->SaveAs("channelcuendcapH.png");
  Ca0->Clear();

  cuendcapH->GetYaxis()->SetTitle("uA");
  setHisto(cuendcapH);
  Ca0->SetGrid();
  Ca0->SaveAs("cuendcapH.png");
  Ca0->Clear();
 
 //-------------------------------
  
  setHistonormalized(CLSH,21);
  setHistosame(DoubleGapBarrelH,22);
  //setHistosame(hvbarrelH,23);
  //setHistosame(thbarrelH,24);

  TLegend *leg5 = new TLegend(0.1295987,0.1437824,0.4297659,0.2448187,NULL,"brNDC");
  leg5->AddEntry(DoubleGapBarrelH,"Efficiency","plc");
  leg5->AddEntry(CLSH,"Cluster Size","plc");
  //leg5->AddEntry(hvbarrelH,"High Voltage","plc");
  //leg5->AddEntry(thbarrelH,"Threshold","plc");
  leg5->Draw("same");
  leg5->Delete();

  Ca0->SaveAs("all.png");

  TFile *  theFileOut = new TFile("summaryTest.root", "RECREATE");
  theFileOut->cd();
  CLSH->Write();
  
  CentralEffBarrelH->Write();
  CentralEffBarrelH_black_masked->Write();
  
  CentralEffBarrelInt->Write();
  CentralEffBarrelWm2H->Write();
  CentralEffBarrelWm1H->Write();
  CentralEffBarrelW0H->Write();
  CentralEffBarrelW1H->Write();
  CentralEffBarrelW2H->Write();

  CentralEffEndCapH->Write();
  CentralEffEndCapH_black_masked->Write();

  CentralEffEndCapInt->Write();
  CentralEffEndCapDm4H->Write();
  CentralEffEndCapDm3H->Write();
  CentralEffEndCapDm2H->Write();
  CentralEffEndCapDm1H->Write();
  CentralEffEndCapD1H->Write();
  CentralEffEndCapD2H->Write();
  CentralEffEndCapD3H->Write();
  CentralEffEndCapD4H->Write();
  
  
  pressureH->Write();
  //hvbarrelH->Write();
  //thbarrelH->Write();
  //hvendcapH->Write();
  //thendcapH->Write();
  DoubleGapBarrelH->Write();
  EventsH->Write();
  durationH->Write();
  DoubleGapBarrelH->Write();
  DoubleGapEndCapH->Write();
  DoubleGapBarrelH_0->Write(); 
  DoubleGapEndCapH_0->Write(); 
  bxbarrelH->Write();
  bxendcapH->Write();
  rmsbxbarrelH->Write();
  rmsbxendcapH->Write();
  CLSH->Write();
  maskedH->Write();
  maskedendcapH->Write();
  sensorstpbarrelH->Write();
  tpbarrelH->Write();
  sensorstpendcapH->Write();
  tpendcapH->Write();
  channelcubarrelH->Write();
  cubarrelH->Write();
  cuendcapH->Write();
  channelcuendcapH->Write();
  theFileOut->Write();

  pressure.close();
  fileruns.close();

  exit(0);
}
