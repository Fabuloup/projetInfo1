#ifndef FUNCTIONMENU_HPP_INCLUDED
#define FUNCTIONMENU_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "functionEditor.hpp"

void DessineMenu(sf::RenderWindow *fenetre,sf::Sprite spriteChoix, sf::Sprite spriteFond, sf::Sprite spriteMenu, sf::Sprite spriteCurseur, sf::Sound sonDeplacement);
void DessineOption(sf::RenderWindow *fenetre, sf::Sprite spriteCurseur, sf::Sprite spriteFond);
void OptionsMenu(sf::RenderWindow *fenetre, sf::Sprite spriteFond, sf::Sprite spriteCurseur, int x_curseur, int y_curseur, sf::Sprite spriteTexte, char titreOpt[], int x_titre, int y_titre, float taille_titre, char vsyncOpt[], int x_vsync, int y_vsinc, float taille_vsync, char sonOpt[], int x_son, int y_son, float taille_son, char quitterOpt[], int x_quit, int y_quit, float taille_quit, char vsync_choixOpt[], int x_vsyncChoix, int y_vsyncChoix, float taille_vsyncChoix, char son_choixOpt[], int x_sonChoix, int y_sonChoix, float taille_sonChoix, char scoresOpt[], int x_scores, int y_scores, float taille_scores);
#endif // FUNCTIONMENU_HPP_INCLUDED
