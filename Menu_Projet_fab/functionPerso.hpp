#ifndef FUNCTIONPERSO_HPP_INCLUDED
#define FUNCTIONPERSO_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "funcWaves.hpp"

class heros
{
public:
    heros();
    heros(int m_x, int m_y, int m_speed, int m_life);
    void setPosition(int m_x, int m_y);
    void setX(int m_x);
    void setY(int m_y);
    void walkX(int m_x);
    void walkY(int m_y);
    void setSpeed(int m_speed);
    void setLife(int m_life);
    void findAngle(int mouse_x, int mouse_y);
    void setWalkStep(int m_walkStep);
    void setIsSlash(int m_slash);
    int getX();
    int getY();
    int getSpeed();
    int getLife();
    float getAngle();
    int getWalkStep();
    int getSlashStep();

private:
    int h_x;
    int h_y;
    int h_speed;
    int h_life;
    float h_angle;
    int h_walkStep;//permet de déterminer quel sprite il faut afficher
    int h_isSlash;
};

void deplacementSouris(heros* ninja, int mouseX, int mouseY, int* plan, ennemy* vague, int* score);
void setTexureRectNinja(sf::Sprite* spriteGeneral, int ninjaWalkStep, int slash);

#endif // FUNCTIONPERSO_HPP_INCLUDED
