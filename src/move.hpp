#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "game.hpp"

class Move {
private:
    int damage; // if damage < 0: defence else offence
    Color color;
    Sound sound;
public:
    Move(int damage, Color color, Sound sound);
    int getDamage();
    void setDamage(int damage);
    Color getColor();
    void setColor(Color color);
    Sound getSound();
    void setSound(Sound sound);
};

#endif // MOVE_HPP_
