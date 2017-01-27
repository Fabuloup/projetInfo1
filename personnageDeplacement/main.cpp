#include "functionPerso.hpp"
#include "functionEditor.hpp"

int main()
{
    sf::RenderWindow fenetre(sf::VideoMode(800,600),"Personnage");
    fenetre.setFramerateLimit(60);

    sf::Event event;
    sf::Vector2i mousePos;

    sf::Texture textureBase;
    if (!textureBase.loadFromFile("ressources/texture.png"))
    {
        printf("impossible de charger la texture\n");
    }
    sf::Texture textureTexte;
    if (!textureTexte.loadFromFile("ressources/alphabetred.png"))
    {
        printf("impossible de charger la texture\n");
    }
    sf::Sprite spriteTexture;
    spriteTexture.setTexture(textureBase);
    spriteTexture.scale(sf::Vector2f(2.0f, 2.0f));
    sf::Sprite spriteTexte;
    spriteTexte.setTexture(textureTexte);
    //int deplacementX;
    //int deplacementY;

    heros ninja(160, 160, 3, 100);
    int planMap[100];
    char nomMap[100]="";

    loadMap(spriteTexture, spriteTexte, &fenetre, nomMap, planMap);

    while(fenetre.isOpen())
    {
        while(fenetre.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                fenetre.close();
                break;
            case sf::Event::MouseMoved:
                mousePos = sf::Mouse::getPosition(fenetre);
                break;
            case sf::Event::MouseButtonPressed:
                ninja.setIsSlash(400);
                break;
            default:
                break;
            }
        }
        deplacementSouris(&ninja, mousePos.x, mousePos.y, planMap);
        setTexureRectNinja(&spriteTexture, ninja.getWalkStep(), ninja.getSlashStep());
        spriteTexture.setPosition(ninja.getX()-20,ninja.getY()-20);

        fenetre.clear();
        drawMap(planMap, 10, 10, spriteTexture,  &fenetre, 0, 0);
        fenetre.draw(spriteTexture);
        fenetre.display();
    }

    return 0;
}
