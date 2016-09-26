#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include "TLegend"

void setHisto(TH1F * residuals, string title,string name,bool barrel){
  residuals->GetXaxis()->SetTitle(name.c_str());
  if(barrel){
    residuals->GetXaxis()->SetLabelSize(0.05);
    residuals->GetXaxis()->SetTitleSize(0.05);
  }else{
    residuals->GetXaxis()->SetLabelSize(0.065);
    residuals->GetXaxis()->SetTitleSize(0.065);
  }
  
  residuals->GetXaxis()->SetRangeUser(-6,6);
  residuals->SetLineWidth(3);
  
  residuals->Fit("gaus","Q" ,"C" ,-3,3);
  float sigma = residuals->GetFunction("gaus")->GetParameter(2);
  stringstream legend;
  TLegend *leg = new TLegend(0.65,0.93,0.89,0.7);
  legend.str("");
  if(sigma<1) legend<<"#sigma="<<setprecision(2)<<sigma<<"cm";
  else        legend<<"#sigma="<<setprecision(3)<<sigma<<"cm";

  residuals->GetFunction("gaus")->SetLineWidth(3);
  leg->AddEntry(residuals->GetFunction("gaus"),legend.str().c_str(),"l");  
  if(barrel)  leg->SetTextSize(0.05);
  else leg->SetTextSize(0.08);
  residuals->Draw();
  leg->Draw("same");
  leg->SetFillColor(0);
}

void setHistocls(TH1F * cls, string title,string name,bool barrel){
  cls->GetXaxis()->SetTitle(name.c_str());
  if(barrel){
    cls->GetXaxis()->SetLabelSize(0.05);
    cls->GetXaxis()->SetTitleSize(0.05);
  }else{
    cls->GetXaxis()->SetLabelSize(0.065);
    cls->GetXaxis()->SetTitleSize(0.065);
  }
  
  cls->SetLineWidth(3);
  
  stringstream legend;
  TLegend *leg = new TLegend(0.65,0.93,0.89,0.7);
  legend.str("");
  legend<<"Mean "<<setprecision(3)<<cls->GetMean();
  leg->AddEntry(cls,legend.str().c_str(),"l");  
  if(barrel)  leg->SetTextSize(0.05);
  else leg->SetTextSize(0.08);
  cls->Draw();
  leg->Draw("same");
  leg->SetFillColor(0);
}

void setHistoeff(TH1F * eff, string title,string name,string wheel){
  eff->GetXaxis()->SetTitle("Sector");
  eff->GetXaxis()->SetLabelSize(0.05);
  eff->GetXaxis()->SetTitleSize(0.05);

  stringstream binLabel;
  
  for(int i=1;i<=12;i++){
    binLabel.str("");
    binLabel<<i;
    eff->GetXaxis()->SetBinLabel(i,binLabel.str().c_str());
  }
  
  stringstream legend;
  TLegend *leg = new TLegend(0.70,0.98,0.94,0.75);
  legend.str("");
  legend<<"Wheel "<<wheel;
  leg->AddEntry(eff,legend.str().c_str(),"l");  
  leg->SetTextSize(0.05);
  eff->Draw();
  eff->SetDrawOption("COLZ");
  leg->Draw("same");
  leg->SetFillColor(0);
}

void setHistoeffEndCap(TH1F * eff, string title,string name,string wheel){
  eff->GetXaxis()->SetTitle("Chamber");
  eff->GetXaxis()->SetLabelSize(0.03);
  eff->GetXaxis()->SetTitleSize(0.05);

  eff->GetXaxis()->LabelsOption("v");

  stringstream binLabel;
  
  for(int i=1;i<=36;i++){
    binLabel.str("");
    binLabel<<i;
    eff->GetXaxis()->SetBinLabel(i,binLabel.str().c_str());
  }
  
  eff->Draw();
  eff->SetDrawOption("COLZ");
}



void gaussianResolutionMuonPaper(){
  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  cout<<"getting the file"<<endl;

  TFile * theFile = new TFile("secTMP.root");  
  //All Residuals
  cout<<"getting the histo"<<endl;

  TCanvas * Ca0 = new TCanvas("Ca0","Residuals",1200,800);  Ca0->Divide(3,2);
  Ca0->SetFillColor(0);
  
  string name,title;
  name = "residuals RB1in (cm)"; title = "residualRB1in";  TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca0_1->cd(); Ca0_1->SetFillColor(0);   setHisto(residuals,title,name,true); 
  name = "residuals RB1out (cm)";title = "residualRB1out"; TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca0_2->cd(); Ca0_2->SetFillColor(0);   setHisto(residuals,title,name,true); 
  name = "residuals RB2in (cm)"; title = "residualRB2in";  TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca0_3->cd(); Ca0_3->SetFillColor(0);   setHisto(residuals,title,name,true); 
  name = "residuals RB2out (cm)";title = "residualRB2out"; TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca0_4->cd(); Ca0_4->SetFillColor(0);   setHisto(residuals,title,name,true); 
  name = "residuals RB3 (cm)";   title = "residualRB3";    TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca0_5->cd(); Ca0_5->SetFillColor(0);   setHisto(residuals,title,name,true); 
  name = "residuals RB4 (cm)";   title = "residualRB4";    TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca0_6->cd(); Ca0_6->SetFillColor(0);   setHisto(residuals,title,name,true); 
 
  Ca0->SaveAs("resolutionBarrel.png"); 

  TCanvas * Ca01 = new TCanvas("Ca01","CLS",1200,800);  Ca01->Divide(3,2);
  Ca01->SetFillColor(0);

  string name,title;
  name = "cluster-size RB1in"; title = "ClusterSizeForLayer1"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca01_1->cd(); Ca01_1->SetFillColor(0);   setHistocls(cls,title,name,true); 
  name = "cluster-size RB1out";title = "ClusterSizeForLayer2"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca01_2->cd(); Ca01_2->SetFillColor(0);   setHistocls(cls,title,name,true); 
  name = "cluster-size RB2in"; title = "ClusterSizeForLayer3"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca01_3->cd(); Ca01_3->SetFillColor(0);   setHistocls(cls,title,name,true); 
  name = "cluster-size RB2out";title = "ClusterSizeForLayer4"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca01_4->cd(); Ca01_4->SetFillColor(0);   setHistocls(cls,title,name,true); 
  name = "cluster-size RB3";   title = "ClusterSizeForLayer5"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca01_5->cd(); Ca01_5->SetFillColor(0);   setHistocls(cls,title,name,true); 
  name = "cluster-size RB4";   title = "ClusterSizeForLayer6"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca01_6->cd(); Ca01_6->SetFillColor(0);   setHistocls(cls,title,name,true); 
 
  Ca01->SaveAs("clsBarrel.png"); 

  TCanvas * Ca1 = new TCanvas("Ca1","Residuals",1200,800);  Ca1->Divide(3,3); Ca1->SetFillColor(0);
  
  name = "residuals RE(1,2,3)/3/A(cm)";title = "residualStation123Ring3_A"; TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_1->cd(); Ca1_1->SetFillColor(0); setHisto(residuals,title,name,false); 
  name = "residuals RE(1,2,3)/3/B(cm)";title = "residualStation123Ring3_B"; TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_2->cd(); Ca1_2->SetFillColor(0); setHisto(residuals,title,name,false); 
  name = "residuals RE(1,2,3)/3/C(cm)";title = "residualStation123Ring3_C"; TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_3->cd(); Ca1_3->SetFillColor(0); setHisto(residuals,title,name,false); 
  name = "residuals RE(2,3)/2/A(cm)";title = "residualStation23Ring2_A";  TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_4->cd(); Ca1_4->SetFillColor(0);   setHisto(residuals,title,name,false); 
  name = "residuals RE(2,3)/2/B(cm)";title = "residualStation23Ring2_B";  TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_5->cd(); Ca1_5->SetFillColor(0);   setHisto(residuals,title,name,false); 
  name = "residuals RE(2,3)/2/C(cm)";title = "residualStation23Ring2_C";  TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_6->cd(); Ca1_6->SetFillColor(0);   setHisto(residuals,title,name,false); 
  name = "residuals RE1/2/A(cm)";title = "residualStation1Ring2_A";   TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_7->cd(); Ca1_7->SetFillColor(0);       setHisto(residuals,title,name,false); 
  name = "residuals RE1/2/B(cm)";title = "residualStation1Ring2_B";   TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_8->cd(); Ca1_8->SetFillColor(0);       setHisto(residuals,title,name,false); 
  name = "residuals RE1/2/C(cm)";title = "residualStation1Ring2_C";   TH1F * residuals = (TH1F*) (theFile->Get(title.c_str())); Ca1_9->cd(); Ca1_9->SetFillColor(0);       setHisto(residuals,title,name,false); 

  Ca1->SaveAs("resolutionEndCap.png"); 													     

  TCanvas * Ca11 = new TCanvas("Ca11","CLS",1200,800);  Ca11->Divide(3,3);   Ca11->SetFillColor(0);
  
  name = "cluster-size RE(1,2,3)/3/A";title = "CLSStation123Ring3_A"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca11_1->cd(); Ca11_1->SetFillColor(0); setHistocls(cls,title,name,false); 
  name = "cluster-size RE(1,2,3)/3/B";title = "CLSStation123Ring3_B"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca11_2->cd(); Ca11_2->SetFillColor(0); setHistocls(cls,title,name,false); 
  name = "cluster-size RE(1,2,3)/3/C";title = "CLSStation123Ring3_C"; TH1F * cls = (TH1F*) (theFile->Get(title.c_str())); Ca11_3->cd(); Ca11_3->SetFillColor(0); setHistocls(cls,title,name,false); 
  name = "cluster-size RE(2,3)/2/A";title = "CLSStation23Ring2_A";  TH1F * cls = (TH1F*) (theFile->Get(title.c_str()));   Ca11_4->cd(); Ca11_4->SetFillColor(0); setHistocls(cls,title,name,false); 
  name = "cluster-size RE(2,3)/2/B";title = "CLSStation23Ring2_B";  TH1F * cls = (TH1F*) (theFile->Get(title.c_str()));   Ca11_5->cd(); Ca11_5->SetFillColor(0); setHistocls(cls,title,name,false); 
  name = "cluster-size RE(2,3)/2/C";title = "CLSStation23Ring2_C";  TH1F * cls = (TH1F*) (theFile->Get(title.c_str()));   Ca11_6->cd(); Ca11_6->SetFillColor(0); setHistocls(cls,title,name,false); 
  name = "cluster-size RE1/2/A";title = "CLSStation1Ring2_A";   TH1F * cls = (TH1F*) (theFile->Get(title.c_str()));       Ca11_7->cd(); Ca11_7->SetFillColor(0); setHistocls(cls,title,name,false); 
  name = "cluster-size RE1/2/B";title = "CLSStation1Ring2_B";   TH1F * cls = (TH1F*) (theFile->Get(title.c_str()));       Ca11_8->cd(); Ca11_8->SetFillColor(0); setHistocls(cls,title,name,false); 
  name = "cluster-size RE1/2/C";title = "CLSStation1Ring2_C";   TH1F * cls = (TH1F*) (theFile->Get(title.c_str()));       Ca11_9->cd(); Ca11_9->SetFillColor(0); setHistocls(cls,title,name,false); 

  Ca11->SaveAs("clsEndCap.png"); 													     

  //Efficiency linear scale

  TCanvas * Ca3 = new TCanvas("Ca3","Central Efficiency",1200,800);  Ca3->Divide(2,1); Ca3->SetFillColor(0);
  Ca3_1->cd(); Ca3_1->SetFillColor(0);
  TH1F * CentralEffBarrel = (TH1F*) (theFile->Get("CentralEffBarrel"));
  CentralEffBarrel->GetYaxis()->SetTitle("Number of rolls");
  CentralEffBarrel->GetYaxis()->SetLabelSize(0.04);
  CentralEffBarrel->GetYaxis()->SetTitleSize(0.065);
  CentralEffBarrel->GetXaxis()->SetTitle("Barrel Efficiency %");
  CentralEffBarrel->GetXaxis()->SetLabelSize(0.04);
  CentralEffBarrel->GetXaxis()->SetTitleSize(0.065);
  CentralEffBarrel->SetLineWidth(3);
  TLegend *leg = new TLegend(0.35,0.93,0.59,0.7);
  stringstream legend;
  legend.str("");
  legend<<" "<<setprecision(4)<<CentralEffBarrel->GetMean()<<"%";
  leg->AddEntry(CentralEffBarrel,legend.str().c_str(),"l");  
  leg->SetTextSize(0.05);
  CentralEffBarrel->Draw();
  leg->Draw("same");
  leg->SetFillColor(0);
  Ca3_2->cd(); Ca3_2->SetFillColor(0);
  TH1F * CentralEffEndCap = (TH1F*) (theFile->Get("CentralEffEndCap"));
  CentralEffEndCap->GetYaxis()->SetTitle("Number of rolls");
  CentralEffEndCap->GetYaxis()->SetLabelSize(0.04);
  CentralEffEndCap->GetYaxis()->SetTitleSize(0.065);
  CentralEffEndCap->GetXaxis()->SetTitle("EndCap Efficiency %");
  CentralEffEndCap->GetXaxis()->SetLabelSize(0.04);
  CentralEffEndCap->GetXaxis()->SetTitleSize(0.065);
  CentralEffEndCap->SetLineWidth(3);
  TLegend *leg = new TLegend(0.35,0.93,0.59,0.7);
  stringstream legend;
  legend.str("");
  legend<<" "<<setprecision(4)<<CentralEffEndCap->GetMean()<<"%";
  leg->AddEntry(CentralEffEndCap,legend.str().c_str(),"l");  
  leg->SetTextSize(0.05);
  CentralEffEndCap->Draw();
  leg->Draw("same");
  leg->SetFillColor(0);


  //Efficiency log scale

  TCanvas * Ca33 = new TCanvas("Ca33","Central Efficiency",1200,800);  Ca33->Divide(2,1);   Ca33->SetFillColor(0);
  Ca33_1->cd(); Ca33_1->SetFillColor(0);
  Ca33_1->SetLogy(); 
  TH1F * CentralEffBarrel = (TH1F*) (theFile->Get("CentralEffBarrel"));
  CentralEffBarrel->GetYaxis()->SetTitle("Number of rolls");
  CentralEffBarrel->GetYaxis()->SetLabelSize(0.04);
  CentralEffBarrel->GetYaxis()->SetTitleSize(0.065);
  CentralEffBarrel->GetXaxis()->SetTitle("Barrel Efficiency %");
  CentralEffBarrel->GetXaxis()->SetLabelSize(0.04);
  CentralEffBarrel->GetXaxis()->SetTitleSize(0.065);
  CentralEffBarrel->SetLineWidth(3);
  TLegend *leg = new TLegend(0.35,0.93,0.59,0.7);
  stringstream legend;
  legend.str("");
  legend<<" "<<setprecision(4)<<CentralEffBarrel->GetMean()<<"%";
  leg->AddEntry(CentralEffBarrel,legend.str().c_str(),"l");  
  leg->SetTextSize(0.05);
  CentralEffBarrel->Draw();
  leg->Draw("same");
  leg->SetFillColor(0);
  Ca33_2->cd(); Ca33_2->SetFillColor(0);
  Ca33_2->SetLogy(); 
  TH1F * CentralEffEndCap = (TH1F*) (theFile->Get("CentralEffEndCap"));
  CentralEffEndCap->GetYaxis()->SetTitle("Number of rolls");
  CentralEffEndCap->GetYaxis()->SetLabelSize(0.04);
  CentralEffEndCap->GetYaxis()->SetTitleSize(0.065);
  CentralEffEndCap->GetXaxis()->SetTitle("EndCap Efficiency %");
  CentralEffEndCap->GetXaxis()->SetLabelSize(0.04);
  CentralEffEndCap->GetXaxis()->SetTitleSize(0.065);
  CentralEffEndCap->SetLineWidth(3);
  TLegend *leg = new TLegend(0.35,0.93,0.59,0.7);
  stringstream legend;
  legend.str("");
  legend<<" "<<setprecision(4)<<CentralEffEndCap->GetMean()<<"%";
  leg->AddEntry(CentralEffEndCap,legend.str().c_str(),"l");  
  leg->SetTextSize(0.05);
  CentralEffEndCap->Draw();
  leg->Draw("same");
  leg->SetFillColor(0);

  //Summary Plots
  
  //barrel
  TCanvas * Ca100 = new TCanvas("Ca100","SummaryBarrel",1200,800);  Ca100->Divide(3,2);   Ca100->SetFillColor(0);
  gStyle->SetPalette(1);
  string name,title;
  name = "Efficiency_Roll_vs_Sector_Wheel_-2"; title = "Efficiency_Roll_vs_Sector_Wheel_-2"; TH1F * eff = (TH1F*) (theFile->Get(title.c_str())); Ca100_1->cd(); Ca100_1->SetFillColor(0);   setHistoeff(eff,title,name,"-2"); 
  name = "Efficiency_Roll_vs_Sector_Wheel_-1"; title = "Efficiency_Roll_vs_Sector_Wheel_-1"; TH1F * eff = (TH1F*) (theFile->Get(title.c_str())); Ca100_2->cd(); Ca100_2->SetFillColor(0);   setHistoeff(eff,title,name,"-1"); 
  name = "Efficiency_Roll_vs_Sector_Wheel_0";  title = "Efficiency_Roll_vs_Sector_Wheel_0"; TH1F * eff = (TH1F*) (theFile->Get(title.c_str())); Ca100_3->cd(); Ca100_3->SetFillColor(0);   setHistoeff(eff,title,name,"0"); 
  name = "Efficiency_Roll_vs_Sector_Wheel_+1";  title = "Efficiency_Roll_vs_Sector_Wheel_+1"; TH1F * eff = (TH1F*) (theFile->Get(title.c_str())); Ca100_4->cd(); Ca100_4->SetFillColor(0);   setHistoeff(eff,title,name,"+1"); 
  name = "Efficiency_Roll_vs_Sector_Wheel_+2";  title = "Efficiency_Roll_vs_Sector_Wheel_+2"; TH1F * eff = (TH1F*) (theFile->Get(title.c_str())); Ca100_5->cd(); Ca100_5->SetFillColor(0);   setHistoeff(eff,title,name,"+2"); 
  
  //endcap
  TCanvas * Ca101 = new TCanvas("Ca101","SummaryBarrel",1200,800);  Ca101->Divide(2,1); Ca101->SetFillColor(0);
  gStyle->SetPalette(1);
  string name,title;
  name = "PositiveEndCapSummary"; title = name; TH1F * eff = (TH1F*) (theFile->Get(title.c_str())); Ca101_1->cd(); Ca101_1->SetFillColor(0);   setHistoeffEndCap(eff,title,name,"-2"); 
  name = "NegativeEndCapSummary"; title = name; TH1F * eff = (TH1F*) (theFile->Get(title.c_str())); Ca101_2->cd(); Ca101_2->SetFillColor(0);   setHistoeffEndCap(eff,title,name,"-1"); 

  //CLSEndCap

  TH1F * allCLS[9];
  allCLS[0]= (TH1F*) (theFile->Get("CLSStation1Ring2_A"));
  allCLS[1]= (TH1F*) (theFile->Get("CLSStation1Ring2_B"));
  allCLS[2]= (TH1F*) (theFile->Get("CLSStation1Ring2_C"));
  allCLS[3]= (TH1F*) (theFile->Get("CLSStation23Ring2_A"));
  allCLS[4]= (TH1F*) (theFile->Get("CLSStation23Ring2_B"));
  allCLS[5]= (TH1F*) (theFile->Get("CLSStation23Ring2_C"));
  allCLS[6]= (TH1F*) (theFile->Get("CLSStation123Ring3_A"));
  allCLS[7]= (TH1F*) (theFile->Get("CLSStation123Ring3_B"));
  allCLS[8]= (TH1F*) (theFile->Get("CLSStation123Ring3_C"));
  
  TH1F * CLSE = new TH1F ("CLSE","Cluster Size for all the endcap",10,0.5,10.5);
  for(int k=0;k<9;k++) CLSE->Add(allCLS[k]);

  TCanvas * CaCLSE = new TCanvas("CaCLSE","CLSEndCap",1200,800);  
  CLSE->Draw(0);
  CaCLSE->SaveAs("CLSE.png");
   


  exit(0);
  
}
