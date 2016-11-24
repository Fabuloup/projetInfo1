# include "functionInGame.hpp"

char searchMap()
{
    return system("dir /B \"ressources/map/\"");
}
void drawMap(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre)
{
    int x=0;
    int y=0;
    for(y=0; y<hauteur; y++)
    {
        for(x=0; x<largeur; x++)
        {
            switch(plan[y*largeur+x])
            {
            case 1:
                tileset.setTextureRect(sf::IntRect(0,0,10,10));
                break;
            case 2:
                tileset.setTextureRect(sf::IntRect(10, 0, 20, 10));
                break;
            case 3:
                tileset.setTextureRect(sf::IntRect(20, 0, 30, 10));
                break;
            case 4:
                tileset.setTextureRect(sf::IntRect(0, 10, 10, 20));
                break;
            case 5:
                tileset.setTextureRect(sf::IntRect(10, 10, 20, 20));
                break;
            case 6:
                tileset.setTextureRect(sf::IntRect(20, 10, 30, 20));
                break;
            case 7:
                tileset.setTextureRect(sf::IntRect(0, 20, 10, 30));
                break;
            case 8:
                tileset.setTextureRect(sf::IntRect(10, 20, 20, 30));
                break;
            case 9:
                tileset.setTextureRect(sf::IntRect(20, 20, 30, 30));
                break;
            default:
                tileset.setTextureRect(sf::IntRect(10, 10, 20, 20));
                break;
            }
            tileset.setPosition(sf::Vector2f(x*10, y*10));
            fenetre->draw(tileset);
        }
    }
}
