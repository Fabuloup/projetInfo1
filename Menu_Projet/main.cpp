#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "functionMenu.hpp"
#include "functionEditor.hpp"

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
int main()
{
    //Création de la fenêtre et de l'évnènement
    sf::RenderWindow fenetre(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "Neo Dojo");
    sf::Event event;
    int choix=1;
    int touche=(HAUTEUR_FENETRE/2)-110+10;

    //Chargement son
    sf::Music musiqueFond;
    if (!musiqueFond.openFromFile("ressources/Blackmoor_Ninjas.wav"))
        printf("Erreur de chargement de la musique");
    sf::SoundBuffer bufferChoix;
    if (!bufferChoix.loadFromFile("ressources/Couteau.flac"))
        printf("Erreur de chargement de la musique");
    sf::SoundBuffer bufferDeplacement;
    if (!bufferDeplacement.loadFromFile("ressources/Bruit.wav"))
        printf("Erreur de chargement du son de deplacement");
    sf::Sound sonChoix;
    sonChoix.setBuffer(bufferChoix);
    sf::Sound sonDeplacement;
    sonDeplacement.setBuffer(bufferDeplacement);
    musiqueFond.setLoop(true);
    musiqueFond.play();

    //Bordel de Fabien
    sf::Texture textTexture;
    if( !textTexture.loadFromFile("ressources/alphabetred.png"))
    {
        printf("Impossible de charger le tileset du texte");
    }
    sf::Sprite spriteTexte;
    spriteTexte.setTexture(textTexture);

    //Création sprites et textures
    sf::Sprite spriteMenu, spriteChoix, spriteCurseur, spriteFond;
    sf::Texture textureMenu, textureFond, textureChoix;

    //Chargement des images
    if (!textureChoix.loadFromFile("ressources/texture.png"))
        printf("Erreur de chargement de texture.png\n");
    if (!textureFond.loadFromFile("ressources/fond_menu.png"))
        printf("Erreur de chargement du fond\n");
    if (!textureMenu.loadFromFile("ressources/titre.png"))
        printf("Erreur de chargement titre.png\n");

    //Association sprite et image
    spriteMenu.setTexture(textureMenu);
    spriteChoix.setTexture(textureChoix);
    spriteCurseur.setTexture(textureChoix);
    spriteFond.setTexture(textureFond);

    //Grossissement image
    spriteMenu.setScale(2.0f,2.0f);

    //Découpage des textures
    //spriteMenu.setTextureRect(sf::IntRect(100,40,100,60));
    spriteChoix.setTextureRect(sf::IntRect(200,0,200,220));
    spriteCurseur.setTextureRect(sf::IntRect(0,170,60,20));

    //Position
    spriteMenu.setPosition((LARGEUR_FENETRE/2)-250,40);
    spriteChoix.setPosition((LARGEUR_FENETRE/2)-40, HAUTEUR_FENETRE/2-110);
    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+10);

    //Premier affichage avec le curseur sur Jouer
    fenetre.draw(spriteFond);
    fenetre.draw(spriteMenu);
    fenetre.draw(spriteChoix);
    fenetre.draw(spriteCurseur);
    fenetre.display();

    //Test position de la souris pour bouger le curseur du menu
    while(fenetre.isOpen())
    {
        while(fenetre.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                fenetre.close();
                break;
            case sf::Event::MouseMoved:
            {
                //Test si souris sur Jouer
                if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && ((HAUTEUR_FENETRE/2)-110)<event.mouseMove.y && event.mouseMove.y<((HAUTEUR_FENETRE/2)-110+40))
                {
                    //Déplacement du curseur
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+10);
                    //Clear puis redessine les sprites
                    fenetre.clear(sf::Color::Black);
                    fenetre.draw(spriteFond);
                    fenetre.draw(spriteMenu);
                    fenetre.draw(spriteChoix);
                    fenetre.draw(spriteCurseur);
                    fenetre.display();
                    //Son deplacement
                    sonDeplacement.play();
                    //Choix = 1 --> Pour définir sur quelle menu lancer ensuite
                    choix=1;
                }
                //Test si souris sur Multi
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+40<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+80)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+50);
                    fenetre.clear(sf::Color::Black);
                    fenetre.draw(spriteFond);
                    fenetre.draw(spriteMenu);
                    fenetre.draw(spriteChoix);
                    fenetre.draw(spriteCurseur);
                    fenetre.display();
                    sonDeplacement.play();
                    choix=2;
                }
                //Test si souris sur Options
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+80<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+120)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+90);
                    fenetre.clear(sf::Color::Black);
                    fenetre.draw(spriteFond);
                    fenetre.draw(spriteMenu);
                    fenetre.draw(spriteChoix);
                    fenetre.draw(spriteCurseur);
                    fenetre.display();
                    sonDeplacement.play();
                    choix=3;
                }
                //Test si souris sur Editeur
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+120<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+160)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+130);
                    fenetre.clear(sf::Color::Black);
                    fenetre.draw(spriteFond);
                    fenetre.draw(spriteMenu);
                    fenetre.draw(spriteChoix);
                    fenetre.draw(spriteCurseur);
                    fenetre.display();
                    sonDeplacement.play();
                    choix=4;
                }
                //Test si souris sur Quitter
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+160<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+200)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+170);
                    fenetre.clear(sf::Color::Black);
                    fenetre.draw(spriteFond);
                    fenetre.draw(spriteMenu);
                    fenetre.draw(spriteChoix);
                    fenetre.draw(spriteCurseur);
                    sonDeplacement.play();
                    fenetre.display();
                    choix=5;
                }
                break;
            }
            //Test si un clic gauche est fait
            case sf::Event::MouseButtonPressed:
            {
                //En fonction du choix, un clic permet d'accéder au menu sélectionné
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    switch (choix)
                    {
                    case 1:
                        printf("Jouer");
                        sonChoix.play();
                        break;
                    case 2:
                        printf("Multi");
                        sonChoix.play();
                        break;
                    case 3:
                        printf("Options");
                        sonChoix.play();
                        break;
                    case 4:
                        funcEditor(spriteChoix, spriteTexte, &fenetre);
                        sonChoix.play();
                        break;
                    case 5:
                        printf("Quitter");
                        sonChoix.play();
                        fenetre.close();
                        musiqueFond.stop();
                        break;
                    }
                }
            }
            //Utilisation des touches haut et bas du clavier pour naviguer dans le menu
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    //On teste si le cursuer n'est pas déjà au plus haut (Option Jouer) sinon on augmente la position de 40
                    if (touche!=((HAUTEUR_FENETRE/2)-110+10))
                        touche=touche-40;
                    //Clear puis dessine la fenêtre
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,touche);
                    fenetre.clear(sf::Color::Black);
                    fenetre.draw(spriteFond);
                    fenetre.draw(spriteMenu);
                    fenetre.draw(spriteChoix);
                    fenetre.draw(spriteCurseur);
                    sonDeplacement.play();
                    fenetre.display();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    //On teste si le curseur n'est pas au plus bas
                    if (touche!=(HAUTEUR_FENETRE/2)-110+170)
                        touche=touche+40;
                    //Clear puis dessine
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,touche);
                    fenetre.clear(sf::Color::Black);
                    fenetre.draw(spriteFond);
                    fenetre.draw(spriteMenu);
                    fenetre.draw(spriteChoix);
                    fenetre.draw(spriteCurseur);
                    fenetre.display();
                    sonDeplacement.play();
                }
                //En fonction de la position de 'touche' qui est la position y du curseur, on définit le choix
                switch (touche)
                {
                case (HAUTEUR_FENETRE/2)-110+10:
                    choix=1;
                    break;
                case (HAUTEUR_FENETRE/2)-110+50:
                    choix=2;
                    break;
                case (HAUTEUR_FENETRE/2)-110+90:
                    choix=3;
                    break;
                case (HAUTEUR_FENETRE/2)-110+130:
                    choix=4;
                    break;
                case (HAUTEUR_FENETRE/2)-110+170:
                    choix=5;
                    break;
                }
                //Si on appuie sur espace, renvoie vers le prochain menu en fonction de choix
                if (event.key.code == sf::Keyboard::Space)
                {
                    switch (choix)
                    {
                    case 1:
                        printf("Jouer");
                        sonChoix.play();
                        break;
                    case 2:
                        printf("Multi");
                        sonChoix.play();
                        break;
                    case 3:
                        printf("Options");
                        sonChoix.play();
                        break;
                    case 4:
                        funcEditor(spriteChoix, spriteTexte, &fenetre);
                        sonChoix.play();
                        break;
                    case 5:
                        printf("Quitter");
                        sonChoix.play();
                        fenetre.close();
                        break;
                    }
                }
            }
            }

        }
    }
    fenetre.draw(spriteMenu);
    fenetre.draw(spriteChoix);
    spriteCurseur.setPosition(0,0);
    fenetre.draw(spriteCurseur);
    fenetre.display();
    return 0;
}
