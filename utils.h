#ifndef UTILS_H
#define UTILS_H

// Charge le contenu du fichier dont le chemin est passé en 
// paramètre dans une chaîne de caractères allouée dynamiquement
// la chaîne doit être subséquemment libérée avec free
char* charger_fichier(char* chemin);

#endif
