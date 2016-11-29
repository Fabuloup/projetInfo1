#include "functionInGame.hpp"


int main()
{
    sf::RenderWindow fenetre(sf::VideoMode(800,600),"Neo Dojo");

    sf::Texture murTexture;
    if( !murTexture.loadFromFile("ressources/murdojo.png"))
    {
        printf("Impossible de charger le tileset de la map");
    }
    string listemap=searchMap();
    cout << listemap;//equivalent à print mais pour les string
    //printf("%s\n", listemap);
    sf::Sprite spritemur;
    spritemur.setTexture(murTexture);
    sf::View vue(sf::FloatRect(0, 0, 800, 600));
    vue.zoom(0.2f);
    vue.setCenter(50,35);
    fenetre.setView(vue);

    int arene[70]={1, 2, 2, 0, 0, 0, 0, 2, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 8, 8, 0, 0, 0, 0, 8, 8, 9};
    int largeur=10;
    int hauteur=7;

    sf::Event evenement;
    while(fenetre.isOpen())
    {
        fenetre.clear();
        while(fenetre.pollEvent(evenement))
        {
            if(evenement.type == sf::Event::Closed)
            {
                fenetre.close();
            }
        }
        fenetre.setActive(false);
        drawMap(arene, largeur, hauteur, spritemur, &fenetre);
        fenetre.setActive(true);
        fenetre.display();
    }
    return 0;
}
