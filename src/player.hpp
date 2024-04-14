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
public:
    Player(std::string name, Color color, int health);
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
};

#endif // PLAYER_HPP_
