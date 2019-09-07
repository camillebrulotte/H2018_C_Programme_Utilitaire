#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "utils.h"

char* charger_fichier(char* nom_fichier) {
  struct stat infos_fichier;
  stat(nom_fichier, &infos_fichier);
  char *contenu = malloc((infos_fichier.st_size + 1) * sizeof (char));
  FILE *fichier = fopen(nom_fichier, "r");
  char *curseur = contenu;
  int c;
  while ((c = fgetc(fichier)) != EOF) {
    char nouveau = (char) c;
    *curseur = nouveau;
    curseur++;
  }
  *curseur = '\0';
  fclose(fichier);
  return contenu;
}


