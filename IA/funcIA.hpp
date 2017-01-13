#ifndef FUNCIA_HPP_INCLUDED
#define FUNCIA_HPP_INCLUDED

class ennemy
{
    private:
        int vie;
        int x;
        int y;
        int type;

    public:
        ennemy();
        ennemy(int m_vie, int m_x, int m_y);
        ennemy(int m_vie, int m_x, int m_y, int m_type);
        void setPosition(int m_x, int m_y);
        int* getPosition();

};

void setPosition(int m_x, int m_y);
int* getPosition();

#endif // FUNCIA_HPP_INCLUDED
