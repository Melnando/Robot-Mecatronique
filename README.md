# Base Roulante pour Robot de Cartographie Radioactive (Projet Mécatronique)
![image robot](https://github.com/user-attachments/assets/993e996c-da22-49cb-bbdf-2ee6657c5e68)

## Description du Projet
Ce projet consiste à concevoir un robot mobile autonome, capable d'évoluer sur une surface horizontale comportant des obstacles afin de cartographier la radioactivité dans des zones de stockage. Il s'agit d'un prototype simple, économique et adaptable à des environnements hostiles, incluant une correction asservie de la trajectoire pour garantir une navigation fiable.

Version 0 : Pas de capteur de radioactivité embarqué – mise en œuvre des fonctionnalités de base uniquement (mouvement droit, détection et contournement d’obstacles, demi-tour).

## Objectifs
- Avancer en ligne droite avec correction automatique de trajectoire

- Détecter et éviter des obstacles à l’aide d’un capteur ultrason

- Effectuer un demi-tour en fin de parcours pour scanner la ligne suivante

- Implémentation d’un système d’asservissement (PID) pour réguler la vitesse des moteurs

## Conception Théorique
- Étude des moteurs CC et commande par signal PWM

- Modélisation d’un pont en H (L293D) pour piloter les moteurs

- Utilisation des capteurs HC-SR04 pour la détection d’obstacles

- Mise en œuvre de l’asservissement PID avec encodeurs pour synchroniser les roues

- Simulation des réponses dynamiques sous MATLAB / Simulink


