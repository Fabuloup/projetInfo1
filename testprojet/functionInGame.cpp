# include "functionInGame.hpp"

string searchMap()
{
    //on ouvre le fichier qui contient le nom des maps
    ifstream listemap("ressources/map/listemap.txt");
    string carte;
    if(listemap)//si on arrive à l'ouvrir
    {
        getline(listemap, carte);//on stock les lignes du fichier listemap dans carte
        listemap.close();//on ferme le fichier
    }
    else
    {
        //si l'ouverture à échouée on affiche l'erreur
        printf("\nImpossible d'ouvrir la liste des maps !\n");
    }
    return carte;
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
                tileset.setTextureRect(sf::IntRect(30,0,10,10));
                break;
            case 2:
                tileset.setTextureRect(sf::IntRect(40, 0, 10, 10));
                break;
            case 3:
                tileset.setTextureRect(sf::IntRect(50, 0, 10, 10));
                break;
            case 4:
                tileset.setTextureRect(sf::IntRect(30, 10, 10, 10));
                break;
            case 5:
                tileset.setTextureRect(sf::IntRect(40, 10, 10, 10));
                break;
            case 6:
                tileset.setTextureRect(sf::IntRect(50, 10, 10, 10));
                break;
            case 7:
                tileset.setTextureRect(sf::IntRect(30, 20, 10, 10));
                break;
            case 8:
                tileset.setTextureRect(sf::IntRect(40, 20, 10, 10));
                break;
            case 9:
                tileset.setTextureRect(sf::IntRect(50, 20, 10, 10));
                break;
            default:
                tileset.setTextureRect(sf::IntRect(40, 10, 10, 10));
                break;
            }
            tileset.setPosition(sf::Vector2f(x*10, y*10));
            fenetre->draw(tileset);
        }
    }
}
