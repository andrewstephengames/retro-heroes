#include "game.hpp"
#include "player.hpp"

Player *p1, *p2;

Vector2 Rec2Vec (Rectangle rec) {
    return (Vector2) {
        rec.x,
        rec.y,
    };
}

Game::Game(){}

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
    turn = GetRandomValue (0, 1);
}

Game::~Game() {
    CloseWindow();
    if (mode == "PvP") {
        delete p1;
        delete p2;
    }
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

void Game::setMode(std::string mode) {
    this->mode = mode;
}

std::string Game::getMode() {
    return mode;
}

void Game::setTurn() {
    turn = !turn;
}

bool Game::getTurn() {
    return turn;
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
       quit.box.x += quit.box.width/2;
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
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            state = Start;
            if (mode == "PvP") {
                p1 = new Player ("Player 1", SKYBLUE, 10);
                p2 = new Player ("Player 2", LIME, 10);
                float scale = 10;
                p1->setPos({w.x/scale, w.y/scale});
                p1->setBox({
                    p1->getPos().x,
                    p1->getPos().y,
                    w.x/2.5f-p1->getPos().x,
                    w.y-p1->getPos().y-w.y/scale,
                });
                p2->setPos({w.x/1.8f, w.y/scale});
                p2->setBox({
                    p2->getPos().x,
                    p2->getPos().y,
                    w.x/3.0f,
                    w.y-p2->getPos().y-w.y/scale,
                });
            }
        }
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
    DrawText ("Work in progress | Game", 32, 32, w.x/30, RED);
    Vector2 mouse = GetMousePosition();
    Button back;
    back.box.x = 32;
    back.box.y = 250;
    back.label = "Back";
    back.size = w.x/30;
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
    if (IsKeyPressed(KEY_ESCAPE))
        state = Menu;
    float scale;
    if (mode == "PvP") {
        float thick = w.x/200;
        float nameSize = w.x/30;
        Rectangle r;
        Color c1, c2;
        if (turn) {
            c1 = p1->getColor();
            c2 = p2->getColor();
            c1.a = 255;
            c2.a = 100;
            p1->setColor(c1);
            p2->setColor(c2);
            if (IsKeyPressed (KEY_A) || IsKeyPressed (KEY_LEFT) ||
                IsKeyPressed (KEY_H)) {
                r = p1->getBox();
                r.x -= w.x/100;
                p1->setBox (r);
                turn = !turn;
            } else if (IsKeyPressed (KEY_D) || IsKeyPressed (KEY_RIGHT) ||
                IsKeyPressed (KEY_L)) {
                r = p1->getBox();
                r.x += w.x/100;
                p1->setBox (r);
                turn = !turn;
            }
        } else {
            c1 = p1->getColor();
            c2 = p2->getColor();
            c1.a = 100;
            c2.a = 255;
            p1->setColor(c1);
            p2->setColor(c2);
            if (IsKeyPressed (KEY_A) || IsKeyPressed (KEY_LEFT) ||
                IsKeyPressed (KEY_H)) {
                r = p2->getBox();
                r.x -= w.x/100;
                p2->setBox (r);
                turn = !turn;
            } else if (IsKeyPressed (KEY_D) || IsKeyPressed (KEY_RIGHT) ||
                IsKeyPressed (KEY_L)) {
                r = p2->getBox();
                r.x += w.x/100;
                p2->setBox (r);
                turn = !turn;
            }
        }
        if (p1->getBox().x <= 0)
            p1->setBox({
                0,
                p1->getBox().x,
                p1->getBox().width,
                p1->getBox().height,
            });
        if (p2->getBox().x <= 0)
            p2->setBox({
                0,
                p2->getBox().y,
                p2->getBox().width,
                p2->getBox().height,
            });
        if (p1->getBox().x >= wr.width-p1->getBox().width)
            p1->setBox({
                wr.width-p1->getBox().width,
                p1->getBox().y,
                p1->getBox().width,
                p1->getBox().height,
            });
        if (p2->getBox().x >= wr.width-p2->getBox().width)
            p2->setBox({
                wr.width-p2->getBox().width,
                p2->getBox().y,
                p2->getBox().width,
                p2->getBox().height,
            });
        DrawRectangleLinesEx(p1->getBox(), thick, p1->getColor());
        DrawText (p1->getName().c_str(), p1->getBox().x+p1->getBox().width-MeasureText(p1->getName().c_str(), nameSize), p1->getBox().y+p1->getBox().height, nameSize, p1->getColor());
        DrawRectangleLinesEx(p2->getBox(), thick, p2->getColor());
        DrawText (p2->getName().c_str(), p2->getBox().x+p2->getBox().width-MeasureText(p2->getName().c_str(), nameSize), p2->getBox().y+p2->getBox().height, nameSize, p2->getColor());
    } else {
        scale = 20;
        Button attack, shield, special;
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
    if (IsKeyPressed(KEY_ESCAPE))
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
    if (IsKeyPressed(KEY_ESCAPE))
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
