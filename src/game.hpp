#ifndef GAME_HPP_
#define GAME_HPP_

#include <raylib.h>
#include <raygui.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#if defined (PLATFORM_WEB)
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
    void stateMachine();
};

namespace RH {
    Rectangle Vector2Rec (Vector2 w);
    em_callback_func drawFrame(Game *game); // we need to draw frames
                                // in a separate function
                                // due to the limitations of web
    void loop(Game *game);
};

#endif // GAME_HPP_
