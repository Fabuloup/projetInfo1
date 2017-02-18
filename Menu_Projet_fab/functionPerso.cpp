#include "functionPerso.hpp"

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

void deplacementSouris(heros* ninja, int mouseX, int mouseY, int* plan, ennemy* vague)
{
    int k=0;
        for(k=0; k<ninja->getSpeed(); k++)
        {
            int distanceY=abs(mouseY-ninja->getY());
            int distanceX=abs(mouseX-ninja->getX());

            if(ninja->getSlashStep() > 0)
            {
                distanceY = -sin(ninja->getAngle())*100;
                distanceX = -cos(ninja->getAngle())*100;
                mouseX = ninja->getX()+distanceX;
                mouseY = ninja->getY()+distanceY;
                printf("%f\n", ninja->getAngle());
                printf("%i\n", distanceY);
            }
            else
            {
                ninja->findAngle(mouseX, mouseY);
            }

            //on test la décédence
            int i=0;
            for(i=0; i<MAXENNEMY; i++)
            {
                if(vague[i].get_x() > ninja->getX()-10 && vague[i].get_x() < ninja->getX()+10 && vague[i].get_y() > ninja->getY()-20 && vague[i].get_y() < ninja->getY()+20 && ninja->getSlashStep()>0)
                {
                    vague[i].setActif(0);
                }
            }
            //fini

            if(distanceY > distanceX && (distanceX>5 || distanceY>5))
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
            else if(distanceX>5 || distanceY>5)
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

