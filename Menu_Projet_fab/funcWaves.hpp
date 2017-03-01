#ifndef FUNCWAVES_HPP_INCLUDED
#define FUNCWAVES_HPP_INCLUDED
#define MAXENNEMY 20

class ennemy
{
private:
    int e_vie;
    int e_x;
    int e_y;
    int e_type;
    int e_actif;
    int e_pas;
    int e_zone;
public:
    ennemy();
    ennemy(int m_vie, int m_x, int m_y);
    void setPosition(int m_x, int m_y);
    int get_x();
    int get_y();
    void setActif(int m_actif);
    int isActif();
    void changePas(int m_pas);
    int getPas();
    void setZone(int new_zone);
    int getZone();
    void setType(int new_type);
    int getType();
};

bool collision_haut(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);
bool collision_bas(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);
bool collision_gauche(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);
bool collision_droite(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);

#endif // FUNCWAVES_HPP_INCLUDED
