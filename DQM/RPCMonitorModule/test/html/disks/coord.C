void coord(){

  float Radio=5000;
  float Xcenter=Radio;
  float Ycenter=Radio;
  float x=0;
  float y=0;
  float angle=0;
  
  cout<<"<html>"<<endl;
  cout<<"<body bgcolor=\"Black\">"<<endl;
  cout<<"<head>"<<endl;
  cout<<"<style type=\"text/css\""<<endl;
  cout<<"<\/style>"<<endl;
  cout<<"<\/head>"<<endl;

  float sizeA = Radio/10;
  float sizeB = sizeA*8/9;
  float sizeC = sizeA*7/9;
	
  float radio = Radio;
  for(int k=1; k <= 36; k++ ){
    angle = (k-1)*10*3.14159565/180.+90*3.14159265/180.;
    y = Ycenter+radio*sin(angle);
    x = Xcenter+radio*cos(angle);

    if(k<10)cout<<"<a href=\"../RE+1_R2_CH0"<<k<<"_A/index.html\">\<IMG STYLE=\"position:absolute; TOP:"<<x<<"px; LEFT:"<<y<<"px; WIDTH:"<<sizeA<<"px; HEIGHT:"<<sizeA<<"px\" SRC=\"RE+1_R2_CH0"<<k<<"_Arot.png\"\>"<<endl;
    else cout<<"<a href=\"../RE+1_R2_CH"<<k<<"_A/index.html\">\<IMG STYLE=\"position:absolute; TOP:"<<x<<"px; LEFT:"<<y<<"px; WIDTH:"<<sizeA<<"px; HEIGHT:"<<sizeA<<"px\" SRC=\"RE+1_R2_CH"<<k<<"_Arot.png\"\>"<<endl;
    //cout<<x<<" "<<y<<endl;
  }

  radio=Radio*8/9;
  for(int k=1; k <= 36; k++ ){
    angle = (k-1)*10*3.14159565/180.+90*3.14159265/180.;
    y = Ycenter+radio*sin(angle);
    x = Xcenter+radio*cos(angle);

    if(k<10)cout<<"<a href=\"../RE+1_R2_CH0"<<k<<"_B/index.html\">\<IMG STYLE=\"position:absolute; TOP:"<<x<<"px; LEFT:"<<y<<"px; WIDTH:"<<sizeB<<"px; HEIGHT:"<<sizeB<<"px\" SRC=\"RE+1_R2_CH0"<<k<<"_Brot.png\"\>"<<endl;
    else cout<<"<a href=\"../RE+1_R2_CH"<<k<<"_B/index.html\">\<IMG STYLE=\"position:absolute; TOP:"<<x<<"px; LEFT:"<<y<<"px; WIDTH:"<<sizeB<<"px; HEIGHT:"<<sizeB<<"px\" SRC=\"RE+1_R2_CH"<<k<<"_Brot.png\"\>"<<endl;
    //cout<<x<<" "<<y<<endl;
  }

  radio=Radio*7/9;
  for(int k=1; k <= 36; k++ ){
    angle = (k-1)*10*3.14159565/180.+90*3.14159265/180.;
    y = Ycenter+radio*sin(angle);
    x = Xcenter+radio*cos(angle);

    if(k<10)cout<<"<a href=\"../RE+1_R2_CH0"<<k<<"_C/index.html\">\<IMG STYLE=\"position:absolute; TOP:"<<x<<"px; LEFT:"<<y<<"px; WIDTH:"<<sizeC<<"px; HEIGHT:"<<sizeC<<"px\" SRC=\"RE+1_R2_CH0"<<k<<"_Crot.png\"\>"<<endl;
    else cout<<"<a href=\"../RE+1_R2_CH"<<k<<"_C/index.html\">\<IMG STYLE=\"position:absolute; TOP:"<<x<<"px; LEFT:"<<y<<"px; WIDTH:"<<sizeC<<"px; HEIGHT:"<<sizeC<<"px\" SRC=\"RE+1_R2_CH"<<k<<"_Crot.png\"\>"<<endl;
    //cout<<x<<" "<<y<<endl;
  }

  cout<<"</body>"<<endl;
  cout<<"</html>"<<endl;
  exit(0);
}
