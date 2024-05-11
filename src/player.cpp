#include "player.hpp"

Player::Player(std::string name, Color color, int health, Texture2D texture) {
    this->name = name;
    this->color = color;
    this->health = health;
    this->pos = pos;
    this->box = box;
    this->texture = texture;
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
    if (health < 0)
        this->health = 0;
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

Texture2D Player::getTexture() {
    return texture;
}
void Player::setTexture(Texture2D texture) {
    this->texture = texture;
}
