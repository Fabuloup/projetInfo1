#include <stdio.h>
#include <stdlib.h>
#include "funcIA.hpp"
#include <SFML/Graphics.hpp>

bool Collision(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p/*, int largeur_ia, int hauteur_ia*/);
bool Collision2(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);

bool Collision(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p/*, int largeur_ia, int hauteur_ia*/)
{
    if (pos_x_ia >= pos_x_p && pos_x_ia < pos_x_p+largeur_p
            && pos_y_ia >= pos_y_p && pos_y_ia < pos_y_p+hauteur_p)
        return true;
    else
        return false;
//   if (curseur_x >= box.x
//    && curseur_x < box.x + box.w
//    && curseur_y >= box.y
//    && curseur_y < box.y + box.h)
//       return true;
//   else
//       return false;
}

bool Collision2(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    if((pos_x_ia >= pos_x_p + largeur_p)      // trop à droite
            || (pos_x_ia + largeur_ia <= pos_x_p) // trop à gauche
            || (pos_y_ia >= pos_y_p + hauteur_p) // trop en bas
            || (pos_y_ia + hauteur_ia <= pos_y_p))  // trop en haut
        return false;
    else
        return true;
}

//bool Collision(AABB box1,AABB box2)
//{
//   if((box2.x >= box1.x + box1.w)      // trop à droite
//	|| (box2.x + box2.w <= box1.x) // trop à gauche
//	|| (box2.y >= box1.y + box1.h) // trop en bas
//	|| (box2.y + box2.h <= box1.y))  // trop en haut
//          return false;
//   else
//          return true;
//}



int main()
{
    //rekt est celui que l'on dirige, juif et negro sont ceux qui nous suivent
    //On dessine tout
    int posxrekt=400, posyrekt=400, pasjuif=10, pasnegro=10, pasrekt=4, posxjuif=750, posyjuif=550, rekttype=0, colijuif=0, colinegro=0, mortjuif=0, mortnegro=0;
    ennemy Enegro(10, 0, 0);
    sf::RenderWindow fenetre(sf::VideoMode(800,600), "La soeur de Jean");
    sf::RectangleShape rekt(sf::Vector2f(120,50));
    sf::RectangleShape negro(sf::Vector2f(50,50));
    sf::RectangleShape juif(sf::Vector2f(50,50));
    sf::Event event;
    rekt.setPosition(400,400);
    juif.setPosition(posxjuif, posyjuif);
    negro.setFillColor(sf::Color(200,0,0));
    rekt.setFillColor(sf::Color(0,200,0));
    juif.setFillColor(sf::Color(200,0,0));
    fenetre.draw(rekt);
    fenetre.draw(negro);
    fenetre.draw(juif);
    fenetre.display();
    while(1)
    {
        pasnegro=2, pasjuif=2, colijuif=0, colinegro=0;
        //On remet a zero les pas si jamais player bouge
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
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Space)
            {
                if (rekttype==0)
                {
                    rekt.setFillColor(sf::Color(0,0,200));
                    rekttype=1;
                }
                else
                {
                    rekt.setFillColor(sf::Color(0,200,0));
                    rekttype=0;
                }
            }

        }
        //Test des collisions, met un pas de 0 pour les bloquer si il y a collision
        int* posnegro=Enegro.getPosition();
        int posxnegro=posnegro[0];
        int posynegro=posnegro[1];
        if (Collision2(posxrekt, posyrekt, posxjuif, posyjuif, 120, 50, 50, 50)==true)
            pasjuif=0, colijuif=1;
        if (Collision2(posxrekt, posyrekt, posxnegro, posynegro, 120, 50, 50,50)==true)
            pasnegro=0, colinegro=1;
        if (Collision2(posxnegro, posynegro, posxjuif, posyjuif, 50, 50, 50,50)==true)
            pasnegro=0;
        if (rekttype==1 && colijuif==1)
        {
            juif.setFillColor(sf::Color::Black);
            mortjuif=1;
        }
        if (rekttype==1 && colinegro==1)
        {
            negro.setFillColor(sf::Color::Black);
            mortnegro=1;
        }
        //On déplace les rectangles
        if (posxrekt-posxnegro>0 && mortnegro==0)
            posxnegro=posxnegro+pasnegro;
        else if (posxrekt-posxnegro<0 && mortnegro==0)
            posxnegro=posxnegro-pasnegro;
        if (posyrekt-posynegro>0 && mortnegro==0)
            posynegro=posynegro+pasnegro;
        else if (posyrekt-posynegro<0 && mortnegro==0)
            posynegro=posynegro-pasnegro;
        if (posxrekt-posxjuif>0 && mortjuif==0)
            posxjuif=posxjuif+pasjuif;
        else if (posxrekt-posxjuif<0 && mortjuif==0)
            posxjuif=posxjuif-pasjuif;
        if (posyrekt-posyjuif>0 && mortjuif==0)
            posyjuif=posyjuif+pasjuif;
        else if (posyrekt-posyjuif<0 && mortjuif==0)
            posyjuif=posyjuif-pasjuif;
        //On redessine tout
        negro.setPosition(posxnegro,posynegro);
        Enegro.setPosition(posxnegro, posynegro);
        juif.setPosition(posxjuif, posyjuif);
        rekt.setPosition(posxrekt, posyrekt);
        fenetre.clear();
        fenetre.draw(rekt);
        fenetre.draw(negro);
        fenetre.draw(juif);
        fenetre.display();
        sf::sleep(sf::milliseconds(15));
    }
    return 0;
}
