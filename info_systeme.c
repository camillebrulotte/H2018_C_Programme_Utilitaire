// Ce projet est faite en c. Il permet d'afficher un menu avec des fonctions dans la console
// Auteur : Camille Brulotte
// Cours : Fonctionnement Interne
// Remise : 10 Mai 2018

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void menu();
void verification_Nombre_Lu();
void memoire();
void configuration();
void peripheriques();
void choix();
void vider_buffer();
int lireChoix();
int donneesMemoire();

void main (int argc, char** argv) {
  menu ();
}

/**
 * Affichage du menu
 */ 
void menu(){
  char hostnom[256];
  printf("\n");
  
    if (gethostname(hostnom, sizeof(hostnom)) == 0){
      printf("Bonjour, vous êtes présentement sur l'ordinateur %s \n", hostnom);
    }
      printf("Veuillez choisir parmi les options suivantes : \n");
      printf("1) Afficher les informations sur la mémoire \n");
      printf("2) Afficher les informations sur la configuration IP \n");
      printf("3) Afficher les informations sur les périphériques \n");
      printf("4) Quitter ce magnifique logiciel \n");

      int choice = lireChoix();

      choix(choice);
}

/**
 * Lire le choix de l'utilisateur
 */ 
int lireChoix(){
  int age_valide = 0;
  int nombre_Valide = 0;
  int choice;
  int nombre_lu;

  // Lecture du nombre
  while (! nombre_Valide) {
    printf("Veuillez choisir entre 1 et 4 : "); 
    nombre_lu = scanf("%d", &choice);
      
    if(choice >= 1 && choice <= 4){
      nombre_Valide = 1;
    }
    else {
      printf("Entrez une valeur entre 1 et 4 inclusivement \n");
      vider_buffer();
      
      nombre_Valide = 0;
    }
  }

  return choice;
}

/**
 * Permet d'aller au choix du menu de l'utilisateur
 */ 
void choix(int choice){
  if (choice == 1){
    memoire(choice);
  }
  else if (choice == 2){
    configuration(choice);
  }
  else if (choice == 3){
    peripheriques(choice);
  }
}

/**
 * Permet de vider le buffer
 */ 
void vider_buffer (int option){
  int c;
  
  do {
    c = getchar();
   } while (c != '\n' && c != EOF);
}

/**
 * Permet d'afficher la mémoire
 */ 
void memoire(int option){
  printf("\n");
  
  //Ce qu'il faut qu'il cherche
  char* MemTotal = "MemTotal:";
  char* MemFree = "MemFree:";
  char* MemAvailable = "MemAvailable";
  
  int donneesTotal;
  int donneesFree;
  int donneesAvailable;

  //Aller chercher les informations dans le fichier 
  system("head -3 /proc/meminfo > meminfo.txt");

  //Aller chercher la données
  donneesTotal = donneesMemoire(MemTotal);
  donneesFree = donneesMemoire(MemFree);
  donneesAvailable = donneesMemoire(MemAvailable);

  //Imprimer a l'écran les memoires, converti en Mo
  printf("Mémoire totale      = %d Mo\n", donneesTotal/1024);
  printf("Mémoire libre       = %d Mo\n", donneesFree/1024);
  printf("Mémoire disponible  = %d Mo\n", donneesAvailable/1024);

  //Effacer le fichier
  system("rm meminfo.txt");
  
  menu();  
}

/**
 * Aller extraire la donnee de la mémoire
 */ 
int donneesMemoire(char* donnees){
  char* nomFichier = "meminfo.txt";
  char* temp;
  char* index;
  int valeur;

  //Ouvrir le fichier
  temp = charger_fichier(nomFichier);

  //Mettre la position temp dans index
  index = strstr(temp, donnees);

  //Déplacer l'index un caracte plus loin
  index += strlen(donnees) + 1;

  //Pour aller chercher la position du premier chiffre
  while (*index != ' '){
    index++;
  }

  //Lire de la position de l'index, jusqu'a la fin de la ligne et le mettre dans val
  sscanf(index, "%d", &valeur);

  //Valeur contient maintenant la données de la mémoire
  return valeur;
}

/**
 * Permet de vérifier la connectivité de l'ordinateur
 */ 
void configuration (int option){
  printf("\n");
  int ping;
  FILE *fp;
  char buff [255];

  //Pour vérifier la connexion a internet
  ping = system("ping -w 2 -c 4 8.8.8.8 > /dev/null 2>&1");

  if (!ping){
    printf("Cet ordinateur est connecté a Internet. \n");

    //Pour mettre dans ip.txt l'adresse IP du systeme
    system("hostname -I >> ip.txt");
    
    fp = fopen("ip.txt", "r");

    //Afficher l'adresse IP
    fgets(buff, 255, (FILE*)fp);
    printf("Son adresse IP est : %s", buff);

    //Effacer le fichier
    system("rm ip.txt");
      
    fclose(fp);
  }
  else{
    printf("Cet ordinateur n'est pas connecté a Internet. \n");
    printf("\n");
  }

  menu(); 
}

/**
 * Permet d'afficher le nom de la carte graphique
 */ 
void peripheriques(int option){
  printf("\n");
  
  //Mettre dans ces variables la ligne qu'il faut afficher
  char* ethernetName;
  char* VGAName;

  //Aller chercher les informations dans le fichier 
  system("lspci > pci.txt");

  //Aller chercher la ligne a afficher
  system("grep Ethernet pci.txt > Ethernet.txt");

  //Mettre dans ethernetName la ligne du fichier
  ethernetName = charger_fichier("Ethernet.txt");

  //Trouver la position ou il faut extraire la ligne
  char *b = strstr(ethernetName, ": ");
  int position = b - ethernetName;

  //Contient la ligne a afficher
  system("grep VGA pci.txt > VGA.txt");

  //Mettre dans VGAName la ligne du fichier
  VGAName = charger_fichier("VGA.txt");

  //Trouver la position ou il faut extraire la ligne
  char *c = strstr(VGAName, ": ");
  int position2 = c- VGAName;

  //Imprimer a l'écran la ligne
  printf("Nom du contrôleur Ethernet : %.*s", 255, ethernetName + position + 2);
  printf("Nom du contrôleur VGA      : %.*s", 255, VGAName + position2 + 2);

  //Effacer le fichier
  system("rm VGA.txt");
  system("rm Ethernet.txt");
  system("rm pci.txt");
  
  menu();
}
