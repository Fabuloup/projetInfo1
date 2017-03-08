#include "boss.hpp"
#include <stdlib.h>
#include "fireball.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>


//Boss codé mais pas encore implanté


Boss::Boss() : m_posx(385), m_posy(275), m_estInvincible(false), m_vie(3)
{

}

void Boss::setInvincible(bool inv)
{
    m_estInvincible=inv;
}

bool Boss::estInvincible() const
{
    return m_estInvincible;
}

void Boss::set_posx(int new_posx)
{
    m_posx=new_posx;
}

void Boss::set_posy(int new_posy)
{
    m_posy=new_posy;
}

int Boss::get_posx()
{
    return m_posx;
}

int Boss::get_posy()
{
    return m_posy;
}

void Boss::recevoirDegats()
{
    m_vie-=1;
}

void vagueBoss(Boss *boss, float *angle, int *nbboule, Fireball* tabFireball, sf::Clock *clocktp, sf::Time tempstp, sf::Clock *clock, sf::Time temps, int originx, int originy, int rayon)
{
    float attaqueTeleportation, attaqueInvincible, attaqueFireball, dirx, diry;
    attaqueTeleportation=(float)rand()/(float)(RAND_MAX);
    attaqueInvincible=(float)rand()/(float)(RAND_MAX);
    attaqueFireball=(float)rand()/(float)(RAND_MAX);
    //Le boss décrit un cercle, donc à la fin, on le remet sur sa position de base
    if (*angle>6.3)
        *angle=0.03;
    //Le boss peut lancer des boules de feu, dans une direction aléatoire
    if (attaqueFireball<=0.05 && *nbboule<20)
    {
        *nbboule=*nbboule+1;
        tabFireball[*nbboule].set_posx(boss->get_posx());
        tabFireball[*nbboule].set_posy(boss->get_posy());
        dirx=rand()%800;
        diry=rand()%600;
        tabFireball[*nbboule].set_directionx(tabFireball[*nbboule].calculeDirectionx(dirx, diry));
        tabFireball[*nbboule].set_directiony(tabFireball[*nbboule].calculeDirectiony(dirx,diry));
    }
    //Il a une attaque pour se téléporter
    if (attaqueTeleportation>=0.99 && clocktp->getElapsedTime()>tempstp)
    {
        angle=angle+3;
        clocktp->restart();
    }
    //Il peut devenir invincible
    if (attaqueInvincible>=0.55 && attaqueInvincible<=0.56 && clock->getElapsedTime()>temps)
    {
        boss->setInvincible(true);
        clock->restart();
    }
    //Au bout d'un certain temps, le boss perd son invincibilité
    if (clock->getElapsedTime()>temps)
    {
        boss->setInvincible(false);
    }
    //On déplace le boss
    *angle=*angle+0.03;
    boss->set_posx(originx+cos(*angle)*rayon);
    boss->set_posy(originy+sin(*angle)*rayon);
}
