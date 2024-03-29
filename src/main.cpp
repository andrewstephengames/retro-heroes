#include "game.hpp"

int main (void) {
    SetConfigFlags (FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel (LOG_ERROR);
    float factor = 100;
    Vector2 w = { factor*16, factor*9 };
    State state = Menu;
    std::string title = "Retro Heroes";
    Game *game = new Game(w, state, title);
    RH::loop(game);
    return 0;
}
