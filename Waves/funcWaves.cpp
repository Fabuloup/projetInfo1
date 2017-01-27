#include "funcWaves.hpp"

ennemy::ennemy() : e_vie(0), e_x(0), e_y(0), e_type(0), e_actif(0)
{

}

ennemy::ennemy(int m_vie, int m_x, int m_y) : e_vie(m_vie), e_x(m_x), e_y(m_y), e_type(0), e_actif(0)
{

}

void ennemy::setPosition(int m_x, int m_y)
{
    e_x=m_x;
    e_y=m_y;
}

int ennemy::get_x()
{
    return e_x;
}

int ennemy::get_y()
{
    return e_y;
}

void ennemy::setActif(int m_actif)
{
    e_actif=m_actif;
}

int ennemy::isActif()
{
    return e_actif;
}

bool Collision(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    if((pos_x_ia >= pos_x_p + largeur_p)      // trop à droite
            || (pos_x_ia + largeur_ia <=pos_x_p) // trop à gauche
            || (pos_y_ia >= pos_y_p + hauteur_p) // trop en bas
            || (pos_y_ia + hauteur_ia <= pos_y_p))  // trop en haut
        return false;
    else
        return true;
}

bool collision_haut (int posx_p, int posy_p, int posx_ia, int posy_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    //Test si p est bloqué vers le haut par ia
    if (posy_p<=posy_ia+hauteur_ia && posx_p+largeur_p>=posx_ia && posx_p<=posx_ia+largeur_ia && posy_p>=posy_ia+hauteur_ia-1)
        return true;
    else
        return false;
}

bool collision_bas (int posx_p, int posy_p, int posx_ia, int posy_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    //Test si p est bloqué vers le bas par ia
    if (posy_p+hauteur_p>=posy_ia && posx_p+largeur_p>=posx_ia && posx_p<=posx_ia+largeur_ia && posy_p+hauteur_p<=posy_ia+1)
        return true;
    else
        return false;
}

bool collision_droite (int posx_p, int posy_p, int posx_ia, int posy_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    //Test si p est bloqué à droite par ia
    if (posx_p+largeur_p>=posx_ia && posy_p+hauteur_p>=posy_ia && posx_p+largeur_p<=posx_ia+1 && posy_p<=posy_ia+hauteur_ia)
        return true;
    else
        return false;
}

bool collision_gauche (int posx_p, int posy_p, int posx_ia, int posy_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    //Test si p est bloqué à gauche par ia
    if (posx_p<=posx_ia+largeur_ia && posx_p>=posx_ia+largeur_ia-1 && posy_p+hauteur_p>=posy_ia && posy_p<=posy_ia+hauteur_ia)
        return true;
    else
        return false;
}

void ennemy::changePas(int m_pas)
{
    e_pas=m_pas;
}

int ennemy::getPas()
{
    return e_pas;
}
