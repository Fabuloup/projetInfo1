#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "functionMenu.hpp"
#include "functionPerso.hpp"
#include "functionEditor.hpp"
#include "funcWaves.hpp"
#include "fireball.hpp"

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

int main()
{
    //Création de la fenêtre et de l'évnènement
    sf::RenderWindow fenetre(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "Neo Dojo");
    sf::Event event;
    int choix=1, quitterOptions=0, posOption=0, sonOn=1, vsyncOn=1;
    int touche=(HAUTEUR_FENETRE/2)-110+10;
    char titreOpt[]="Options";
    char vsyncOpt[]="Vsync";
    char sonOpt[]="Son";
    char quitterOpt[]="Quitter";
    char *son_choixOpt[3];
    char *vsync_choixOpt[3];
    char scoresOpt[]="Scores";
    *son_choixOpt = (char*)malloc(256);
    *vsync_choixOpt = (char*)malloc(256);
    srand(time(NULL));

    //Activation vsync
    free(vsync_choixOpt);
    *vsync_choixOpt=strcpy(*vsync_choixOpt, "ON");
    fenetre.setVerticalSyncEnabled(true);
    vsyncOn=1;

    //Chargement son
    sf::Music musiqueFond, musiqueJeu;
    if (!musiqueFond.openFromFile("ressources/Blackmoor_Ninjas.wav"))
        printf("Erreur de chargement de la musique du menu");
    if (!musiqueJeu.openFromFile("ressources/NeoDojoOST.wav"))
        printf("Erreur de chargement de la musique du jeu");
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

    //Activation son
    free(son_choixOpt);
    *son_choixOpt=strcpy(*son_choixOpt, "ON");
    sonChoix.setVolume(100);
    sonDeplacement.setVolume(100);
    musiqueFond.setVolume(100);
    sonOn=1;

    //Bordel de Fabien
    sf::Texture textTexture;
    if( !textTexture.loadFromFile("ressources/alphabetred.png"))
    {
        printf("Impossible de charger le tileset du texte");
    }
    sf::Sprite spriteTexte;
    spriteTexte.setTexture(textTexture);

    //Création sprites et textures
    sf::Sprite spriteMenu, spriteChoix, spriteCurseur, spriteFond, spriteOptions;
    sf::Texture textureMenu, textureFond, textureChoix, textureOptions;

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
    spriteOptions.setTexture(textureOptions);

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

    //pour jouer
    char nomMap[100]="";
    int carte[100];

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
                    //Fonction pour redessiner la fenêtre
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    //Choix = 1 --> Pour définir sur quelle menu lancer ensuite
                    choix=1;
                    touche=(HAUTEUR_FENETRE/2)-110+10;
                }
                //Test si souris sur Multi
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+40<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+80)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+50);
                    //Fonction pour redessiner la fenêtre
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=2;
                    touche=(HAUTEUR_FENETRE/2)-110+50;
                }
                //Test si souris sur Options
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+80<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+120)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+90);
                    //Fonction pour redessiner la fenêtre
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=3;
                    touche=(HAUTEUR_FENETRE/2)-110+90;
                }
                //Test si souris sur Editeur
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+120<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+160)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+130);
                    //Fonction pour redessiner la fenêtre
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=4;
                    touche=(HAUTEUR_FENETRE/2)-110+130;
                }
                //Test si souris sur Quitter
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+160<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+200)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+170);
                    //Fonction pour redessiner la fenêtre
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=5;
                    touche=(HAUTEUR_FENETRE/2)-110+170;
                }
                break;
            }
            //Utilisation des touches haut et bas du clavier pour naviguer dans le menu
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    //On teste si le cursuer n'est pas déjà au plus haut (Option Jouer) sinon on augmente la position de 40
                    if (touche!=((HAUTEUR_FENETRE/2)-110+10))
                        touche=touche-40;
                    //Nouvelle position du curseur
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,touche);
                    //Fonction pour redessiner la fenêtre
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    //On teste si le curseur n'est pas au plus bas
                    if (touche!=(HAUTEUR_FENETRE/2)-110+170)
                        touche=touche+40;
                    //Nouvelle position du curseur
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,touche);
                    //Fonction pour redessiner la fenêtre
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                }
                //En fonction de la position de 'touche' qui est la position en y du curseur, on définit le choix
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
                break;
            }
            }
            if ((event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Return) || (event.type==sf::Event::MouseButtonPressed && event.key.code==sf::Mouse::Left))
            {
                sonChoix.play();
                switch (choix)
                {
                case 1:
                    printf("Jouer");
                    Jouer(spriteChoix, spriteTexte, &fenetre, nomMap, carte);
                    musiqueFond.stop();
                    if (sonOn==1)
                    {
                        musiqueJeu.play();
                        musiqueJeu.setLoop(true);
                    }
                    InGame(&fenetre, carte, spriteChoix, spriteTexte, spriteCurseur);
                    break;
                case 2:
                    printf("Multi");
                    break;
                case 3:
                    printf("Options");
                    quitterOptions=0;
                    posOption=1;
                    //On dessine le menu d'Options et on met le curseur sur le premier choix
                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240, 210, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.2, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.2, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                    //While pour éviter de sortir du menu, on en sortira quand on choisira 'Quitter'
                    while(quitterOptions==0)
                    {
                        if (fenetre.pollEvent(event))
                        {
                            if (event.type==sf::Event::MouseMoved)
                            {
                                sonDeplacement.play();
                                //Si souris est sur vsync
                                if (event.mouseMove.x>=300 && event.mouseMove.x<=500 && event.mouseMove.y>=200 && event.mouseMove.y<=240)
                                {
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240, 210, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.2, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.2, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                                    posOption=1;
                                }
                                //Si souris sur Son
                                else if (event.mouseMove.x>=350 && event.mouseMove.x<=470 && event.mouseMove.y>=300 && event.mouseMove.y<=340)
                                {
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 290,310, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.2, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.2, scoresOpt, 300, 400, 2.0);
                                    posOption=2;
                                }
                                //Si souris sur Scores
                                else if (event.mouseMove.x>=300 && event.mouseMove.x<=540 && event.mouseMove.y>=400 && event.mouseMove.y<=440)
                                {
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240,410, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.2);
                                    posOption=3;
                                }
                                //Si souris sur Quitter
                                else if (event.mouseMove.x>=275 && event.mouseMove.x<=600 && event.mouseMove.y>=500 && event.mouseMove.y<=550)
                                {
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 210,510, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.2, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                                    posOption=4;
                                }
                            }
                            //Test touches clavier
                            if(event.type==sf::Event::KeyPressed)
                            {
                                sonDeplacement.play();
                                if (event.key.code==sf::Keyboard::Up)
                                {
                                    posOption=posOption-1;
                                    if (posOption<=0)
                                        posOption=1;
                                }
                                else if (event.key.code==sf::Keyboard::Down)
                                {
                                    posOption=posOption+1;
                                    if (posOption>4)
                                        posOption=4;
                                }
                                switch (posOption)
                                {
                                case 1:
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240, 210, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.2, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.2, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                                    break;
                                case 2:
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 290,310, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.2, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.2, scoresOpt, 300, 400, 2.0);
                                    break;
                                case 3:
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240,410, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.2);
                                    break;
                                case 4:
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 210,510, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.2, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                                    break;
                                }
                            }
                            //Test des clics
                            if (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left || (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Return))
                            {
                                sonChoix.play();
                                if (posOption==4)
                                {
                                    quitterOptions=1;
                                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+10);
                                }
                                else if (posOption==1)
                                {
                                    switch(vsyncOn)
                                    {
                                    case 1:
                                        free(vsync_choixOpt);
                                        *vsync_choixOpt=strcpy(*vsync_choixOpt, "OFF");
                                        fenetre.setVerticalSyncEnabled(false);
                                        vsyncOn=0;
                                        break;
                                    case 0:
                                        free(vsync_choixOpt);
                                        *vsync_choixOpt=strcpy(*vsync_choixOpt, "ON");
                                        fenetre.setVerticalSyncEnabled(true);
                                        vsyncOn=1;
                                        break;
                                    }
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240, 210, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.2, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.2, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                                }
                                else if (posOption==2)
                                {
                                    switch(sonOn)
                                    {
                                    case 1:
                                        free(son_choixOpt);
                                        *son_choixOpt=strcpy(*son_choixOpt, "OFF");
                                        sonChoix.setVolume(0);
                                        sonDeplacement.setVolume(0);
                                        musiqueFond.stop();
                                        sonOn=0;
                                        break;
                                    case 0:
                                        free(son_choixOpt);
                                        *son_choixOpt=strcpy(*son_choixOpt, "ON");
                                        sonChoix.setVolume(100);
                                        sonDeplacement.setVolume(100);
                                        musiqueFond.play();
                                        sonOn=1;
                                        break;
                                    }
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 290,310, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.2, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.2, scoresOpt, 300, 400, 2.0);
                                }
                                 else if (posOption==3)
                                {
                                    printf("Scores");
                                }
                            }

                        }
                    }
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=1;
                    touche=(HAUTEUR_FENETRE/2)-110+10;
                    break;
                case 4:
                    funcEditor(spriteChoix, spriteTexte, &fenetre);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    break;
                case 5:
                    printf("Quitter");
                    fenetre.close();
                    musiqueFond.stop();
                    break;
                }
            }
        }
    }
    return 0;
}
