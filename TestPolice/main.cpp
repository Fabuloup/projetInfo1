#include "fonction.hpp"

int main()
{
    sf::RenderWindow fenetre(sf::VideoMode(LARGEUR,HAUTEUR),"Test Ecriture");
    fenetre.setFramerateLimit(60);
    sf::Texture fontTexture;
    if( !fontTexture.loadFromFile("ressources/alphabetred.png"))
    {
        printf("Impossible de charger le tileset de la police");
    }
    sf::Sprite spriteLettre;
    spriteLettre.setTexture(fontTexture);
    char texteTest[]="Hello World";

    sf::Event event;

    while(fenetre.isOpen())
    {
        fenetre.clear();
        MachineAEcrire(spriteLettre, &fenetre, texteTest, 100,10, 2.0f);
        while(fenetre.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                fenetre.close();
                break;
            case sf::Event::KeyPressed:
                break;
            default:
                break;
            }
        }
        fenetre.display();
    }

    return 0;
}
