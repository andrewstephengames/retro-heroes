#include "move.hpp"

Move::Move(int damage, Color color) {
    this->damage = damage;
    this->color = color;
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
