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
    InitAudioDevice();
    SetRandomSeed(clock());
    //res.titleT = LoadTexture ("../res/img/retro-heroes.png");
    res.titleF = LoadFontEx("/home/andrew/git/retro-heroes/res/font/DSFetteKanzlei.ttf", MAX_TITLE_SIZE, NULL, 0);
    mode = "PvP";
    turn = GetRandomValue (0, 1);
    res.menuClick = LoadSound ("/home/andrew/git/retro-heroes/res/sfx/click.ogg");
    res.attackS = LoadSound ("/home/andrew/git/retro-heroes/res/sfx/attack.ogg");
    res.healS = LoadSound ("/home/andrew/git/retro-heroes/res/sfx/heal.ogg");
    res.specialS = LoadSound ("/home/andrew/git/retro-heroes/res/sfx/special.ogg");
    res.gameMusic = LoadMusicStream ("/home/andrew/git/retro-heroes/res/sfx/music.ogg");
//    rc = sqlite3_open ("/home/andrew/git/retro-heroes/res/db/players.db", &db);
//    if (rc != SQLITE_OK) {
//        std::cerr << "ERROR: Could not open the database: " << sqlite3_errmsg(db);
//        sqlite3_close(db);
//        exit (EXIT_FAILURE);
//    }
//    sql = "CREATE TABLE IF NOT EXISTS Players (Id INT, Name TEXT, Win INT)";
}

Game::~Game() {
    CloseAudioDevice();
    CloseWindow();
    if (IsMusicStreamPlaying(res.gameMusic))
        UnloadMusicStream(res.gameMusic);
    delete p1;
    delete p2;
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

void drawInput(Element *e, bool texture, bool center, Vector2 canvas) {
     Vector2 mouse = GetMousePosition();
     bool is_mouse_on_box = CheckCollisionPointRec (mouse, e->box);
     Vector2 w = {
          .x = canvas.x/2 - e->box.width/2,
          .y = canvas.y/2 - e->box.height/2,
     };
     if (center) {
          e->box.x = w.x;
          e->box.y = w.y;
     }
     if (texture) {
          DrawTextureRec (e->texture, e->box, Rec2Vec(e->box), e->fg);
     } else {
          DrawRectangleRec(e->box, e->bg);
     }
     if (e->label_len == 0) {
          DrawText("Type..", e->box.x + 10, e->box.y + e->box.height / 2 - 10, e->font_size, e->fg);
     } else {
          DrawText(e->label, e->box.x + 10, e->box.y + e->box.height / 2 - 10, e->font_size, e->fg);
     }
     int key = GetCharPressed();
     if (is_mouse_on_box) {
          SetMouseCursor(MOUSE_CURSOR_IBEAM);
          DrawText("|", e->box.x + 10 + MeasureText(e->label, e->font_size), e->box.y + e->box.height / 2 - 10, e->font_size, e->fg);
          if (key != 0) {
               if (e->font_size < MAX_INPUT_SIZE - 1) {
                    e->label[e->label_len++] = (char)key;
                    e->label[e->label_len] = '\0';
               }
          } else if (IsKeyPressed(KEY_BACKSPACE) && e->label_len > 0) {
               e->label[--e->label_len] = '\0';
          }
     } else {
          SetMouseCursor(MOUSE_CURSOR_DEFAULT);
     }
}

void Game::drawMenu() {
    Button titleB, play, options, quit, modeB, about;
    Element in1, in2;
    titleB.box = wr;
    titleB.size = wr.width/10;
    titleB.box.x = wr.width/2;
    titleB.box.y = wr.height/4;
    titleB.label = title;
    titleB.box.width = MeasureText (titleB.label.c_str(), titleB.size);
    titleB.box.height = titleB.size;
    titleB.box.x -= titleB.box.width/3;
    titleB.box.y -= titleB.box.height/3;
    titleB.bg = BLACK;
    titleB.fg = BLACK;
    //DrawTextureRec (res.titleT, titleB.box, Rec2Vec(titleB.box), BLACK);
    DrawTextEx (res.titleF, title.c_str(), Rec2Vec(titleB.box), titleB.size, 1, BLACK);
    //#ifdef PLATFORM_WEB
    //DrawText(titleB.label.c_str(), titleB.box.x, titleB.box.y, titleB.size, titleB.fg);
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
    strcpy (in1.label, "Player 1");
    strcpy (in2.label, "Player 2");
    in1.bg = BLACK;
    in1.bg.a = 100;
    in1.fg = WHITE;
    in2.bg = BLACK;
    in2.bg.a = 100;
    in2.fg = WHITE;

    if (CheckCollisionPointRec(GetMousePosition(), in1.box))
        in1.bg = GRAY;
    if (CheckCollisionPointRec(GetMousePosition(), in2.box))
        in2.bg = GRAY;

    //drawInput(&in1, false, false, (Vector2){w.x / 3, w.y});
    //drawInput(&in2, false, false, w);
    if (CheckCollisionPointRec (GetMousePosition(), play.box)) {
        play.bg = BLACK;
        PlaySound (res.menuHover);
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            PlaySound (res.menuClick);
            state = Start;
            if (mode == "PvP") {
                Color c1 = ColorFromHSV (GetRandomValue (0, 360), 1.0, 1.0);
                Color c2 = ColorFromHSV (GetRandomValue (0, 360), 1.0, 1.0);
                p1 = new Player ("Player 1", c1, 100, LoadTexture ("/home/andrew/git/retro-heroes/res/img/player.png"));
                Image image = LoadImage ("/home/andrew/git/retro-heroes/res/img/player.png");
                ImageFlipHorizontal(&image);
                p2 = new Player ("Player 2", c2, 100, LoadTextureFromImage(image));
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
            PlaySound (res.menuHover);
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            PlaySound (res.menuClick);
            state = Options;
        }
    }
    DrawRectangleRec (options.box, options.bg);
    DrawText (options.label.c_str(), options.box.x, options.box.y, options.size, options.fg);
    #ifndef PLATFORM_WEB
        if (CheckCollisionPointRec (GetMousePosition(), quit.box)) {
            quit.bg = BLACK;
            PlaySound (res.menuHover);
            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
                PlaySound (res.menuClick);
                exit(EXIT_SUCCESS);
            }
        }
        DrawRectangleRec (quit.box, quit.bg);
        DrawText (quit.label.c_str(), quit.box.x, quit.box.y, quit.size, quit.fg);
    #endif // PLATFORM_WEB
    if (CheckCollisionPointRec (GetMousePosition(), modeB.box)) {
        modeB.bg = BLACK;
        PlaySound (res.menuHover);
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            PlaySound (res.menuClick);
            if (mode.compare("PvP") == 0)
                mode = "PvE";
            else mode = "PvP";
        }
    }
    DrawRectangleRec (modeB.box, modeB.bg);
    DrawText (modeB.label.c_str(), modeB.box.x, modeB.box.y, modeB.size, modeB.fg);
    if (CheckCollisionPointRec (GetMousePosition(), about.box)) {
        about.bg = BLACK;
        PlaySound (res.menuHover);
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            PlaySound (res.menuClick);
            state = About;
        }
    }
    DrawRectangleRec (about.box, about.bg);
    DrawText (about.label.c_str(), about.box.x, about.box.y, about.size, about.fg);
    if (CheckCollisionPointRec (GetMousePosition(), in1.box))
        in1.bg = BLACK;
    if (CheckCollisionPointRec (GetMousePosition(), in2.box))
        in2.bg = BLACK;
    /*
    in1.box = {
        w.x / 3 - MeasureText(in1.label, in1.font_size) / 2,
        w.y - 2 * in1.box.height,
        MeasureText(in1.label, in1.font_size) * 2,
        in1.font_size
    };

    in2.box = {
        w.x - MeasureText(in2.label, in2.font_size) * 2,
        w.y - 3 * in2.box.height,
        MeasureText(in2.label, in2.font_size) * 2,
        in2.font_size
    };
    */
}

bool drawWin (Game *game) {
    std::string win;
    Color wc;
    float ws = game->getWindow().x/20;
    bool v = false;
    if (p2->getHealth() == 0) {
        win = "Player 1 won";
        wc = p1->getColor();
        v = true;
    }
    if (p1->getHealth() == 0) {
        win = "Player 2 won";
        wc = p2->getColor();
        v = true;
    }
    wc.r += 10;
    wc.g += 10;
    wc.b += 10;
    float dt = 0;
    while (v) {
        DrawText (win.c_str(), game->getWindow().x/2-MeasureText (win.c_str(), ws)/2, game->getWindow().y/2-ws/2, ws, wc);
        dt += GetFrameTime();
        EndDrawing();
        BeginDrawing();
        if (dt > 3)
            break;
    }
    return v;
}

void Game::drawGame() {
    //DrawText ("Work in progress | Game", 32, 32, w.x/30, RED);
    SetMusicVolume (res.gameMusic, 1.0f);
    DrawText (TextFormat ("Health Player 1: %i", p1->getHealth()), 32, 32, w.x/30, p1->getColor());
    DrawText (TextFormat ("Health Player 2: %i", p2->getHealth()), 32, w.y/8, w.x/30, p2->getColor());
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
    if (drawWin(this)) {
        state = Menu;
    }
    if (CheckCollisionPointRec (mouse, back.box)) {
        back.bg = BLACK;
        PlaySound (res.menuHover);
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            state = Menu;
            PlaySound (res.menuClick);
            Color c1 = ColorFromHSV (GetRandomValue (0, 360), 1.0, 1.0);
            Color c2 = ColorFromHSV (GetRandomValue (0, 360), 1.0, 1.0);
            p1->setColor(c1);
            p2->setColor(c2);
        }
    }
    DrawRectangleRec (back.box, back.bg);
    DrawText (back.label.c_str(), back.box.x, back.box.y, back.size, back.fg);
    if (IsKeyPressed(KEY_ESCAPE))
        state = Menu;
    float scale;
        float thick = w.x/300;
        float nameSize = w.x/30;
        Rectangle r;
        Color c1, c2;
        if (turn) {
            c1 = p1->getColor();
            c2 = p2->getColor();
            c1.a = 255;
            c2.a = 255;
            p1->setColor(c1);
            p2->setColor(c2);
//            if (IsKeyPressed (KEY_A) || IsKeyPressed (KEY_LEFT) ||
//                IsKeyPressed (KEY_H)) {
//                r = p1->getBox();
//                r.x -= w.x/100;
//                p1->setBox (r);
//                turn = !turn;
//            } else if (IsKeyPressed (KEY_D) || IsKeyPressed (KEY_RIGHT) ||
//                IsKeyPressed (KEY_L)) {
//                r = p1->getBox();
//                r.x += w.x/100;
//                p1->setBox (r);
//                turn = !turn;
//            }
        } else {
            c1 = p1->getColor();
            c2 = p2->getColor();
            c1.a = 255;
            c2.a = 255;
            p1->setColor(c1);
            p2->setColor(c2);
//            if (IsKeyPressed (KEY_A) || IsKeyPressed (KEY_LEFT) ||
//                IsKeyPressed (KEY_H)) {
//                r = p2->getBox();
//                r.x -= w.x/100;
//                p2->setBox (r);
//                turn = !turn;
//            } else if (IsKeyPressed (KEY_D) || IsKeyPressed (KEY_RIGHT) ||
//                IsKeyPressed (KEY_L)) {
//                r = p2->getBox();
//                r.x += w.x/100;
//                p2->setBox (r);
//                turn = !turn;
//            }
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
        //DrawRectangleLinesEx(p1->getBox(), thick, p1->getColor());
        scale = 30;
        Button attack1, heal1, special1;
        attack1.box.x = w.x/scale;
        attack1.box.y = wr.height - 2*w.x/scale;
        attack1.box.width = w.x/scale;
        attack1.box.height = w.x/scale;
        attack1.bg = RED;
        heal1.box = attack1.box;
        heal1.box.x += 2*w.x/scale;
        heal1.bg = ORANGE;
        special1.box = heal1.box;
        special1.box.x += 2*w.x/scale;
        special1.bg = PURPLE;
        Rectangle r1, r2, sprite1, sprite2;
        sprite1 = {0, 0, 16, 16};
        sprite2 = {17, 0, 16, 16};
        Move *attack, *heal, *special;
        attack = new Move (10, attack1.bg);
        heal = new Move (-10, heal1.bg);
        special = new Move (20, special1.bg);
        if (CheckCollisionPointRec (mouse, attack1.box) ||
            IsKeyPressed(KEY_A)) {
            attack1.bg.a = 50;
            PlaySound (res.menuHover);
            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) ||
                IsKeyPressed (KEY_A)) {
                PlaySound(res.attackS);
                p1->addMove(*attack);
                p2->setHealth(p2->getHealth()-p1->useMove().getDamage());
                //DrawTexturePro (p1->getTexture(), (Rectangle){17, 0, 16, 16}, p1->getBox(), {0, 0}, 0, p1->getColor());
                sprite1 = {17, 0, 16, 16};
                r1 = p1->getBox();
                r2 = p2->getBox();
                int rand1 = GetRandomValue (0, r1.height);
                int rand2 = GetRandomValue (0, r2.height);
                DrawLineEx({
                    r1.x + r1.width,
                    r1.y + rand1,
                },{
                    r2.x,
                    r2.y + rand2,
                },
                    thick,
                    attack1.bg
                );
                DrawRectangleV((Vector2){ r2.x, r2.y + rand2 }, { w.x/50, w.x/50 }, attack1.bg);
            }
        }
        if (CheckCollisionPointRec (mouse, heal1.box) ||
            IsKeyPressed (KEY_S)) {
            heal1.bg.a = 50;
            PlaySound (res.menuHover);
            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) ||
                IsKeyPressed (KEY_S)) {
                PlaySound(res.healS);
                p1->addMove (*heal);
                p1->setHealth(p1->getHealth()-p1->useMove().getDamage());
                if (p1->getHealth() > 100)
                    p1->setHealth(100);
                //DrawTexturePro (p1->getTexture(), (Rectangle){17, 0, 16, 16}, p1->getBox(), {0, 0}, 0, p1->getColor());
                sprite1 = {17, 0, 16, 16};
                r1 = p1->getBox();
                r2 = p2->getBox();
                int rand1 = GetRandomValue (0, r1.height);
                int rand2 = GetRandomValue (0, r2.height);
                DrawRectangleLinesEx(p1->getBox(), thick, p1->getColor());
                DrawLineEx({
                    r1.x + r1.width,
                    r1.y + rand1,
                },{
                    r2.x,
                    r2.y + rand2,
                },
                    thick,
                    heal1.bg
                );
                DrawRectangleV((Vector2){ r2.x, r2.y + rand2 }, { w.x/50, w.x/50 }, heal1.bg);
            }
        }
        if (CheckCollisionPointRec (mouse, special1.box) ||
            IsKeyPressed(KEY_D)) {
            special1.bg.a = 50;
            PlaySound (res.menuHover);
            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) ||
                IsKeyPressed(KEY_D)) {
                PlaySound(res.specialS);
                p1->addMove(*special);
                p2->setHealth(p2->getHealth()-p1->useMove().getDamage());
                //DrawTexturePro (p1->getTexture(), (Rectangle){17, 0, 16, 16}, p1->getBox(), {0, 0}, 0, p1->getColor());
                sprite1 = {17, 0, 16, 16};
                r1 = p1->getBox();
                r2 = p2->getBox();
                int rand1 = GetRandomValue (0, r1.height);
                int rand2 = GetRandomValue (0, r2.height);
                DrawLineEx({
                    r1.x + r1.width,
                    r1.y + rand1,
                },{
                    r2.x,
                    r2.y + rand2,
                },
                    thick,
                    special1.bg
                );
                DrawRectangleV((Vector2){ r2.x, r2.y + rand2 }, { w.x/50, w.x/50 }, special1.bg);
            }
        }
        DrawRectangleRec (attack1.box, attack1.bg);
        DrawRectangleRec (heal1.box, heal1.bg);
        DrawRectangleRec (special1.box, special1.bg);
        Button attack2, heal2, special2;
        attack2.box.x = w.x-p2->getBox().width-4*w.x/scale;
        attack2.box.y = wr.height - 2*w.x/scale;
        attack2.box.width = w.x/scale;
        attack2.box.height = w.x/scale;
        attack2.bg = RED;
        heal2.box = attack2.box;
        heal2.box.x += 2*w.x/scale;
        heal2.bg = ORANGE;
        special2.box = heal2.box;
        special2.box.x += 2*w.x/scale;
        special2.bg = PURPLE;
        if (CheckCollisionPointRec (mouse, attack2.box) ||
            IsKeyPressed(KEY_LEFT)) {
            PlaySound (res.menuHover);
            attack2.bg.a = 50;
            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) ||
                IsKeyPressed (KEY_LEFT)) {
                PlaySound(res.attackS);
                p2->addMove(*attack);
                p1->setHealth(p1->getHealth()-p2->useMove().getDamage());
                //DrawTexturePro (p2->getTexture(), (Rectangle){0, 0, 16, 16}, p2->getBox(), {0, 0}, 0, p2->getColor());
                sprite2 = {0, 0, 16, 16};
                r1 = p1->getBox();
                r2 = p2->getBox();
                int rand1 = GetRandomValue (0, r1.height);
                int rand2 = GetRandomValue (0, r2.height);
                DrawLineEx({
                    r1.x + r1.width,
                    r1.y + rand1,
                },{
                    r2.x,
                    r2.y + rand2,
                },
                    thick,
                    attack2.bg
                );
                DrawRectangleV((Vector2){ r1.x + r1.width, r1.y + rand1 }, { w.x/50, w.x/50 }, attack2.bg);
            }
        }
        if (CheckCollisionPointRec (mouse, heal2.box) ||
            IsKeyPressed(KEY_DOWN)) {
            heal2.bg.a = 50;
            PlaySound (res.menuHover);
            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) ||
                IsKeyPressed(KEY_DOWN)) {
                PlaySound(res.healS);
                p2->addMove(*heal);
                p2->setHealth(p2->getHealth()-p2->useMove().getDamage());
                if (p2->getHealth() > 100)
                    p2->setHealth(100);
                //DrawTexturePro (p2->getTexture(), (Rectangle){0, 0, 16, 16}, p2->getBox(), {0, 0}, 0, p2->getColor());
                sprite2 = {0, 0, 16, 16};
                DrawRectangleLinesEx(p2->getBox(), thick, p2->getColor());
                r1 = p1->getBox();
                r2 = p2->getBox();
                int rand1 = GetRandomValue (0, r1.height);
                int rand2 = GetRandomValue (0, r2.height);
                DrawLineEx({
                    r1.x + r1.width,
                    r1.y + rand1,
                },{
                    r2.x,
                    r2.y + rand2,
                },
                    thick,
                    heal2.bg
                );
                DrawRectangleV((Vector2){ r1.x + r1.width, r1.y + rand1 }, { w.x/50, w.x/50 }, heal2.bg);
            }
        }
        if (CheckCollisionPointRec (mouse, special2.box) ||
            IsKeyPressed(KEY_RIGHT)) {
            special2.bg.a = 50;
            PlaySound (res.menuHover);
            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) ||
            IsKeyPressed(KEY_RIGHT)) {
                PlaySound(res.specialS);
                //DrawTexturePro (p2->getTexture(), (Rectangle){0, 0, 16, 16}, p2->getBox(), {0, 0}, 0, p2->getColor());
                sprite2 = {0, 0, 16, 16};
                p2->addMove(*special);
                p1->setHealth(p1->getHealth()-p2->useMove().getDamage());
                r1 = p1->getBox();
                r2 = p2->getBox();
                int rand1 = GetRandomValue (0, r1.height);
                int rand2 = GetRandomValue (0, r2.height);
                DrawLineEx({
                    r1.x + r1.width,
                    r1.y + rand1,
                },{
                    r2.x,
                    r2.y + rand2,
                },
                    thick,
                    special2.bg
                );
                DrawRectangleV((Vector2){ r1.x + r1.width, r1.y + rand1 }, { w.x/50, w.x/50 }, special2.bg);
            }
        }
        DrawRectangleRec (attack2.box, attack2.bg);
        DrawRectangleRec (heal2.box, heal2.bg);
        DrawRectangleRec (special2.box, special2.bg);
        DrawTexturePro (p1->getTexture(), sprite1, p1->getBox(), {0, 0}, 0, p1->getColor());
        DrawText (p1->getName().c_str(), p1->getBox().x+p1->getBox().width-MeasureText(p1->getName().c_str(), nameSize), p1->getBox().y+p1->getBox().height, nameSize, p1->getColor());
        //DrawRectangleLinesEx(p2->getBox(), thick, p2->getColor());
        DrawTexturePro (p2->getTexture(), sprite2, p2->getBox(), {0, 0}, 0, p2->getColor());
        DrawText (p2->getName().c_str(), p2->getBox().x+p2->getBox().width-MeasureText(p2->getName().c_str(), nameSize), p2->getBox().y+p2->getBox().height, nameSize, p2->getColor());
//        scale = 20;
//        Button attack1, heal1, special1;
//        attack1.box.x = w.x/scale;
//        attack1.box.y = wr.height - 2*w.x/scale;
//        attack1.box.width = w.x/scale;
//        attack1.box.height = w.x/scale;
//        attack1.bg = RED;
//        heal1.box = attack1.box;
//        heal1.box.x += 2*w.x/scale;
//        heal1.bg = ORANGE;
//        special1.box = heal1.box;
//        special1.box.x += 2*w.x/scale;
//        special1.bg = PURPLE;
//        if (CheckCollisionPointRec (mouse, attack1.box)) {
//            attack1.bg.a = 50;
//            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
//            }
//        }
//        if (CheckCollisionPointRec (mouse, heal1.box)) {
//            heal1.bg.a = 50;
//            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
//            }
//        }
//        if (CheckCollisionPointRec (mouse, special1.box)) {
//            special1.bg.a = 50;
//            if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
//            }
//        }
//        DrawRectangleRec (attack1.box, attack1.bg);
//        DrawRectangleRec (heal1.box, heal1.bg);
//        DrawRectangleRec (special1.box, special1.bg);
//    }
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
        PlaySound (res.menuHover);
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            PlaySound (res.menuClick);
            state = Menu;
        }
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
        PlaySound (res.menuHover);
        if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
            PlaySound (res.menuClick);
            state = Menu;
        }
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
        case Win: {
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
