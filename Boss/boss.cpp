#include "boss.hpp"

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
