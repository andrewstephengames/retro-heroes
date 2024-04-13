#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "player.hpp"

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
    void drawMove(Player p1, Player p2);
}

#endif // MOVE_HPP_
