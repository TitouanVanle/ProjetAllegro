#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
/// chaque perso a 5 6 images et le V nb de tour pour que les images changent == animations
#define V  150
#include "mesfonctions.h"
#include "personnage.h"
#include "deplacement.h"
#include "attaque.h"



int main()
{
    allegro_init();
    install_keyboard();
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    set_color_depth(desktop_color_depth());


    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    install_mouse();
    BITMAP* page=create_bitmap(SCREEN_W,SCREEN_H);
    int menu=0;
    while (menu!=3)
    {
        menu=Acceuil(page,1,"");
        while(menu==1) // MODE 1
        {
            while((mouse_b&1)!=0)
            {

            }
            menu = LancerPartie();
        }

    }
    allegro_exit();
    return 0;
}
END_OF_MAIN();
