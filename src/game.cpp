#include "game.hpp"

Vector2 Rec2Vec (Rectangle rec) {
    return (Vector2) {
        rec.x,
        rec.y,
    };
}

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
    res.titleT = LoadTexture ("../res/img/retro-heroes.png");
    mode = "PvP";
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

Resources Game::getRes() {
    return res;
}

void Game::drawMenu() {
    Button titleB, play, options, quit, modeB, about;
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
    titleB.fg = BLACK;
    //DrawTextureRec (res.titleT, titleB.box, Rec2Vec(titleB.box), BLACK);
    //#ifdef PLATFORM_WEB
        DrawText(titleB.label.c_str(), titleB.box.x, titleB.box.y, titleB.size, titleB.fg);
    //#endif // PLATFORM_WEB
    play.box = wr;
    play.size = wr.width/15;
    play.box.x = wr.width/2;
    play.box.y = wr.height/2;
    play.label = "Play";
    play.box.width = MeasureText (play.label.c_str(), play.size);
    play.box.height = play.size;
    play.box.x -= play.box.width/2;
    play.box.y -= play.box.height/2;
    play.bg = BLACK;
    play.bg.a = 100;
    play.fg = WHITE;
    options = play;
    options.label = "Options";
    options.box.y += 1.5*play.box.height;
    options.box.width = MeasureText (options.label.c_str(), options.size);
    options.box.height = options.size;
    options.box.x -= options.box.width/4;
    options.box.y -= options.box.height/4;
    #ifndef PLATFORM_WEB
       quit = options;
       quit.label = "Quit";
       quit.box.width = MeasureText (quit.label.c_str(), quit.size);
       quit.box.height = quit.size;
       quit.box.y += 1.5*options.box.height;
       quit.box.x -= quit.box.width/4;
       quit.box.y -= quit.box.height/4;
    #endif // PLATFORM_WEB
    modeB.size = options.size/1.25;
    modeB.box.x = 0;
    modeB.box.y = w.y;
    modeB.label = "Mode: ";
    modeB.label.append (mode);
    modeB.box.width = MeasureText (modeB.label.c_str(), modeB.size);
    modeB.box.height = modeB.size;
    modeB.box.x += modeB.box.width/8;
    modeB.box.y -= 2*modeB.box.height;
    modeB.bg = BLACK;
    modeB.bg.a = 100;
    modeB.fg = WHITE;
    about = modeB;
    about.box.x = w.x;
    about.box.y = w.y;
    about.label = "About";
    about.box.width = MeasureText (about.label.c_str(), about.size);
    about.box.height = about.size;
    about.box.x -= 1.25*about.box.width;
    about.box.y -= 2*about.box.height;
    about.bg = BLACK;
    about.bg.a = 100;
    about.fg = WHITE;
    if (CheckCollisionPointRec (GetMousePosition(), play.box)) {
        play.bg = BLACK;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
            state = Start;
    }
    DrawRectangleRec (play.box, play.bg);
    DrawText (play.label.c_str(), play.box.x, play.box.y, play.size, play.fg);
    if (CheckCollisionPointRec (GetMousePosition(), options.box)) {
        options.bg = BLACK;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
            state = Options;
    }
    DrawRectangleRec (options.box, options.bg);
    DrawText (options.label.c_str(), options.box.x, options.box.y, options.size, options.fg);
    #ifndef PLATFORM_WEB
        if (CheckCollisionPointRec (GetMousePosition(), quit.box)) {
            quit.bg = BLACK;
            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
                exit(EXIT_SUCCESS);
        }
        DrawRectangleRec (quit.box, quit.bg);
        DrawText (quit.label.c_str(), quit.box.x, quit.box.y, quit.size, quit.fg);
    #endif // PLATFORM_WEB
    if (CheckCollisionPointRec (GetMousePosition(), modeB.box)) {
        modeB.bg = BLACK;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            if (mode.compare("PvP") == 0)
                mode = "PvE";
            else mode = "PvP";
        }
    }
    DrawRectangleRec (modeB.box, modeB.bg);
    DrawText (modeB.label.c_str(), modeB.box.x, modeB.box.y, modeB.size, modeB.fg);
    if (CheckCollisionPointRec (GetMousePosition(), about.box)) {
        about.bg = BLACK;
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
            state = About;
    }
    DrawRectangleRec (about.box, about.bg);
    DrawText (about.label.c_str(), about.box.x, about.box.y, about.size, about.fg);
}

void Game::drawGame() {
    DrawText ("Work in progress | Game", 32, 32, w.x/20, RED);
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

void Game::drawOptions() {
    DrawText ("Work in progress | Options", 32, 32, w.x/20, RED);
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
}

void Game::drawAbout() {
    DrawText ("Work in progress | About", 32, 32, w.x/20, RED);
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
        case Options: {
            drawOptions();
        } break;
        case About: {
            drawAbout();
        } break;
        default:
            TraceLog (LOG_ERROR, "Unreachable state.");
            exit (EXIT_FAILURE);
    }
}
