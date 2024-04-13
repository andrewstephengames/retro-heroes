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
    SetRandomSeed(clock());
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
    wr = {
        0,
        0,
        this->w.x,
        this->w.y,
    };
}

void Game::drawMenu() {
    Button titleB, play;
    titleB.box = wr;
    titleB.size = wr.width/10;
    titleB.box.x = wr.width/2;
    titleB.box.y = wr.height/4;
    titleB.label = title;
    titleB.box.width = MeasureText (titleB.label.c_str(), titleB.size);
    titleB.box.height = titleB.size;
    titleB.box.x -= titleB.box.width/2;
    titleB.box.y -= titleB.box.height/2;
    titleB.bg = BLACK;
    titleB.fg = DARKGRAY;
    DrawText (titleB.label.c_str(), titleB.box.x, titleB.box.y, titleB.size, titleB.fg);
    play.box = wr;
    play.size = wr.width/20;
    play.box.x = wr.width/2;
    play.box.y = wr.height/1.66;
    play.label = "Play";
    play.box.width = MeasureText (play.label.c_str(), play.size);
    play.box.height = play.size;
    play.box.x -= play.box.width/2;
    play.box.y -= play.box.height/2;
    play.bg = BLACK;
    play.bg.a = 100;
    play.fg = WHITE;
    if (CheckCollisionPointRec (GetMousePosition(), play.box)) {
        play.bg = BLACK;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
            state = Start;
    }
    DrawRectangleRec (play.box, play.bg);
    DrawText (play.label.c_str(), play.box.x, play.box.y, play.size, play.fg);
}

void Game::drawGame() {
    DrawText ("Work in progress", 32, 32, w.x/20, RED);
    Vector2 mouse = GetMousePosition();
    Button back;
    back.box.x = 32;
    back.box.y = 250;
    back.label = "Back to Menu";
    back.size = w.x/20;
    back.box.width = MeasureText (back.label.c_str(), back.size);
    back.box.height = back.size;
    back.bg = BLACK;
    back.bg.a = 100;
    back.fg = WHITE;
    if (CheckCollisionPointRec (mouse, back.box)) {
        back.bg = BLACK;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
            state = Menu;
    }
    DrawRectangleRec (back.box, back.bg);
    DrawText (back.label.c_str(), back.box.x, back.box.y, back.size, back.fg);
    if (IsKeyPressed(KEY_H))
        state = Menu;
    Button attack, shield, special;
    float scale = 30;
    attack.box.x = w.x/scale;
    attack.box.y = wr.height - 2*w.x/scale;
    attack.box.width = w.x/scale;
    attack.box.height = w.x/scale;
    attack.bg = RED;
    shield.box = attack.box;
    shield.box.x += 2*w.x/scale;
    shield.bg = ORANGE;
    special.box = shield.box;
    special.box.x += 2*w.x/scale;
    special.bg = PURPLE;
    if (CheckCollisionPointRec (mouse, attack.box)) {
        attack.bg.a = 100;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            printf("Attack\n");
        }
    }
    if (CheckCollisionPointRec (mouse, shield.box)) {
        shield.bg.a = 100;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            printf("Shield\n");
        }
    }
    if (CheckCollisionPointRec (mouse, special.box)) {
        special.bg.a = 100;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            printf("Special attack\n");
        }
    }
    DrawRectangleRec (attack.box, attack.bg);
    DrawRectangleRec (shield.box, shield.bg);
    DrawRectangleRec (special.box, special.bg);
}

void Game::drawPaused() {
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
            drawMenu();
        } break;
        case Start: {
            drawGame();
        } break;
        case Paused: {
            drawPaused();
        } break;
        default:
            TraceLog (LOG_ERROR, "Unreachable state.");
            exit (EXIT_FAILURE);
    }
}
