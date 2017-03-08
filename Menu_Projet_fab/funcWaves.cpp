#include "funcWaves.hpp"

//Création d'une classe ennemi
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

int ennemy::getType()
{
    return e_type;
}

void ennemy::setType(int new_type)
{
    e_type=new_type;
}

void ennemy::setZone(int new_zone)
{
    e_zone=new_zone;
}

int ennemy::getZone()
{
    return e_zone;
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

//Fonction pour les collisions
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
