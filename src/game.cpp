#include "game.hpp"

Game::Game(Vector2 w, State state, std::string title) {
    this->w = w;
    this->state = state;
    this->title = title;
    wr = {
        0,
        0,
        this->w.x,
        this->w.y,
    };
    InitWindow (this->w.x, this->w.y, this->title.c_str());
}

Game::~Game() {
    CloseWindow();
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
    #ifdef MOUSE_DEBUG
        char buf[500];
        sprintf (buf, "%.0f %.0f", GetMousePosition().x, GetMousePosition().y);
        DrawText (buf, 0, 0, w.x/30, BLACK);
    #endif // MOUSE_DEBUG
    if (IsKeyPressed (KEY_Q))
        exit (EXIT_SUCCESS);
    switch (state) {
        case Menu: {
            //drawMenu();
        } break;
        case Start: {
            //drawGame();
        } break;
        case Paused: {
            //drawPaused();
        } break;
        default:
            TraceLog (LOG_ERROR, "Unreachable state.");
            exit (EXIT_FAILURE);
    }
}
