#include "move.hpp"

Move::Move(int damage, Color color, Sound sound) {
    this->damage = damage;
    this->color = color;
    this->sound = sound;
}

int Move::getDamage() {
    return damage;
}

void Move::setDamage(int damage) {
    this->damage = damage;
}

Color Move::getColor() {
    return color;
}

void Move::setColor(Color color) {
    this->color = color;
}

Sound Move::getSound() {
    return sound;
}

void Move::setSound(Sound sound) {
    this->sound = sound;
}
