#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <time.h>
#include <iostream>
#include "boss.hpp"
#include "fireball.hpp"


int main()
{
    srand(time(NULL));
    int x=0, y=0, rayon=100, originx=385, originy=275, vener=0, skin=0, etat=0, nbboule=-1,i, j;
    float angle=0, attaque, feu, fireball, dirx, diry;
    sf::RenderWindow fenetre(sf::VideoMode(800,600),"Boss");
    sf::Sprite spriteBoss, spriteFireball;
    sf::Time temps, tempstp;
    tempstp=sf::seconds(7.0);
    temps=sf::seconds(4.0);
    sf::Clock clock, clocktp;
    sf::Texture textureBoss, textureBoss2, textureFireball;
    if (!textureBoss.loadFromFile("skullHeadbang.png"))
        printf("Erreur !");
    if (!textureBoss2.loadFromFile("skullHeadbang2.png"))
        printf("Erreur !");
    if(!textureFireball.loadFromFile("fireball.png"))
        printf("Erreur !");

    Boss Michel;
    Fireball skill[20];

    spriteBoss.setTexture(textureBoss);
    spriteFireball.setTexture(textureFireball);
    spriteBoss.setTextureRect(sf::IntRect(0,0,30,30));
    spriteBoss.setPosition(Michel.get_posx(),Michel.get_posy());
    spriteBoss.setScale(sf::Vector2f(2.0f,2.0f));
    fenetre.clear(sf::Color::Black);
    fenetre.draw(spriteBoss);
    fenetre.display();
    srand(time(NULL));
    while(1)
    {
        if (etat==0)
        {
            spriteBoss.setTextureRect(sf::IntRect(0,0,30,30));
        }
        else if (etat==1)
        {
            spriteBoss.setTextureRect(sf::IntRect(30,0,30,30));
        }
        else if (etat==2)
        {
            spriteBoss.setTextureRect(sf::IntRect(60,0,30,30));
        }
        attaque=(float)rand()/(float)(RAND_MAX);
        feu=(float)rand()/(float)(RAND_MAX);
        fireball=(float)rand()/(float)(RAND_MAX);
        printf("%f\n%f",attaque,feu);
        if (angle>6.3)
            angle=0.03;
        if (fireball<=0.05 && nbboule<20)
        {
            nbboule++;
            skill[nbboule].set_posx(Michel.get_posx());
            skill[nbboule].set_posy(Michel.get_posy());
            spriteFireball.setPosition(skill[nbboule].get_posx(),skill[nbboule].get_posy());
            dirx=rand()%800;
            diry=rand()%600;
            skill[nbboule].set_directionx(skill[nbboule].calculeDirectionx(dirx, diry));
            skill[nbboule].set_directiony(skill[nbboule].calculeDirectiony(dirx,diry));
        }
        /*if (nbboule!=-1)
        {
            for (i=0; i<nbboule; i++)
            {
                skill[i].set_posx(skill[i].get_posx()+skill[i].get_directionx()*5);
                skill[i].set_posy(skill[i].get_posy()+skill[i].get_directiony()*5);
            }
        }*/
        if (attaque>=0.99 && clocktp.getElapsedTime()>tempstp)
        {
            angle=angle+3;
            clocktp.restart();
        }
        if (feu>=0.55 && feu<=0.56 && clock.getElapsedTime()>temps)
        {
            spriteBoss.setTexture(textureBoss2);
            Michel.setInvincible(true);
            clock.restart();
        }
        if (clock.getElapsedTime()>temps)
        {
            spriteBoss.setTexture(textureBoss);
            Michel.setInvincible(false);
        }

        angle=angle+0.03;
        Michel.set_posx(originx+cos(angle)*rayon);
        Michel.set_posy(originy+sin(angle)*rayon);
        spriteBoss.setPosition(Michel.get_posx(),Michel.get_posy());
        fenetre.clear(sf::Color::Black);
        fenetre.draw(spriteBoss);
        if (nbboule!=-1)
        {
            for (i=0; i<nbboule; i++)
            {
                skill[i].set_posx(skill[i].get_posx()+skill[i].get_directionx()*5);
                skill[i].set_posy(skill[i].get_posy()+skill[i].get_directiony()*5);
                spriteFireball.setPosition(skill[i].get_posx(), skill[i].get_posy());
                if ((skill[i].get_posx()>800 || skill[i].get_posy()>600) || (skill[i].get_posx()<0 || skill[i].get_posy()<0))
                {
                    skill[i].~Fireball();
                    nbboule--;
                    for (j=i; j<nbboule+1; j++)
                    {
                        skill[j]=skill[j+1];
                    }
                }
                fenetre.draw(spriteFireball);
            }
        }
        fenetre.display();
        sf::sleep(sf::milliseconds(15));
        if (etat==0 && skin==5)
        {
            etat=1;
            skin=0;
        }
        else if (etat==1 && skin==5)
        {
            etat=2;
            skin=0;
        }
        else if (etat==2 && skin==5)
        {
            etat=0;
            skin=0;
        }
        skin++;
    }
}
