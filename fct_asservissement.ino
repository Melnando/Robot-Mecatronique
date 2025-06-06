void asservissement1(int nbticks1){
//Serial.println(nbticks1);

  //Calcul de l'erreur  
   rpm1 = 60000*1.6*nbticks1/(360*16.4);
  //Serial.println(rpm1);
   erreur1 =rpm1 - consigneRPM1;
  somme_erreur1 += erreur1;
  delta_erreur1 = erreur1-erreur_precedente1;
  erreur_precedente1 = erreur1;
  
  //Calcul de la commande
  cmd1 = kp1*erreur1 + ki1*somme_erreur1 + kd1*delta_erreur1;
  //Normalisation et contrôle du moteur
  if(cmd1<0) cmd1=0;
  else if(cmd1>255) cmd1 = 255;
  analogWrite(enablePin1,255-cmd1);

//Debug
/*
  Serial.print(rpm1,8);
    Serial.print(" : ");
    Serial.print(erreur1,4);
    Serial.println();
  */
  ++mesures;
}



void compteur1(){
  ++tick_codeur1;
}


//Asservissement moteur 2

void asservissement2(int nbticks2){
//Serial.println(nbticks2);
  //Calcul de l'erreur (moteur 2) 
   rpm2 = 60000*1.6*nbticks2/(360*16.4);
  //Serial.println(rpm2);
   erreur2 =rpm2 - consigneRPM2;
  somme_erreur2 += erreur2;
  delta_erreur2 = erreur2-erreur_precedente2;
  erreur_precedente2 = erreur2;
  
  //Calcul de la commande
  cmd2 = kp2*erreur2 + ki2*somme_erreur2 + kd2*delta_erreur2;
  
  //Normalisation et contrôle du moteur
  if(cmd2<0) cmd2=0;
  else if(cmd2>255) cmd2 = 255;
  analogWrite(enablePin2,255-cmd2);
}


void compteur2(){
  ++tick_codeur2;
}
