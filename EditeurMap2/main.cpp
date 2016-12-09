#include "functionEditor.hpp"

int main()
{

    sf::RenderWindow fenetre(sf::VideoMode(LARGEUR,HAUTEUR),"Editeur de map - Neo Dojo");
    fenetre.setFramerateLimit(60);
    sf::Texture murTexture;
    if( !murTexture.loadFromFile("ressources/texture.png"))
    {
        printf("Impossible de charger le tileset de la map");
    }
    sf::Sprite spritemur;
    spritemur.setTexture(murTexture);

    sf::Texture textTexture;
    if( !textTexture.loadFromFile("ressources/alphabetred.png"))
    {
        printf("Impossible de charger le tileset du texte");
    }
    sf::Sprite spriteTexte;
    spriteTexte.setTexture(textTexture);

    sf::View vue(sf::FloatRect(0, 0, LARGEUR, HAUTEUR));
    vue.zoom(ZOOM);
    vue.setCenter((int)(LARGEUR*ZOOM)/2, (int)(HAUTEUR*ZOOM)/2);
    fenetre.setView(vue);

    while(fenetre.isOpen())
    {
        funcEditor(spritemur, spriteTexte, &fenetre);
    }
    return 0;
}
