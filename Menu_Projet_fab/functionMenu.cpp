#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "functionMenu.hpp"


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
