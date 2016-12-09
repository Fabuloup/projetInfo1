#include "fonction.hpp"

int findLetter(char lettre)
{
    int numLettre=29;

    switch(lettre)
    {
    case 'a':
        numLettre=0;
        break;
    case 'b':
        numLettre=1;
        break;
    case 'c':
        numLettre=2;
        break;
    case 'd':
        numLettre=3;
        break;
    case 'e':
        numLettre=4;
        break;
    case 'f':
        numLettre=5;
        break;
    case 'g':
        numLettre=6;
        break;
    case 'h':
        numLettre=7;
        break;
    case 'i':
        numLettre=8;
        break;
    case 'j':
        numLettre=9;
        break;
    case 'k':
        numLettre=10;
        break;
    case 'l':
        numLettre=11;
        break;
    case 'm':
        numLettre=12;
        break;
    case 'n':
        numLettre=13;
        break;
    case 'o':
        numLettre=14;
        break;
    case 'p':
        numLettre=15;
        break;
    case 'q':
        numLettre=16;
        break;
    case 'r':
        numLettre=17;
        break;
    case 's':
        numLettre=18;
        break;
    case 't':
        numLettre=19;
        break;
    case 'u':
        numLettre=20;
        break;
    case 'v':
        numLettre=21;
        break;
    case 'w':
        numLettre=22;
        break;
    case 'x':
        numLettre=23;
        break;
    case 'y':
        numLettre=24;
        break;
    case 'z':
        numLettre=25;
        break;
    case '.':
        numLettre=26;
        break;
    default:
        break;
    }

    return numLettre;
}

void MachineAEcrire(sf::Sprite fontTile, sf::RenderWindow *fenetre, char* texte, int posX, int posY, float taille)
{
    int i=0;
    int lettre=0;
    for(i=0; i<strlen(texte); i++)
    {
        texte[i]=tolower(texte[i]);
        //passe en majuscule le lettre avant de trouver quel lettre c'est
        lettre=findLetter(texte[i]);
        fontTile.setTextureRect(sf::IntRect((lettre%10)*DIMENSIONLETTRE, (lettre/10)*DIMENSIONLETTRE, DIMENSIONLETTRE, DIMENSIONLETTRE));
        /*switch(couleur)
        {
        case 0:
            fontTile.setColor(sf::Color(0, 0, 0));
            break;
        case 1:
            fontTile.setColor(sf::Color(0, 10, 255));
            break;
        default:
            fontTile.setColor(sf::Color(0, 10, 255));
            break;
        }*/
        //permet de redimensionner les lettres
        fontTile.setScale(taille, taille);
        fontTile.setPosition(posX+i*(DIMENSIONLETTRE*taille), posY);
        fenetre->draw(fontTile);
    }
}
