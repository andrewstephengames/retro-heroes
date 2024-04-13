#include "move.hpp"

Move::Move(int damage, Color color, Sound sound) {
    this->damage = damage;
    this->color = color;
    this->sound = sound;
}

int getDamage() {
    return damage;
}

void setDamage(int damage) {
    this->damage = damage;
}

Color getColor() {
    return color;
}

void setColor(Color color) {
    this->color = color;
}

Sound getSound() {
    return sound;
}

void setSound(Sound sound) {
    this->sound = sound;
}

void drawMove(Player p1, Player p2) {
    Rectangle box1, box2;
    Vector2 start, end;
    box1 = p1.getBox();
    box2 = p2.getBox();
    start.x = box1.x + box1.width;
    start.y = box1.y + GetRandomValue (0, box1.height);
    end.x = box2.x;
    end.y = box2.y + GetRandomValue (0, box2.height);
    thick = w.x/100;
    DrawLineEx (start, end, thick, color);
}
