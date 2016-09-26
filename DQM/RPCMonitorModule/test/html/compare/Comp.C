{
gROOT->Reset();

gStyle->SetOptStat(0);

#include "Riostream.h"
#include<fstream>

//-----------Parametros de entrada --------------------------------------
/*
 string run1 = "109112";
 string run2 = "109578";

 string descriptionRun1 = "9.2kV";
 string descriptionRun2 = "9.3kV";
*/

 string run1 = "109573";
 string run2 = "110916";

 string descriptionRun1 = "9.3kV_220mV";
 string descriptionRun2 = "9.3kV_210mV";

//-----------------------------------------------------------------------

//-----------------------Bringin Files-----------------------------------

system(("scp -r carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/"+run1+" .").c_str());
system(("scp -r carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/"+run2+" .").c_str());

//----------------------------------------------------------------------


//Reading fils and creating scripts-------------------------------------------

 TFile * theFile2 = new TFile((run2+"/eff"+run2+".root").c_str());
 TFile * theFile2sec = new TFile((run2+"/sec"+run2+".root").c_str());

 TFile * theFile1 = new TFile((run1+"/eff"+run1+".root").c_str());
 TFile * theFile1sec = new TFile((run1+"/sec"+run1+".root").c_str());

 std::string string2 = descriptionRun2+"_Run_"+run2; //should be short!!!
 std::string string1 = descriptionRun1+"_Run_"+run1;

//----------------------------------------------------------------------------

 std::string folder = string1+"Vs"+string2+"/";
 system(("mkdir "+folder).c_str());
 system(("mkdir "+folder+"Sides").c_str());
 system(("mkdir "+folder+"Distro").c_str());
 system(("mkdir "+folder+"CLS").c_str());
 system(("mkdir "+folder+"Greg").c_str());

 std::stringstream sta1; 
 std::stringstream sta2; 


 std::cout<<"Creating Canvas"<<std::endl;
 TCanvas *Ca0 = new TCanvas("Ca0","Plots",1200,600);
 gStyle->SetOptStat(0);

//// Statistics

 std::cout<<"Reading Statistics"<<std::endl;
 TH1F * Statistics1 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Statistics"));
 TH1F * Statistics2 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Statistics"));
 std::cout<<"DrawNormalizeding first Statistics"<<std::endl;
 Statistics2->GetXaxis()->LabelsOption("v");
 Statistics2->GetXaxis()->SetLabelSize(0.035);
 Statistics2->Draw("");
 std::cout<<"DrawNormalizeding second Statistics"<<std::endl;
 Statistics1->SetMarkerColor(9);
 Statistics1->SetLineColor(9);
 Statistics1->GetXaxis()->LabelsOption("v");
 Statistics1->GetXaxis()->SetLabelSize(0.035);
 Statistics1->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<Statistics1->GetMean()<<" RMS="<<Statistics1->GetRMS();
 sta2<<"Mean="<<Statistics2->GetMean()<<" RMS="<<Statistics2->GetRMS();
 leg->AddEntry(Statistics1,(string1).c_str(),"l");  
 leg->AddEntry(Statistics1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(Statistics2,(string2).c_str(),"l");
 leg->AddEntry(Statistics2,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca0->SetBottomMargin(0.35);
 Ca0->SaveAs((folder+"Statistics.png").c_str());
 Ca0->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Creating Canvas"<<std::endl;
 TCanvas *Ca1 = new TCanvas("Ca1","Plots",800,600);
 gStyle->SetOptStat(0);


///MeanResiduals

 std::cout<<"Reading Mean_Residuals_Distribution"<<std::endl;
 TH1F * Mean_Residuals_Distribution1 = (TH1F*) (theFile1sec->Get("Mean_Residuals_Distribution"));
 TH1F * Mean_Residuals_Distribution2 = (TH1F*) (theFile2sec->Get("Mean_Residuals_Distribution"));
 std::cout<<"DrawNormalizeding first Mean_Residuals_Distribution"<<std::endl;
 Mean_Residuals_Distribution2->Draw("");
 std::cout<<"Drawing second Mean_Residuals_Distribution"<<std::endl;
 Mean_Residuals_Distribution1->SetMarkerColor(9);
 Mean_Residuals_Distribution1->SetLineColor(9);
 Mean_Residuals_Distribution1->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<Mean_Residuals_Distribution1->GetMean()<<" RMS="<<Mean_Residuals_Distribution1->GetRMS();
 sta2<<"Mean="<<Mean_Residuals_Distribution2->GetMean()<<" RMS="<<Mean_Residuals_Distribution2->GetRMS();
 leg->AddEntry(Mean_Residuals_Distribution1,(string1).c_str(),"l");  
 leg->AddEntry(Mean_Residuals_Distribution1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(Mean_Residuals_Distribution2,(string2).c_str(),"l");
 leg->AddEntry(Mean_Residuals_Distribution2,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"MeanResiduals.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


/// Mean_Residuals_Distribution_1cm
 std::cout<<"Reading Mean_Residuals_Distribution_1cm"<<std::endl;
 TH1F * Mean_Residuals_Distribution_1cm1 = (TH1F*) (theFile1sec->Get("Mean_Residuals_Distribution_1cm"));
 TH1F * Mean_Residuals_Distribution_1cm2 = (TH1F*) (theFile2sec->Get("Mean_Residuals_Distribution_1cm"));
 std::cout<<"Draw first Mean_Residuals_Distribution_1cm"<<std::endl;
 Mean_Residuals_Distribution_1cm2->Draw("");
 std::cout<<"Drawing second Mean_Residuals_Distribution_1cm"<<std::endl;
 Mean_Residuals_Distribution_1cm1->SetMarkerColor(9);
 Mean_Residuals_Distribution_1cm1->SetLineColor(9);
 Mean_Residuals_Distribution_1cm1->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<Mean_Residuals_Distribution_1cm1->GetMean()<<" RMS="<<Mean_Residuals_Distribution_1cm1->GetRMS();
 sta2<<"Mean="<<Mean_Residuals_Distribution_1cm2->GetMean()<<" RMS="<<Mean_Residuals_Distribution_1cm2->GetRMS();
 leg->AddEntry(Mean_Residuals_Distribution_1cm1,(string1).c_str(),"l");  
 leg->AddEntry(Mean_Residuals_Distribution_1cm1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(Mean_Residuals_Distribution_1cm2,(string2).c_str(),"l");
 leg->AddEntry(Mean_Residuals_Distribution_1cm2,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"MeanResiduals11.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


//// Clu 1

 std::cout<<"Reading DistBorderClu1La1"<<std::endl;
 TH1F * DistBorderClu1La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La1"));
 TH1F * DistBorderClu1La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La1"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La1"<<std::endl;
 DistBorderClu1La12->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La1"<<std::endl;
 DistBorderClu1La11->SetMarkerColor(9);
 DistBorderClu1La11->SetLineColor(9);
 DistBorderClu1La11->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La11->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La12->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La11,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La11,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La12,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La12,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu1La1.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu1La2"<<std::endl;
 TH1F * DistBorderClu1La21 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La2"));
 TH1F * DistBorderClu1La22 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La2"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La2"<<std::endl;
 DistBorderClu1La22->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La2"<<std::endl;
 DistBorderClu1La21->SetMarkerColor(9);
 DistBorderClu1La21->SetLineColor(9);
 DistBorderClu1La21->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La21->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La22->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La21,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La22,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu1La2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu1La3"<<std::endl;
 TH1F * DistBorderClu1La31 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La3"));
 TH1F * DistBorderClu1La32 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La3"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La3"<<std::endl;
 DistBorderClu1La32->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La3"<<std::endl;
 DistBorderClu1La31->SetMarkerColor(9);
 DistBorderClu1La31->SetLineColor(9);
 DistBorderClu1La31->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La31->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La32->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La31,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La32,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu1La3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu1La4"<<std::endl;
 TH1F * DistBorderClu1La41 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La4"));
 TH1F * DistBorderClu1La42 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La4"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La4"<<std::endl;
 DistBorderClu1La42->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La4"<<std::endl;
 DistBorderClu1La41->SetMarkerColor(9);
 DistBorderClu1La41->SetLineColor(9);
 DistBorderClu1La41->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La41->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La42->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La41,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La41,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La42,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La42,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu1La4.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu1La5"<<std::endl;
 TH1F * DistBorderClu1La51 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La5"));
 TH1F * DistBorderClu1La52 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La5"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La5"<<std::endl;
 DistBorderClu1La52->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La5"<<std::endl;
 DistBorderClu1La51->SetMarkerColor(9);
 DistBorderClu1La51->SetLineColor(9);
 DistBorderClu1La51->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La51->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La52->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La51,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La51,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La52,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La52,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu1La5.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading DistBorderClu1La6"<<std::endl;
 TH1F * DistBorderClu1La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La6"));
 TH1F * DistBorderClu1La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu1La6"));
 std::cout<<"DrawNormalizeding first DistBorderClu1La6"<<std::endl;
 DistBorderClu1La62->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu1La6"<<std::endl;
 DistBorderClu1La61->SetMarkerColor(9);
 DistBorderClu1La61->SetLineColor(9);
 DistBorderClu1La61->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu1La61->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu1La62->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu1La61,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La61,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu1La62,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu1La62,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu1La6.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

///// Clu 2

 std::cout<<"Reading DistBorderClu2La1"<<std::endl;
 TH1F * DistBorderClu2La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La1"));
 TH1F * DistBorderClu2La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La1"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La1"<<std::endl;
 DistBorderClu2La12->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu2La1"<<std::endl;
 DistBorderClu2La11->SetMarkerColor(9);
 DistBorderClu2La11->SetLineColor(9);
 DistBorderClu2La11->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La11->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La12->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu2La11,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La11,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La12,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La12,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu2La1.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading DistBorderClu2La2"<<std::endl;
 TH1F * DistBorderClu2La21 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La2"));
 TH1F * DistBorderClu2La22 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La2"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La2"<<std::endl;
 DistBorderClu2La22->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu2La2"<<std::endl;
 DistBorderClu2La21->SetMarkerColor(9);
 DistBorderClu2La21->SetLineColor(9);
 DistBorderClu2La21->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La21->GetMean()<<" RMS="<<DistBorderClu1La21->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La22->GetMean()<<" RMS="<<DistBorderClu1La22->GetRMS();
 leg->AddEntry(DistBorderClu2La21,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La22,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu2La2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading DistBorderClu2La3"<<std::endl;
 TH1F * DistBorderClu2La31 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La3"));
 TH1F * DistBorderClu2La32 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La3"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La3"<<std::endl;
 DistBorderClu2La32->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu2La3"<<std::endl;
 DistBorderClu2La31->SetMarkerColor(9);
 DistBorderClu2La31->SetLineColor(9);
 DistBorderClu2La31->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La31->GetMean()<<" RMS="<<DistBorderClu2La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La32->GetMean()<<" RMS="<<DistBorderClu2La12->GetRMS();
 leg->AddEntry(DistBorderClu2La31,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La32,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu2La3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu2La4"<<std::endl;
 TH1F * DistBorderClu2La41 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La4"));
 TH1F * DistBorderClu2La42 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La4"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La4"<<std::endl;
 DistBorderClu2La42->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu2La4"<<std::endl;
 DistBorderClu2La41->SetMarkerColor(9);
 DistBorderClu2La41->SetLineColor(9);
 DistBorderClu2La41->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La41->GetMean()<<" RMS="<<DistBorderClu2La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La42->GetMean()<<" RMS="<<DistBorderClu2La12->GetRMS();
 leg->AddEntry(DistBorderClu2La41,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La41,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La42,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La42,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu2La4.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu2La5"<<std::endl;
 TH1F * DistBorderClu2La51 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La5"));
 TH1F * DistBorderClu2La52 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La5"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La5"<<std::endl;
 DistBorderClu2La52->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu2La5"<<std::endl;
 DistBorderClu2La51->SetMarkerColor(9);
 DistBorderClu2La51->SetLineColor(9);
 DistBorderClu2La51->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La51->GetMean()<<" RMS="<<DistBorderClu2La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La52->GetMean()<<" RMS="<<DistBorderClu2La12->GetRMS();
 leg->AddEntry(DistBorderClu2La51,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La51,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La52,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La52,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu2La5.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu2La6"<<std::endl;
 TH1F * DistBorderClu2La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La6"));
 TH1F * DistBorderClu2La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu2La6"));
 std::cout<<"DrawNormalizeding first DistBorderClu2La6"<<std::endl;
 std::cout<<"DrawNormalizeding second DistBorderClu2La6"<<std::endl;
 DistBorderClu2La61->SetMarkerColor(9);
 DistBorderClu2La61->SetLineColor(9);
 DistBorderClu2La61->DrawNormalized("");
 DistBorderClu2La62->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu2La61->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<DistBorderClu2La62->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(DistBorderClu2La61,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La61,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu2La62,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu2La62,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu2La6.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

/////

///// Clu 3

 std::cout<<"Reading DistBorderClu3La1"<<std::endl;
 TH1F * DistBorderClu3La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La1"));
 TH1F * DistBorderClu3La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La1"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La1"<<std::endl;
 DistBorderClu3La12->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu3La1"<<std::endl;
 DistBorderClu3La11->SetMarkerColor(9);
 DistBorderClu3La11->SetLineColor(9);
 DistBorderClu3La11->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La11->GetMean()<<" RMS="<<DistBorderClu1La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La12->GetMean()<<" RMS="<<DistBorderClu1La12->GetRMS();
 leg->AddEntry(DistBorderClu3La11,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La11,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La12,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La12,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu3La1.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading DistBorderClu3La2"<<std::endl;
 TH1F * DistBorderClu3La21 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La2"));
 TH1F * DistBorderClu3La22 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La2"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La2"<<std::endl;
 DistBorderClu3La22->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu3La2"<<std::endl;
 DistBorderClu3La21->SetMarkerColor(9);
 DistBorderClu3La21->SetLineColor(9);
 DistBorderClu3La21->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La21->GetMean()<<" RMS="<<DistBorderClu1La21->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La22->GetMean()<<" RMS="<<DistBorderClu1La22->GetRMS();
 leg->AddEntry(DistBorderClu3La21,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La22,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu3La2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu3La3"<<std::endl;
 TH1F * DistBorderClu3La31 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La3"));
 TH1F * DistBorderClu3La32 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La3"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La3"<<std::endl;
 DistBorderClu3La32->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu3La3"<<std::endl;
 DistBorderClu3La31->SetMarkerColor(9);
 DistBorderClu3La31->SetLineColor(9);
 DistBorderClu3La31->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La31->GetMean()<<" RMS="<<DistBorderClu3La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La32->GetMean()<<" RMS="<<DistBorderClu3La12->GetRMS();
 leg->AddEntry(DistBorderClu3La31,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La32,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu3La3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu3La4"<<std::endl;
 TH1F * DistBorderClu3La41 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La4"));
 TH1F * DistBorderClu3La42 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La4"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La4"<<std::endl;
 DistBorderClu3La42->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu3La4"<<std::endl;
 DistBorderClu3La41->SetMarkerColor(9);
 DistBorderClu3La41->SetLineColor(9);
 DistBorderClu3La41->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La41->GetMean()<<" RMS="<<DistBorderClu3La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La42->GetMean()<<" RMS="<<DistBorderClu3La12->GetRMS();
 leg->AddEntry(DistBorderClu3La41,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La41,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La42,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La42,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu3La4.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu3La5"<<std::endl;
 TH1F * DistBorderClu3La51 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La5"));
 TH1F * DistBorderClu3La52 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La5"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La5"<<std::endl;
 DistBorderClu3La52->DrawNormalized("");
 std::cout<<"DrawNormalizeding second DistBorderClu3La5"<<std::endl;
 DistBorderClu3La51->SetMarkerColor(9);
 DistBorderClu3La51->SetLineColor(9);
 DistBorderClu3La51->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La51->GetMean()<<" RMS="<<DistBorderClu3La11->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La52->GetMean()<<" RMS="<<DistBorderClu3La12->GetRMS();
 leg->AddEntry(DistBorderClu3La51,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La51,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La52,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La52,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu3La5.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DistBorderClu3La6"<<std::endl;
 TH1F * DistBorderClu3La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La6"));
 TH1F * DistBorderClu3La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Investigation/DistBorderClu3La6"));
 std::cout<<"DrawNormalizeding first DistBorderClu3La6"<<std::endl;
 std::cout<<"DrawNormalizeding second DistBorderClu3La6"<<std::endl;
 DistBorderClu3La61->SetMarkerColor(9);
 DistBorderClu3La61->SetLineColor(9);
 DistBorderClu3La61->DrawNormalized("");
 DistBorderClu3La62->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<DistBorderClu3La61->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<DistBorderClu3La62->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(DistBorderClu3La61,(string1).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La61,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DistBorderClu3La62,(string2).c_str(),"l");
 leg->AddEntry(DistBorderClu3La62,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/DistBorderClu3La6.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

/////

//// CLS

 std::cout<<"Reading CLS"<<std::endl;
 TH1F * CLS1 = (TH1F*) (theFile1sec->Get("CLS"));
 TH1F * CLS2 = (TH1F*) (theFile2sec->Get("CLS"));
 std::cout<<"DrawNormalizeding first CLS"<<std::endl;
 std::cout<<"DrawNormalizeding second CLS"<<std::endl;
 CLS1->SetMarkerColor(9);
 CLS1->SetLineColor(9);
 CLS1->DrawNormalized("");
 CLS2->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<CLS1->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<CLS2->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(CLS1,(string1).c_str(),"l");  
 leg->AddEntry(CLS1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(CLS2,(string2).c_str(),"l");
 leg->AddEntry(CLS2,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/CLS.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading ClusterSizeForLayer1"<<std::endl;
 TH1F * ClusterSizeForLayer11 = (TH1F*) (theFile1sec->Get("ClusterSizeForLayer1"));
 TH1F * ClusterSizeForLayer12 = (TH1F*) (theFile2sec->Get("ClusterSizeForLayer1"));
 std::cout<<"DrawNormalizeding first ClusterSizeForLayer1"<<std::endl;
 std::cout<<"DrawNormalizeding second ClusterSizeForLayer1"<<std::endl;
 ClusterSizeForLayer11->SetMarkerColor(9);
 ClusterSizeForLayer11->SetLineColor(9);
 ClusterSizeForLayer11->DrawNormalized("");
 ClusterSizeForLayer12->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<ClusterSizeForLayer11->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<ClusterSizeForLayer12->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(ClusterSizeForLayer11,(string1).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer11,(sta1.str()).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer12,(string2).c_str(),"l");
 leg->AddEntry(ClusterSizeForLayer12,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/ClusterSizeForLayer1.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading ClusterSizeForLayer2"<<std::endl;
 TH1F * ClusterSizeForLayer21 = (TH1F*) (theFile1sec->Get("ClusterSizeForLayer2"));
 TH1F * ClusterSizeForLayer22 = (TH1F*) (theFile2sec->Get("ClusterSizeForLayer2"));
 std::cout<<"DrawNormalizeding first ClusterSizeForLayer2"<<std::endl;
 std::cout<<"DrawNormalizeding second ClusterSizeForLayer2"<<std::endl;
 ClusterSizeForLayer21->SetMarkerColor(9);
 ClusterSizeForLayer21->SetLineColor(9);
 ClusterSizeForLayer21->DrawNormalized("");
 ClusterSizeForLayer22->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<ClusterSizeForLayer21->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<ClusterSizeForLayer22->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(ClusterSizeForLayer21,(string1).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer22,(string2).c_str(),"l");
 leg->AddEntry(ClusterSizeForLayer22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/ClusterSizeForLayer2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading ClusterSizeForLayer3"<<std::endl;
 TH1F * ClusterSizeForLayer31 = (TH1F*) (theFile1sec->Get("ClusterSizeForLayer3"));
 TH1F * ClusterSizeForLayer32 = (TH1F*) (theFile2sec->Get("ClusterSizeForLayer3"));
 std::cout<<"DrawNormalizeding first ClusterSizeForLayer3"<<std::endl;
 std::cout<<"DrawNormalizeding second ClusterSizeForLayer3"<<std::endl;
 ClusterSizeForLayer31->SetMarkerColor(9);
 ClusterSizeForLayer31->SetLineColor(9);
 ClusterSizeForLayer31->DrawNormalized("");
 ClusterSizeForLayer32->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<ClusterSizeForLayer31->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<ClusterSizeForLayer32->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(ClusterSizeForLayer31,(string1).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer32,(string2).c_str(),"l");
 leg->AddEntry(ClusterSizeForLayer32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/ClusterSizeForLayer3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading ClusterSizeForLayer4"<<std::endl;
 TH1F * ClusterSizeForLayer41 = (TH1F*) (theFile1sec->Get("ClusterSizeForLayer4"));
 TH1F * ClusterSizeForLayer42 = (TH1F*) (theFile2sec->Get("ClusterSizeForLayer4"));
 std::cout<<"DrawNormalizeding first ClusterSizeForLayer4"<<std::endl;
 std::cout<<"DrawNormalizeding second ClusterSizeForLayer4"<<std::endl;
 ClusterSizeForLayer41->SetMarkerColor(9);
 ClusterSizeForLayer41->SetLineColor(9);
 ClusterSizeForLayer41->DrawNormalized("");
 ClusterSizeForLayer42->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<ClusterSizeForLayer41->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<ClusterSizeForLayer42->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(ClusterSizeForLayer41,(string1).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer41,(sta1.str()).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer42,(string2).c_str(),"l");
 leg->AddEntry(ClusterSizeForLayer42,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/ClusterSizeForLayer4.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading ClusterSizeForLayer5"<<std::endl;
 TH1F * ClusterSizeForLayer51 = (TH1F*) (theFile1sec->Get("ClusterSizeForLayer5"));
 TH1F * ClusterSizeForLayer52 = (TH1F*) (theFile2sec->Get("ClusterSizeForLayer5"));
 std::cout<<"DrawNormalizeding first ClusterSizeForLayer5"<<std::endl;
 std::cout<<"DrawNormalizeding second ClusterSizeForLayer5"<<std::endl;
 ClusterSizeForLayer51->SetMarkerColor(9);
 ClusterSizeForLayer51->SetLineColor(9);
 ClusterSizeForLayer51->DrawNormalized("");
 ClusterSizeForLayer52->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<ClusterSizeForLayer51->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<ClusterSizeForLayer52->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(ClusterSizeForLayer51,(string1).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer51,(sta1.str()).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer52,(string2).c_str(),"l");
 leg->AddEntry(ClusterSizeForLayer52,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/ClusterSizeForLayer5.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading ClusterSizeForLayer6"<<std::endl;
 TH1F * ClusterSizeForLayer61 = (TH1F*) (theFile1sec->Get("ClusterSizeForLayer6"));
 TH1F * ClusterSizeForLayer62 = (TH1F*) (theFile2sec->Get("ClusterSizeForLayer6"));
 std::cout<<"DrawNormalizeding first ClusterSizeForLayer6"<<std::endl;
 std::cout<<"DrawNormalizeding second ClusterSizeForLayer6"<<std::endl;
 ClusterSizeForLayer61->SetMarkerColor(9);
 ClusterSizeForLayer61->SetLineColor(9);
 ClusterSizeForLayer61->DrawNormalized("");
 ClusterSizeForLayer62->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<ClusterSizeForLayer61->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<ClusterSizeForLayer62->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(ClusterSizeForLayer61,(string1).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer61,(sta1.str()).c_str(),"l");  
 leg->AddEntry(ClusterSizeForLayer62,(string2).c_str(),"l");
 leg->AddEntry(ClusterSizeForLayer62,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"CLS/ClusterSizeForLayer6.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

//------------------------------Comparing Greg Histograms -----------------------------------------------------

//Ring R2

 std::cout<<"Reading GregDistroD1R2"<<std::endl;
 TH1F * GregDistroD1R21 = (TH1F*) (theFile1sec->Get("GregDistroD1R2"));
 TH1F * GregDistroD1R22 = (TH1F*) (theFile2sec->Get("GregDistroD1R2"));
 std::cout<<"Drawing first GregDistroD1R2"<<std::endl;
 std::cout<<"Drawing second GregDistroD1R2"<<std::endl;
 GregDistroD1R21->SetMarkerColor(9);
 GregDistroD1R21->SetLineColor(9);
 GregDistroD1R21->Draw("");
 GregDistroD1R22->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroD1R21->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroD1R22->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroD1R21,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroD1R21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroD1R22,(string2).c_str(),"l");
 leg->AddEntry(GregDistroD1R22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/D1R2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading GregDistroD2R2"<<std::endl;
 TH1F * GregDistroD2R21 = (TH1F*) (theFile1sec->Get("GregDistroD2R2"));
 TH1F * GregDistroD2R22 = (TH1F*) (theFile2sec->Get("GregDistroD2R2"));
 std::cout<<"Drawing first GregDistroD2R2"<<std::endl;
 std::cout<<"Drawing second GregDistroD2R2"<<std::endl;
 GregDistroD2R21->SetMarkerColor(9);
 GregDistroD2R21->SetLineColor(9);
 GregDistroD2R21->Draw("");
 GregDistroD2R22->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroD2R21->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroD2R22->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroD2R21,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroD2R21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroD2R22,(string2).c_str(),"l");
 leg->AddEntry(GregDistroD2R22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/D2R2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading GregDistroD3R2"<<std::endl;
 TH1F * GregDistroD3R21 = (TH1F*) (theFile1sec->Get("GregDistroD3R2"));
 TH1F * GregDistroD3R22 = (TH1F*) (theFile2sec->Get("GregDistroD3R2"));
 std::cout<<"Drawing first GregDistroD3R2"<<std::endl;
 std::cout<<"Drawing second GregDistroD3R2"<<std::endl;
 GregDistroD3R21->SetMarkerColor(9);
 GregDistroD3R21->SetLineColor(9);
 GregDistroD3R21->Draw("");
 GregDistroD3R22->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroD3R21->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroD3R22->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroD3R21,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroD3R21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroD3R22,(string2).c_str(),"l");
 leg->AddEntry(GregDistroD3R22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/D3R2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

//Negative Side Ring 2 R2

 std::cout<<"Reading GregDistroDm1R2"<<std::endl;
 TH1F * GregDistroDm1R21 = (TH1F*) (theFile1sec->Get("GregDistroDm1R2"));
 TH1F * GregDistroDm1R22 = (TH1F*) (theFile2sec->Get("GregDistroDm1R2"));
 std::cout<<"Drawing first GregDistroDm1R2"<<std::endl;
 std::cout<<"Drawing second GregDistroDm1R2"<<std::endl;
 GregDistroDm1R21->SetMarkerColor(9);
 GregDistroDm1R21->SetLineColor(9);
 GregDistroDm1R21->Draw("");
 GregDistroDm1R22->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroDm1R21->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroDm1R22->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroDm1R21,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroDm1R21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroDm1R22,(string2).c_str(),"l");
 leg->AddEntry(GregDistroDm1R22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/Dm1R2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading GregDistroDm2R2"<<std::endl;
 TH1F * GregDistroDm2R21 = (TH1F*) (theFile1sec->Get("GregDistroDm2R2"));
 TH1F * GregDistroDm2R22 = (TH1F*) (theFile2sec->Get("GregDistroDm2R2"));
 std::cout<<"Drawing first GregDistroDm2R2"<<std::endl;
 std::cout<<"Drawing second GregDistroDm2R2"<<std::endl;
 GregDistroDm2R21->SetMarkerColor(9);
 GregDistroDm2R21->SetLineColor(9);
 GregDistroDm2R21->Draw("");
 GregDistroDm2R22->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroDm2R21->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroDm2R22->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroDm2R21,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroDm2R21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroDm2R22,(string2).c_str(),"l");
 leg->AddEntry(GregDistroDm2R22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/Dm2R2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading GregDistroDm3R2"<<std::endl;
 TH1F * GregDistroDm3R21 = (TH1F*) (theFile1sec->Get("GregDistroDm3R2"));
 TH1F * GregDistroDm3R22 = (TH1F*) (theFile2sec->Get("GregDistroDm3R2"));
 std::cout<<"Drawing first GregDistroDm3R2"<<std::endl;
 std::cout<<"Drawing second GregDistroDm3R2"<<std::endl;
 GregDistroDm3R21->SetMarkerColor(9);
 GregDistroDm3R21->SetLineColor(9);
 GregDistroDm3R21->Draw("");
 GregDistroDm3R22->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroDm3R21->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroDm3R22->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroDm3R21,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroDm3R21,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroDm3R22,(string2).c_str(),"l");
 leg->AddEntry(GregDistroDm3R22,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/Dm3R2.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

// Ring 3 R3

 std::cout<<"Reading GregDistroD1R3"<<std::endl;
 TH1F * GregDistroD1R31 = (TH1F*) (theFile1sec->Get("GregDistroD1R3"));
 TH1F * GregDistroD1R32 = (TH1F*) (theFile2sec->Get("GregDistroD1R3"));
 std::cout<<"Drawing first GregDistroD1R3"<<std::endl;
 std::cout<<"Drawing second GregDistroD1R3"<<std::endl;
 GregDistroD1R31->SetMarkerColor(9);
 GregDistroD1R31->SetLineColor(9);
 GregDistroD1R31->Draw("");
 GregDistroD1R32->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroD1R31->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroD1R32->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroD1R31,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroD1R31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroD1R32,(string2).c_str(),"l");
 leg->AddEntry(GregDistroD1R32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/D1R3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading GregDistroD2R3"<<std::endl;
 TH1F * GregDistroD2R31 = (TH1F*) (theFile1sec->Get("GregDistroD2R3"));
 TH1F * GregDistroD2R32 = (TH1F*) (theFile2sec->Get("GregDistroD2R3"));
 std::cout<<"Drawing first GregDistroD2R3"<<std::endl;
 std::cout<<"Drawing second GregDistroD2R3"<<std::endl;
 GregDistroD2R31->SetMarkerColor(9);
 GregDistroD2R31->SetLineColor(9);
 GregDistroD2R31->Draw("");
 GregDistroD2R32->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroD2R31->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroD2R32->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroD2R31,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroD2R31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroD2R32,(string2).c_str(),"l");
 leg->AddEntry(GregDistroD2R32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/D2R3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading GregDistroD3R3"<<std::endl;
 TH1F * GregDistroD3R31 = (TH1F*) (theFile1sec->Get("GregDistroD3R3"));
 TH1F * GregDistroD3R32 = (TH1F*) (theFile2sec->Get("GregDistroD3R3"));
 std::cout<<"Drawing first GregDistroD3R3"<<std::endl;
 std::cout<<"Drawing second GregDistroD3R3"<<std::endl;
 GregDistroD3R31->SetMarkerColor(9);
 GregDistroD3R31->SetLineColor(9);
 GregDistroD3R31->Draw("");
 GregDistroD3R32->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroD3R31->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroD3R32->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroD3R31,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroD3R31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroD3R32,(string2).c_str(),"l");
 leg->AddEntry(GregDistroD3R32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/D3R3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

//Negative Side Ring 2 R3

 std::cout<<"Reading GregDistroDm1R3"<<std::endl;
 TH1F * GregDistroDm1R31 = (TH1F*) (theFile1sec->Get("GregDistroDm1R3"));
 TH1F * GregDistroDm1R32 = (TH1F*) (theFile2sec->Get("GregDistroDm1R3"));
 std::cout<<"Drawing first GregDistroDm1R3"<<std::endl;
 std::cout<<"Drawing second GregDistroDm1R3"<<std::endl;
 GregDistroDm1R31->SetMarkerColor(9);
 GregDistroDm1R31->SetLineColor(9);
 GregDistroDm1R31->Draw("");
 GregDistroDm1R32->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroDm1R31->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroDm1R32->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroDm1R31,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroDm1R31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroDm1R32,(string2).c_str(),"l");
 leg->AddEntry(GregDistroDm1R32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/Dm1R3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading GregDistroDm2R3"<<std::endl;
 TH1F * GregDistroDm2R31 = (TH1F*) (theFile1sec->Get("GregDistroDm2R3"));
 TH1F * GregDistroDm2R32 = (TH1F*) (theFile2sec->Get("GregDistroDm2R3"));
 std::cout<<"Drawing first GregDistroDm2R3"<<std::endl;
 std::cout<<"Drawing second GregDistroDm2R3"<<std::endl;
 GregDistroDm2R31->SetMarkerColor(9);
 GregDistroDm2R31->SetLineColor(9);
 GregDistroDm2R31->Draw("");
 GregDistroDm2R32->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroDm2R31->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroDm2R32->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroDm2R31,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroDm2R31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroDm2R32,(string2).c_str(),"l");
 leg->AddEntry(GregDistroDm2R32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/Dm2R3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading GregDistroDm3R3"<<std::endl;
 TH1F * GregDistroDm3R31 = (TH1F*) (theFile1sec->Get("GregDistroDm3R3"));
 TH1F * GregDistroDm3R32 = (TH1F*) (theFile2sec->Get("GregDistroDm3R3"));
 std::cout<<"Drawing first GregDistroDm3R3"<<std::endl;
 std::cout<<"Drawing second GregDistroDm3R3"<<std::endl;
 GregDistroDm3R31->SetMarkerColor(9);
 GregDistroDm3R31->SetLineColor(9);
 GregDistroDm3R31->Draw("");
 GregDistroDm3R32->Draw("same");
 TLegend *leg = new TLegend(0.6,0.85,0.9,0.7);
 sta1<<"Mean="<<GregDistroDm3R31->GetMean()<<" RMS="<<DistBorderClu1La61->GetRMS();
 sta2<<"Mean="<<GregDistroDm3R32->GetMean()<<" RMS="<<DistBorderClu1La62->GetRMS();
 leg->AddEntry(GregDistroDm3R31,(string1).c_str(),"l");  
 leg->AddEntry(GregDistroDm3R31,(sta1.str()).c_str(),"l");  
 leg->AddEntry(GregDistroDm3R32,(string2).c_str(),"l");
 leg->AddEntry(GregDistroDm3R32,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Greg/Dm3R3.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");




//----------------------------------------------------------------------------------------------------------------


// Global Residuals Layer 1

 std::cout<<"Reading GlobalResiduals"<<std::endl;
 TH1F * GlobalResidualsClu1La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu1La1"));
 TH1F * GlobalResidualsClu2La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu2La1"));
 TH1F * GlobalResidualsClu3La11 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu3La1"));

 TH1F * GlobalResidualsLa11 = GlobalResidualsClu1La11->Clone();
 GlobalResidualsLa11->Add(GlobalResidualsClu2La11);
 GlobalResidualsLa11->Add(GlobalResidualsClu3La11);

 TH1F * GlobalResidualsClu1La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu1La1"));
 TH1F * GlobalResidualsClu2La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu2La1"));
 TH1F * GlobalResidualsClu3La12 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu3La1"));
 TH1F * GlobalResidualsLa12 = GlobalResidualsClu1La12->Clone();
 GlobalResidualsLa12->Add(GlobalResidualsClu2La12);
 GlobalResidualsLa12->Add(GlobalResidualsClu3La12);

 std::cout<<"Global Residuals  first AllLa11"<<std::endl;
 GlobalResidualsLa12->DrawNormalized("");
 std::cout<<"Global Residuals second AllLa12"<<std::endl;
 GlobalResidualsLa11->SetMarkerColor(9);
 GlobalResidualsLa11->SetLineColor(9);
 GlobalResidualsLa11->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.8,0.9,0.6);
 leg->AddEntry(GlobalResidualsLa11,string1.c_str(),"l");  
 leg->AddEntry(GlobalResidualsLa12,string2.c_str(),"l");
 leg->Draw("same");
 Ca1->SaveAs((folder+"GlobalResidualsLa1Comp.png").c_str());
 Ca1->Clear();



//// Global Residuals Layer 6

 std::cout<<"Reading GlobalResiduals"<<std::endl;
 TH1F * GlobalResidualsClu1La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu1La6"));
 TH1F * GlobalResidualsClu2La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu2La6"));
 TH1F * GlobalResidualsClu3La61 = (TH1F*) (theFile1->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu3La6"));

 TH1F * GlobalResidualsLa61 = GlobalResidualsClu1La61->Clone();
 GlobalResidualsLa61->Add(GlobalResidualsClu2La61);
 GlobalResidualsLa61->Add(GlobalResidualsClu3La61);

 TH1F * GlobalResidualsClu1La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu1La6"));
 TH1F * GlobalResidualsClu2La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu2La6"));
 TH1F * GlobalResidualsClu3La62 = (TH1F*) (theFile2->Get("DQMData/Muons/MuonSegEff/Residuals/Barrel/GlobalResidualsClu3La6"));
 TH1F * GlobalResidualsLa62 = GlobalResidualsClu1La62->Clone();
 GlobalResidualsLa62->Add(GlobalResidualsClu2La62);
 GlobalResidualsLa62->Add(GlobalResidualsClu3La62);

 std::cout<<"Global Residuals  first AllLa61"<<std::endl;
 GlobalResidualsLa62->DrawNormalized("");
 std::cout<<"Global Residuals second AllLa62"<<std::endl;
 GlobalResidualsLa61->SetMarkerColor(9);
 GlobalResidualsLa61->SetLineColor(9);
 GlobalResidualsLa61->DrawNormalized("same");
 TLegend *leg = new TLegend(0.6,0.8,0.9,0.6);
 leg->AddEntry(GlobalResidualsLa61,string1.c_str(),"l");  
 leg->AddEntry(GlobalResidualsLa62,string2.c_str(),"l");
 leg->Draw("same");
 Ca1->SaveAs((folder+"GlobalResidualsLa6Comp.png").c_str());
 Ca1->Clear();


////// EffBarrel and others

 std::cout<<"Reading PinoBarrel"<<std::endl;
 TH1F * PinoBarrel1 = (TH1F*) (theFile1sec->Get("PinoBarrel"));
 TH1F * PinoBarrel2 = (TH1F*) (theFile2sec->Get("PinoBarrel"));
 std::cout<<"Drawing first PinoBarrel"<<std::endl;
 PinoBarrel2->Draw("");
 std::cout<<"Drawing second PinoBarrel"<<std::endl;
 PinoBarrel1->SetMarkerColor(9);
 PinoBarrel1->SetLineColor(9);
 PinoBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<PinoBarrel1->GetMean()<<" RMS="<<PinoBarrel1->GetRMS();
 sta2<<"Mean="<<PinoBarrel2->GetMean()<<" RMS="<<PinoBarrel2->GetRMS();
 leg->AddEntry(PinoBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(PinoBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(PinoBarrel2,string2.c_str(),"l");
 leg->AddEntry(PinoBarrel2,(sta2.str()).c_str(),"l");  
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/PinoBarrel.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading PinoEndCap"<<std::endl;
 TH1F * PinoEndCap1 = (TH1F*) (theFile1sec->Get("PinoEndCap"));
 TH1F * PinoEndCap2 = (TH1F*) (theFile2sec->Get("PinoEndCap"));
 std::cout<<"Drawing first PinoEndCap"<<std::endl;
 PinoEndCap2->Draw("");
 std::cout<<"Drawing second PinoEndCap"<<std::endl;
 PinoEndCap1->SetMarkerColor(9);
 PinoEndCap1->SetLineColor(9);
 PinoEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<PinoEndCap1->GetMean()<<" RMS="<<PinoEndCap1->GetRMS();
 sta2<<"Mean="<<PinoEndCap2->GetMean()<<" RMS="<<PinoEndCap2->GetRMS();
 leg->AddEntry(PinoEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(PinoEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(PinoEndCap2,string2.c_str(),"l");
 leg->AddEntry(PinoEndCap2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/PinoEndCap.png").c_str()); 
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading EffBarrel"<<std::endl;
 TH1F * EffBarrel1 = (TH1F*) (theFile1sec->Get("EffBarrel"));
 TH1F * EffBarrel2 = (TH1F*) (theFile2sec->Get("EffBarrel"));
 std::cout<<"Drawing first EffBarrel"<<std::endl;
 EffBarrel2->Draw("");
 std::cout<<"Drawing second EffBarrel"<<std::endl;
 EffBarrel1->SetMarkerColor(9);
 EffBarrel1->SetLineColor(9);
 EffBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<EffBarrel1->GetMean()<<" RMS="<<EffBarrel1->GetRMS();
 sta2<<"Mean="<<EffBarrel2->GetMean()<<" RMS="<<EffBarrel2->GetRMS();
 leg->AddEntry(EffBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(EffBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(EffBarrel2,string2.c_str(),"l");
 leg->AddEntry(EffBarrel2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/EffDistroBarrel.png").c_str()); 
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Pino EndCap"<<std::endl;
 TH1F * EffEndCap1 = (TH1F*) (theFile1sec->Get("EffDistroEndCap"));
 TH1F * EffEndCap2 = (TH1F*) (theFile2sec->Get("EffDistroEndCap"));
 std::cout<<"Drawing first EffEndCap"<<std::endl;
 EffEndCap2->Draw("");
 std::cout<<"Drawing second EffEndCap"<<std::endl;
 EffEndCap1->SetMarkerColor(9);
 EffEndCap1->SetLineColor(9);
 EffEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<EffEndCap1->GetMean()<<" RMS="<<EffEndCap1->GetRMS();
 sta2<<"Mean="<<EffEndCap2->GetMean()<<" RMS="<<EffEndCap2->GetRMS();
 leg->AddEntry(EffEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(EffEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(EffEndCap2,string2.c_str(),"l");
 leg->AddEntry(EffEndCap2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/EffDistroEndCap.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DoubleGapBarrel"<<std::endl;
 TH1F * DoubleGapBarrel1 = (TH1F*) (theFile1sec->Get("DoubleGapBarrel"));
 TH1F * DoubleGapBarrel2 = (TH1F*) (theFile2sec->Get("DoubleGapBarrel"));
 std::cout<<"Drawing first DoubleGapBarrel"<<std::endl;
 DoubleGapBarrel2->Draw("");
 std::cout<<"Drawing second DoubleGapBarrel"<<std::endl;
 DoubleGapBarrel1->SetMarkerColor(9);
 DoubleGapBarrel1->SetLineColor(9);
 DoubleGapBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<DoubleGapBarrel1->GetMean()<<" RMS="<<DoubleGapBarrel1->GetRMS();
 sta2<<"Mean="<<DoubleGapBarrel2->GetMean()<<" RMS="<<DoubleGapBarrel2->GetRMS();
 leg->AddEntry(DoubleGapBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(DoubleGapBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DoubleGapBarrel2,string2.c_str(),"l");
 leg->AddEntry(DoubleGapBarrel2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/DoubleGapBarrel.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading DoubleGapEndCap"<<std::endl;
 TH1F * DoubleGapEndCap1 = (TH1F*) (theFile1sec->Get("DoubleGapEndCap"));
 TH1F * DoubleGapEndCap2 = (TH1F*) (theFile2sec->Get("DoubleGapEndCap"));
 std::cout<<"Drawing first DoubleGapEndCap"<<std::endl;
 DoubleGapEndCap2->Draw("");
 std::cout<<"Drawing second DoubleGapEndCap"<<std::endl;
 DoubleGapEndCap1->SetMarkerColor(9);
 DoubleGapEndCap1->SetLineColor(9);
 DoubleGapEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<DoubleGapEndCap1->GetMean()<<" RMS="<<DoubleGapEndCap1->GetRMS();
 sta2<<"Mean="<<DoubleGapEndCap2->GetMean()<<" RMS="<<DoubleGapEndCap2->GetRMS();
 leg->AddEntry(DoubleGapEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(DoubleGapEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(DoubleGapEndCap2,string2.c_str(),"l");
 leg->AddEntry(DoubleGapEndCap2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/DoubleGapEndCap.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading BXBarrel"<<std::endl;
 TH2F * BXBarrel1 = (TH2F*) (theFile1sec->Get("BXBarrel"));
 TH2F * BXBarrel2 = (TH2F*) (theFile2sec->Get("BXBarrel"));
 std::cout<<"Drawing first BXBarrel"<<std::endl;
 BXBarrel2->Draw("");
 std::cout<<"Drawing second BXBarrel"<<std::endl;
 BXBarrel1->SetMarkerColor(9);
 BXBarrel1->SetLineColor(9);
 BXBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<BXBarrel1->GetMean()<<" RMS="<<BXBarrel1->GetRMS();
 sta2<<"Mean="<<BXBarrel2->GetMean()<<" RMS="<<BXBarrel2->GetRMS();
 leg->AddEntry(BXBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(BXBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(BXBarrel2,string2.c_str(),"l");
 leg->AddEntry(BXBarrel2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"bxbarrel.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading BXEndCap"<<std::endl;
 TH2F * BXEndCap1 = (TH2F*) (theFile1sec->Get("BXEndCap"));
 TH2F * BXEndCap2 = (TH2F*) (theFile2sec->Get("BXEndCap"));
 std::cout<<"Drawing first BXEndCap"<<std::endl;
 BXEndCap2->Draw("");
 std::cout<<"Drawing second BXEndCap"<<std::endl;
 BXEndCap1->SetMarkerColor(9);
 BXEndCap1->SetLineColor(9);
 BXEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.8,0.5,0.6);
 sta1<<"Mean="<<BXEndCap1->GetMean()<<" RMS="<<BXEndCap1->GetRMS();
 sta2<<"Mean="<<BXEndCap2->GetMean()<<" RMS="<<BXEndCap2->GetRMS();
 leg->AddEntry(BXEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(BXEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(BXEndCap2,string2.c_str(),"l");
 leg->AddEntry(BXEndCap2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"bxendcap.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Reading BXEffBarrel"<<std::endl;
 TH1F * BXEffBarrel1 = (TH1F*) (theFile1sec->Get("BXEffBarrel"));
 TH1F * BXEffBarrel2 = (TH1F*) (theFile2sec->Get("BXEffBarrel"));
 std::cout<<"Drawing first BXEffBarrel"<<std::endl;
 BXEffBarrel2->Draw("");
 std::cout<<"Drawing second BXEffBarrel"<<std::endl;
 BXEffBarrel1->SetMarkerColor(9);
 BXEffBarrel1->SetLineColor(9);
 BXEffBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<BXEffBarrel1->GetMean()<<" RMS="<<BXEffBarrel1->GetRMS();
 sta2<<"Mean="<<BXEffBarrel2->GetMean()<<" RMS="<<BXEffBarrel2->GetRMS();
 leg->AddEntry(BXEffBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(BXEffBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(BXEffBarrel2,string2.c_str(),"l");
 leg->AddEntry(BXEffBarrel2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/BXEffDistroBarrel.png").c_str()); 
 Ca1->Clear();
 sta1.str("");
 sta2.str("");

 std::cout<<"Pino EndCap"<<std::endl;
 TH1F * BXEffEndCap1 = (TH1F*) (theFile1sec->Get("BXEffEndCap"));
 TH1F * BXEffEndCap2 = (TH1F*) (theFile2sec->Get("BXEffEndCap"));
 std::cout<<"Drawing first BXEffEndCap"<<std::endl;
 BXEffEndCap2->Draw("");
 std::cout<<"Drawing second BXEffEndCap"<<std::endl;
 BXEffEndCap1->SetMarkerColor(9);
 BXEffEndCap1->SetLineColor(9);
 BXEffEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<BXEffEndCap1->GetMean()<<" RMS="<<BXEffEndCap1->GetRMS();
 sta2<<"Mean="<<BXEffEndCap2->GetMean()<<" RMS="<<BXEffEndCap2->GetRMS();
 leg->AddEntry(BXEffEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(BXEffEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(BXEffEndCap2,string2.c_str(),"l");
 leg->AddEntry(BXEffEndCap2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/BXEffDistroEndCap.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading badBXEffBarrel"<<std::endl;
 TH1F * badBXEffBarrel1 = (TH1F*) (theFile1sec->Get("badBXEffBarrel"));
 TH1F * badBXEffBarrel2 = (TH1F*) (theFile2sec->Get("badBXEffBarrel"));
 std::cout<<"Drawing first badBXEffBarrel"<<std::endl;
 badBXEffBarrel2->Draw("");
 std::cout<<"Drawing second badBXEffBarrel"<<std::endl;
 badBXEffBarrel1->SetMarkerColor(9);
 badBXEffBarrel1->SetLineColor(9);
 badBXEffBarrel1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<badBXEffBarrel1->GetMean()<<" RMS="<<badBXEffBarrel1->GetRMS();
 sta2<<"Mean="<<badBXEffBarrel2->GetMean()<<" RMS="<<badBXEffBarrel2->GetRMS();
 leg->AddEntry(badBXEffBarrel1,string1.c_str(),"l"); 
 leg->AddEntry(badBXEffBarrel1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(badBXEffBarrel2,string2.c_str(),"l");
 leg->AddEntry(badBXEffBarrel2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/badBXEffDistroBarrel.png").c_str()); 
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 std::cout<<"Pino badBXEffEndCap"<<std::endl;
 TH1F * badBXEffEndCap1 = (TH1F*) (theFile1sec->Get("badBXEffEndCap"));
 TH1F * badBXEffEndCap2 = (TH1F*) (theFile2sec->Get("badBXEffEndCap"));
 std::cout<<"Drawing first badBXEffEndCap"<<std::endl;
 badBXEffEndCap2->Draw("");
 std::cout<<"Drawing second badBXEffEndCap"<<std::endl;
 badBXEffEndCap1->SetMarkerColor(9);
 badBXEffEndCap1->SetLineColor(9);
 badBXEffEndCap1->Draw("same");
 TLegend *leg = new TLegend(0.2,0.85,0.5,0.6);
 sta1<<"Mean="<<badBXEffEndCap1->GetMean()<<" RMS="<<badBXEffEndCap1->GetRMS();
 sta2<<"Mean="<<badBXEffEndCap2->GetMean()<<" RMS="<<badBXEffEndCap2->GetRMS();
 leg->AddEntry(badBXEffEndCap1,string1.c_str(),"l"); 
 leg->AddEntry(badBXEffEndCap1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(badBXEffEndCap2,string2.c_str(),"l");
 leg->AddEntry(badBXEffEndCap2,(sta2.str()).c_str(),"l"); 
 leg->Draw("same");
 Ca1->SaveAs((folder+"Distro/badBXEffDistroEndCap.png").c_str());
 Ca1->Clear();
 sta1.str("");
 sta2.str("");


 TCanvas *Ca2 = new TCanvas("Ca2","Global Efficiency",1200,600);
 gStyle->SetOptStat(0);
 Ca2->SetBottomMargin(0.4);

 //-------------------------------------------------all far sides Barrel ---------------------------------------------------------------------------------------------------

 std::cout<<"Reading AverageEfficiencyWheel_-2far"<<std::endl;
 TH1F * AverageEfficiencyWheel_m2far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_-2far"));
 TH1F * AverageEfficiencyWheel_m2far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_-2far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_-2far"<<std::endl;
 AverageEfficiencyWheel_m2far2->Draw("");
 AverageEfficiencyWheel_m2far2->GetYaxis()->SetTitle("%");
 std::cout<<"Drawing second AverageEfficiencyWheel_-2far"<<std::endl;
 AverageEfficiencyWheel_m2far1->SetMarkerColor(9);
 AverageEfficiencyWheel_m2far1->SetLineColor(9);
 AverageEfficiencyWheel_m2far1->Draw("same");
 
 AverageEfficiencyWheel_m2far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m2far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m2far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_m2far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_m2far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m2far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_m2far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m2far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_m2far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_m2far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_m2far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_m2far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Wm2far.png").c_str());
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading AverageEfficiencyWheel_-1far"<<std::endl;
 TH1F * AverageEfficiencyWheel_m1far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_-1far"));
 TH1F * AverageEfficiencyWheel_m1far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_-1far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_-1far"<<std::endl;
 AverageEfficiencyWheel_m1far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_-1far"<<std::endl;
 AverageEfficiencyWheel_m1far1->SetMarkerColor(9);
 AverageEfficiencyWheel_m1far1->SetLineColor(9);
 AverageEfficiencyWheel_m1far1->Draw("same");

 AverageEfficiencyWheel_m1far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m1far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m1far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_m1far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_m1far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m1far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_m1far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m1far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_m1far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_m1far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_m1far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_m1far2,(sta3.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Wm1far.png").c_str());
 sta1.str("");
 sta2.str("");


 
 std::cout<<"Reading AverageEfficiencyWheel_0far"<<std::endl;
 TH1F * AverageEfficiencyWheel_0far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_0far"));
 TH1F * AverageEfficiencyWheel_0far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_0far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_0far"<<std::endl;
 AverageEfficiencyWheel_0far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_0far"<<std::endl;
 AverageEfficiencyWheel_0far1->SetMarkerColor(9);
 AverageEfficiencyWheel_0far1->SetLineColor(9);
 AverageEfficiencyWheel_0far1->Draw("same");

 AverageEfficiencyWheel_0far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_0far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_0far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_0far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_0far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_0far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_0far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_0far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_0far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_0far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_0far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_0far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W0far.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyWheel_1far"<<std::endl;
 TH1F * AverageEfficiencyWheel_1far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_1far"));
 TH1F * AverageEfficiencyWheel_1far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_1far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_1far"<<std::endl;
 AverageEfficiencyWheel_1far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_1far"<<std::endl;
 AverageEfficiencyWheel_1far1->SetMarkerColor(9);
 AverageEfficiencyWheel_1far1->SetLineColor(9);
 AverageEfficiencyWheel_1far1->Draw("same");

 AverageEfficiencyWheel_1far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_1far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_1far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_1far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_1far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_1far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_1far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_1far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_1far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_1far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_1far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_1far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W1far.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyWheel_2far"<<std::endl;
 TH1F * AverageEfficiencyWheel_2far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_2far"));
 TH1F * AverageEfficiencyWheel_2far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_2far"));
 std::cout<<"Drawing first AverageEfficiencyWheel_2far"<<std::endl;
 AverageEfficiencyWheel_2far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_2far"<<std::endl;
 AverageEfficiencyWheel_2far1->SetMarkerColor(9);
 AverageEfficiencyWheel_2far1->SetLineColor(9);
 AverageEfficiencyWheel_2far1->Draw("same");

 AverageEfficiencyWheel_2far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_2far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_2far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_2far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_2far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_2far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_2far1->GetMean()<<" RMS="<<AverageEfficiencyWheel_2far2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_2far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_2far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_2far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_2far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W2far.png").c_str());
 sta1.str("");
 sta2.str("");



////

 //all near sides

 std::cout<<"Reading AverageEfficiencyWheel_-2near"<<std::endl;
 TH1F * AverageEfficiencyWheel_m2near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_-2near"));
 TH1F * AverageEfficiencyWheel_m2near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_-2near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_-2near"<<std::endl;
 AverageEfficiencyWheel_m2near2->Draw("");
 AverageEfficiencyWheel_m2near2->GetYaxis()->SetTitle("%");
 std::cout<<"Drawing second AverageEfficiencyWheel_-2near"<<std::endl;
 AverageEfficiencyWheel_m2near1->SetMarkerColor(9);
 AverageEfficiencyWheel_m2near1->SetLineColor(9);
 AverageEfficiencyWheel_m2near1->Draw("same");
 
 AverageEfficiencyWheel_m2near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m2near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m2near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_m2near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_m2near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m2near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_m2near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m2near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_m2near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_m2near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_m2near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_m2near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Wm2near.png").c_str());
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading AverageEfficiencyWheel_-1near"<<std::endl;
 TH1F * AverageEfficiencyWheel_m1near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_-1near"));
 TH1F * AverageEfficiencyWheel_m1near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_-1near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_-1near"<<std::endl;
 AverageEfficiencyWheel_m1near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_-1near"<<std::endl;
 AverageEfficiencyWheel_m1near1->SetMarkerColor(9);
 AverageEfficiencyWheel_m1near1->SetLineColor(9);
 AverageEfficiencyWheel_m1near1->Draw("same");

 AverageEfficiencyWheel_m1near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m1near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_m1near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_m1near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_m1near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m1near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_m1near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_m1near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_m1near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_m1near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_m1near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_m1near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Wm1near.png").c_str());
 sta1.str("");
 sta2.str("");

 
 std::cout<<"Reading AverageEfficiencyWheel_0near"<<std::endl;
 TH1F * AverageEfficiencyWheel_0near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_0near"));
 TH1F * AverageEfficiencyWheel_0near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_0near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_0near"<<std::endl;
 AverageEfficiencyWheel_0near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_0near"<<std::endl;
 AverageEfficiencyWheel_0near1->SetMarkerColor(9);
 AverageEfficiencyWheel_0near1->SetLineColor(9);
 AverageEfficiencyWheel_0near1->Draw("same");

 AverageEfficiencyWheel_0near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_0near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_0near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_0near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_0near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_0near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_0near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_0near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_0near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_0near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_0near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_0near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W0near.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyWheel_1near"<<std::endl;
 TH1F * AverageEfficiencyWheel_1near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_1near"));
 TH1F * AverageEfficiencyWheel_1near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_1near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_1near"<<std::endl;
 AverageEfficiencyWheel_1near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_1near"<<std::endl;
 AverageEfficiencyWheel_1near1->SetMarkerColor(9);
 AverageEfficiencyWheel_1near1->SetLineColor(9);
 AverageEfficiencyWheel_1near1->Draw("same");

 AverageEfficiencyWheel_1near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_1near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_1near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_1near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_1near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_1near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_1near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_1near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_1near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_1near1,(sta2.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_1near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_1near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W1near.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyWheel_2near"<<std::endl;
 TH1F * AverageEfficiencyWheel_2near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyWheel_2near"));
 TH1F * AverageEfficiencyWheel_2near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyWheel_2near"));
 std::cout<<"Drawing first AverageEfficiencyWheel_2near"<<std::endl;
 AverageEfficiencyWheel_2near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyWheel_2near"<<std::endl;
 AverageEfficiencyWheel_2near1->SetMarkerColor(9);
 AverageEfficiencyWheel_2near1->SetLineColor(9);
 AverageEfficiencyWheel_2near1->Draw("same");

 AverageEfficiencyWheel_2near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_2near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyWheel_2near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyWheel_2near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyWheel_2near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_2near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyWheel_2near1->GetMean()<<" RMS="<<AverageEfficiencyWheel_2near2->GetRMS();
 leg->AddEntry(AverageEfficiencyWheel_2near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyWheel_2near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyWheel_2near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyWheel_2near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_W2near.png").c_str());
 sta1.str("");
 sta2.str("");



 //-------------------------------------------------all far sides EndCap ---------------------------------------------------------------------------------------------------

 std::cout<<"Reading AverageEfficiencyDisk_3far"<<std::endl;
 TH1F * AverageEfficiencyDisk_3far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_3far"));
 TH1F * AverageEfficiencyDisk_3far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_3far"));
 std::cout<<"Drawing first AverageEfficiencyDisk_3far"<<std::endl;
 AverageEfficiencyDisk_3far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_3far"<<std::endl;
 AverageEfficiencyDisk_3far1->SetMarkerColor(9);
 AverageEfficiencyDisk_3far1->SetLineColor(9);
 AverageEfficiencyDisk_3far1->Draw("same");

 AverageEfficiencyDisk_3far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_3far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_3far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_3far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_3far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_3far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_3far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_3far2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_3far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_3far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_3far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_3far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_D3far.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyDisk_2far"<<std::endl;
 TH1F * AverageEfficiencyDisk_2far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_2far"));
 TH1F * AverageEfficiencyDisk_2far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_2far"));
 std::cout<<"Drawing first AverageEfficiencyDisk_2far"<<std::endl;
 AverageEfficiencyDisk_2far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_2far"<<std::endl;
 AverageEfficiencyDisk_2far1->SetMarkerColor(9);
 AverageEfficiencyDisk_2far1->SetLineColor(9);
 AverageEfficiencyDisk_2far1->Draw("same");

 AverageEfficiencyDisk_2far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_2far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_2far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_2far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_2far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_2far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_2far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_2far2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_2far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_2far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_2far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_2far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_D2far.png").c_str());
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading AverageEfficiencyDisk_1far"<<std::endl;
 TH1F * AverageEfficiencyDisk_1far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_1far"));
 TH1F * AverageEfficiencyDisk_1far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_1far"));
 std::cout<<"Drawing first AverageEfficiencyDisk_1far"<<std::endl;
 AverageEfficiencyDisk_1far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_1far"<<std::endl;
 AverageEfficiencyDisk_1far1->SetMarkerColor(9);
 AverageEfficiencyDisk_1far1->SetLineColor(9);
 AverageEfficiencyDisk_1far1->Draw("same");

 AverageEfficiencyDisk_1far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_1far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_1far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_1far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_1far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_1far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_1far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_1far2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_1far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_1far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_1far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_1far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_D1far.png").c_str());
 sta1.str("");
 sta2.str("");

//Negative Sides

 std::cout<<"Reading AverageEfficiencyDisk_m3far"<<std::endl;
 TH1F * AverageEfficiencyDisk_m3far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_m3far"));
 TH1F * AverageEfficiencyDisk_m3far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_m3far"));
 std::cout<<"Drawing first AverageEfficiencyDisk_m3far"<<std::endl;
 AverageEfficiencyDisk_m3far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_m3far"<<std::endl;
 AverageEfficiencyDisk_m3far1->SetMarkerColor(9);
 AverageEfficiencyDisk_m3far1->SetLineColor(9);
 AverageEfficiencyDisk_m3far1->Draw("same");

 AverageEfficiencyDisk_m3far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m3far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m3far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_m3far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_m3far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m3far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_m3far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m3far2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_m3far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_m3far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_m3far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_m3far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Dm3far.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyDisk_m2far"<<std::endl;
 TH1F * AverageEfficiencyDisk_m2far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_m2far"));
 TH1F * AverageEfficiencyDisk_m2far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_m2far"));
 std::cout<<"Drawing first AverageEfficiencyDisk_m2far"<<std::endl;
 AverageEfficiencyDisk_m2far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_m2far"<<std::endl;
 AverageEfficiencyDisk_m2far1->SetMarkerColor(9);
 AverageEfficiencyDisk_m2far1->SetLineColor(9);
 AverageEfficiencyDisk_m2far1->Draw("same");

 AverageEfficiencyDisk_m2far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m2far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m2far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_m2far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_m2far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m2far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_m2far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m2far2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_m2far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_m2far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_m2far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_m2far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Dm2far.png").c_str());
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading AverageEfficiencyDisk_m1far"<<std::endl;
 TH1F * AverageEfficiencyDisk_m1far1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_m1far"));
 TH1F * AverageEfficiencyDisk_m1far2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_m1far"));
 std::cout<<"Drawing first AverageEfficiencyDisk_m1far"<<std::endl;
 AverageEfficiencyDisk_m1far2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_m1far"<<std::endl;
 AverageEfficiencyDisk_m1far1->SetMarkerColor(9);
 AverageEfficiencyDisk_m1far1->SetLineColor(9);
 AverageEfficiencyDisk_m1far1->Draw("same");

 AverageEfficiencyDisk_m1far1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m1far2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m1far1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_m1far2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_m1far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m1far1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_m1far1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m1far2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_m1far1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_m1far1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_m1far2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_m1far2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Dm1far.png").c_str());
 sta1.str("");
 sta2.str("");



 //-------------------------------------------------all near sides EndCap ---------------------------------------------------------------------------------------------------


 std::cout<<"Reading AverageEfficiencyDisk_3near"<<std::endl;
 TH1F * AverageEfficiencyDisk_3near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_3near"));
 TH1F * AverageEfficiencyDisk_3near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_3near"));
 std::cout<<"Drawing first AverageEfficiencyDisk_3near"<<std::endl;
 AverageEfficiencyDisk_3near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_3near"<<std::endl;
 AverageEfficiencyDisk_3near1->SetMarkerColor(9);
 AverageEfficiencyDisk_3near1->SetLineColor(9);
 AverageEfficiencyDisk_3near1->Draw("same");

 AverageEfficiencyDisk_3near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_3near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_3near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_3near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_3near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_3near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_3near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_3near2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_3near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_3near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_3near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_3near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_D3near.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyDisk_2near"<<std::endl;
 TH1F * AverageEfficiencyDisk_2near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_2near"));
 TH1F * AverageEfficiencyDisk_2near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_2near"));
 std::cout<<"Drawing first AverageEfficiencyDisk_2near"<<std::endl;
 AverageEfficiencyDisk_2near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_2near"<<std::endl;
 AverageEfficiencyDisk_2near1->SetMarkerColor(9);
 AverageEfficiencyDisk_2near1->SetLineColor(9);
 AverageEfficiencyDisk_2near1->Draw("same");

 AverageEfficiencyDisk_2near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_2near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_2near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_2near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_2near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_2near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_2near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_2near2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_2near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_2near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_2near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_2near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_D2near.png").c_str());
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading AverageEfficiencyDisk_1near"<<std::endl;
 TH1F * AverageEfficiencyDisk_1near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_1near"));
 TH1F * AverageEfficiencyDisk_1near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_1near"));
 std::cout<<"Drawing first AverageEfficiencyDisk_1near"<<std::endl;
 AverageEfficiencyDisk_1near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_1near"<<std::endl;
 AverageEfficiencyDisk_1near1->SetMarkerColor(9);
 AverageEfficiencyDisk_1near1->SetLineColor(9);
 AverageEfficiencyDisk_1near1->Draw("same");

 AverageEfficiencyDisk_1near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_1near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_1near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_1near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_1near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_1near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_1near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_1near2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_1near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_1near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_1near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_1near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_D1near.png").c_str());
 sta1.str("");
 sta2.str("");

//Negative Sides

 std::cout<<"Reading AverageEfficiencyDisk_m3near"<<std::endl;
 TH1F * AverageEfficiencyDisk_m3near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_m3near"));
 TH1F * AverageEfficiencyDisk_m3near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_m3near"));
 std::cout<<"Drawing first AverageEfficiencyDisk_m3near"<<std::endl;
 AverageEfficiencyDisk_m3near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_m3near"<<std::endl;
 AverageEfficiencyDisk_m3near1->SetMarkerColor(9);
 AverageEfficiencyDisk_m3near1->SetLineColor(9);
 AverageEfficiencyDisk_m3near1->Draw("same");

 AverageEfficiencyDisk_m3near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m3near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m3near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_m3near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_m3near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m3near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_m3near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m3near2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_m3near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_m3near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_m3near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_m3near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Dm3near.png").c_str());
 sta1.str("");
 sta2.str("");



 std::cout<<"Reading AverageEfficiencyDisk_m2near"<<std::endl;
 TH1F * AverageEfficiencyDisk_m2near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_m2near"));
 TH1F * AverageEfficiencyDisk_m2near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_m2near"));
 std::cout<<"Drawing first AverageEfficiencyDisk_m2near"<<std::endl;
 AverageEfficiencyDisk_m2near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_m2near"<<std::endl;
 AverageEfficiencyDisk_m2near1->SetMarkerColor(9);
 AverageEfficiencyDisk_m2near1->SetLineColor(9);
 AverageEfficiencyDisk_m2near1->Draw("same");

 AverageEfficiencyDisk_m2near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m2near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m2near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_m2near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_m2near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m2near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_m2near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m2near2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_m2near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_m2near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_m2near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_m2near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Dm2near.png").c_str());
 sta1.str("");
 sta2.str("");


 std::cout<<"Reading AverageEfficiencyDisk_m1near"<<std::endl;
 TH1F * AverageEfficiencyDisk_m1near1 = (TH1F*) (theFile1sec->Get("AverageEfficiencyDisk_m1near"));
 TH1F * AverageEfficiencyDisk_m1near2 = (TH1F*) (theFile2sec->Get("AverageEfficiencyDisk_m1near"));
 std::cout<<"Drawing first AverageEfficiencyDisk_m1near"<<std::endl;
 AverageEfficiencyDisk_m1near2->Draw("");
 std::cout<<"Drawing second AverageEfficiencyDisk_m1near"<<std::endl;
 AverageEfficiencyDisk_m1near1->SetMarkerColor(9);
 AverageEfficiencyDisk_m1near1->SetLineColor(9);
 AverageEfficiencyDisk_m1near1->Draw("same");

 AverageEfficiencyDisk_m1near1->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m1near2->GetXaxis()->LabelsOption("v");
 AverageEfficiencyDisk_m1near1->GetXaxis()->SetLabelSize(0.03);
 AverageEfficiencyDisk_m1near2->GetXaxis()->SetLabelSize(0.03);

 TLegend *leg = new TLegend(0.4,0.6,0.7,0.5);
 sta1<<"Mean="<<AverageEfficiencyDisk_m1near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m1near1->GetRMS();
 sta2<<"Mean="<<AverageEfficiencyDisk_m1near1->GetMean()<<" RMS="<<AverageEfficiencyDisk_m1near2->GetRMS();
 leg->AddEntry(AverageEfficiencyDisk_m1near1,string1.c_str(),"l"); 
 //leg->AddEntry(AverageEfficiencyDisk_m1near1,(sta1.str()).c_str(),"l");  
 leg->AddEntry(AverageEfficiencyDisk_m1near2,string2.c_str(),"l");
 //leg->AddEntry(AverageEfficiencyDisk_m1near2,(sta2.str()).c_str(),"l");
 leg->Draw("same");
 Ca2->SaveAs((folder+"Sides/SegEff_Dm1near.png").c_str());
 sta1.str("");
 sta2.str("");


//// --- Creating html code ---

 system(("sed -e \"s|-RUN-|"+string1+"_Vs_"+string2+"|g\" -e \"s|-firstrun-|"+run1+"|g\" -e \"s|-seconrun-|"+run2+"|g\" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/compare/MainIndex.html >"+folder+"/MainIndex.html").c_str());
 system(("sed -e \"s|-RUN-|"+string1+"_Vs_"+string2+"|g\" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/compare/index.html >"+folder+"/index.html").c_str());
 system(("sed -e \"s|-RUN-|"+string1+"_Vs_"+string2+"|g\" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/compare/indexEndCap.html >"+folder+"/indexEndCap.html").c_str());
 system(("sed -e \"s|-RUN-|"+string1+"_Vs_"+string2+"|g\" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/compare/quality.html >"+folder+"/quality.html").c_str());
 system(("sed -e \"s|-RUN-|"+string1+"_Vs_"+string2+"|g\" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/compare/azimutal.html >"+folder+"/azimutal.html").c_str());
 system(("sed -e \"s|-RUN-|"+string1+"_Vs_"+string2+"|g\" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/compare/cls.html >"+folder+"/cls.html").c_str());

////============================

//--- Sending Comparison File ---

system(("scp -r "+folder+" carrillo@cmsrpc402b20:/var/www/html/comparison/").c_str());
system(("firefox cmsrpc402b20/comparison/"+folder).c_str());

//--=============================
}


