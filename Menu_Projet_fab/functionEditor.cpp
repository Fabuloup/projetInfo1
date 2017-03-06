#include "functionEditor.hpp"
#include "fireball.hpp"
#include "functionMenu.hpp"

// demande dans l'invite de commande ce que souhaite faire l'utilisateur (editer ou creer une nouvelle map

void funcEditor(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre)
{
    sf::View vue(sf::FloatRect(0, 0, LARGEUR, HAUTEUR));
    vue.zoom(ZOOM);
    vue.setCenter((int)(LARGEUR*ZOOM)/2, (int)(HAUTEUR*ZOOM)/2);
    fenetre->setView(vue);
    int choixEdit =0;
    char NomMap[100]="";
    //choix de l'utilisateur (voir fonction)
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
    int position=0;//stock la position du curseur des choix dans le menu
    int finBoucle=0; //pour terminer la boucle quand l'utilisateur a fais son choix
    char titre[]="editeur de map";
    char choix1[]="creer une map";
    char choix2[]="editer une map";
    //75 touche gauche / 77 touche droite
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
//fonction qui permet au joueur de choisir sa map parmis celle qui existe déjà
void loadMap(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre, char *nomMap, int *carte)
{
    //exitVar passera a 1 quand le joueur aura choisi sa map
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
        //on ajoute le nom du dossier au nom de la map
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
                printf("%i\n", carte[k]);
            }
            fclose(fichierMap);
            exitVar=1;
        }
    }
}

void scanGraphique(char *texte,sf::Sprite tileText, sf::RenderWindow *fenetre, int posX, int posY, float taille)
{
    int position=0; //nous permet de connaitre notre posistion dans le mot
    int toContinue = 0; // pour sortir de la boucle lorsque l'utilisateur aura fini d'ecrire son mot
    char *lettreTapee; //le caractère tapé par l'utilisateur
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
//fonction pour tester si la souris est sur un bouton
bool isClickOn(int xToTest, int yToTest, int x, int y, int width, int height)
{
    //le zoom est de 0.15
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
    //tileset.scale(3.0f, 3.0f);
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

//on lui passe en parametres la map et la position de la souris et il peint la map
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

//l'editeur
void editor(int *plan, sf::Sprite tileset, sf::RenderWindow *fenetre, char *mapName)
{
    int tileSelected=0;
    //coordonnées des boutons
    //le troisième correspond à l'image du sprite
    int boutonCoord[][2]= {{1,1},{23,1},{12,1}};
    int isOpen=1;
    //les fleche remplace le point quand on passe la fenetre par pointeur
    //fenetre->setActive(true);
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
        //fleche droite
        tileset.setTextureRect(sf::IntRect(50, 30, 10, 10));
        tileset.setPosition(boutonCoord[1][0],boutonCoord[1][1]);
        fenetre->draw(tileset);
        //fleche gauche
        tileset.setTextureRect(sf::IntRect(50, 40, 10, 10));
        tileset.setPosition(boutonCoord[0][0],boutonCoord[0][1]);
        fenetre->draw(tileset);
        //tuile selectionner
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
    //fenetre->setActive(false);
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
        //passe en majuscule le lettre avant de trouver quel lettre c'est
        lettre=findLetter(texte[i]);
        fontTile.setTextureRect(sf::IntRect((lettre%10)*DIMENSIONLETTRE, (lettre/10)*DIMENSIONLETTRE, DIMENSIONLETTRE, DIMENSIONLETTRE));
        //permet de redimensionner les lettres
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

    //code Sylvain
    //Gestion timer
    sf::Clock clock;
    sf::Time temps=sf::seconds(4.0);
    //Tableau de boules de feu

    //variables boss
    srand(time(NULL));
    int rayon=100, originx=385, originy=275, skin=0, etat=0, nbboule=-1,i, j;
    float angle=0, attaqueTeleportation, attaqueInvincible, attaqueFireball, dirx, diry;
    sf::Sprite spriteBoss, spriteFireball;
    sf::Time tempstp;
    tempstp=sf::seconds(7.0);
    sf::Clock clocktp;
    sf::Texture textureBoss, textureBoss2, textureFireball;
    if (!textureBoss.loadFromFile("skullHeadbang.png"))
        printf("Erreur !");
    if (!textureBoss2.loadFromFile("skullHeadbang2.png"))
        printf("Erreur !");
    Boss skullBoss;

    spriteBoss.setTexture(textureBoss);
    spriteBoss.setTextureRect(sf::IntRect(0,0,30,30));
    spriteBoss.setPosition(skullBoss.get_posx(),skullBoss.get_posy());
    spriteBoss.setScale(sf::Vector2f(2.0f,2.0f));
    //fin variables boss

    Fireball fireball[20];

    ennemy vague[20];
    int max=20, slime_etat=0, nb_nonActif, k, retourMenu=0, nbMorts=0, nbVagues=1, nbEnnemiSupp=0;
    sf::Sprite spriteSlime, spriteMage, spriteFireball_mage;
    sf::Texture textureSlime, textureSlime2, textureMage, textureFireball_mage;
    if (!textureFireball_mage.loadFromFile("fireball_mage.png"))
        printf("Problème\n");
    if (!textureSlime.loadFromFile("slime.png"))
        printf("Problème\n");
    if (!textureSlime2.loadFromFile("slime2.png"))
        printf("Problème\n");
    if (!textureMage.loadFromFile("mage.png"))
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
    //Code Sylvain

    spriteTexture.scale(sf::Vector2f(2.0f, 2.0f));

    heros ninja(160, 160, 3, 100);

    while(fenetre->isOpen() && retourMenu==0)
    {

        //code Sylvain
        //Temps
        if (clock.getElapsedTime()>temps)
        {
            printf("time");
            clock.restart();
            aleat=rand()%4;
            printf("%i", aleat);
            for (j=0; j<3; j++)
            {
                for(i=0; i<max; i++)
                {
                    if(vague[i].isActif()==0)
                    {
                        if (aleat==0)
                        {
                            vague[i].setPosition(0,240+((i)*40));
                        }
                        else if (aleat==1)
                        {
                            vague[i].setPosition(500+((i)*40), 240);
                        }
                        else if (aleat==2)
                        {
                            vague[i].setPosition(240,500+((i)*40));
                        }
                        else if (aleat==3)
                        {
                            vague[i].setPosition(240+((i)*40),10);
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
        //test de l'état des slimes pour la texture
        /*if (slime_etat==0 and slimeStep<=0)
        {
            spriteSlime.setTexture(textureSlime);
            slimeStep = 10;
            slime_etat = 1;
        }
        else if (slime_etat==1 and slimeStep<=0)
        {
            spriteSlime.setTexture(textureSlime2);
            slimeStep = 10;
            slime_etat = 0;
        }
        else
            slimeStep-=1;*/
        if (slimeStep <= 0)
        {
            slimeStep = 2;
        }
        else
        {
            slimeStep -= 1;
        }

        nb_nonActif=0;
        //code Sylvain
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
            /*case sf::Event::MouseMoved:
                mousePos = sf::Mouse::getPosition(*fenetre);
                //printf("x : %i || y : %i\n", mousePos.x, mousePos.y);
                //600,600
                break;*/
            case sf::Event::MouseButtonPressed:
                ninja.setIsSlash(400);
                break;
            default:
                break;
            }
        }
        mousePos = sf::Mouse::getPosition(*fenetre);
        deplacementSouris(&ninja, mousePos.x, mousePos.y, planMap, vague, &score, &nbMorts);
        setTexureRectNinja(&spriteTexture, ninja.getWalkStep(), ninja.getSlashStep());
        spriteTexture.setPosition(ninja.getX()-20,ninja.getY()-20);

        //gestion boss
        if (etat==0)
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
        //fin gestion boss

        //code sylvain
        fenetre->clear();
        drawMapGame(planMap, 10, 10, spriteTexture,  fenetre, 0, 0);
        //on met à jour le score
        /*for(curseurScore=10; curseurScore<100; curseurScore++)
        {
            scoreTXT[k]=(char)((int)score/1000);
        }*/
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

        /*if (nbVagues%5==0)
        {
            for (i=0; i<max; i++)
            {
                vague[i].setActif(0);
                //printf("coucou");

            }
            vagueBoss(&skullBoss, &angle, &nbboule, fireball, &clocktp, tempstp, &clock, temps,  originx,  originy,  rayon);
            if (skullBoss.estInvincible()==true)
                spriteBoss.setTexture(textureBoss2);
            else
                spriteBoss.setTexture(textureBoss);
            spriteBoss.setPosition(skullBoss.get_posx(),skullBoss.get_posy());
            fenetre->draw(spriteBoss);
        }*/

        //Slimes 1 par 1
        for (i=0; i<max; i++)
        {
            pas_haut=1;
            pas_bas=1;
            pas_gauche=1;
            pas_droite=1;
            if(vague[i].isActif()==1)
            {
                for (k=0; k<pas; k++)
                    //Faire avancer de 10
                {
                    if(slimeStep == 0)
                    {
                        for (j=0; j<max; j++)
                            //Collisions slime 1 par 1
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
                        spriteMage.setPosition(vague[i].get_x(), vague[i].get_y());
                    else
                        spriteSlime.setPosition(vague[i].get_x(), vague[i].get_y());
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
        /*if (slime_etat==1)
            slime_etat=0;
        else if (slime_etat==0)
            slime_etat=1;
        slimeStep-=1;
        if(slimeStep<=0)
        {
            slimeStep=3;
        }*/
        //code sylvain

        //fenetre->clear();
        //drawMapGame(planMap, 10, 10, spriteTexture,  fenetre, 0, 0);
        fenetre->draw(spriteTexture);
        fenetre->display();
    }
    spriteTexture.scale(sf::Vector2f(1.0f, 1.0f));
}


void Jouer(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre, char *nomMap, int *carte)
{
    //exitVar passera a 1 quand le joueur aura choisi sa map
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
        //on ajoute le nom du dossier au nom de la map
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
                printf("%i\n", carte[k]);
            }
            fclose(fichierMap);
            exitVar=1;
        }
    }
}
