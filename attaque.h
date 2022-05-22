#ifndef ATTAQUE_H_INCLUDED
#define ATTAQUE_H_INCLUDED

#include "mesfonctions.h"

t_attaque newAttaque(char fichier[10]);
void afficheZoneAttaque(BITMAP* page,t_joueur* J);
void attaquer(t_joueur * liste[4], BITMAP * page,int nmb, int act);

#endif // ATTAQUE_H_INCLUDED
