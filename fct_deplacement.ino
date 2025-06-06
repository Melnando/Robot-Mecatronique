void ralentir(){ //Consigne mise à 30rpm
    for(int i = rapide; i>=lent; i--){
      consigneRPM1--;
      consigneRPM2--;
      delay(10);
  }
  ralentit = true;
  accelere = false;
}


void arreter(){
  digitalWrite(avancerPin1,LOW);
  digitalWrite(avancerPin2,LOW);
  digitalWrite(reculerPin1,LOW);
  digitalWrite(reculerPin2,LOW);
  arrete = true;
  delay(1000);
}


void reculer(){
  digitalWrite(reculerPin1,HIGH);
  digitalWrite(reculerPin2,HIGH);
  recule = true;
}


void avancer(){

  digitalWrite(avancerPin1,HIGH);
  digitalWrite(avancerPin2,HIGH);
    consigneRPM1=lent;
  consigneRPM2=lent;
  arrete = false;
  ralentit = true;
}


void accelerer(){ //consigne mise à 130 rpm
  for(int i = lent; i<=rapide; i++){
      consigneRPM1++;
      consigneRPM2++;
      delay(10);
  }
  accelere = true;
      ralentit = false;
}

void tournerG(){
  digitalWrite(avancerPin1,LOW);
  digitalWrite(avancerPin2,HIGH);
  delay(1550);
}
void tournerD(){
  digitalWrite(avancerPin1,HIGH);
  digitalWrite(avancerPin2,LOW);
  delay(1550);
}
 

/*void contournerG(){  //idée de programme pour le contournement
    int i = 0;
  arreter();
  reculer();
  while (cm<12 || cm2<12 || cm3<12){
      distance_Capteurs();
  }
  arreter();


  do{
    i = 0;
  tournerG();
  while(cm<17 || cm2<17 || cm3<17){
      distance_Capteurs();
      i++;
  }
  arreter();
  avancer();
  delay(3000);
  arreter();
  tournerD();
    while(cm<17 || cm2<17 || cm3<17 || i >0){
        distance_Capteurs();
    i--;
  }
  arreter();
    distance_Capteurs();
  }while (cm<12 || cm2<12 || cm3<12);
  avancer();
  delay(3000);
  arreter();
  tournerD();
  delay(5000);
  arreter();
  avancer();
  delay(3000);
  arreter();
  tournerG();
  delay(5000);
  arreter();  
}*/
