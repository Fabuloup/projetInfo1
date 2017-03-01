#include "fireball.hpp"
#include <math.h>

Fireball::Fireball() : m_posx(0), m_posy(0), m_pas(0)
{

}

Fireball::~Fireball()
{

}

int Fireball::get_posx()
{
    return m_posx;
}

int Fireball::get_posy()
{
    return m_posy;
}

int Fireball::get_pas()
{
    return m_pas;
}

void Fireball::set_pas(int new_pas)
{
    m_pas=new_pas;
}

void Fireball::set_posx(int new_x)
{
    m_posx=new_x;
}

void Fireball::set_posy(int new_y)
{
    m_posy=new_y;
}

double Fireball::calculeDirectionx(int cible_x, int cible_y)
{
    double angle=atan2(cible_y-m_posy, cible_x-m_posx);
    return cos(angle);
}

double Fireball::calculeDirectiony(int cible_x, int cible_y)
{
    double angle=atan2(cible_y-m_posy, cible_x-m_posx);
    return sin(angle);
}

void Fireball::set_directionx(double new_directionx)
{
    m_directionx=new_directionx;
}

void Fireball::set_directiony(double new_directiony)
{
    m_directiony=new_directiony;
}

double Fireball::get_directionx()
{
    return m_directionx;
}
double Fireball::get_directiony()
{
    return m_directiony;
}
