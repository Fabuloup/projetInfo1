#include "funcIA.hpp"

ennemy::ennemy() : vie(10),x(0), y(0), type(0)
{

}
ennemy::ennemy(int m_vie, int m_x, int m_y) : vie(m_vie),x(m_x), y(m_y), type(0)
{

}
ennemy::ennemy(int m_vie, int m_x, int m_y, int m_type) : vie(m_vie),x(m_x), y(m_y), type(m_type)
{

}

int* ennemy::getPosition()
{
    int position[]={ennemy::x, ennemy::y};
    return position;
}

void ennemy::setPosition(int m_x, int m_y)
{
    ennemy::x=m_x;
    ennemy::y=m_y;
}
