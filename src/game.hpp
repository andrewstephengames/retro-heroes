#ifndef GAME_HPP_
#define GAME_HPP_

#include <raylib.h>
#include <raygui.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif

enum State {
    Menu,
    Start,
    Paused,
};

class Game {
private:
    Vector2 w;
    Rectangle wr;
    std::string title;
    State state;
public:
    Game(Vector2 w, State state, std::string title);
    // call: Game ({1920, 1080}, Menu, "Retro Heroes");
    ~Game();
    State getState();
    void setState(State state);
    Vector2 getWindow();
    void setWindow(Vector2 w);
    void drawMenu();
    void drawGame();
    void drawPaused();
    void stateMachine();
};

#endif // GAME_HPP_
