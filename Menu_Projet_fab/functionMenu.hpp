#ifndef FUNCTIONMENU_HPP_INCLUDED
#define FUNCTIONMENU_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>

void DessineMenu(sf::RenderWindow *fenetre,sf::Sprite spriteChoix, sf::Sprite spriteFond, sf::Sprite spriteMenu, sf::Sprite spriteCurseur, sf::Sound sonDeplacement);
void DessineOption(sf::RenderWindow *fenetre, sf::Sprite spriteCurseur, sf::Sprite spriteFond);

#endif // FUNCTIONMENU_HPP_INCLUDED
