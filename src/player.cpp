#include "player.hpp"

Player(std::string name, Color color, int health, Vector2 pos, Rectangle box) {
    this->name = name;
    this->color = color;
    this->health = health;
    this->pos = pos;
    this->box = box;
}

std::string getName() {
    return name;
}

void setName (std::string name) {
    this->name = name;
}

Color getColor() {
    return color;
}

void setColor(Color color) {
    this->color = color;
}

int getHealth() {
    return health;
}

void setHealth(int health) {
    this->health = health;
}

Vector2 getPos() {
    return pos;
}

void setPos(Vector2 pos) {
    this->pos = pos;
}

Rectangle getBox() {
    return box;
}

void setBox(Rectangle box) {
    this->box = box;
}

void addMove(Move move) {
    this->move.push(move);
}

Move useMove() {
    return move.pop();
}
