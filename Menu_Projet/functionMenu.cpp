#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "functionMenu.hpp"

//void drawMenu(sf::Sprite sprite, sf::RenderWindow *fenetre, )

void DessineMenu(sf::RenderWindow *fenetre, sf::Sprite spriteChoix, sf::Sprite spriteFond, sf::Sprite spriteMenu, sf::Sprite spriteCurseur, sf::Sound sonDeplacement)
{
    fenetre->clear(sf::Color::Black);
    fenetre->draw(spriteFond);
    fenetre->draw(spriteMenu);
    fenetre->draw(spriteChoix);
    fenetre->draw(spriteCurseur);
    fenetre->display();
    //Son deplacement
    sonDeplacement.play();
}

void DessineOption(sf::RenderWindow *fenetre, sf::Sprite spriteCurseur, sf::Sprite spriteFond)
{
    fenetre->clear(sf::Color::Black);
    fenetre->draw(spriteFond);
    fenetre->draw(spriteCurseur);
}
