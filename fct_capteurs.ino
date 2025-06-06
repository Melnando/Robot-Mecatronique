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
