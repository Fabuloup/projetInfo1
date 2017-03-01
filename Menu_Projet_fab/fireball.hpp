#ifndef FIREBALL_HPP_INCLUDED
#define FIREBALL_HPP_INCLUDED

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

#endif // FIREBALL_HPP_INCLUDED
