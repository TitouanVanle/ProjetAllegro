#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

#include "mesfonctions.h"

void chargement(t_joueur* characteres[4],int nmbJoueur,int tab[4]);
void afficherPerso(t_joueur * J,BITMAP * page,BITMAP * fondPerso,int i);
void choixPerso(int nmb, int tab[4]);

#endif // PERSONNAGE_H_INCLUDED
