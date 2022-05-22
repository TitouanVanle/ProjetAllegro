#include <stdlib.h>
#include <allegro.h>
#include <stdio.h>
/// chaque perso a 5 6 images et le V nb de tour pour que les images changent == animations
#define V  150
#include "mesfonctions.h"
#include "personnage.h"
#include "deplacement.h"



/// determine les cases ou le deplacement est possible
void afficheDeplacement(BITMAP * page,t_joueur* J)
{
    for(int i = 0 ; i < 32 ; i++)
    {
        for(int j = 0; j < 44 ; j++)    ///POUR CHAQUE CASE DU PLATEAU
        {
            /// pour chaque case on calcule la distance entre la case et le perso en faisant valeur absolue des diff abscisses et ordonnees
            /// on fait la valeur absolue de la diff des abscisses + valeur absolue de la diff des ordonnees
            /// si le resultat est inferieur ou égal au nb de pts de deplacement ça veut dire que la case est assez proche et donc que le perso peut y aller
            /// chaque case eligible est alors colorée
            if(abs(i-J->pos[0]) + abs(j-J->pos[1]) <= J->Pm)  /// ON VERIFIE SI LA CASE EST ASSEZ PROCHE DU JOUEUR SELON SES POINT DE DEPLACEMENT
            {
                rectfill(page,i*18+2,j*18+2,i*18+18-2,j*18+18-2,makecol(0,0,203));  /// ON AFFICHE UN CARRE BLEU SUR LA CASE
            }
        }
    }
}


/// sous prg pour deplacer le personnage
void sedeplacer(t_joueur* J,BITMAP * fond, BITMAP *page)
{
    if(mouse_b&1) /// est-ce qu'on a clique
    {
        int b = getb((getpixel(page,mouse_x,mouse_y)));
        /// r et g = coordonnees de la case d arrivee
        int r = getr((getpixel(fond,mouse_x,mouse_y)));
        int g = getg((getpixel(fond,mouse_x,mouse_y)));
        /// b est de la meme couleur que 203 (voir prg au dessus) alors c'est une case eligible
        ///page est l ecran de jeu
        /// fond est une bitmap non affichee  dite de fond qui sert a voir les infos sur les cases comme les coordonnees
        if(b == 203)
        {
            J->action = 0; /// deplacement effectue = retour au menu
            J->pos[0] = g;
            J->pos[1] = r;
            J->deplacement = 1; /// on change le booleen pour empecher de refaire l action

        }

    }
}
