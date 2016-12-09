#include "functionEditor.hpp"

// demande dans l'invite de commande ce que souhaite faire l'utilisateur (editer ou creer une nouvelle map

void funcEditor(sf::Sprite tileset, sf::Sprite tileTexte, sf::RenderWindow *fenetre)
{
    int choixEdit =0;
    //choix de l'utilisateur (voir fonction)
    choixEdit = createOrNew(fenetre, tileset, tileTexte);
    if(choixEdit==1)
    {
        fenetre->setActive(false);
        printf("En cours de développement\n");
        fenetre->setActive(true);
    }
    else if (choixEdit==0)
    {
        char NomMap[50]="";
        printf("Entrez le nom de votre map sans oublier le \".map\"\n>>> ");
        scanf("%s", NomMap);
        fenetre->setActive(false);
        int carteDeBase[10*10]= {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
        editor(carteDeBase, tileset, fenetre, NomMap);
        fenetre->setActive(true);
    }
}

int createOrNew(sf::RenderWindow *fenetre, sf::Sprite tileset, sf::Sprite textTile)
{
    int position=0;//stock la position du curseur des choix dans le menu
    int finBoucle=0; //pour terminer la boucle quand l'utilisateur a fais son choix
    char titre[]="editeur de map";
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
        fenetre->display();
    }

    return position;
}
//fonction qui permet au joueur de choisir sa map parmis celle qui existe déjà
int loadMap(sf::Sprite tileset, sf::RenderWindow *fenetre)
{
    sf::Event event;
    //exitVar passera a 1 quand le joueur aura choisi sa map
    int exitVar = 0;
    while (exitVar == 0 and fenetre->isOpen())
    {
        fenetre->clear();
        fenetre->draw(tileset);
        fenetre->display();
    }
}

void scanGraphique(char *texte, sf::RenderWindow *fenetre, int posX, int posY, float taille)
{
    int position=0; //nous permet de connaitre notre posistion dans le mot
    char *lettreTapee; //le caractère tapé par l'utilisateur
    sf::Event event;
    sf::Texture textTexture;
    if( !textTexture.loadFromFile("ressources/alphabetred.png"))
    {
        printf("Impossible de charger le tileset du texte");
    }
    sf::Sprite spriteTexte;
    spriteTexte.setTexture(textTexture);
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
            case sf::Keyboard::Space:
                lettreTapee=" ";
                break;
            case sf::Keyboard::A:
                lettreTapee="a";
                break;
            default :
                lettreTapee=" ";
                break;
            }
            strcat(texte, lettreTapee);
            MachineAEcrire(spriteTexte, fenetre, lettreTapee, posX, posY, taille);
            break;
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
        fenetre->clear(sf::Color::Black);
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
                        fichier<<plan[k];
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
