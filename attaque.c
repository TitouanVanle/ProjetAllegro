#include <stdlib.h>
#include <allegro.h>
#include <stdio.h>
/// chaque perso a 5 6 images et le V nb de tour pour que les images changent == animations
#define V  150
#include "mesfonctions.h"
#include "attaque.h"
#include "personnage.h"
#include "deplacement.h"




/// recuperer les infos du fichier qui contient les attaques
t_attaque newAttaque(char fichier[10])
{

    t_attaque NEW;
    FILE * fic = NULL;

    fic = fopen(fichier, "r");

    if (fic != NULL)
    {

        fscanf(fic, "%s\n",&NEW.nom);
        fscanf(fic, "%d\n",&NEW.degats);
        fscanf(fic, "%d\n",&NEW.random);
        fscanf(fic, "%d\n",&NEW.Pa);
        for(int i = 0 ; i < 11 ; i++)
        {
            fscanf(fic, "%d %d %d %d %d %d %d %d %d %d %d\n",&NEW.zone[i][0],&NEW.zone[i][1],&NEW.zone[i][2],&NEW.zone[i][3],&NEW.zone[i][4],&NEW.zone[i][5],&NEW.zone[i][6],&NEW.zone[i][7],&NEW.zone[i][8],&NEW.zone[i][9],&NEW.zone[i][10],&NEW.zone[i][11]);
        }

        fclose(fic);
    }

    // printf("%s  %d %d  %d\n\n",NEW.nom, NEW.degats,NEW.random, NEW.Pa);

    return NEW;

}


/// affiche les cases touchées par une attaque

void afficheZoneAttaque(BITMAP* page,t_joueur* J)
{
    int r = getr((getpixel(page,mouse_x,mouse_y))); /// on recupere l attaque selectionnee

    int x =10;
    /// on verifie quelle attaque il s'agit
    /// les num 40 80 120 160 sont definis dans le sous prg MenuJoueur
    if(r == 40)
        x=1;

    if(r == 80)
        x=2;
    if(r == 120)
        x=3;

    if(r == 160)
        x=0;

    if(x!=10) /// on verifie qu une attaque a été selectionnée
    {
        /// on affiche les cases possibles pour l attaque
        for(int i = 0 ; i < 11 ; i++ )
            for(int j= 0 ; j <11 ; j++ )
                if(J->attaques[x].zone[i][j] == 1)
                    rectfill(page,(J->pos[0]-5+j)*18+2,(J->pos[1]-5+i)*18+2,(J->pos[0]-5+j)*18+18-2,(J->pos[1]-5+i)*18+18-2,makecol(57,50,131));

    }


}



void attaquer(t_joueur * liste[4], BITMAP * page,int nmb, int act)
{

    if(mouse_b&1) /// le joueur clique
    {
        int r = getr((getpixel(page,mouse_x,mouse_y)));
        /// on verifie de quelle attaque il sagait
        int x =10;

        if(r == 40)
            x=1;

        if(r == 80)
            x=2;
        if(r == 120)
            x=3;

        if(r == 160)
            x=0;

        if(x != 10)
        {
            /// S correspond a l attaque selectionnee
            t_attaque S = liste[act]->attaques[x];
            liste[act]->action = 0; /// repasse au menu
            liste[act]->Pa = liste[act]->Pa - S.Pa; /// on enleve les pts d attaque
            liste[act]->attaquement = 1; /// on passe le booleen a true pour ne pas repeter l action lors du meme tour

            printf("Vous avez attaque\n");

            for(int i = 0 ; i < nmb ; i++)
            {
                /// on regarde si la couleur du perso cible est
                if(getb((getpixel(page,liste[i]->pos[0]*18+4,liste[i]->pos[1]*18+4))) == 131)
                {
                    int nmbDegats = S.degats + rand()%S.random;
                    liste[i]->Pv = liste[i]->Pv - nmbDegats;/// on enleve les degats
                    printf("Vous avez inflige %d degats a %s",nmbDegats,liste[i]->nom);
                }
            }
        }
    }
}
