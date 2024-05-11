#ifndef GAME_HPP_
#define GAME_HPP_

#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <string>
#include <queue>

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif

#define MAX_TITLE_SIZE 1024
#define MAX_INPUT_SIZE 1024

typedef struct {
     Rectangle box;
     char label[MAX_INPUT_SIZE];
     int label_len;
     size_t font_size;
     Color bg;
     Color fg;
     Texture2D texture;
} Element;

enum State {
    Menu,
    Start,
    Win,
    Paused,
    Options,
    About,
};

struct Button {
    Rectangle box;
    Color fg;
    Color bg;
    std::string label;
    int size;
    void print () {
        printf ("box: { %0.f, %0.f, %0.f, %0.f }\nfg: #%x, bg: #%x\nlabel: %s, size: %d\n",
                box.x, box.y, box.width, box.height, ColorToInt(fg), ColorToInt(bg), label.c_str(), size);
    }
};

struct Resources {
    Music gameMusic;
    Sound menuHover, menuClick, attackS, shieldS, healS, specialS;
    Font titleF;
};

Vector2 Rec2Vec (Rectangle rec);
void drawInput(Element *e, bool texture, bool center, Vector2 canvas);

class Game {
private:
    Vector2 w;
    Rectangle wr;
    std::string title;
    State state;
    Resources res;
    std::string mode;
    bool turn;
public:
//    int rc;
//    sqlite3 *db;
//    char *sql, *err;
    Game();
    Game(Vector2 w, State state, std::string title);
    // call: Game ({1920, 1080}, Menu, "Retro Heroes");
    ~Game();
    State getState();
    void setState(State state);
    Vector2 getWindow();
    void setWindow(Vector2 w);
    Resources getRes();
    void setMode(std::string mode);
    std::string getMode();
    void setTurn();
    bool getTurn();
    void drawMenu();
    void drawGame();
    void drawPaused();
    void drawOptions();
    void drawAbout();
    void stateMachine();
};

bool drawWin (Game *game);

#endif // GAME_HPP_
