#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
/// chaque perso a 5 6 images et le V nb de tour pour que les images changent == animations
#define V  150
#include "mesfonctions.h"


/// sous programme qui decoupe l image ex 5eme image de goku
BITMAP* recup_sprites( BITMAP*scr,int w,int h,int startx,int starty,int col,int element)
{
    BITMAP *bmp;
    int x,y;
    bmp=create_bitmap(w,h);
    if (bmp!=NULL)
    {
        x = startx + (element%col)*w;
        y = starty + (element/col)*h;
        blit( scr, bmp, x, y, 0, 0, w, h);
    }
    return bmp;
}


/// sous programme qui affiche le menu
int Acceuil(BITMAP*page,int type, char gagnant[30])
{
    BITMAP* acceuil= load_bitmap("Acceuil.bmp",NULL);
    int menu=0;
    rectfill(acceuil,320,100,520,180,makecol(255,255,255));
    rectfill(acceuil,320,200,520,280,makecol(255,255,255));
    rectfill(acceuil,320,300,520,380,makecol(255,255,255));
    if((mouse_y >=100 )&& (mouse_y<=180)&&( mouse_x >= 320)&&(mouse_x<=520))
    {
        rectfill(acceuil,320,100,520,180,makecol(128,128,128));
        if(mouse_b&1)
            menu=1;
    }
    else if( (mouse_y>=200&& mouse_y<=280) &&(( mouse_x >= 320 &&mouse_x<=520)))
    {
        rectfill(acceuil,320,200,520,280,makecol(128,128,128));
        if(mouse_b&1)
            menu=2;
    }
    else if((mouse_y>=300&& mouse_y<=380)&&(( mouse_x >= 320 &&mouse_x<=520)))
    {
        rectfill(acceuil,320,300,520,380,makecol(128,128,128));
        if(mouse_b&1)
            menu=3;
    }
    char T1[30]=" JOUER";
    char T2[30]=" OPTION";
    char T3[30]=" QUITTER";

    if(type == 2)
    {
        strcpy(T1,"2 JOUEUR");
        strcpy(T2,"3 JOUEUR");
        strcpy(T3,"4 JOUEUR");
    }
    if(type == 3)
    {
        strcpy(T1,"REJOUER ");
        strcpy(T2,"NOUVELLE PARTIE");
        strcpy(T3,"QUITTER");
    }
    while(mouse_b&1) {};
    textprintf_ex(acceuil, font,390,140,0,-1,T1);
    textprintf_ex(acceuil, font,390,240,0,-1,T2);
    textprintf_ex(acceuil, font,390,340, 0,-1,T3);
    if(type == 3)
        textprintf_centre_ex(acceuil, font,400,30,0,-1,"Felicitation %s vous avez gagne",gagnant);



    show_mouse(acceuil);
    blit(acceuil,page,0,0,0,15,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    clear(page);
    return menu;
}


/// permet d afficher les infos en bas de l ecran
void MenuJoueur(t_joueur* J,BITMAP * page)
{
    rectfill(page,0,500,180,600,makecol(255,255,255));
    /// infos sur le perso : nom, pv etc
    textprintf_ex(page, font,5,505, makecol(0,0,0),-1, "%s",J->nom);
    textprintf_ex(page, font,5,520, makecol(0,0,0),-1, "Pv: %d",J->Pv);
    textprintf_ex(page, font,5,535, makecol(0,0,0),-1, "Pa: %d",J->Pa);
    textprintf_ex(page, font,5,550, makecol(0,0,0),-1, "Pm: %d",J->Pm);


    if(J->action == 0)
    {
        /// menu
        rectfill(page,200,550,380,600,makecol(237,0,0));
        rectfill(page,380,550,560,600,makecol(0,237,0));
        rectfill(page,560,550,740,600,makecol(0,0,237));
        /// affichage des actions possibles
        textprintf_centre_ex(page, font,290,570, makecol(255,255,255),-1, "ATTAQUER");
        textprintf_centre_ex(page, font,470,570, makecol(255,255,255),-1, "SE DEPLACER");
        textprintf_centre_ex(page, font,650,570, makecol(255,255,255),-1, "TOUR SUIVANT");
    }

    if(J->action == 1)
    {
        ///deplacement
        rectfill(page,200,550,740,600,makecol(221,221,0));
        textprintf_centre_ex(page, font,470,570, makecol(255,255,255),-1, "RETOUR");
    }

    if(J->action == 2)
    {
        /// attaquer
        rectfill(page,200,550,380,600,makecol(40,0,0));
        rectfill(page,380,550,560,600,makecol(80,255,0));
        rectfill(page,560,550,740,600,makecol(120,0,255));
        rectfill(page,200,500,740,550,makecol(160,0,255));

        /// affiche les infos des attaques possibles

        textprintf_centre_ex(page, font,290,555, makecol(255,255,255),-1,"%s",J->attaques[1].nom);
        textprintf_centre_ex(page, font,470,555, makecol(255,255,255),-1,"%s",J->attaques[2].nom);
        textprintf_centre_ex(page, font,650,555, makecol(255,255,255),-1,"%s",J->attaques[3].nom);
        textprintf_centre_ex(page, font,470,505, makecol(255,255,255),-1,"%s",J->attaques[0].nom);

        textprintf_centre_ex(page, font,290,570, makecol(255,255,255),-1,"Degats: %d",J->attaques[1].degats);
        textprintf_centre_ex(page, font,470,570, makecol(255,255,255),-1,"Degats: %d",J->attaques[2].degats);
        textprintf_centre_ex(page, font,650,570, makecol(255,255,255),-1,"Degats: %d",J->attaques[3].degats);
        textprintf_centre_ex(page, font,470,520, makecol(255,255,255),-1,"Degats: %d",J->attaques[0].degats);

        textprintf_centre_ex(page, font,290,585, makecol(255,255,255),-1,"PA: %d",J->attaques[1].Pa);
        textprintf_centre_ex(page, font,470,585, makecol(255,255,255),-1,"PA: %d",J->attaques[2].Pa);
        textprintf_centre_ex(page, font,650,585, makecol(255,255,255),-1,"PA: %d",J->attaques[3].Pa);
        textprintf_centre_ex(page, font,470,535, makecol(255,255,255),-1,"PA: %d",J->attaques[0].Pa);
    }

}


/// quand on clique sur un joueur ses infos arrivent dans la console
void AfficheInfo(t_joueur * j[4],BITMAP * fondPerso)
{
     int r = getr((getpixel(fondPerso,mouse_x,mouse_y)));
     if(r > 0)
     {
         int y = r-1;
         system("cls");
         printf("%s\n",j[y]->nom);
         printf("Pv: %d\n",j[y]->Pv);
         printf("Pa: %d\n",j[y]->Pa);
         printf("Pm: %d\n",j[y]->Pm);
     }
}



int LancerPartie()
{
    BITMAP* page=create_bitmap(SCREEN_W,SCREEN_H); /// creation du buffer
    BITMAP* fond=create_bitmap(SCREEN_W,SCREEN_H); /// bitmap de fond pour la map
    BITMAP* fondPerso=create_bitmap(SCREEN_W,SCREEN_H); /// bitmap de fond pour les perso
    BITMAP* map= load_bitmap("map.bmp",NULL);

    for(int i = 0 ; i < 32 ; i++) /// on colorie chaque case selon sa position
        for(int j = 0 ; j < 44 ; j++)
            rectfill(fond,j*18,i*18,j*18+18,i*18+18,makecol(i,j,0));

    /// creation du quadrillage pour voir les cases
    for(int i = 0 ; i < 32 ; i++)
    {
        line(map,0,18*i,800,18*i,makecol(0,0,0));
    }

    for(int i = 0 ; i < 44 ; i++ )
    {
        line(map,18*i,0,18*i,600,makecol(0,0,0));
    }


    int nmb =0; /// nombre de joueurs
    while(nmb == 0)
        nmb=Acceuil(page,2,""); /// choix du nb de joueurs dans le menu

    nmb++;

    int tabi[32][44];
    for(int i =0 ; i < 32 ; i++)
        for(int j = 0 ; j < 44 ; j++)
        {
            tabi[i][j]=0;
        }


    int tab[4];
    choixPerso(nmb,tab);

    t_joueur* characteres[4]; /// tab de joueurs
    chargement(characteres,nmb,tab);


    while(1==1) /// boucle infinie
    {

    int finPartie = 0; /// tant que false alors on reste dans le while

    while(finPartie == 0)
    {
        int cmpmort =0;
        for(int j = 0  ; j < nmb ; j++) /// boucle pour que chaque joueur ait son tour
        {
            if(characteres[j]->Pv > 0) /// on verifie qu il a encore des pts de vie
            {
                characteres[j]->action = 0; /// joueur au menu
                int t = 0;
                characteres[j]->deplacement = 0; /// ne s'est pas encore deplacer
                characteres[j]->attaquement = 0; /// n'a pas encore attaque

                while(characteres[j]->action !=3) /// tant qu'on est pas a 3 qui correspond a fin du tour, le joueur peut effectuer des actions
                {
                    /// affichage du terrain sur buffer
                    draw_sprite(page,map,0,0);

                    /// affiche un carre rouge piur voir quel joueur on joue et sa localisation
                    rectfill(page,characteres[j]->pos[0]*18,characteres[j]->pos[1]*18,characteres[j]->pos[0]*18+18,characteres[j]->pos[1]*18+18,makecol(198,0,0));

                    /// afficher les boutons donc les actions possibles
                    MenuJoueur(characteres[j],page);

                    if(characteres[j]->action == 1) /// deplacement selectionné
                    {
                        afficheDeplacement(page,characteres[j]);
                        sedeplacer(characteres[j],fond,page);
                    }
                    if(characteres[j]->action == 2) /// attaque selectionnée
                    {
                        afficheZoneAttaque(page,characteres[j]);
                        attaquer(characteres,page,nmb,j);
                    }
                    if(mouse_b&1) /// pour savoir où le joueur a clique
                    {
                        int r = getr((getpixel(page,mouse_x,mouse_y)));
                        int g = getg((getpixel(page,mouse_x,mouse_y)));
                        int b = getb((getpixel(page,mouse_x,mouse_y)));

                        if(g == 237 && characteres[j]->deplacement == 0) /// si bouton deplacer select et que le joueur ne s'est pas encore deplace alors execute
                        {
                            characteres[j]->action = 1;

                        }

                        if(r == 237 && characteres[j]->attaquement == 0) /// meme chose pour attaque
                            characteres[j]->action = 2;

                        if(b == 237) /// bouton terminer son tour
                            characteres[j]->action = 3;

                        if(r == 221) /// bouton retour
                            characteres[j]->action = 0;

                        while((mouse_b&1)!=0) /// end du click
                        {

                        }
                    }

                    for(int i = 0 ; i < nmb ; i++) /// boucle pour afficher les perso
                        afficherPerso(characteres[i],page,fondPerso,i);

                    if(mouse_b&1) /// si clique sur un perso ses infos s'affichent dans la console
                    AfficheInfo(characteres,fondPerso);

                    show_mouse(page); /// affiche la souris
                    draw_sprite(screen,page,0,0); /// affiche le buffer sur l ecran
                }
            }
            else /// si le joueur n a pas de PV on augmente le compteur de joueurs morts
            {
                cmpmort++;
            }
        }

        if(cmpmort == nmb -1) /// il ne reste qu un seul joueur en vie
            finPartie = 1; /// fin de partie

    }

    t_joueur * gagnant; /// recherche du joueur gagnant
    for(int o = 0 ; o < nmb ; o++)
    {
        if(characteres[o]->Pv > 0)
            gagnant = characteres[o];
    }
    /// creation du menu de fin
    int menu=0;

    while (menu==0)
    {
        menu=Acceuil(page,3,gagnant->nom);
    }

    if(menu == 3) /// quitte le programme
        return 3;

    if(menu == 2 ) /// recommencer une partie
        return 1;


    }

}
