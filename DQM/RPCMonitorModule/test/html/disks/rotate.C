void rotate(){

  float Xcenter=1000;
  float Ycenter=1000;
  float x=0;
  float y=0;
  float radio=1000;
  float angle=0;


  for(int disk =1;disk <=3;disk++){
    for(int ring =2;ring<=3;ring++){
      for(int k=1; k <= 36; k++ ){
	angle = (k-1)*-10+90;
	if(k<10){
	  cout<<"convert -rotate \""<<angle<<"\" ../RE+"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_A/Profile_2D.png RE+"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_Arot.png"<<endl;
	  cout<<"convert -rotate \""<<angle<<"\" ../RE+"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_B/Profile_2D.png RE+"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_Brot.png"<<endl;
	  cout<<"convert -rotate \""<<angle<<"\" ../RE+"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_C/Profile_2D.png RE+"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_Crot.png"<<endl;
	}
	else{
	  cout<<"convert -rotate \""<<angle<<"\" ../RE+"<<disk<<"_R"<<ring<<"_CH"<<k<<"_A/Profile_2D.png RE+"<<disk<<"_R"<<ring<<"_CH"<<k<<"_Arot.png"<<endl;
	  cout<<"convert -rotate \""<<angle<<"\" ../RE+"<<disk<<"_R"<<ring<<"_CH"<<k<<"_B/Profile_2D.png RE+"<<disk<<"_R"<<ring<<"_CH"<<k<<"_Brot.png"<<endl;
	  cout<<"convert -rotate \""<<angle<<"\" ../RE+"<<disk<<"_R"<<ring<<"_CH"<<k<<"_C/Profile_2D.png RE+"<<disk<<"_R"<<ring<<"_CH"<<k<<"_Crot.png"<<endl;
	}
      }
    }
  }

  for(int disk =1;disk <=3;disk++){
    for(int ring =2;ring<=3;ring++){
      for(int k=1; k <= 36; k++ ){
	angle = (k-1)*-10+90;
	if(k<10){
	  cout<<"convert -rotate \""<<angle<<"\" ../RE-"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_A/Profile_2D.png RE-"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_Arot.png"<<endl;
	  cout<<"convert -rotate \""<<angle<<"\" ../RE-"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_B/Profile_2D.png RE-"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_Brot.png"<<endl;
	  cout<<"convert -rotate \""<<angle<<"\" ../RE-"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_C/Profile_2D.png RE-"<<disk<<"_R"<<ring<<"_CH0"<<k<<"_Crot.png"<<endl;
	}
	else{
	  cout<<"convert -rotate \""<<angle<<"\" ../RE-"<<disk<<"_R"<<ring<<"_CH"<<k<<"_A/Profile_2D.png RE-"<<disk<<"_R"<<ring<<"_CH"<<k<<"_Arot.png"<<endl;
	  cout<<"convert -rotate \""<<angle<<"\" ../RE-"<<disk<<"_R"<<ring<<"_CH"<<k<<"_B/Profile_2D.png RE-"<<disk<<"_R"<<ring<<"_CH"<<k<<"_Brot.png"<<endl;
	  cout<<"convert -rotate \""<<angle<<"\" ../RE-"<<disk<<"_R"<<ring<<"_CH"<<k<<"_C/Profile_2D.png RE-"<<disk<<"_R"<<ring<<"_CH"<<k<<"_Crot.png"<<endl;
	}
      }
    }
  }

  exit(0);
}
