#ifndef MESFONCTIONS_H_INCLUDED
#define MESFONCTIONS_H_INCLUDED

/// struct attaque
typedef struct attaque
{
    char nom[30];
    int degats;
    int random; /// nb de degats aleatoire en surplus
    int zone[11][11]; /// zone d action de l attaque le 0 au milieu est le perso et les 1 sont les zones touchées par l attaque
    int Pa;

} t_attaque;

///struct perso
typedef struct joueur
{
    char nom[30];
    int pos[2];/// position du perso contenant pX et pY
    int Pv;
    int Pm;/// pts mouv : cb de deplacements le perso peut faire
    int Pa; /// pts actions : nb d actions pouvant etre realises lors d un tour
    BITMAP* animation[20]; /// toutes les images du perso
    BITMAP* attaque[100];
    int fin_animation; /// nb total d images par perso, permet de revenir a l image zero
    int fin_attaque;
    int cmp; /// compteur de boucle jusqu'à V
    int act; /// image que l on va afficher
    int action; /// 0 = rien fait; 1 = deplacement; 2= attaquer; 3= fin du tour
    int deplacement; /// passe a True quand on s est deplace == on ne peut plus le faire
    int attaquement; /// meme chose pour l action attaquer
    t_attaque attaques[4]; /// liste des attaques = [0] = corps a corps commune à tous et les autres en fct du perso

} t_joueur;



int Acceuil(BITMAP*page,int type, char gagnant[30]);
void MenuJoueur(t_joueur* J,BITMAP * page);
BITMAP* recup_sprites( BITMAP*scr,int w,int h,int startx,int starty,int col,int element);
void AfficheInfo(t_joueur * j[4],BITMAP * fondPerso);
int LancerPartie();

#endif // MESFONCTIONS_H_INCLUDED
