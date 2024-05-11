#include "game.hpp"

Game *game;

namespace RH {
    void drawFrame (void);
    void loop(Game *game);
};

int main (void) {
    SetConfigFlags (FLAG_WINDOW_RESIZABLE);
    SetConfigFlags (FLAG_MSAA_4X_HINT);
    //SetTraceLogLevel (LOG_ERROR);
    float factor = 120;
    Vector2 w = { factor*16, factor*9 };
    State state = Menu;
    std::string title = "Retro Heroes";
    game = new Game(w, state, title);
    PlayMusicStream(game->getRes().gameMusic);
    RH::loop(game);
    delete game;
    return 0;
}

void RH::loop(Game *game) {
#if defined (PLATFORM_WEB)
    emscripten_set_main_loop (drawFrame, 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateMusicStream (game->getRes().gameMusic);
        drawFrame();
    }
#endif
}

void RH::drawFrame(void) {
    Vector2 resize;
    resize.x = GetScreenWidth();
    resize.y = GetScreenHeight();
    game->setWindow(resize);
    BeginDrawing();
        ClearBackground (WHITE);
        game->stateMachine();
    EndDrawing();
}
