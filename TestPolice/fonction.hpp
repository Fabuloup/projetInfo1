#ifndef FONCTION_HPP_INCLUDED
#define FONCTION_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <SFML/Graphics.hpp>

#define LARGEUR 800
#define HAUTEUR 600
//dimension d'une tuile
#define DIMENSION 10
//dimension d'un lettre
#define DIMENSIONLETTRE 20

using namespace std;

void MachineAEcrire(sf::Sprite fontTile, sf::RenderWindow *fenetre, char* texte, int posX=0, int posY=0, float taille=1.0);

#endif // FONCTION_HPP_INCLUDED
