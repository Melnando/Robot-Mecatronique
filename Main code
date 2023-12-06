// ASSERVISSEMENT

//pin utilisés moteur 1
uint8_t enablePin1 = 9;
uint8_t avancerPin1 = 10;
uint8_t reculerPin1 = 8;

//pin acquérant les ticks moteur 1
uint8_t acquereur1 = 2;

//comptage de ticks Moteur 1
volatile uint8_t tick_codeur1 = 0;
volatile uint8_t nbTicks1 = 0;

//Nombre de mesures
int mesures = 0;

//Paramètres du moteur 1
int cmd1 = 0;
float rpm1 = 0;
float erreur1 = 0;
float consigneRPM1 = 130;
float somme_erreur1 = 0;
float delta_erreur1 = 0;
float erreur_precedente1 = consigneRPM1;

//correcteurs Moteur 1
int kp1 = 50;
int ki1 = 0;
int kd1 = 0;

void compteur1();
void asservissement1(int nbTicks1);



//Asservissement moteur 2

//pin utilisés moteur 2
uint8_t enablePin2 = 6;
uint8_t avancerPin2 = 7;
uint8_t reculerPin2 = 5;

//pin acquérant les ticks moteur 2
uint8_t acquereur2 = 3;

//comptage de ticks Moteur 2
volatile uint8_t tick_codeur2 = 0;
volatile uint8_t nbTicks2 = 0;

//Paramètres du moteur 2
int cmd2 = 0;
float rpm2 = 0;
float erreur2 = 0;
float consigneRPM2 = 130;
float somme_erreur2 = 0;
float delta_erreur2 = 0;
float erreur_precedente2 = consigneRPM2;

//correcteurs Moteur 2
int kp2 = 50;
int ki2 = 0;
int kd2 = 0;

void compteur2();
void asservissement2(int nbTicks2);




// CAPTEURS DISTANCE

// initialisation des variables globales

int trig = 13;
int echo = 12; 
int echo2 = 11; 
int echo3 = 4;
long lecture_echo;    // long correspond à une variable allant jusqu’à 32 bits
long lecture_echo2;
long lecture_echo3; 
long cm; 
long cm2;
long cm3;
//fonctions utilisées
void distance_Capteurs();


// FONCTIONS POUR LE DEPLACEMENT


int marge = 12;

//variables servant aux fonctions de déplacement
int lent = 30;
bool ralentit = false;
bool arrete = true;
bool accelere = false;
bool recule = false;
bool obstacle = false;
int rapide = 130;

void ralentir();
void contournerG();
void arreter();
void reculer();



void setup() {
  
// ASSERVISSEMENT

// Setup des pins utilisés pour le moteur 1 
pinMode(enablePin1,OUTPUT);
pinMode(avancerPin1,OUTPUT);
pinMode(reculerPin1,OUTPUT);


digitalWrite(avancerPin1, LOW);
digitalWrite(reculerPin1, LOW);


// Setup des pins utilisés pour le moteur 2

attachInterrupt(digitalPinToInterrupt(acquereur1),compteur1,RISING); //A chaque tick du reçu par acquereur1, cela déclenche la fonction compteur

//Setup des pins utilisés pour le moteur 2
pinMode(enablePin2,OUTPUT);
pinMode(avancerPin2,OUTPUT);
pinMode(reculerPin2,OUTPUT);


digitalWrite(avancerPin2, LOW);
digitalWrite(reculerPin2, LOW);


attachInterrupt(digitalPinToInterrupt(acquereur2),compteur2,RISING);

// CAPTEURS
pinMode(trig, OUTPUT);  // le pin de valeur « trig » est configuré en sortie
pinMode(echo, INPUT);   // le pin de valeur « echo » est configuré en entrée
pinMode(echo2, INPUT); 
pinMode(echo3, INPUT); 

digitalWrite(trig, LOW);  // le pin de valeur « trig » est mis à l’état bas

//Timers

TCCR2A = 0;   //Mode normal(pas PWM) 
TCCR2B = B111;  //prescaler 1024
TIMSK2 = 0x01;  //interruption sur débordement du timer

sei(); // interruptions activées

Serial.begin(9600); //Communication avec le PC mise à 9600 bit/s
analogWrite(enablePin1, 255);
}

void loop() {
  distance_Capteurs(); //mesure de la distance par les capteurs

  if(cm>12 && cm2>12&&cm3>12 && arrete == true&&obstacle == false){
    avancer();  
  }
  else if((cm<12 || cm2<12 || cm3<12)){
    arreter();
    reculer();
    while(cm<12 || cm2<12 || cm3<12){
      distance_Capteurs();
    }
    obstacle = true;    
  }
  else if(cm3>cm && obstacle == true){ //évitement de l'obstacle par la droite
    avancer();
    arreter();
    tournerD();
    arreter();
    avancer();
    distance_Capteurs();
    if(cm>12 && cm2>12 && cm3>12){
      obstacle = false;
    }
  }
  else if(cm3<cm && obstacle == true){ // évitement de l'obstacle par la gauche
    avancer();
    arreter();
    tournerG();
    arreter();
    if(cm>12 && cm2>12 && cm3>12){
      obstacle = false;
    }
  }

// affichage
      Serial.print("capteur 1 :");
  Serial.println(cm);
  Serial.print("capteur 2 :");
  Serial.println(cm2);
  Serial.print("capteur 3 :");
  Serial.println(cm3);
  Serial.print(rpm2,8);
    Serial.print(" : ");
    Serial.print(erreur2,4);
    Serial.println();

  
  /*if(mesures >100){ //utilisé pour faire les mesures de la réponse indicielle des moteurs
    analogWrite(enablePin1,0);
    analogWrite(enablePin2,0);
    cli();*/
}

ISR(TIMER2_OVF_vect){ // interruption toutes les 16,4 ms

  

//Comptage ticks moteur 1
 nbTicks1 = tick_codeur1;
 asservissement1(nbTicks1); // asservissement du moteur 1
 tick_codeur1 = 0;

//Comptage ticks moteur 2
 nbTicks2 = tick_codeur2;
 asservissement2(nbTicks2); // asservissement du moteur 2
 tick_codeur2=0;
  // start new ticks count. Compte le nombre de ticks durant l'interruption de periode T. 



}

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

void distance_Capteurs()
{
  
digitalWrite(trig, HIGH); // le pin de valeur « trig » est mis à l’état haut
delayMicroseconds(10);  //Un delais de 10 µs temporise l’execution du programme
digitalWrite(trig, LOW);    // le pin de valeur « trig » est mis à l’état bas : on a généré un signal de 10 µs

lecture_echo = pulseIn(echo,HIGH);  // la variable “ lecture_echo “ prend la valeur du temps de la pulsation reçue par le pin « echo ». 
if(lecture_echo !=0){
cm = lecture_echo /58 ;   // La variable « cm » prend la valeur de « lecture_echo » multipliée par la vitesse du son divisée par 2 et convertie en cm/micro secondes
}

digitalWrite(trig, HIGH); // le pin de valeur « trig » est mis à l’état haut
delayMicroseconds(10);  //Un delais de 10 µs temporise l’execution du programme
digitalWrite(trig, LOW);    // le pin de valeur « trig » est mis à l’état bas : on a généré un signal de 10 µs
lecture_echo2 = pulseIn(echo2,HIGH); 
if(lecture_echo2 !=0){
cm2 = lecture_echo2 /58; 
}


digitalWrite(trig, HIGH); // le pin de valeur « trig » est mis à l’état haut
delayMicroseconds(10);  //Un delais de 10 µs temporise l’execution du programme
digitalWrite(trig, LOW);    // le pin de valeur « trig » est mis à l’état bas : on a généré un signal de 10 µs
lecture_echo3 = pulseIn(echo3,HIGH); 
if(lecture_echo3 !=0){
cm3 = lecture_echo3 /58; 
}

}


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



