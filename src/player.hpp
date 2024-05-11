#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "game.hpp"
#include "move.hpp"

class Player : public Game {
private:
    std::string name;
    Color color;
    int health;
    Vector2 pos;
    Rectangle box;
    std::queue<Move> move;
    Texture2D texture;
public:
    Player(std::string name, Color color, int health, Texture2D texture);
    std::string getName();
    void setName (std::string name);
    Color getColor();
    void setColor(Color color);
    int getHealth();
    void setHealth(int health);
    Vector2 getPos();
    void setPos(Vector2 pos);
    Rectangle getBox();
    void setBox(Rectangle box);
    void addMove(Move move);
    Move useMove ();
    Texture2D getTexture();
    void setTexture(Texture2D texture);
};

#endif // PLAYER_HPP_
