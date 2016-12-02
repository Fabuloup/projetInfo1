#include "functionEditor.hpp"

int main()
{
    int choixEdit =0;
    //choix de l'utilisateur (voir fonction)
    choixEdit = createOrNew();

    sf::RenderWindow fenetre(sf::VideoMode(LARGEUR,HAUTEUR),"Editeur de map - Neo Dojo");
    fenetre.setFramerateLimit(60);
    sf::Texture murTexture;
    if( !murTexture.loadFromFile("ressources/texture.png"))
    {
        printf("Impossible de charger le tileset de la map");
    }
    sf::Sprite spritemur;
    spritemur.setTexture(murTexture);
    sf::View vue(sf::FloatRect(0, 0, LARGEUR, HAUTEUR));
    vue.zoom(ZOOM);
    vue.setCenter((int)(LARGEUR*ZOOM)/2, (int)(HAUTEUR*ZOOM)/2);
    fenetre.setView(vue);

    if(choixEdit==1)
    {
        printf("En cours de développement\n");
    }
    else if (choixEdit==0)
    {
        char NomMap[50]="";
        printf("Entrez le nom de votre map sans oublier le \".map\"\n>>> ");
        scanf("%s", NomMap);
        fenetre.setActive(false);
        int carteDeBase[10*10]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
        editor(carteDeBase, spritemur, &fenetre, NomMap);
        fenetre.setActive(true);
    }
    return 0;
}
