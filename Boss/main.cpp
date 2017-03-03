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
    int rayon=100, originx=385, originy=275, skin=0, etat=0, nbboule=-1,i, j;
    float angle=0, attaqueTeleportation, attaqueInvincible, attaqueFireball, dirx, diry;
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

    Boss skullBoss;
    Fireball tabFireball[20];

    spriteBoss.setTexture(textureBoss);
    spriteFireball.setTexture(textureFireball);
    spriteBoss.setTextureRect(sf::IntRect(0,0,30,30));
    spriteBoss.setPosition(skullBoss.get_posx(),skullBoss.get_posy());
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
        /*attaqueTeleportation=(float)rand()/(float)(RAND_MAX);
        attaqueInvincible=(float)rand()/(float)(RAND_MAX);
        attaqueFireball=(float)rand()/(float)(RAND_MAX);
        if (angle>6.3)
            angle=0.03;
        if (attaqueFireball<=0.05 && nbboule<20)
        {
            nbboule++;
            tabFireball[nbboule].set_posx(skullBoss.get_posx());
            tabFireball[nbboule].set_posy(skullBoss.get_posy());
            spriteFireball.setPosition(tabFireball[nbboule].get_posx(),tabFireball[nbboule].get_posy());
            dirx=rand()%800;
            diry=rand()%600;
            tabFireball[nbboule].set_directionx(tabFireball[nbboule].calculeDirectionx(dirx, diry));
            tabFireball[nbboule].set_directiony(tabFireball[nbboule].calculeDirectiony(dirx,diry));
        }
        if (attaqueTeleportation>=0.99 && clocktp.getElapsedTime()>tempstp)
        {
            angle=angle+3;
            clocktp.restart();
        }
        if (attaqueInvincible>=0.55 && attaqueInvincible<=0.56 && clock.getElapsedTime()>temps)
        {
            spriteBoss.setTexture(textureBoss2);
            skullBoss.setInvincible(true);
            clock.restart();
        }
        if (clock.getElapsedTime()>temps)
        {
            spriteBoss.setTexture(textureBoss);
            skullBoss.setInvincible(false);
        }

        angle=angle+0.03;
        skullBoss.set_posx(originx+cos(angle)*rayon);
        skullBoss.set_posy(originy+sin(angle)*rayon);*/
        vagueBoss(&skullBoss, &angle, &nbboule, tabFireball, &clocktp, tempstp, &clock, temps,  originx,  originy,  rayon);
        spriteFireball.setPosition(tabFireball[nbboule].get_posx(),tabFireball[nbboule].get_posy());
        if (skullBoss.estInvincible()==true)
            spriteBoss.setTexture(textureBoss2);
        else
            spriteBoss.setTexture(textureBoss);
        spriteBoss.setPosition(skullBoss.get_posx(),skullBoss.get_posy());
        fenetre.clear(sf::Color::Black);
        fenetre.draw(spriteBoss);
        if (nbboule!=-1)
        {
            for (i=0; i<nbboule; i++)
            {
                tabFireball[i].set_posx(tabFireball[i].get_posx()+tabFireball[i].get_directionx()*5);
                tabFireball[i].set_posy(tabFireball[i].get_posy()+tabFireball[i].get_directiony()*5);
                spriteFireball.setPosition(tabFireball[i].get_posx(), tabFireball[i].get_posy());
                if ((tabFireball[i].get_posx()>800 || tabFireball[i].get_posy()>600) || (tabFireball[i].get_posx()<0 || tabFireball[i].get_posy()<0))
                {
                    tabFireball[i].~Fireball();
                    nbboule--;
                    for (j=i; j<nbboule+1; j++)
                    {
                        tabFireball[j]=tabFireball[j+1];
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
