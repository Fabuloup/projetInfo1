#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <math.h>

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define ZOOM 0.3
#define LARGEUR 800
#define HAUTEUR 600
#define DIMENSION 10
#define DIMENSIONLETTRE 20
#define MAXENNEMY 20

using namespace std;

void DessineMenu(sf::RenderWindow *fenetre,sf::Sprite spriteChoix, sf::Sprite spriteFond, sf::Sprite spriteMenu, sf::Sprite spriteCurseur, sf::Sound sonDeplacement);
void DessineOption(sf::RenderWindow *fenetre, sf::Sprite spriteCurseur, sf::Sprite spriteFond);
void OptionsMenu(sf::RenderWindow *fenetre, sf::Sprite spriteFond, sf::Sprite spriteCurseur, int x_curseur, int y_curseur, sf::Sprite spriteTexte, char titreOpt[], int x_titre, int y_titre, float taille_titre, char vsyncOpt[], int x_vsync, int y_vsinc, float taille_vsync, char sonOpt[], int x_son, int y_son, float taille_son, char quitterOpt[], int x_quit, int y_quit, float taille_quit, char vsync_choixOpt[], int x_vsyncChoix, int y_vsyncChoix, float taille_vsyncChoix, char son_choixOpt[], int x_sonChoix, int y_sonChoix, float taille_sonChoix, char scoresOpt[], int x_scores, int y_scores, float taille_scores);
void PauseJeu(sf::RenderWindow *fenetre, sf::Sprite spriteTexte, int *retourMenu, sf::Sprite spriteCurseur);
void EcranDefaite(sf::RenderWindow *fenetre, char *scoreTXT, char *vagueTXT, sf::Sprite spriteTexte);


int createOrNew(sf::RenderWindow *fenetre, sf::Sprite tileset, sf::Sprite textTile);
void loadMap(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre, char *nomMap, int *carte);
void editor(int *plan, sf::Sprite tileset, sf::RenderWindow *fenetre, char *mapName="mapEdit.map");
bool isClickOn(int xToTest, int yToTest, int x, int y, int width, int height);
void drawMap(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre, int decalageX=0, int decalageY=0);
void changeMapValue(int *plan, int largeurMap, int hauteurMap, int x, int y, int tileSelected, int decalageX=0, int decalageY=0);
void funcEditor(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre);
void MachineAEcrire(sf::Sprite fontTile, sf::RenderWindow *fenetre, char* texte, int posX=0, int posY=0, float taille=1.0);
void scanGraphique(char *texte,sf::Sprite tileText, sf::RenderWindow *fenetre, int posX=0, int posY=0, float taille=1.0f);
void Jouer(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre, char *nomMap, int *carte);
void InGame(sf::RenderWindow *fenetre, int *planMap, sf::Sprite spriteTexture, sf::Sprite spriteTexte, sf::Sprite spriteCurseur);
void drawMapGame(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre, int decalageX, int decalageY);

class ennemy
{
private:
    int e_vie;
    int e_x;
    int e_y;
    int e_type;
    int e_actif;
    int e_pas;
    int e_zone;
public:
    ennemy();
    ennemy(int m_vie, int m_x, int m_y);
    void setPosition(int m_x, int m_y);
    int get_x();
    int get_y();
    void setActif(int m_actif);
    int isActif();
    void changePas(int m_pas);
    int getPas();
    void setZone(int new_zone);
    int getZone();
    void setType(int new_type);
    int getType();
};

bool collision_haut(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);
bool collision_bas(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);
bool collision_gauche(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);
bool collision_droite(int pos_x_p,int pos_y_p,int pos_x_ia, int pos_y_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia);

class heros
{
public:
    heros();
    heros(int m_x, int m_y, int m_speed, int m_life);
    void setPosition(int m_x, int m_y);
    void setX(int m_x);
    void setY(int m_y);
    void walkX(int m_x);
    void walkY(int m_y);
    void setSpeed(int m_speed);
    void setLife(int m_life);
    void findAngle(int mouse_x, int mouse_y);
    void setWalkStep(int m_walkStep);
    void setIsSlash(int m_slash);
    int getX();
    int getY();
    int getSpeed();
    int getLife();
    float getAngle();
    int getWalkStep();
    int getSlashStep();

private:
    int h_x;
    int h_y;
    int h_speed;
    int h_life;
    float h_angle;
    int h_walkStep;
    int h_isSlash;
};

class Fireball
{
public:
    Fireball();
    ~Fireball();
    int get_posx();
    int get_posy();
    void set_posx(int new_x);
    void set_posy(int new_y);
    void set_pas(int new_pas);
    int get_pas();
    double calculeDirectionx(int cible_x, int cible_y);
    double calculeDirectiony(int cible_x, int cible_y);
    void set_directionx(double new_directionx);
    void set_directiony(double new_directiony);
    double get_directionx();
    double get_directiony();

private:
    int m_posx;
    int m_posy;
    int m_pas;
    double m_directionx;
    double m_directiony;
};

void deplacementSouris(heros* ninja, int mouseX, int mouseY, int* plan, ennemy* vague, int* score, int* nbMorts, Fireball* tabFireball, int nbboule);
void setTexureRectNinja(sf::Sprite* spriteGeneral, int ninjaWalkStep, int slash);

class Boss
{
public :
    Boss();
    bool estInvincible() const;
    void recevoirDegats();
    int get_posx();
    int get_posy();
    void set_posx(int new_posx);
    void set_posy(int new_posy);
    void setInvincible(bool inv);

private :
    int m_posx;
    int m_posy;
    bool m_estInvincible;
    int m_vie;
};

void vagueBoss(Boss *boss, float *angle, int *nbboule, Fireball* tabFireball, sf::Clock *clocktp, sf::Time tempstp, sf::Clock *clock, sf::Time temps, int originx, int originy, int rayon);


int main()
{
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

    free(vsync_choixOpt);
    *vsync_choixOpt=strcpy(*vsync_choixOpt, "ON");
    fenetre.setVerticalSyncEnabled(true);
    vsyncOn=1;

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

    free(son_choixOpt);
    *son_choixOpt=strcpy(*son_choixOpt, "ON");
    sonChoix.setVolume(100);
    sonDeplacement.setVolume(100);
    musiqueFond.setVolume(100);
    sonOn=1;

    sf::Texture textTexture;
    if( !textTexture.loadFromFile("ressources/alphabetred.png"))
        printf("Impossible de charger le tileset du texte");
    sf::Sprite spriteTexte;
    spriteTexte.setTexture(textTexture);

    sf::Sprite spriteMenu, spriteChoix, spriteCurseur, spriteFond, spriteOptions;
    sf::Texture textureMenu, textureFond, textureChoix, textureOptions;

    if (!textureChoix.loadFromFile("ressources/texture.png"))
        printf("Erreur de chargement de texture.png\n");
    if (!textureFond.loadFromFile("ressources/fond_menu.png"))
        printf("Erreur de chargement du fond\n");
    if (!textureMenu.loadFromFile("ressources/titre.png"))
        printf("Erreur de chargement titre.png\n");

    spriteMenu.setTexture(textureMenu);
    spriteChoix.setTexture(textureChoix);
    spriteCurseur.setTexture(textureChoix);
    spriteFond.setTexture(textureFond);
    spriteOptions.setTexture(textureOptions);

    spriteMenu.setScale(2.0f,2.0f);

    spriteChoix.setTextureRect(sf::IntRect(200,0,200,220));
    spriteCurseur.setTextureRect(sf::IntRect(0,170,60,20));

    spriteMenu.setPosition((LARGEUR_FENETRE/2)-250,40);
    spriteChoix.setPosition((LARGEUR_FENETRE/2)-40, HAUTEUR_FENETRE/2-110);
    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+10);

    char nomMap[100]="";
    int carte[100];

    fenetre.draw(spriteFond);
    fenetre.draw(spriteMenu);
    fenetre.draw(spriteChoix);
    fenetre.draw(spriteCurseur);
    fenetre.display();

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
                if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && ((HAUTEUR_FENETRE/2)-110)<event.mouseMove.y && event.mouseMove.y<((HAUTEUR_FENETRE/2)-110+40))
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+10);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=1;
                    touche=(HAUTEUR_FENETRE/2)-110+10;
                }
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+40<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+80)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+50);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=2;
                    touche=(HAUTEUR_FENETRE/2)-110+50;
                }
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+80<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+120)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+90);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=3;
                    touche=(HAUTEUR_FENETRE/2)-110+90;
                }
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+120<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+160)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+130);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=4;
                    touche=(HAUTEUR_FENETRE/2)-110+130;
                }
                else if ((LARGEUR_FENETRE/2-40)<event.mouseMove.x && event.mouseMove.x<(LARGEUR_FENETRE/2)-40+127 && (HAUTEUR_FENETRE/2)-110+160<event.mouseMove.y && event.mouseMove.y<(HAUTEUR_FENETRE/2)-110+200)
                {
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,(HAUTEUR_FENETRE/2)-110+170);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=5;
                    touche=(HAUTEUR_FENETRE/2)-110+170;
                }
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (touche!=((HAUTEUR_FENETRE/2)-110+10))
                        touche=touche-40;
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,touche);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    if (touche!=(HAUTEUR_FENETRE/2)-110+170)
                        touche=touche+40;
                    spriteCurseur.setPosition((LARGEUR_FENETRE/2)-40-70,touche);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                }
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
                    Jouer(spriteChoix, spriteTexte, &fenetre, nomMap, carte);
                    musiqueFond.stop();
                    if (sonOn==1)
                    {
                        musiqueJeu.play();
                        musiqueJeu.setLoop(true);
                    }
                    InGame(&fenetre, carte, spriteChoix, spriteTexte, spriteCurseur);
                    DessineMenu(&fenetre, spriteChoix, spriteFond, spriteMenu, spriteCurseur, sonDeplacement);
                    choix=1;
                    touche=(HAUTEUR_FENETRE/2)-110+10;
                    musiqueJeu.stop();
                    musiqueFond.play();
                    break;
                case 2:
                    break;
                case 3:
                    quitterOptions=0;
                    posOption=1;
                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240, 210, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.2, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.2, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                    while(quitterOptions==0)
                    {
                        if (fenetre.pollEvent(event))
                        {
                            if (event.type==sf::Event::MouseMoved)
                            {
                                sonDeplacement.play();
                                if (event.mouseMove.x>=300 && event.mouseMove.x<=500 && event.mouseMove.y>=200 && event.mouseMove.y<=240)
                                {
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240, 210, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.2, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.2, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                                    posOption=1;
                                }
                                else if (event.mouseMove.x>=350 && event.mouseMove.x<=470 && event.mouseMove.y>=300 && event.mouseMove.y<=340)
                                {
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 290,310, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.2, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.2, scoresOpt, 300, 400, 2.0);
                                    posOption=2;
                                }
                                else if (event.mouseMove.x>=300 && event.mouseMove.x<=540 && event.mouseMove.y>=400 && event.mouseMove.y<=440)
                                {
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 240,410, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.0, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.2);
                                    posOption=3;
                                }
                                else if (event.mouseMove.x>=275 && event.mouseMove.x<=600 && event.mouseMove.y>=500 && event.mouseMove.y<=550)
                                {
                                    OptionsMenu(&fenetre, spriteFond, spriteCurseur, 210,510, spriteTexte, titreOpt, 200, 25, 3.0, vsyncOpt, 300, 200, 2.0, sonOpt, 350, 300, 2.0, quitterOpt, 275, 500, 2.2, *vsync_choixOpt, 600, 200, 2.0, *son_choixOpt, 600, 300, 2.0, scoresOpt, 300, 400, 2.0);
                                    posOption=4;
                                }
                            }
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
                    fenetre.close();
                    musiqueFond.stop();
                    break;
                }
            }
        }
    }
    return 0;
}

void DessineMenu(sf::RenderWindow *fenetre, sf::Sprite spriteChoix, sf::Sprite spriteFond, sf::Sprite spriteMenu, sf::Sprite spriteCurseur, sf::Sound sonDeplacement)
{
    fenetre->clear(sf::Color::Black);
    fenetre->draw(spriteFond);
    fenetre->draw(spriteMenu);
    fenetre->draw(spriteChoix);
    fenetre->draw(spriteCurseur);
    fenetre->display();
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

void funcEditor(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre)
{
    sf::View vue(sf::FloatRect(0, 0, LARGEUR, HAUTEUR));
    vue.zoom(ZOOM);
    vue.setCenter((int)(LARGEUR*ZOOM)/2, (int)(HAUTEUR*ZOOM)/2);
    fenetre->setView(vue);
    int choixEdit =0;
    char NomMap[100]="";
    choixEdit = createOrNew(fenetre, tileset, tileTexte);
    if(choixEdit==1)
    {
        int carte[100];
        loadMap(tileset, tileTexte, fenetre, NomMap, carte);
        editor(carte, tileset, fenetre, NomMap);
    }
    else if (choixEdit==0)
    {
        char titre[]="Entrez le nom de votre map (tab ajoute le .map)";
        fenetre->clear();
        MachineAEcrire(tileTexte, fenetre, titre, 30, 1, 0.2f);
        fenetre->display();
        fenetre->clear();
        MachineAEcrire(tileTexte, fenetre, titre, 30, 1, 0.2f);
        fenetre->display();
        scanGraphique(NomMap, tileTexte, fenetre, 30, 60, 0.4f);
        int carteDeBase[10*10]= {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
        editor(carteDeBase, tileset, fenetre, NomMap);
    }
    vue.zoom(1/0.3);
    vue.setCenter(LARGEUR/2, HAUTEUR/2);
    fenetre->setView(vue);
    fenetre->clear();
    fenetre->display();
    fenetre->clear();
    fenetre->display();
}

int createOrNew(sf::RenderWindow *fenetre, sf::Sprite tileset, sf::Sprite textTile)
{
    int position=0;
    int finBoucle=0;
    char titre[]="editeur de map";
    char choix1[]="creer une map";
    char choix2[]="editer une map";
    sf::Event event;
    while(fenetre->isOpen() && finBoucle==0)
    {
        fenetre->clear();
        while(fenetre->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                fenetre->close();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                case sf::Keyboard::Return:
                    finBoucle=1;
                    break;
                case sf::Keyboard::Left:
                    position=0;
                    break;
                case sf::Keyboard::Right:
                    position=1;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        MachineAEcrire(textTile, fenetre, titre, 50, 10, 0.5f);
        MachineAEcrire(textTile, fenetre, choix1, 30, 60, 0.3f);
        MachineAEcrire(textTile, fenetre, choix2, 130, 60, 0.3f);
        tileset.setTextureRect(sf::IntRect(50, 30, 10, 10));
        tileset.setPosition(18+position*100, 58);
        fenetre->draw(tileset);
        fenetre->display();
    }

    return position;
}

void loadMap(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre, char *nomMap, int *carte)
{
    int exitVar = 0;
    char informations[]="Entrez le nom de la map a charger";
    char astuce[]="La touche TAB ajoute le .map";
    while (exitVar == 0 and fenetre->isOpen())
    {
        char chemin[]="ressources/map/";
        fenetre->clear();
        MachineAEcrire(tileTexte, fenetre, informations, 30, 10, 0.3f);
        MachineAEcrire(tileTexte, fenetre, astuce, 40, 20, 0.3f);
        fenetre->display();
        fenetre->clear();
        MachineAEcrire(tileTexte, fenetre, informations, 30, 10, 0.3f);
        MachineAEcrire(tileTexte, fenetre, astuce, 40, 20, 0.3f);
        fenetre->display();
        scanGraphique(nomMap, tileTexte, fenetre, 20,70, 0.3f);
        fenetre->display();
        strcat(chemin, nomMap);
        printf("%s\n", chemin);
        FILE* fichierMap=NULL;
        fichierMap = fopen(chemin, "r");
        if(fichierMap==NULL)
        {
            printf("Impossible d'ouvrir le fichier\n");
        }
        else
        {
            int k=0;
            for(k=0; k<100; k++)
            {
                carte[k]=(int)(fgetc(fichierMap)-48);
            }
            fclose(fichierMap);
            exitVar=1;
        }
    }
}

void scanGraphique(char *texte,sf::Sprite tileText, sf::RenderWindow *fenetre, int posX, int posY, float taille)
{
    int position=0;
    int toContinue = 0;
    char *lettreTapee;
    sf::Event event;
    while(fenetre->isOpen() && toContinue==0)
    {
        while(fenetre->pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                fenetre->close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
                    lettreTapee="";
                    toContinue=1;
                    break;
                case sf::Keyboard::Space:
                    lettreTapee=" ";
                    break;
                case sf::Keyboard::BackSpace:
                    lettreTapee="";
                    texte[strlen(texte)-1]=texte[strlen(texte)];
                    break;
                case sf::Keyboard::A:
                    lettreTapee="a";
                    break;
                case sf::Keyboard::B:
                    lettreTapee="b";
                    break;
                case sf::Keyboard::C:
                    lettreTapee="c";
                    break;
                case sf::Keyboard::D:
                    lettreTapee="d";
                    break;
                case sf::Keyboard::E:
                    lettreTapee="e";
                    break;
                case sf::Keyboard::F:
                    lettreTapee="f";
                    break;
                case sf::Keyboard::G:
                    lettreTapee="g";
                    break;
                case sf::Keyboard::H:
                    lettreTapee="h";
                    break;
                case sf::Keyboard::I:
                    lettreTapee="i";
                    break;
                case sf::Keyboard::J:
                    lettreTapee="j";
                    break;
                case sf::Keyboard::K:
                    lettreTapee="k";
                    break;
                case sf::Keyboard::L:
                    lettreTapee="l";
                    break;
                case sf::Keyboard::M:
                    lettreTapee="m";
                    break;
                case sf::Keyboard::N:
                    lettreTapee="n";
                    break;
                case sf::Keyboard::O:
                    lettreTapee="o";
                    break;
                case sf::Keyboard::P:
                    lettreTapee="p";
                    break;
                case sf::Keyboard::Q:
                    lettreTapee="q";
                    break;
                case sf::Keyboard::R:
                    lettreTapee="r";
                    break;
                case sf::Keyboard::S:
                    lettreTapee="s";
                    break;
                case sf::Keyboard::T:
                    lettreTapee="t";
                    break;
                case sf::Keyboard::U:
                    lettreTapee="u";
                    break;
                case sf::Keyboard::V:
                    lettreTapee="v";
                    break;
                case sf::Keyboard::W:
                    lettreTapee="w";
                    break;
                case sf::Keyboard::X:
                    lettreTapee="x";
                    break;
                case sf::Keyboard::Y:
                    lettreTapee="y";
                    break;
                case sf::Keyboard::Z:
                    lettreTapee="z";
                    break;
                case sf::Keyboard::Tab:
                    lettreTapee=".map";
                    break;
                default :
                    lettreTapee=" ";
                    break;
                }
                fenetre->clear();
                strcat(texte, lettreTapee);
                MachineAEcrire(tileText, fenetre, texte, posX, posY, taille);
                fenetre->display();
                break;
            default:
                break;
            }
        }
    }
}
bool isClickOn(int xToTest, int yToTest, int x, int y, int width, int height)
{
    x=x/ZOOM;
    y=y/ZOOM;
    width=width/ZOOM;
    height=height/ZOOM;
    if(xToTest>x && xToTest<x+width && yToTest>y && yToTest<y+height)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void drawMap(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre, int decalageX, int decalageY)
{
    int x=0;
    int y=0;
    for(y=0; y<hauteur; y++)
    {
        for(x=0; x<largeur; x++)
        {
            switch(plan[y*largeur+x])
            {
            case 0:
                tileset.setTextureRect(sf::IntRect(30,0,10,10));
                break;
            case 1:
                tileset.setTextureRect(sf::IntRect(40, 0, 10, 10));
                break;
            case 2:
                tileset.setTextureRect(sf::IntRect(50, 0, 10, 10));
                break;
            case 3:
                tileset.setTextureRect(sf::IntRect(30, 10, 10, 10));
                break;
            case 4:
                tileset.setTextureRect(sf::IntRect(40, 10, 10, 10));
                break;
            case 5:
                tileset.setTextureRect(sf::IntRect(50, 10, 10, 10));
                break;
            case 6:
                tileset.setTextureRect(sf::IntRect(30, 20, 10, 10));
                break;
            case 7:
                tileset.setTextureRect(sf::IntRect(40, 20, 10, 10));
                break;
            case 8:
                tileset.setTextureRect(sf::IntRect(50, 20, 10, 10));
                break;
            case 9:
                tileset.setTextureRect(sf::IntRect(0, 0, 10, 10));
                break;
            case 10:
                tileset.setTextureRect(sf::IntRect(10, 0, 10, 10));
                break;
            case 11:
                tileset.setTextureRect(sf::IntRect(20, 0, 10, 10));
                break;
            case 12:
                tileset.setTextureRect(sf::IntRect(0, 10, 10, 10));
                break;
            case 13:
                tileset.setTextureRect(sf::IntRect(10, 10, 10, 10));
                break;
            case 14:
                tileset.setTextureRect(sf::IntRect(20, 10, 10, 10));
                break;
            case 15:
                tileset.setTextureRect(sf::IntRect(0, 20, 10, 10));
                break;
            case 16:
                tileset.setTextureRect(sf::IntRect(10, 20, 10, 10));
                break;
            case 17:
                tileset.setTextureRect(sf::IntRect(20, 20, 10, 10));
                break;
            default:
                tileset.setTextureRect(sf::IntRect(40, 10, 10, 10));
                break;
            }
            tileset.setPosition(sf::Vector2f(x*10+decalageX, y*10+decalageY));
            fenetre->draw(tileset);
        }
    }
}

void drawMapGame(int *plan, int largeur, int hauteur, sf::Sprite tileset, sf::RenderWindow *fenetre, int decalageX, int decalageY)
{
    int x=0;
    int y=0;
    tileset.scale(3.0f, 3.0f);
    for(y=0; y<hauteur; y++)
    {
        for(x=0; x<largeur; x++)
        {
            switch(plan[y*largeur+x])
            {
            case 0:
                tileset.setTextureRect(sf::IntRect(30,0,10,10));
                break;
            case 1:
                tileset.setTextureRect(sf::IntRect(40, 0, 10, 10));
                break;
            case 2:
                tileset.setTextureRect(sf::IntRect(50, 0, 10, 10));
                break;
            case 3:
                tileset.setTextureRect(sf::IntRect(30, 10, 10, 10));
                break;
            case 4:
                tileset.setTextureRect(sf::IntRect(40, 10, 10, 10));
                break;
            case 5:
                tileset.setTextureRect(sf::IntRect(50, 10, 10, 10));
                break;
            case 6:
                tileset.setTextureRect(sf::IntRect(30, 20, 10, 10));
                break;
            case 7:
                tileset.setTextureRect(sf::IntRect(40, 20, 10, 10));
                break;
            case 8:
                tileset.setTextureRect(sf::IntRect(50, 20, 10, 10));
                break;
            case 9:
                tileset.setTextureRect(sf::IntRect(0, 0, 10, 10));
                break;
            case 10:
                tileset.setTextureRect(sf::IntRect(10, 0, 10, 10));
                break;
            case 11:
                tileset.setTextureRect(sf::IntRect(20, 0, 10, 10));
                break;
            case 12:
                tileset.setTextureRect(sf::IntRect(0, 10, 10, 10));
                break;
            case 13:
                tileset.setTextureRect(sf::IntRect(10, 10, 10, 10));
                break;
            case 14:
                tileset.setTextureRect(sf::IntRect(20, 10, 10, 10));
                break;
            case 15:
                tileset.setTextureRect(sf::IntRect(0, 20, 10, 10));
                break;
            case 16:
                tileset.setTextureRect(sf::IntRect(10, 20, 10, 10));
                break;
            case 17:
                tileset.setTextureRect(sf::IntRect(20, 20, 10, 10));
                break;
            default:
                tileset.setTextureRect(sf::IntRect(40, 10, 10, 10));
                break;
            }
            tileset.setPosition(sf::Vector2f(x*60+decalageX, y*60+decalageY));
            fenetre->draw(tileset);
        }
    }
}

void changeMapValue(int *plan, int largeurMap, int hauteurMap, int x, int y, int tileSelected, int decalageX, int decalageY)
{
    int k=0;
    int j=0;
    for(k=0; k<hauteurMap; k++)
    {
        for(j=0; j<largeurMap; j++)
        {
            if(isClickOn(x, y, j*DIMENSION+decalageX, k*DIMENSION+decalageY, DIMENSION, DIMENSION))
            {
                plan[k*largeurMap+j]=tileSelected;
            }
        }
    }
}

void editor(int *plan, sf::Sprite tileset, sf::RenderWindow *fenetre, char *mapName)
{
    int tileSelected=0;
    int boutonCoord[][2]= {{1,1},{23,1},{12,1}};
    int isOpen=1;
    while(isOpen==1 and fenetre->isOpen())
    {
        fenetre->clear();
        sf::Event event;

        while(fenetre->pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                fenetre->close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code==sf::Keyboard::Return)
                {
                    isOpen=0;
                    char filePath[100];
                    strcpy(filePath, "ressources\\map\\");
                    strcat(filePath, mapName);
                    ofstream fichier(filePath, ios::out | ios::trunc);
                    int k=0;
                    for(k=0; k<10*10; k++)
                    {
                        if(plan[k]>=10)
                        {
                            fichier<<(char)(plan[k]+48);
                        }
                        else
                        {
                            fichier<<plan[k];
                        }
                    }
                    fichier.close();
                    ofstream fichierListe("ressources\\map\\listemap.txt", ios::out | ios::app);
                    fichierListe<<"\n";
                    fichierListe<<mapName;
                    fichierListe.close();
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button==sf::Mouse::Left)
                {
                    if(isClickOn(event.mouseButton.x, event.mouseButton.y, boutonCoord[0][0], boutonCoord[0][1], DIMENSION, DIMENSION) && tileSelected>0)
                    {
                        tileSelected-=1;
                    }
                    else if (isClickOn(event.mouseButton.x, event.mouseButton.y, boutonCoord[1][0], boutonCoord[1][1], DIMENSION, DIMENSION) && tileSelected<17)
                    {
                        tileSelected+=1;
                    }
                    else
                    {
                        changeMapValue(plan, 10, 10, event.mouseButton.x, event.mouseButton.y, tileSelected, 35, 20);
                    }
                }
            }
        }
        tileset.setTextureRect(sf::IntRect(50, 30, 10, 10));
        tileset.setPosition(boutonCoord[1][0],boutonCoord[1][1]);
        fenetre->draw(tileset);
        tileset.setTextureRect(sf::IntRect(50, 40, 10, 10));
        tileset.setPosition(boutonCoord[0][0],boutonCoord[0][1]);
        fenetre->draw(tileset);
        switch(tileSelected)
        {
        case 0:
            tileset.setTextureRect(sf::IntRect(30, 0, 10, 10));
            break;
        case 1:
            tileset.setTextureRect(sf::IntRect(40, 0, 10, 10));
            break;
        case 2:
            tileset.setTextureRect(sf::IntRect(50, 0, 10, 10));
            break;
        case 3:
            tileset.setTextureRect(sf::IntRect(30, 10, 10, 10));
            break;
        case 4:
            tileset.setTextureRect(sf::IntRect(40, 10, 10, 10));
            break;
        case 5:
            tileset.setTextureRect(sf::IntRect(50, 10, 10, 10));
            break;
        case 6:
            tileset.setTextureRect(sf::IntRect(30, 20, 10, 10));
            break;
        case 7:
            tileset.setTextureRect(sf::IntRect(40, 20, 10, 10));
            break;
        case 8:
            tileset.setTextureRect(sf::IntRect(50, 20, 10, 10));
            break;
        case 9:
            tileset.setTextureRect(sf::IntRect(0, 0, 10, 10));
            break;
        case 10:
            tileset.setTextureRect(sf::IntRect(10, 0, 10, 10));
            break;
        case 11:
            tileset.setTextureRect(sf::IntRect(20, 0, 10, 10));
            break;
        case 12:
            tileset.setTextureRect(sf::IntRect(0, 10, 10, 10));
            break;
        case 13:
            tileset.setTextureRect(sf::IntRect(10, 10, 10, 10));
            break;
        case 14:
            tileset.setTextureRect(sf::IntRect(20, 10, 10, 10));
            break;
        case 15:
            tileset.setTextureRect(sf::IntRect(0, 20, 10, 10));
            break;
        case 16:
            tileset.setTextureRect(sf::IntRect(10, 20, 10, 10));
            break;
        case 17:
            tileset.setTextureRect(sf::IntRect(20, 20, 10, 10));
            break;
        default:
            tileset.setTextureRect(sf::IntRect(30, 0, 10, 10));
            break;
        }
        tileset.setPosition(boutonCoord[2][0],boutonCoord[2][1]);
        fenetre->draw(tileset);

        drawMap(plan, 10, 10, tileset, fenetre, 35, 20);

        fenetre->display();
    }
}

int findLetter(char lettre)
{
    int numLettre=29;

    switch(lettre)
    {
    case 'a':
        numLettre=0;
        break;
    case 'b':
        numLettre=1;
        break;
    case 'c':
        numLettre=2;
        break;
    case 'd':
        numLettre=3;
        break;
    case 'e':
        numLettre=4;
        break;
    case 'f':
        numLettre=5;
        break;
    case 'g':
        numLettre=6;
        break;
    case 'h':
        numLettre=7;
        break;
    case 'i':
        numLettre=8;
        break;
    case 'j':
        numLettre=9;
        break;
    case 'k':
        numLettre=10;
        break;
    case 'l':
        numLettre=11;
        break;
    case 'm':
        numLettre=12;
        break;
    case 'n':
        numLettre=13;
        break;
    case 'o':
        numLettre=14;
        break;
    case 'p':
        numLettre=15;
        break;
    case 'q':
        numLettre=16;
        break;
    case 'r':
        numLettre=17;
        break;
    case 's':
        numLettre=18;
        break;
    case 't':
        numLettre=19;
        break;
    case 'u':
        numLettre=20;
        break;
    case 'v':
        numLettre=21;
        break;
    case 'w':
        numLettre=22;
        break;
    case 'x':
        numLettre=23;
        break;
    case 'y':
        numLettre=24;
        break;
    case 'z':
        numLettre=25;
        break;
    case '.':
        numLettre=26;
        break;
    case ':':
        numLettre=27;
        break;
    case '0':
        numLettre=30;
        break;
    case '1':
        numLettre=31;
        break;
    case '2':
        numLettre=32;
        break;
    case '3':
        numLettre=33;
        break;
    case '4':
        numLettre=34;
        break;
    case '5':
        numLettre=35;
        break;
    case '6':
        numLettre=36;
        break;
    case '7':
        numLettre=37;
        break;
    case '8':
        numLettre=38;
        break;
    case '9':
        numLettre=39;
        break;
    default:
        numLettre=29;
        break;
    }
    return numLettre;
}

void MachineAEcrire(sf::Sprite fontTile, sf::RenderWindow *fenetre, char* texte, int posX, int posY, float taille)
{
    int i=0;
    int lettre=0;
    for(i=0; texte[i] != '\0'; i++)
    {
        texte[i]=tolower(texte[i]);
        lettre=findLetter(texte[i]);
        fontTile.setTextureRect(sf::IntRect((lettre%10)*DIMENSIONLETTRE, (lettre/10)*DIMENSIONLETTRE, DIMENSIONLETTRE, DIMENSIONLETTRE));
        fontTile.setScale(taille, taille);
        fontTile.setPosition(posX+i*(DIMENSIONLETTRE*taille), posY);
        fenetre->draw(fontTile);
    }
}

void InGame(sf::RenderWindow *fenetre, int *planMap, sf::Sprite spriteTexture, sf::Sprite spriteTexte, sf::Sprite spriteCurseur)
{
    sf::Event event;
    sf::Vector2i mousePos;

    int score = 0;
    char scoreTXT[100] = "Score : ";
    int curseurScore=0;

    char vagueTXT[100]="Vague : ";

    sf::Clock clock;
    sf::Time temps=sf::seconds(4.0);

    srand(time(NULL));
    int rayon=100, originx=385, originy=275, skin=0, etat=0, nbboule=-1,i, j;
    float angle=0, attaqueTeleportation, attaqueInvincible, attaqueFireball, dirx, diry;
    sf::Sprite spriteBoss, spriteFireball;
    sf::Time tempstp;
    tempstp=sf::seconds(7.0);
    sf::Clock clocktp;
    sf::Texture textureBoss, textureBoss2, textureFireball;
    if (!textureBoss.loadFromFile("ressources/textureboss1.png"))
        printf("Erreur !");
    if (!textureBoss2.loadFromFile("ressources/textureboss2.png"))
        printf("Erreur !");
    Boss skullBoss;

    sf::SoundBuffer bufferFireball;
    sf::Sound sonFireball;

    if (!bufferFireball.loadFromFile("ressources/fire.wav"))
        printf("Erreur de chargement du son de fire");
    sonFireball.setBuffer(bufferFireball);
    sonFireball.setVolume(100);

    spriteBoss.setTexture(textureBoss);
    spriteBoss.setTextureRect(sf::IntRect(0,0,30,30));
    spriteBoss.setPosition(skullBoss.get_posx(),skullBoss.get_posy());
    spriteBoss.setScale(sf::Vector2f(2.0f,2.0f));
    Fireball fireball[20];

    ennemy vague[20];
    int max=20, slime_etat=0, nb_nonActif, k, retourMenu=0, nbMorts=0, nbVagues=1, nbEnnemiSupp=0;
    sf::Sprite spriteSlime, spriteMage, spriteFireball_mage;
    sf::Texture textureSlime, textureSlime2, textureMage, textureFireball_mage;
    if (!textureFireball_mage.loadFromFile("ressources/fireball_mage.png"))
        printf("Problème\n");
    if (!textureSlime.loadFromFile("ressources/slime.png"))
        printf("Problème\n");
    if (!textureSlime2.loadFromFile("ressources/slime2.png"))
        printf("Problème\n");
    if (!textureMage.loadFromFile("ressources/mage.png"))
        printf("Problème\n");
    spriteSlime.setTexture(textureSlime);
    spriteFireball_mage.setTexture(textureFireball_mage);
    spriteMage.setTexture(textureMage);

    int pas_droite, pas_gauche, pas_haut, pas_bas;
    int pas=3, aleat;
    int slimeStep=5;

    for (i=0; i<3; i++)
    {
        vague[i].setPosition(240+40*i, 80+40*i);
        vague[i].setActif(1);
        vague[i].setType(0);
        vague[i].setZone(0);
        if (i==2)
        {
            vague[i].setType(1);
            vague[i].setZone(100);
        }
    }

    spriteTexture.scale(sf::Vector2f(2.0f, 2.0f));

    heros ninja(160, 160, 3, 100);

    while(fenetre->isOpen() && retourMenu==0)
    {
        if (clock.getElapsedTime()>temps)
        {
            clock.restart();
            aleat=rand()%4;
            for (j=0; j<3; j++)
            {
                for(i=0; i<max; i++)
                {
                    if(vague[i].isActif()==0)
                    {
                        if (aleat==0)
                        {
                            vague[i].setPosition(0,200+((j)*20));
                        }
                        else if (aleat==1)
                        {
                            vague[i].setPosition(500+((j)*20), 240);
                        }
                        else if (aleat==2)
                        {
                            vague[i].setPosition(240,500+((j)*20));
                        }
                        else if (aleat==3)
                        {
                            vague[i].setPosition(240+((j)*20),10);
                        }
                        vague[i].setActif(1);
                        vague[i].setType(0);
                        vague[i].setZone(0);
                        if (int a = rand()%10<2)
                        {
                            vague[i].setType(1);
                            vague[i].setZone(100);
                        }
                        break;
                    }
                }
            }
            max=max+3;
        }
        if (slimeStep <= 0)
        {
            slimeStep = 2;
        }
        else
        {
            slimeStep -= 1;
        }
        nb_nonActif=0;
        while(fenetre->pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code==sf::Keyboard::P)
                {
                    PauseJeu(fenetre, spriteTexte, &retourMenu, spriteCurseur);
                }

                break;
            case sf::Event::Closed:
                fenetre->close();
                break;
            case sf::Event::MouseButtonPressed:
                ninja.setIsSlash(400);
                break;
            default:
                break;
            }
        }
        mousePos = sf::Mouse::getPosition(*fenetre);
        deplacementSouris(&ninja, mousePos.x, mousePos.y, planMap, vague, &score, &nbMorts, fireball, nbboule);
        setTexureRectNinja(&spriteTexture, ninja.getWalkStep(), ninja.getSlashStep());
        spriteTexture.setPosition(ninja.getX()-20,ninja.getY()-20);

        /*if (etat==0)
        {
            spriteBoss.setTextureRect(sf::IntRect(0,0,30,30));
        }
        else if (etat==1)
        {
            spriteBoss.setTextureRect(sf::IntRect(30,0,30,30));
        }
        else if (etat==2)
        {
            spriteBoss.setTextureRect(sf::IntRect(60,0,30,30));
        }


        if (etat==0 && skin==5)
        {
            etat=1;
            skin=0;
        }
        else if (etat==1 && skin==5)
        {
            etat=2;
            skin=0;
        }
        else if (etat==2 && skin==5)
        {
            etat=0;
            skin=0;
        }
        skin++;
        */

        fenetre->clear();
        drawMapGame(planMap, 10, 10, spriteTexture,  fenetre, 0, 0);

        scoreTXT[7]=(char)(score/1000)+48;
        scoreTXT[8]=(char)((score-(score/1000)*1000)/100)+48;
        scoreTXT[9]=(char)((score-(score/100)*100)/10)+48;
        scoreTXT[10]=(char)(score-(score/10)*10)+48;

        vagueTXT[7]=(char)(nbVagues/1000)+48;
        vagueTXT[8]=(char)((nbVagues-(nbVagues/1000)*1000)/100)+48;
        vagueTXT[9]=(char)((nbVagues-(nbVagues/100)*100)/10)+48;
        vagueTXT[10]=(char)(nbVagues-(nbVagues/10)*10)+48;

        if (nbMorts>=3+nbEnnemiSupp)
        {
            nbVagues++;
            nbMorts=0;
            nbEnnemiSupp=nbEnnemiSupp+3;
        }

        MachineAEcrire(spriteTexte, fenetre, scoreTXT, 610, 100, 0.8);
        MachineAEcrire(spriteTexte, fenetre, vagueTXT, 610, 200, 0.8);

        if (ninja.getLife()==0)
        {
            retourMenu=1;
            EcranDefaite(fenetre, scoreTXT, vagueTXT, spriteTexte);
        }
        /*if (nbVagues%5==0)
        {
            for (i=0; i<max; i++)
            {
                vague[i].setActif(0);

            }
            vagueBoss(&skullBoss, &angle, &nbboule, fireball, &clocktp, tempstp, &clock, temps,  originx,  originy,  rayon);
            if (skullBoss.estInvincible()==true)
                spriteBoss.setTexture(textureBoss2);
            else
                spriteBoss.setTexture(textureBoss);
            spriteBoss.setPosition(skullBoss.get_posx(),skullBoss.get_posy());
            fenetre->draw(spriteBoss);
        }*/

        for (i=0; i<max; i++)
        {
            pas_haut=1;
            pas_bas=1;
            pas_gauche=1;
            pas_droite=1;

            if(vague[i].isActif()==1)
            {
                for (k=0; k<pas; k++)
                {
                    if(slimeStep == 0)
                    {
                        for (j=0; j<max; j++)
                        {
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
                    }
                    else
                    {
                        pas_bas=0;
                        pas_droite=0;
                        pas_gauche=0;
                        pas_haut=0;
                    }
                    if (ninja.getX()-vague[i].get_x()>0-vague[i].getZone() && pas_droite!=0)
                    {
                        vague[i].setPosition(vague[i].get_x()+1, vague[i].get_y());
                    }
                    if (ninja.getX()-vague[i].get_x()<0+vague[i].getZone() && pas_gauche!=0)
                    {
                        vague[i].setPosition(vague[i].get_x()-1, vague[i].get_y());
                    }
                    if (ninja.getY()-vague[i].get_y()>0-vague[i].getZone() && pas_bas!=0)
                    {
                        vague[i].setPosition(vague[i].get_x(), vague[i].get_y()+1);
                    }
                    if (ninja.getY()-vague[i].get_y()<0+vague[i].getZone()  && pas_haut!=0)
                    {
                        vague[i].setPosition(vague[i].get_x(), vague[i].get_y()-1);
                    }
                    if (vague[i].getType()==1)
                    {
                        spriteMage.setPosition(vague[i].get_x(), vague[i].get_y());
                    }
                    else
                    {
                        spriteSlime.setPosition(vague[i].get_x(), vague[i].get_y());
                    }
                }
                float b = (float)rand()/(RAND_MAX);
                if (nbboule<20 && b<0.01 && vague[i].getType()==1 && vague[i].isActif()==1)
                {
                    nbboule++;
                    fireball[nbboule].set_posx(vague[i].get_x());
                    fireball[nbboule].set_posy(vague[i].get_y());
                    fireball[nbboule].set_directionx(fireball[nbboule].calculeDirectionx(ninja.getX(), ninja.getY()));
                    fireball[nbboule].set_directiony(fireball[nbboule].calculeDirectiony(ninja.getX(), ninja.getY()));
                    spriteFireball_mage.setPosition(fireball[nbboule].get_posx(), fireball[nbboule].get_posy());
                    sonFireball.play();
                }
            }
            if(vague[i].isActif()==1)
            {
                if (vague[i].getType()==0)
                    fenetre->draw(spriteSlime);
                else
                    fenetre->draw(spriteMage);
            }
        }
        if (nbboule!=-1)
        {
            for(i=0; i<nbboule; i++)
            {
                fireball[i].set_posx(fireball[i].get_posx()+fireball[i].get_directionx()*5);
                fireball[i].set_posy(fireball[i].get_posy()+fireball[i].get_directiony()*5);
                spriteFireball_mage.setPosition(fireball[i].get_posx(), fireball[i].get_posy());
                if ((fireball[i].get_posx()>600 || fireball[i].get_posy()>600) || (fireball[i].get_posx()<0 || fireball[i].get_posy()<0))
                {
                    fireball[i].~Fireball();
                    nbboule--;
                    for (j=i; j<nbboule+1; j++)
                    {
                        fireball[j]=fireball[j+1];
                    }
                }
                fenetre->draw(spriteFireball_mage);
            }

        }
        fenetre->draw(spriteTexture);
        fenetre->display();
    }
    spriteTexture.scale(sf::Vector2f(1.0f, 1.0f));
}


void Jouer(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre, char *nomMap, int *carte)
{
    int exitVar = 0;
    char informations[]="Entrez le nom de la map a charger";
    char astuce[]="La touche TAB ajoute le .map";
    while (exitVar == 0 and fenetre->isOpen())
    {
        char chemin[]="ressources/map/";
        fenetre->clear();
        MachineAEcrire(tileTexte, fenetre, informations, 30, 10, 0.6f);
        MachineAEcrire(tileTexte, fenetre, astuce, 40, 23, 0.6f);
        fenetre->display();
        fenetre->clear();
        MachineAEcrire(tileTexte, fenetre, informations, 30, 10, 0.6f);
        MachineAEcrire(tileTexte, fenetre, astuce, 40, 23, 0.6f);
        fenetre->display();
        scanGraphique(nomMap, tileTexte, fenetre, 20,70, 0.6f);
        fenetre->display();
        strcat(chemin, nomMap);
        FILE* fichierMap=NULL;
        fichierMap = fopen(chemin, "r");
        if(fichierMap==NULL)
        {
            printf("Impossible d'ouvrir le fichier\n");
        }
        else
        {
            int k=0;
            for(k=0; k<100; k++)
            {
                carte[k]=(int)(fgetc(fichierMap)-48);
            }
            fclose(fichierMap);
            exitVar=1;
        }
    }
}

ennemy::ennemy() : e_vie(0), e_x(0), e_y(0), e_type(0), e_actif(0)
{

}

ennemy::ennemy(int m_vie, int m_x, int m_y) : e_vie(m_vie), e_x(m_x), e_y(m_y), e_type(0), e_actif(0)
{

}

void ennemy::setPosition(int m_x, int m_y)
{
    e_x=m_x;
    e_y=m_y;
}

int ennemy::getType()
{
    return e_type;
}

void ennemy::setType(int new_type)
{
    e_type=new_type;
}

void ennemy::setZone(int new_zone)
{
    e_zone=new_zone;
}

int ennemy::getZone()
{
    return e_zone;
}

int ennemy::get_x()
{
    return e_x;
}

int ennemy::get_y()
{
    return e_y;
}

void ennemy::setActif(int m_actif)
{
    e_actif=m_actif;
}

int ennemy::isActif()
{
    return e_actif;
}

bool collision_haut (int posx_p, int posy_p, int posx_ia, int posy_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    if (posy_p<=posy_ia+hauteur_ia && posx_p+largeur_p>=posx_ia && posx_p<=posx_ia+largeur_ia && posy_p>=posy_ia+hauteur_ia-1)
        return true;
    else
        return false;
}

bool collision_bas (int posx_p, int posy_p, int posx_ia, int posy_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    if (posy_p+hauteur_p>=posy_ia && posx_p+largeur_p>=posx_ia && posx_p<=posx_ia+largeur_ia && posy_p+hauteur_p<=posy_ia+1)
        return true;
    else
        return false;
}

bool collision_droite (int posx_p, int posy_p, int posx_ia, int posy_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    if (posx_p+largeur_p>=posx_ia && posy_p+hauteur_p>=posy_ia && posx_p+largeur_p<=posx_ia+1 && posy_p<=posy_ia+hauteur_ia)
        return true;
    else
        return false;
}

bool collision_gauche (int posx_p, int posy_p, int posx_ia, int posy_ia, int largeur_p, int hauteur_p, int largeur_ia, int hauteur_ia)
{
    if (posx_p<=posx_ia+largeur_ia && posx_p>=posx_ia+largeur_ia-1 && posy_p+hauteur_p>=posy_ia && posy_p<=posy_ia+hauteur_ia)
        return true;
    else
        return false;
}

void ennemy::changePas(int m_pas)
{
    e_pas=m_pas;
}

int ennemy::getPas()
{
    return e_pas;
}

heros::heros() : h_x(0), h_y(0), h_speed(0), h_life(0), h_angle(0), h_walkStep(0), h_isSlash(0)
{

}

heros::heros(int m_x, int m_y, int m_speed, int m_life) : h_x(m_x), h_y(m_y), h_speed(m_speed), h_life(m_life), h_angle(0), h_walkStep(0), h_isSlash(0)
{

}

void heros::setPosition(int m_x, int m_y)
{
    h_x=m_x;
    h_y=m_y;
}

void heros::setX(int m_x)
{
    h_x=m_x;
}

void heros::setY(int m_y)
{
    h_y=m_y;
}

void heros::setSpeed(int m_speed)
{
    h_speed=m_speed;
}

void heros::setLife(int m_life)
{
    h_life=m_life;
}

void heros::findAngle(int mouse_x, int mouse_y)
{
    h_angle=atan2((h_y-mouse_y),(h_x-mouse_x));
}

void heros::setWalkStep(int m_walkStep)
{
    m_walkStep=h_walkStep;
}

void heros::setIsSlash(int m_slash)
{
    if(h_isSlash<=0)
        h_isSlash=m_slash;
}

int heros::getX()
{
    return h_x;
}

int heros::getY()
{
    return h_y;
}

int heros::getSpeed()
{
    return h_speed;
}

int heros::getLife()
{
    return h_life;
}

float heros::getAngle()
{
    return h_angle;
}

int heros::getWalkStep()
{
    return h_walkStep;
}

int heros::getSlashStep()
{
    return h_isSlash;
}

void heros::walkX(int m_x)
{
    if(h_isSlash>0)
    {
        h_isSlash-=1;
        if(h_isSlash>200)
        {
            h_speed=40;
        }
        else
        {
            h_speed=3;
        }
    }
    if(m_x>0)
    {
        if(h_walkStep==6)
        {
            h_walkStep=7;
        }
        else
        {
            h_walkStep=6;
        }
    }
    else
    {
        if(h_walkStep==4)
        {
            h_walkStep=5;
        }
        else
        {
            h_walkStep=4;
        }
    }
    h_x+=m_x;
}

void heros::walkY(int m_y)
{
    if(h_isSlash>0)
    {
        h_isSlash-=1;
        if(h_isSlash>200)
        {
            h_speed=40;
        }
        else
        {
            h_speed=3;
        }
    }
    if(m_y>0)
    {
        if(h_walkStep==0)
        {
            h_walkStep=1;
        }
        else
        {
            h_walkStep=0;
        }
    }
    else
    {
        if(h_walkStep==2)
        {
            h_walkStep=3;
        }
        else
        {
            h_walkStep=2;
        }
    }
    h_y+=m_y;
}

void setTexureRectNinja(sf::Sprite* spriteGeneral, int ninjaWalkStep, int slash)
{
    if(slash<200)
    {
        switch(ninjaWalkStep)
        {
        case 0:
            spriteGeneral->setTextureRect(sf::IntRect(60, 0, 20, 20));
            break;
        case 1:
            spriteGeneral->setTextureRect(sf::IntRect(80, 0, 20, 20));
            break;
        case 2:
            spriteGeneral->setTextureRect(sf::IntRect(60, 20, 20, 20));
            break;
        case 3:
            spriteGeneral->setTextureRect(sf::IntRect(80, 20, 20, 20));
            break;
        case 4:
            spriteGeneral->setTextureRect(sf::IntRect(80, 0, -20, 20));
            break;
        case 5:
            spriteGeneral->setTextureRect(sf::IntRect(80, 0, -20, 20));
            break;
        case 6:
            spriteGeneral->setTextureRect(sf::IntRect(60, 0, 20, 20));
            break;
        case 7:
            spriteGeneral->setTextureRect(sf::IntRect(80, 0, 20, 20));
            break;
        default:
            spriteGeneral->setTextureRect(sf::IntRect(60, 0, 20, 20));
            break;
        }
    }
    else
    {
        switch(ninjaWalkStep)
        {
        case 0:
            spriteGeneral->setTextureRect(sf::IntRect(120, 20, 20, 20));
            break;
        case 1:
            spriteGeneral->setTextureRect(sf::IntRect(120, 20, 20, 20));
            break;
        case 2:
            spriteGeneral->setTextureRect(sf::IntRect(100, 20, 20, 20));
            break;
        case 3:
            spriteGeneral->setTextureRect(sf::IntRect(100, 20, 20, 20));
            break;
        case 4:
            spriteGeneral->setTextureRect(sf::IntRect(120, 0, -20, 20));
            break;
        case 5:
            spriteGeneral->setTextureRect(sf::IntRect(120, 0, -20, 20));
            break;
        case 6:
            spriteGeneral->setTextureRect(sf::IntRect(100, 0, 20, 20));
            break;
        case 7:
            spriteGeneral->setTextureRect(sf::IntRect(100, 0, 20, 20));
            break;
        default:
            spriteGeneral->setTextureRect(sf::IntRect(120, 20, 20, 20));
            break;
        }
    }
}

void writeDebugMap(int ninjaX, int ninjaY, int*plan)
{
    printf("map : \n\n");

    int i=0;
    int j=0;
    int posX=ninjaX/60;
    int posY=ninjaY/60;
    int numCase=0;

    for (i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            numCase=j+i*10;
            numCase=plan[numCase];
            if(posX==j && posY==i)
            {
                printf("  n ");
            }
            else
            {
                if(numCase<10)
                {
                    printf("  %i ", numCase);
                }
                else
                {
                    printf(" %i ", numCase);
                }
            }
        }
        printf("\n");
    }

    printf("\n---------------------\n");
}

int collisionNinjaMur(int ninjaX, int ninjaY, int* plan, int direction)
{
    int tailleCase = 60;
    int nbCase = 10;
    int caseUP=plan[((ninjaX/tailleCase))+(((ninjaY-1)/tailleCase)*nbCase)];
    int caseDOWN=plan[((ninjaX)/tailleCase)+(((ninjaY+40)/tailleCase)*nbCase)];
    int caseLEFT=plan[((ninjaX-1)/tailleCase)+((ninjaY/tailleCase)*nbCase)];
    int caseRIGHT=plan[((ninjaX+40)/tailleCase)+((ninjaY/tailleCase)*nbCase)];
    int retour=0;
    int k=0;
    switch(direction)
    {
    case 0:
        for(k=-9; k<20; k++)
        {
            caseUP=plan[(((ninjaX+k)/tailleCase))+(((ninjaY-21)/tailleCase)*nbCase)];
            if(caseUP!=4 && caseUP<9)
            {
                retour=1;
            }
            if(((ninjaY-22)/tailleCase) < 0)
            {
                retour = 1;
            }
        }
        break;
    case 1:
        for(k=-9; k<10; k++)
        {
            caseDOWN=plan[((ninjaX+k)/tailleCase)+(((ninjaY+21)/tailleCase)*nbCase)];
            if(caseDOWN!=4 && caseDOWN<9)
            {
                retour= 1;
            }
            if(((ninjaY+22)/tailleCase) >= nbCase)
            {
                retour = 1;
            }
        }
        break;
    case 2:
        for(k=-20; k<20; k++)
        {
            caseLEFT=plan[((ninjaX-10)/tailleCase)+(((ninjaY+k)/tailleCase)*nbCase)];
            if(caseLEFT!=4 && caseLEFT<9)
            {
                retour= 1;
            }
            if(((ninjaX-11)/tailleCase) < 0)
            {
                retour = 1;
            }
        }
        break;
    case 3:
        for(k=-20; k<20; k++)
        {
            caseRIGHT=plan[((ninjaX+10)/tailleCase)+(((ninjaY+k)/tailleCase)*nbCase)];
            if(caseRIGHT!=4 && caseRIGHT<9)
            {
                retour= 1;
            }
            if(((ninjaX+11)/tailleCase) >= nbCase)
            {
                retour = 1;
            }
        }
        break;
    default:
        retour= 0;
        break;
    }
    return retour;
}

void deplacementSouris(heros* ninja, int mouseX, int mouseY, int* plan, ennemy* vague, int* score, int* nbMorts, Fireball* tabFireball, int nbboule)
{
    int k=0;
        for(k=0; k<ninja->getSpeed(); k++)
        {
            int distanceY=abs(mouseY-ninja->getY());
            int distanceX=abs(mouseX-ninja->getX());

            if(ninja->getSlashStep() > 200)
            {
                distanceY = -sin(ninja->getAngle())*100;
                distanceX = -cos(ninja->getAngle())*100;
                mouseX = ninja->getX()+distanceX;
                mouseY = ninja->getY()+distanceY;
            }
            else
            {
                ninja->findAngle(mouseX, mouseY);
            }
            int i=0;
            for(i=0; i<MAXENNEMY; i++)
            {
                if(vague[i].get_x() > ninja->getX()-10 && vague[i].get_x() < ninja->getX()+10 && vague[i].get_y() > ninja->getY()-20 && vague[i].get_y() < ninja->getY()+20)
                {
                    if(ninja->getSlashStep()>200)
                        {
                    if(vague[i].isActif() == 1)
                    {
                        if(vague[i].getType()==0)
                        {
                            *score += 10;
                        }
                        else
                        {
                            *score += 4;
                        }
                    (*nbMorts)++;
                    }
                    vague[i].setActif(0);
                        }
                        else
                        {
                            ninja->setLife(0);
                        }
                }
            }
            for (i=0;i<nbboule;i++)
            {
                if (tabFireball[i].get_posx() > ninja->getX()-10 && tabFireball[i].get_posx() < ninja->getX()+10 && tabFireball[i].get_posy() > ninja->getY()-20 && tabFireball[i].get_posy() < ninja->getY()+20)
                {
                    if (ninja->getSlashStep()<200)
                    {
                        ninja->setLife(0);
                    }
                }
            }
            if(distanceY > distanceX && (abs(distanceX)>5 || abs(distanceY)>5))
            {
                if(mouseY>ninja->getY() && collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 1)==0)
                {
                    ninja->walkY(1);
                }
                else if(collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 0)==0)
                {
                    ninja->walkY(-1);
                }

                if(mouseX>ninja->getX() && collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 3)==0)
                {
                    ninja->walkX(1);
                }
                else if(collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 2)==0)
                {
                    ninja->walkX(-1);
                }

                if(mouseY>ninja->getY()  && collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 1)==0)
                {
                    ninja->walkY(1);
                }
                else if(collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 0)==0)
                {
                    ninja->walkY(-1);
                }
            }
            else if(abs(distanceX)>5 || abs(distanceY)>5)
            {
                if(mouseX>ninja->getX() && collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 3)==0)
                {
                    ninja->walkX(1);
                }
                else if(collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 2)==0)
                {
                    ninja->walkX(-1);
                }
                if(mouseY>ninja->getY() && collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 1)==0)
                {
                    ninja->walkY(1);
                }
                else if(collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 0)==0)
                {
                    ninja->walkY(-1);
                }

                if(mouseX>ninja->getX() && collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 3)==0)
                {
                    ninja->walkX(1);
                }
                else if(collisionNinjaMur(ninja->getX(), ninja->getY(), plan, 2)==0)
                {
                    ninja->walkX(-1);
                }
            }
        }
}

Fireball::Fireball() : m_posx(0), m_posy(0), m_pas(0)
{

}

Fireball::~Fireball()
{
}

int Fireball::get_posx()
{
    return m_posx;
}

int Fireball::get_posy()
{
    return m_posy;
}

int Fireball::get_pas()
{
    return m_pas;
}

void Fireball::set_pas(int new_pas)
{
    m_pas=new_pas;
}

void Fireball::set_posx(int new_x)
{
    m_posx=new_x;
}

void Fireball::set_posy(int new_y)
{
    m_posy=new_y;
}

double Fireball::calculeDirectionx(int cible_x, int cible_y)
{
    double angle=atan2(cible_y-m_posy, cible_x-m_posx);
    return cos(angle);
}

double Fireball::calculeDirectiony(int cible_x, int cible_y)
{
    double angle=atan2(cible_y-m_posy, cible_x-m_posx);
    return sin(angle);
}

void Fireball::set_directionx(double new_directionx)
{
    m_directionx=new_directionx;
}

void Fireball::set_directiony(double new_directiony)
{
    m_directiony=new_directiony;
}

double Fireball::get_directionx()
{
    return m_directionx;
}
double Fireball::get_directiony()
{
    return m_directiony;
}

Boss::Boss() : m_posx(385), m_posy(275), m_estInvincible(false), m_vie(3)
{

}

void Boss::setInvincible(bool inv)
{
    m_estInvincible=inv;
}

bool Boss::estInvincible() const
{
    return m_estInvincible;
}

void Boss::set_posx(int new_posx)
{
    m_posx=new_posx;
}

void Boss::set_posy(int new_posy)
{
    m_posy=new_posy;
}

int Boss::get_posx()
{
    return m_posx;
}

int Boss::get_posy()
{
    return m_posy;
}

void Boss::recevoirDegats()
{
    m_vie-=1;
}

void vagueBoss(Boss *boss, float *angle, int *nbboule, Fireball* tabFireball, sf::Clock *clocktp, sf::Time tempstp, sf::Clock *clock, sf::Time temps, int originx, int originy, int rayon)
{
    float attaqueTeleportation, attaqueInvincible, attaqueFireball, dirx, diry;
    attaqueTeleportation=(float)rand()/(float)(RAND_MAX);
    attaqueInvincible=(float)rand()/(float)(RAND_MAX);
    attaqueFireball=(float)rand()/(float)(RAND_MAX);
    if (*angle>6.3)
        *angle=0.03;
    if (attaqueFireball<=0.05 && *nbboule<20)
    {
        *nbboule=*nbboule+1;
        tabFireball[*nbboule].set_posx(boss->get_posx());
        tabFireball[*nbboule].set_posy(boss->get_posy());
        dirx=rand()%800;
        diry=rand()%600;
        tabFireball[*nbboule].set_directionx(tabFireball[*nbboule].calculeDirectionx(dirx, diry));
        tabFireball[*nbboule].set_directiony(tabFireball[*nbboule].calculeDirectiony(dirx,diry));
    }
    if (attaqueTeleportation>=0.99 && clocktp->getElapsedTime()>tempstp)
    {
        angle=angle+3;
        clocktp->restart();
    }
    if (attaqueInvincible>=0.55 && attaqueInvincible<=0.56 && clock->getElapsedTime()>temps)
    {
        boss->setInvincible(true);
        clock->restart();
    }
    if (clock->getElapsedTime()>temps)
    {
        boss->setInvincible(false);
    }
    *angle=*angle+0.03;
    boss->set_posx(originx+cos(*angle)*rayon);
    boss->set_posy(originy+sin(*angle)*rayon);
}
