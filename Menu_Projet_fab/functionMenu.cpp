#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "functionMenu.hpp"
#include "functionEditor.hpp"


void DessineMenu(sf::RenderWindow *fenetre, sf::Sprite spriteChoix, sf::Sprite spriteFond, sf::Sprite spriteMenu, sf::Sprite spriteCurseur, sf::Sound sonDeplacement)
{
    fenetre->clear(sf::Color::Black);
    fenetre->draw(spriteFond);
    fenetre->draw(spriteMenu);
    fenetre->draw(spriteChoix);
    fenetre->draw(spriteCurseur);
    fenetre->display();
    //Son deplacement
    sonDeplacement.play();
}

void DessineOption(sf::RenderWindow *fenetre, sf::Sprite spriteCurseur, sf::Sprite spriteFond)
{
    fenetre->clear(sf::Color::Black);
    fenetre->draw(spriteFond);
    fenetre->draw(spriteCurseur);
}

void OptionsMenu(sf::RenderWindow *fenetre, sf::Sprite spriteFond, sf::Sprite spriteCurseur, int x_curseur, int y_curseur, sf::Sprite spriteTexte, char titreOpt[], int x_titre, int y_titre, float taille_titre, char vsyncOpt[], int x_vsync, int y_vsinc, float taille_vsync, char sonOpt[], int x_son, int y_son, float taille_son, char quitterOpt[], int x_quit, int y_quit, float taille_quit, char vsync_choixOpt[], int x_vsyncChoix, int y_vsyncChoix, float taille_vsyncChoix, char son_choixOpt[], int x_sonChoix, int y_sonChoix, float taille_sonChoix, char scoresOpt[], int x_scores, int y_scores, float taille_scores)
{
    fenetre->clear(sf::Color::Black);
    spriteCurseur.setPosition(x_curseur,y_curseur);
    DessineOption(fenetre, spriteCurseur, spriteFond);
    MachineAEcrire(spriteTexte, fenetre, titreOpt, x_titre, y_titre, taille_titre);
    MachineAEcrire(spriteTexte, fenetre, vsyncOpt, x_vsync, y_vsinc, taille_vsync);
    MachineAEcrire(spriteTexte, fenetre, sonOpt, x_son, y_son, taille_son);
    MachineAEcrire(spriteTexte, fenetre, quitterOpt, x_quit, y_quit, taille_quit);
    MachineAEcrire(spriteTexte, fenetre, vsync_choixOpt, x_vsyncChoix,y_vsyncChoix,taille_vsyncChoix);
    MachineAEcrire(spriteTexte, fenetre, son_choixOpt, x_sonChoix, y_sonChoix, taille_sonChoix);
    MachineAEcrire(spriteTexte, fenetre, scoresOpt, x_scores,y_scores,taille_scores);
    fenetre->display();
}

void PauseJeu(sf::RenderWindow *fenetre, sf::Sprite spriteTexte, int *retourMenu, sf::Sprite spriteCurseur)
{
    sf::Event event;
    sf::Sprite spriteFond;
    sf::Texture textureFond;
    if (!textureFond.loadFromFile("ressources/fond_pause.png"))
        printf("Erreur de chargement");
    spriteFond.setTexture(textureFond);
    spriteFond.scale(5.0,5.0);
    spriteFond.setPosition(150,50);
    int quitterPause=0, choix=1, xcurseur=205, ycurseur=255;
    char pauseTitre[]="Pause";
    char pauseReprendre[]="Reprendre";
    char pauseQuitter[]="Quitter";
    spriteCurseur.setPosition(205,255);
    while(quitterPause==0)
    {
        while (fenetre->isOpen() && quitterPause==0)
        {
            fenetre->clear(sf::Color::Black);
            fenetre->draw(spriteFond);
            MachineAEcrire(spriteTexte, fenetre, pauseTitre, 310,120,2.0);
            MachineAEcrire(spriteTexte, fenetre, pauseReprendre, 270,250,1.5);
            MachineAEcrire(spriteTexte, fenetre, pauseQuitter, 300, 400, 1.5);
            while (fenetre->pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::Closed:
                    fenetre->close();
                    break;
                case sf::Event::MouseMoved:
                    if (event.mouseMove.x>270 && event.mouseMove.x<540 && event.mouseMove.y>250 && event.mouseMove.y<280)
                    {
                        xcurseur=205;
                        ycurseur=255;
                        choix=1;
                    }
                    if (event.mouseMove.x>300 && event.mouseMove.x<510 && event.mouseMove.y>390 && event.mouseMove.y<430)
                    {
                        xcurseur=235;
                        ycurseur=405;
                        choix=2;
                    }
                    spriteCurseur.setPosition(xcurseur, ycurseur);
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code==sf::Keyboard::Up)
                    {
                        xcurseur=xcurseur-30;
                        if (xcurseur<205)
                            xcurseur=205;
                    }
                    if (event.key.code==sf::Keyboard::Down)
                    {
                        xcurseur=xcurseur+30;
                        if (xcurseur>235)
                            xcurseur=235;
                    }
                    if (xcurseur==205)
                        {
                            ycurseur=255;
                            choix=1;
                        }
                    else
                        {
                            ycurseur=405;
                            choix=2;
                        }
                    spriteCurseur.setPosition(xcurseur, ycurseur);
                    break;
                }
                    if ((event.type==sf::Event::MouseButtonPressed && event.key.code==sf::Mouse::Left) || (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Return))
                    {
                        switch(choix)
                        {
                        case 1:
                            quitterPause=1;
                            break;
                        case 2:
                            *retourMenu=1;
                            quitterPause=1;
                            break;
                        }
                    }

            }
            fenetre->draw(spriteCurseur);
            fenetre->display();
        }
    }
}

void EcranDefaite(sf::RenderWindow *fenetre, char *scoreTXT, char *vagueTXT, sf::Sprite spriteTexte)
{
    sf::Event event;
    char pauseTitre[]="Defaite";
    char pauseQuitter[]="Appuyez sur Entree pour quitter";
    int quitterDefaite=0;
    MachineAEcrire(spriteTexte, fenetre, pauseTitre, 150,100,2.0);
    MachineAEcrire(spriteTexte, fenetre, pauseQuitter, 10, 400,1);
    MachineAEcrire(spriteTexte, fenetre, scoreTXT, 120,200,1.5);
    MachineAEcrire(spriteTexte, fenetre, vagueTXT, 120, 300, 1.5);
    fenetre->display();
    while(quitterDefaite==0)
    {
        if (fenetre->pollEvent(event) && (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Return))
        {
            quitterDefaite=1;
        }
    }
}

