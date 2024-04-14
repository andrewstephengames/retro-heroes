#include "player.hpp"

Player::Player(std::string name, Color color, int health) {
    this->name = name;
    this->color = color;
    this->health = health;
    this->pos = pos;
    this->box = box;
}

std::string Player::getName() {
    return name;
}

void Player::setName (std::string name) {
    this->name = name;
}

Color Player::getColor() {
    return color;
}

void Player::setColor(Color color) {
    this->color = color;
}

int Player::getHealth() {
    return health;
}

void Player::setHealth(int health) {
    this->health = health;
}

Vector2 Player::getPos() {
    return pos;
}

void Player::setPos(Vector2 pos) {
    this->pos = pos;
}

Rectangle Player::getBox() {
    return box;
}

void Player::setBox(Rectangle box) {
    this->box = box;
}

void Player::addMove(Move move) {
    this->move.push(move);
}

Move Player::useMove () {
    Move lastMove = move.front();
    move.pop();
    return lastMove;
}
