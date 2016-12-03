#ifndef FUNCTIONEDITOR_HPP_INCLUDED
#define FUNCTIONEDITOR_HPP_INCLUDED

//bibliotheques utiles
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#define ZOOM 0.3
#define LARGEUR 800
#define HAUTEUR 600
//dimension d'une tuile
#define DIMENSION 10

using namespace std; //ouverture des fichiers
//fonction
int createOrNew();
void editor(int *plan, sf::Sprite tileset, sf::RenderWindow *fenetre, char *mapName="mapEdit.map");
bool isClickOn(int xToTest, int yToTest, int x, int y, int width, int height);
void drawMap(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre, int decalageX=0, int decalageY=0);
void changeMapValue(int *plan, int largeurMap, int hauteurMap, int x, int y, int tileSelected, int decalageX=0, int decalageY=0);

#endif // FUNCTIONEDITOR_HPP_INCLUDED
