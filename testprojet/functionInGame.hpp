#ifndef FUNCTIONINGAME_HPP_INCLUDED
#define FUNCTIONINGAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void drawMap(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre);
char searchMap();

#endif // FUNCTIONINGAME_HPP_INCLUDED
