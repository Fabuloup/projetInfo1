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
    int posxrekt=400, posyrekt=300, pas=10, pasrekt=10;
    int pas_droite, pas_gauche, pas_haut, pas_bas;
    sf::RectangleShape rekt(sf::Vector2f(10,10));
    rekt.setFillColor(sf::Color::Red);
    rekt.setPosition(posxrekt, posyrekt);
    fenetre.draw(rekt);
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

        //carré rouge --> joueur
        if (fenetre.pollEvent(event))
        {
            //test des touches pour déplacer player
            if (event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
                posyrekt=posyrekt-pasrekt;
            if (event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
                posyrekt=posyrekt+pasrekt;
            if (event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
                posxrekt=posxrekt-pasrekt;
            if (event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
                posxrekt=posxrekt+pasrekt;
        }
        rekt.setPosition(posxrekt, posyrekt);
        //Slimes 1 par 1
        for (i=0; i<max; i++)
        {
            pas_haut=1;
            pas_bas=1;
            pas_gauche=1;
            pas_droite=1;
            for (k=0; k<pas; k++)
                //Faire avancer de 10
            {
                for (j=0; j<max; j++)
                    //Collisions slime 1 par 1
                {
                    //Collision entre i et j
                    //if ((Collision(vague[i].get_x(), vague[i].get_y(), vague[j].get_x(), vague[j].get_y(), 20, 20, 20,20))==true && i!=j)
                    //vague[i].changePas(0);
                    //Colision haut, bas, droite, gauche
                    //Pas haut, bas, droite, gauche
                    if (collision_droite(vague[i].get_x(), vague[i].get_y(), vague[j].get_x(), vague[j].get_y(), 20, 20, 20,20)==true && i!=j)
                    {
                        pas_droite=0;
                    }
                    if (collision_gauche(vague[i].get_x(), vague[i].get_y(), vague[j].get_x(), vague[j].get_y(), 20, 20, 20,20)==true && i!=j)
                    {
                        pas_gauche=0;
                    }
                    if (collision_haut(vague[i].get_x(), vague[i].get_y(), vague[j].get_x(), vague[j].get_y(), 20, 20, 20,20)==true && i!=j)
                    {
                        pas_haut=0;
                    }
                    if (collision_bas(vague[i].get_x(), vague[i].get_y(), vague[j].get_x(), vague[j].get_y(), 20, 20, 20,20)==true && i!=j)
                    {
                        pas_bas=0;
                    }
                }
                if (posxrekt-vague[i].get_x()>0 && pas_droite!=0)
                {
                    vague[i].setPosition(vague[i].get_x()+1, vague[i].get_y());
                }
                else if (posxrekt-vague[i].get_x()<0 && pas_gauche!=0)
                {
                    vague[i].setPosition(vague[i].get_x()-1, vague[i].get_y());
                }
                if (posyrekt-vague[i].get_y()>0 && pas_bas!=0)
                {
                    vague[i].setPosition(vague[i].get_x(), vague[i].get_y()+1);
                }
                else if (posyrekt-vague[i].get_y()<0  && pas_haut!=0)
                {
                    vague[i].setPosition(vague[i].get_x(), vague[i].get_y()-1);
                }
                spriteSlime.setPosition(vague[i].get_x(), vague[i].get_y());

            }

            fenetre.draw(spriteSlime);
            fenetre.draw(rekt);
        }
        if (slime_etat==1)
            slime_etat=0;
        else if (slime_etat==0)
            slime_etat=1;
        fenetre.display();
        sf::sleep(sf::milliseconds(150));
    }
    return 0;
}
