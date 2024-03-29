#include "game.hpp"

Rectangle RH::Vector2Rec (Vector2 w) {
    return (Rectangle) {
        .x = 0,
        .y = 0,
        .width = w.x,
        .height = w.y,
    };
}

void RH::loop(Game *game) {
#if defined (PLATFORM_WEB)
    emscripten_set_main_loop (RH::drawFrame(game), 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        RH::drawFrame(game);
    }
#endif
    CloseWindow();
}

Game::Game(Vector2 w, State state, std::string title) {
    this->w = w;
    this->state = state;
    this->title = title;
}

Game::~Game() {
    TraceLog (LOG_INFO, "Game exited graciously.");   
}

State Game::getState() {
    return state;
}

void Game::setState (State state) {
    this->state = state;
}

Vector2 Game::getWindow() {
    return w;
}

void Game::setWindow(Vector2 w) {
    this->w = w;
}

void Game::stateMachine() {
    Rectangle rec = RH::Vector2Rec (w);
    switch (state) {
        case Menu: {
            DrawRectangleRec (rec, LIGHTGRAY);
            if (IsKeyPressed (KEY_Q) || IsMouseButtonPressed (MOUSE_BUTTON_RIGHT))
                exit (EXIT_SUCCESS);
            if (IsKeyPressed (KEY_ENTER) || IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
                state = Start;
        } break;
        case Start: {
            DrawRectangleRec (rec, LIME);
            if (IsKeyPressed (KEY_Q) || IsMouseButtonPressed (MOUSE_BUTTON_RIGHT))
                state = Menu;
            if (IsKeyPressed (KEY_ENTER) || IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
                state = Paused;
        } break;
        case Paused: {
            DrawRectangleRec (rec, YELLOW);
            if (IsKeyPressed (KEY_ENTER) || IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
                state = Start;
        } break;
        default:
            TraceLog (LOG_ERROR, "Unreachable state.");
            exit (EXIT_FAILURE);
    }
}

em_callback_func RH::drawFrame(Game *game) {
    BeginDrawing();
        ClearBackground (BLACK);
        game->stateMachine();
    EndDrawing();
}
