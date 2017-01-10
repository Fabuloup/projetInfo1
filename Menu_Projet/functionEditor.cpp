#include "functionEditor.hpp"

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
