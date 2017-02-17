#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <math.h>

int main()
{
    int coeff=0;
    float directionx=0, directiony=0, posx=400, posy=300;
    double angle;
    sf::RenderWindow fenetre(sf::VideoMode(800,600), "Distant");
    sf::RectangleShape ennemi(sf::Vector2f(20,20));
    sf::RectangleShape projectile(sf::Vector2f(10,10));
    ennemi.setPosition(posx,posy);
    fenetre.draw(ennemi);
    fenetre.display();
    sf::Event event;
    while(fenetre.isOpen())
    {
        while(fenetre.pollEvent(event))
        {
            if (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                projectile.setPosition(posx,posy);
                /*distance=abs((event.mouseButton.y-550));
                a=sin(distance)*/
                angle=atan2((sf::Mouse::getPosition(fenetre).y-posy),(sf::Mouse::getPosition(fenetre).x-posx));
                printf("x :%i\n", sf::Mouse::getPosition(fenetre).x);
                printf("y :%i\n", sf::Mouse::getPosition(fenetre).y);
                printf("angle :%f\n", angle);
                //angle=(angle*2*M_PI)/360;
                printf("\ns\n");
                directionx=cos(angle);
                directiony=sin(angle);
                printf("dir y:%f\n", directiony);
                printf("dir x:%f\n", directionx);
                while(1)
                {

                    /*posx=posx+10;
                    printf("x :%i\n", posx);
                    posy=(coeff*posx);
                    printf("y :%i\n", posy);*/
                    posx=posx+directionx*10;
                    posy=posy+directiony*10;
                    printf("x :%i\n", posx);
                    printf("y :%i\n", posy);
                    projectile.setPosition(posx,posy);
                    fenetre.draw(projectile);
                    fenetre.display();
                    sleep(sf::milliseconds(100));
                }
            }
        }
    }
    return 0;
}
