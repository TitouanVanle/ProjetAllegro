#include <stdlib.h>
#include <allegro.h>
#include <stdio.h>
/// chaque perso a 5 6 images et le V nb de tour pour que les images changent == animations
#define V  150
#include "mesfonctions.h"
#include "personnage.h"
#include "deplacement.h"
#include "attaque.h"





/// pour le choix des perso
/// tab = ce que le joueur a choisi = il contient le num du perso
/// tab[k] == k le numero du joueur et tab[k] == num du perso choisi
void chargement(t_joueur* characteres[4],int nmbJoueur,int tab[4])
{
    int i=0;

    for ( i=0; i<4; i++)
        characteres[i]=(t_joueur*)malloc(sizeof(t_joueur)); /// allocution dynamique du tab


    char chaine[200];

    for(int k = 0 ; k < nmbJoueur ; k++)
    {
        strcpy(chaine,"");

        if(tab[k] == 0)
        {
            strcpy(characteres[k]->nom,"Naruto");
            for (i=0; i<5; i++)
            {
                sprintf(chaine,"Naruto/frame_%d_delay-0.2s.bmp",i); /// recuperation de simages
                characteres[k]->animation[i]=load_bitmap(chaine,NULL);
            }
            characteres[k]->fin_animation=5;

            for (i=0; i<16; i++)
            {
                characteres[k]->attaque[i]=create_bitmap(150,79);
                characteres[k]->attaque[i]=recup_sprites(load_bitmap("Naruto/Naruto_attaque.bmp",NULL),150,79,0,0,16,i); /// recup des images d attaque

            }
            characteres[k]->attaques[1] = newAttaque("B2.txt");
            characteres[k]->attaques[2] = newAttaque("B3.txt");
            characteres[k]->attaques[3] = newAttaque("B4.txt");
            characteres[k]->fin_attaque=16;


        }
        strcpy(chaine,"");
        if(tab[k] == 1)
        {
            strcpy(characteres[k]->nom,"Franky");
            for (i=0; i<24; i++)
            {
                if(i<7)
                {
                    characteres[k]->animation[i]=create_bitmap(236,118);
                    characteres[k]->animation[i]=recup_sprites(load_bitmap("Franky/Franky.bmp",NULL),236,118,0,0,24,i);
                }
                else
                {
                    characteres[k]->attaque[i-7]=create_bitmap(236,118);
                    characteres[k]->attaque[i-7]=recup_sprites(load_bitmap("Franky/Franky.bmp",NULL),236,118,0,0,24,i);
                }

            }
            characteres[k]->fin_animation=7;
            characteres[k]->fin_attaque=17;
            characteres[k]->attaques[1] = newAttaque("C2.txt");
            characteres[k]->attaques[2] = newAttaque("C3.txt");
            characteres[k]->attaques[3] = newAttaque("C4.txt");
        }
        strcpy(chaine,"");

        if(tab[k] == 2)
        {
            strcpy(characteres[k]->nom,"Goku");
            for (i=0; i<4; i++)
            {
                sprintf(chaine,"Goku/frame_%d_delay-0.16s.bmp",i);
                characteres[k]->animation[i]=load_bitmap(chaine,NULL);
            }
            characteres[k]->fin_animation=4;
            for (i=0; i<31; i++)
            {
                characteres[k]->attaque[i]=create_bitmap(217,210);
                characteres[k]->attaque[i]=recup_sprites(load_bitmap("Goku/Goku_attaque.bmp",NULL),217,210,0,0,31,i);
            }
            characteres[k]->fin_attaque=31;
            characteres[k]->attaques[1] = newAttaque("A2.txt");
            characteres[k]->attaques[2] = newAttaque("A3.txt");
            characteres[k]->attaques[3] = newAttaque("A4.txt");
        }
        strcpy(chaine,"");

        if(tab[k]==3)
        {
            strcpy(characteres[k]->nom,"Brook");
            for (i=0; i<15; i++)
            {
                sprintf(chaine,"Brook/frame_%d_delay-0.1s.bmp",i);

                if(i<5)
                {
                    characteres[k]->animation[i]=load_bitmap(chaine,NULL);
                }
                else
                {
                    characteres[k]->attaque[i-5]=load_bitmap(chaine,NULL);
                }
            }
            characteres[k]->fin_animation=5;
            characteres[k]->fin_attaque=10;
            characteres[k]->attaques[1] = newAttaque("D2.txt");
            characteres[k]->attaques[2] = newAttaque("D3.txt");
            characteres[k]->attaques[3] = newAttaque("D4.txt");
        }
        characteres[k]->act  = 0;
        characteres[k]->cmp = 0;
        characteres[k]->Pa = 20;
        characteres[k]->Pv = 30;
        characteres[k]->Pm = 4;
        characteres[k]->deplacement = 0;
        characteres[k]->attaquement = 0;
        characteres[k]->Pm = 4;
        characteres[k]->pos[0] =9+ 5*k;
        characteres[k]->pos[1] =9 + 5*k;
        characteres[k]->attaques[0] = newAttaque("CaC.txt");
        //characteres[k]->attaques[1] = newAttaque("CaC.txt");
        //characteres[k]->attaques[2] = newAttaque("CaC.txt");
        //characteres[k]->attaques[3] = newAttaque("CaC.txt");
/// CREER D AUTRES FICHIER TXT AVEC D AUTRES ATTAQUES
/// CaC = Attaque de corps a corps

    }
}

void afficherPerso(t_joueur * J,BITMAP * page,BITMAP * fondPerso,int i)
{
    draw_sprite(page,J->animation[J->act],J->pos[0]*18,J->pos[1]*18- J->animation[J->act]->h +18);/// affiche l image
    rectfill(fondPerso,J->pos[0]*18,J->pos[1]*18- J->animation[J->act]->h +18,J->pos[0]*18+J->animation[J->act]->w,J->pos[1]*18 +18,makecol(i+1,128,128));
    /// affiche un rectangle sur la position du perso pour voir où il est

    J->cmp++;
    /// succession d images == creation du cycle
    if(J->cmp == V)
    {
        J->cmp = 0;
        J->act++;
    }
    /// si derniere image atteinte alors retour a la premiere
    if(J->act == J->fin_animation)
    {
        J->act = 0;
    }

}



/// choix des joueurs
/// on clique sur le perso que l on veut
/// chaque perso est associe a un numero qui est associe quand le joueur clique
void choixPerso(int nmb, int tab[4])
{
    BITMAP* acceuil= load_bitmap("Acceuil.bmp",NULL);
    BITMAP* page=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* fond=create_bitmap(SCREEN_W,SCREEN_H);

    for(int i = 0 ; i < nmb ; i++)
    {
        int choix = 10;
        while(choix == 10)
        {
            draw_sprite(page,acceuil,0,0);
            rectfill(page,100,50,700,100,makecol(255,255,255));
            textprintf_centre_ex(page, font,400,70, makecol(0,0,0),-1, "Joueur %d veuillez choisir votre perso",i+1);

            for(int j = 0 ; j < 4 ; j ++)
            {
                rectfill(fond,170 + j*120,200,170 + j*120 +100,450,makecol(j+1,255,255));
                rect(page,170 + j*120,200,170 + j*120 +100,450,makecol(255,255,255));
            }

            int r =getr((getpixel(fond,mouse_x,mouse_y)));
            if( r > 0)
            {
                r--;
                rectfill(page,170 + r*120,200,170 + r*120 +100,450,makecol(255,255,255));

                if(mouse_b&1)
                {
                    choix = 0;
                    tab[i] = r;

                    while((mouse_b&1)!=0)
                    {

                    }
                }
            }
            show_mouse(page);
            draw_sprite(screen,page,0,0);
        }
    }
}
