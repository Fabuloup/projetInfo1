#ifndef FUNCTIONINGAME_HPP_INCLUDED
#define FUNCTIONINGAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
//pour lire les fichiers
#include <iostream>
#include <string>
#include <fstream>
//pour lire les fichiers
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void drawMap(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre);
string searchMap();

#endif // FUNCTIONINGAME_HPP_INCLUDED
