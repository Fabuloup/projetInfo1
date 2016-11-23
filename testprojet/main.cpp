#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow fenetre(sf::VideoMode(800,600),"Neo Dojo");

    sf::Texture murTexture;
    murTexture.loadFromFile("ressources/murdojo.png");
    sf::Sprite spritemur;
    spritemur.setTexture(murTexture);

    //draw map
    int k;
    int j;
    sf::Event evenement;
    while(fenetre.isOpen())
    {
        while(fenetre.pollEvent(evenement))
        {
            if(evenement.type == sf::Event::Closed)
            {
                fenetre.close();
            }
        }
        for (k=0; k<5; k++)
        {
            for(j=0; j<5; j++)
            {
                if(k==0)
                {
                    if(j==0)
                    {
                        spritemur.setTextureRect(sf::IntRect(0,0,10,10));
                    }
                    /*else if(j==4)
                    {
                        spritemur.setTextureRect(sf::IntRect(20,0,30,10));
                    }
                    else
                    {
                        spritemur.setTextureRect(sf::IntRect(10,0,20,10));
                    }*/
                }
                else if(k==4)
                {
                    if(j==0)
                    {
                        spritemur.setTextureRect(sf::IntRect(0,20,10,30));
                    }
                    /*else if(j==4)
                    {
                        spritemur.setTextureRect(sf::IntRect(20,20,30,30));
                    }
                    else
                    {
                        spritemur.setTextureRect(sf::IntRect(10,20,20,30));
                    }*/
                }
                /*else
                {
                    if(j==0)
                    {
                        spritemur.setTextureRect(sf::IntRect(0,10,10,20));
                    }
                    else if(j==4)
                    {
                        spritemur.setTextureRect(sf::IntRect(20,10,30,20));
                    }
                }*/
                spritemur.setPosition(j*10, k*10);
                fenetre.draw(spritemur);
            }
        }
        fenetre.display();
    }
    return 0;
}
