#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <math.h>

int main()
{
    int x=0, y=0, rayon=200, originx=385, originy=275;
    float angle=0;
    sf::RenderWindow fenetre(sf::VideoMode(800,600),"Boss");
    sf::Sprite spriteBoss;
    sf::Texture textureBoss;
    if (!textureBoss.loadFromFile("boss.png"))
        printf("Erreur !");
    spriteBoss.setTexture(textureBoss);
    spriteBoss.setPosition(385,275);
    fenetre.clear(sf::Color::White);
    fenetre.draw(spriteBoss);
    fenetre.display();
    while(1)
    {
        if (angle>6.3)
            angle=0.01;
        angle=angle+0.01;
        x=originx+cos(angle)*rayon;
        y=originy+sin(angle)*rayon;
        spriteBoss.setPosition(x,y);
        fenetre.clear(sf::Color::White);
        fenetre.draw(spriteBoss);
        fenetre.display();
        sf::sleep(sf::milliseconds(15));
    }
}
