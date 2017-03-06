#ifndef FUNCTIONEDITOR_HPP_INCLUDED
#define FUNCTIONEDITOR_HPP_INCLUDED

//bibliotheques utiles
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "functionPerso.hpp"
#include "funcWaves.hpp"
#include "boss.hpp"

#define ZOOM 0.3
#define LARGEUR 800
#define HAUTEUR 600
//dimension d'une tuile
#define DIMENSION 10
//dimension d'un lettre
#define DIMENSIONLETTRE 20

using namespace std; //ouverture des fichiers
//fonction
int createOrNew(sf::RenderWindow *fenetre, sf::Sprite tileset, sf::Sprite textTile);
void loadMap(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre, char *nomMap, int *carte);
void editor(int *plan, sf::Sprite tileset, sf::RenderWindow *fenetre, char *mapName="mapEdit.map");
bool isClickOn(int xToTest, int yToTest, int x, int y, int width, int height);
void drawMap(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre, int decalageX=0, int decalageY=0);
void changeMapValue(int *plan, int largeurMap, int hauteurMap, int x, int y, int tileSelected, int decalageX=0, int decalageY=0);
void funcEditor(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre);
void MachineAEcrire(sf::Sprite fontTile, sf::RenderWindow *fenetre, char* texte, int posX=0, int posY=0, float taille=1.0);
void scanGraphique(char *texte,sf::Sprite tileText, sf::RenderWindow *fenetre, int posX=0, int posY=0, float taille=1.0f);
void Jouer(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre, char *nomMap, int *carte);
void InGame(sf::RenderWindow *fenetre, int *planMap, sf::Sprite spriteTexture, sf::Sprite spriteTexte, sf::Sprite spriteCurseur);
void drawMapGame(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre, int decalageX, int decalageY);

#endif // FUNCTIONEDITOR_HPP_INCLUDED
