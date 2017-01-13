#include <stdio.h>
#include <stdlib.h>
#include "funcWaves.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow fenetre(sf::VideoMode(800,600), "La soeur de Jean");

    //Chargement texture+création tableau ennemis
    ennemy vague[20];
    int max=10, i,j, slime_etat=0, nb_nonActif, k;
    sf::Event event;
    sf::Sprite spriteSlime;
    sf::Texture textureSlime, textureSlime2;
    if (!textureSlime.loadFromFile("slime.png"))
        printf("Problème\n");
    if (!textureSlime2.loadFromFile("slime2.png"))
        printf("Problème\n");
    spriteSlime.setTexture(textureSlime);
    int posxrekt=400, posyrekt=300, pas=10;

    //Créations des 10 premiers ennemis
    for (i=0; i<max; i++)
    {
        vague[i].setPosition(40*i, 40*i);
        vague[i].setActif(1);
    }
    while (fenetre.isOpen())
    {
        //test de l'état des slimes pour la texture
        if (slime_etat==0)
            spriteSlime.setTexture(textureSlime);
        else if (slime_etat==1)
            spriteSlime.setTexture(textureSlime2);

        //Clear la fenetre et met le nombre de slims actifs à 0
        fenetre.clear(sf::Color::Black);
        nb_nonActif=0;
        for (i=0; i<max; i++)
        {
            vague[i].changePas(10);
            pas=10;
            for (k=0; k<pas; k++)
            {
                for (j=0; j<max; j++)
                {
                    //Collision entre i et j
                    if ((Collision(vague[i].get_x(), vague[i].get_y(), vague[j].get_x(), vague[j].get_y(), 20, 20, 20,20))==true && i!=j)
                        pas=0;
                }
                if (posxrekt-vague[i].get_x()>0 && pas!=0)
                {
                    vague[i].setPosition(vague[i].get_x()+1, vague[i].get_y());
                }
                else if (posxrekt-vague[i].get_x()<0 && pas!=0)
                {
                    vague[i].setPosition(vague[i].get_x()-1, vague[i].get_y());
                }
                if (posyrekt-vague[i].get_y()>0 && pas!=0)
                {
                    vague[i].setPosition(vague[i].get_x(), vague[i].get_y()+1);
                }
                else if (posyrekt-vague[i].get_y()<0  && pas!=0)
                {
                    vague[i].setPosition(vague[i].get_x(), vague[i].get_y()-1);
                }
                spriteSlime.setPosition(vague[i].get_x(), vague[i].get_y());

            }

            fenetre.draw(spriteSlime);
        }
        if (slime_etat==1)
            slime_etat=0;
        else if (slime_etat==0)
            slime_etat=1;
        fenetre.display();
        sf::sleep(sf::milliseconds(100));
    }
    return 0;
}
