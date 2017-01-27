#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

bool collision_haut (int posx_p, int posy_p, int largeur_p, int hauteur_p, int posx_ia, int posy_ia, int largeur_ia, int hauteur_ia);
bool collision_bas (int posx_p, int posy_p, int largeur_p, int hauteur_p, int posx_ia, int posy_ia, int largeur_ia, int hauteur_ia);
bool collision_droite (int posx_p, int posy_p, int largeur_p, int hauteur_p, int posx_ia, int posy_ia, int largeur_ia, int hauteur_ia);
bool collision_gauche (int posx_p, int posy_p, int largeur_p, int hauteur_p, int posx_ia, int posy_ia, int largeur_ia, int hauteur_ia);

int main()
{
    int posxrekt=400, posyrekt=300, pasrekt=2;
    sf::RenderWindow fenetre(sf::VideoMode(800,600), "La soeur de Jean");
    sf::Event event;
    sf::Sprite sprite_haut, sprite_bas, sprite_droite, sprite_gauche;
    sf::Texture texture;
    if (!texture.loadFromFile("slime.png"))
        printf("Problème\n");
    sprite_haut.setTexture(texture);
    sprite_bas.setTexture(texture);
    sprite_droite.setTexture(texture);
    sprite_gauche.setTexture(texture);
    sf::RectangleShape rekt(sf::Vector2f(20,20));
    rekt.setPosition(posxrekt,posyrekt);
    rekt.setFillColor(sf::Color::Red);
    sprite_haut.setPosition(400,260);
    sprite_bas.setPosition(400,340);
    sprite_droite.setPosition(440,300);
    sprite_gauche.setPosition(360,300);
    fenetre.draw(rekt);
    fenetre.draw(sprite_haut);
    fenetre.draw(sprite_bas);
    fenetre.draw(sprite_droite);
    fenetre.draw(sprite_gauche);
    fenetre.display();
    while (fenetre.isOpen())
    {
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
        if (collision_haut(posxrekt, posyrekt, 20, 20, 400, 260, 20, 20)==true)
            posyrekt=posyrekt+2;
        else if (collision_bas(posxrekt, posyrekt, 20, 20, 400, 340, 20, 20)==true)
            posyrekt=posyrekt-2;
        else if (collision_droite(posxrekt, posyrekt, 20, 20, 440, 300, 20, 20)==true)
            posxrekt=posxrekt-2;
        else if (collision_gauche(posxrekt, posyrekt, 20, 20, 360, 300, 20, 20)==true)
            posxrekt=posxrekt+2;
        fenetre.clear(sf::Color::Black);
        rekt.setPosition(posxrekt,posyrekt);
        fenetre.draw(rekt);
        fenetre.draw(sprite_haut);
        fenetre.draw(sprite_bas);
        fenetre.draw(sprite_droite);
        fenetre.draw(sprite_gauche);
        fenetre.display();
    }


}

bool collision_haut (int posx_p, int posy_p, int largeur_p, int hauteur_p, int posx_ia, int posy_ia, int largeur_ia, int hauteur_ia)
{
    //Test si p est bloqué vers le haut par ia
    if (posy_p<=posy_ia+hauteur_ia && posx_p+largeur_p>=posx_ia && posx_p<=posx_ia+largeur_ia && posy_p>=posy_ia+hauteur_ia-2)
        return true;
    else
        return false;
}

bool collision_bas (int posx_p, int posy_p, int largeur_p, int hauteur_p, int posx_ia, int posy_ia, int largeur_ia, int hauteur_ia)
{
    //Test si p est bloqué vers le bas par ia
    if (posy_p+hauteur_p>=posy_ia && posx_p+largeur_p>=posx_ia && posx_p<=posx_ia+largeur_ia && posy_p+hauteur_p<=posy_ia+2)
        return true;
    else
        return false;
}
bool collision_droite (int posx_p, int posy_p, int largeur_p, int hauteur_p, int posx_ia, int posy_ia, int largeur_ia, int hauteur_ia)
{
    //Test si p est bloqué à droite par ia
    if (posx_p+largeur_p>=posx_ia && posy_p+hauteur_p>=posy_ia && posx_p+largeur_p<=posx_ia+2 && posy_p<=posy_ia+hauteur_ia)
        return true;
    else
        return false;
}
bool collision_gauche (int posx_p, int posy_p, int largeur_p, int hauteur_p, int posx_ia, int posy_ia, int largeur_ia, int hauteur_ia)
{
    //Test si p est bloqué à gauche par ia
    if (posx_p<=posx_ia+largeur_ia && posx_p>=posx_ia+largeur_ia-2 && posy_p+hauteur_p>=posy_ia && posy_p<=posy_ia+hauteur_ia)
        return true;
    else
        return false;
}



