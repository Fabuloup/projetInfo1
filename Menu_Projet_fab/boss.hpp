#ifndef BOSS_HPP_INCLUDED
#define BOSS_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "fireball.hpp"

class Boss
{
public :
    Boss();
    bool estInvincible() const;
    void recevoirDegats();
    int get_posx();
    int get_posy();
    void set_posx(int new_posx);
    void set_posy(int new_posy);
    void setInvincible(bool inv);

private :
    int m_posx;
    int m_posy;
    bool m_estInvincible;
    int m_vie;
};

void vagueBoss(Boss *boss, float *angle, int *nbboule, Fireball* tabFireball, sf::Clock *clocktp, sf::Time tempstp, sf::Clock *clock, sf::Time temps, int originx, int originy, int rayon);

#endif // BOSS_HPP_INCLUDED
