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

void ennemy::changePas(int m_pas)
{
    e_pas=m_pas;
}

int ennemy::getPas()
{
    return e_pas;
}
