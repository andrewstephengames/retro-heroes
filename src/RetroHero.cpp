#include <iostream>
#include <cstdlib>
using namespace std;

class Moves
{
private:
    int sp;

public:
    Moves() {}

    int getSp()
    {
        return sp;
    }

    void setSp(int newSp)
    {
        this->sp = newSp;
    }
};

class Player
{
private:
    int health;
    int attack;
    bool deff, confusion, fog;

public:
    Player()
    {
        this->health = 100;
        this->attack = 10;
        this->deff = false;
        this->confusion = false;
        this->fog = false;
    }

    int getHealth()
    {
        return health;
    }

    int getAttack()
    {
        return attack;
    }

    bool getDeff()
    {
        return deff;
    }

    bool getConfusion()
    {
        return confusion;
    }

    bool getFog()
    {
        return fog;
    }

    void setDeff(bool newDeff)
    {
        this->deff = newDeff;
    }

    void setConfusion(bool newConfusion)
    {
        this->confusion = newConfusion;
    }

    void setFog(bool newFog)
    {
        this->fog = newFog;
    }

    void setHealth(int newHealth)
    {
        this->health = newHealth;
    }

    void setAttack(int newAttack)
    {
        this->attack = newAttack;
    }
};

class Monster
{
private:
    int health;
    int attack;
    bool deff, confusion, fog;

public:
    Monster()
    {
        this->attack = 10;
        this->health = 100;
        this->deff = false;
        this->confusion = false;
        this->fog = false;
    }

    void setAttack(int newAttack)
    {
        this->attack = newAttack;
    }

    int getAttack()
    {
        return attack;
    }

    void setHealth(int newHealth)
    {
        this->health = newHealth;
    }

    int getHealth()
    {
        return health;
    }

    bool getDeff()
    {
        return deff;
    }

    void setDeff(bool newDeff)
    {
        this->deff = newDeff;
    }

    void setConfusion(bool newConfusion)
    {
        this->confusion = newConfusion;
    }

    void setFog(bool newFog)
    {
        this->fog = newFog;
    }

    bool getConfusion()
    {
        return confusion;
    }

    bool getFog()
    {
        return fog;
    }
};

// moves:

void basicAttackMonster(Player p, Monster m)
{
    if(m.getConfusion() == true){
        m.setHealth(m.getHealth() - m.getAttack());
        m.setConfusion(false);
    }

    if(m.getConfusion() == true){
        cout << "Mosnter missed because of the fog";
        m.setFog(false);
    }

    if (p.getDeff() != true)
    {
        p.setHealth(p.getHealth() - m.getAttack());
    }
    else
    {
        cout << "Enemy has deffence on" << endl;
        p.setDeff(false);
    }
}

void basicAttackPlayerVsPlayer(Player p1, Player p2)
{
    if(p2.getConfusion() == true){
        p2.setHealth(p2.getHealth() - p2.getAttack());
        p2.setConfusion(false);
    }

    if(p2.getFog() == true){
        cout << "Hit missed, the payer is under fog";
        p2.setFog(false);
    }
    
    if (p1.getDeff() != true)
    {
        p1.setHealth(p1.getHealth() - p2.getAttack());
    }
    else
    {
        cout << "Enemy player tanked the hit" << endl;
        p1.setDeff(false);
    }
}

void basicAttackPlayerVsMonster(Monster m, Player p)
{
    if(p.getConfusion() == true){
        p.setHealth(p.getHealth() - p.getAttack());
        p.setConfusion(false);
    }

    if(p.getFog() == true){
        cout << "Player can't because of the fog, hit missed";
        p.setFog(false);
    }
    
    if (m.getDeff() != true)
    {
        m.setHealth(m.getHealth() - p.getAttack());
    }
    else
    {
        cout << "Monster tanked the hit" << endl;
        m.setDeff(false);
    }
}

void healPlayer(Player p)
{
    if (p.getHealth() < 100)
    {
        p.setHealth(p.getHealth() + 10);
    }
    if (p.getHealth() > 100)
    {
        p.setHealth(100);
    }
}

void healMonster(Monster m)
{
    if (m.getHealth() < 100)
    {
        m.setHealth(m.getHealth() + 10);
    }
    if (m.getHealth() > 100)
    {
        m.setHealth(100);
    }
}

void shieldPlayer(Player p)
{
    p.setDeff(true);
}

void shieldMonster(Monster m)
{
    m.setDeff(true);
}

void specialAttackMonster(Player p, Monster m)
{
    //can break shield and fog, not confusion
    if(m.getConfusion() == false){
        p.setHealth(p.getHealth() - 2 * m.getAttack());
        p.setDeff(false);
    }
    else{
        m.setHealth(m.getHealth() - 2 * m.getAttack());
        m.setConfusion(false);
    }
}

void specialAttackPlayerVsPlayer(Player p1, Player p2)
{
    //can break shield and fog, not confusion
    if(p2.getConfusion() == false){
        p1.setHealth(p1.getHealth() - 2 * p2.getAttack());
        p1.setDeff(false);
    }
    else{
        p2.setHealth(p2.getHealth() - 2 * p2.getAttack());
        p2.setConfusion(false);
    }
}

void specialAttackPlayerVsMonster(Monster m, Player p)
{
    //can break shield and fog, not confusion
    if(p.getConfusion() == false){
        m.setHealth(m.getHealth() - 2 * p.getAttack());
        m.setDeff(false);
    }
    else{
        p.setHealth(p.getHealth() - 2 * p.getAttack());
        p.setConfusion(false);
    }
}

void buffStrengthPlayer(Player p)
{
    // buff by 20%, might reduce it
    p.setAttack(p.getAttack() + ((p.getAttack() * 20) / 100));
}

void buffStrengthMonster(Monster m)
{
    // buff by 20%, might reduce it
    m.setAttack(m.getAttack() + ((m.getAttack() * 20) / 100));
}

void megaHealPlayer(Player p)
{
    // i m thinking of implementing this for a mage support class
    if (p.getHealth() < 100)
    {
        p.setHealth(p.getHealth() + 30);
    }
    if (p.getHealth() > 100)
    {
        p.setHealth(100);
    }
}

void megaHealMonster(Monster m)
{
    // i m thinking of implementing this for a mage support class
    if (m.getHealth() < 100)
    {
        m.setHealth(m.getHealth() + 30);
    }
    if (m.getHealth() > 100)
    {
        m.setHealth(100);
    }
}

void fogMonsterOrPlayerVsPlayer(Player p)
{
    // i m thinking with this to make it such that the entity attacked has a 50% chance to miss
    // use random nr generator
    // make it as an effect, calculate here and make it be effective(true) or noneffective(false)
    int decision;

    srand((unsigned)time(NULL));
    decision = 1 + (rand() % 10);

    if(decision % 2 == 0){
        //effect applied
        cout << "Attack was succesful!" << endl; 
        p.setFog(true);
    }
    else cout << "Attack failed" << endl;
}

void fogPlayerVsMonster(Monster m)
{
    // i m thinking with this to make it such that the entity attacked has a 50% chance to miss
    // use random nr generator
    // make it as an effect, calculate here and make it be effective(true) or noneffective(false)
    int decision;

    srand((unsigned)time(NULL));
    decision = 1 + (rand() % 10);

    if(decision % 2 == 0){
        //effect applied
        cout << "Attack was succesful!" << endl; 
        m.setFog(true);
    }
    else cout << "Attack failed" << endl;
}

void confusionMonsterOrPlayerVsPlayer(Player p)
{
    // i m thinking of making this as a move to make the entity hit with it hit himself next round
    // have to implement it as an effect, like shield
    int decision;

    srand((unsigned)time(NULL));
    decision = 1 + (rand() % 10);

    if(decision % 2 == 0){
        //effect applied
        cout << "Attack was succesful!" << endl; 
        p.setConfusion(true);
    }
    else cout << "Attack failed" << endl;
}

void confusionPlayerVsMonster(Monster m)
{
    // i m thinking of making this as a move to make the entity hit with it hit himself next round
    // have to implement it as an effect, like shield
    int decision;

    srand((unsigned)time(NULL));
    decision = 1 + (rand() % 10);

    if(decision % 2 == 0){
        //effect applied
        cout << "Attack was succesful!" << endl; 
        m.setConfusion(true);
    }
    else cout << "Attack failed" << endl;
}

void healAllyMonster(Monster m)
{
    if (m.getHealth() < 100)
    {
        m.setHealth(m.getHealth() + 20);
    }
    if (m.getHealth() > 100)
    {
        m.setHealth(100);
    }
}

void healAllyPlayer(Player p)
{
    if (p.getHealth() < 100)
    {
        p.setHealth(p.getHealth() + 20);
    }
    if (p.getHealth() > 100)
    {
        p.setHealth(100);
    }
}

void leechMonster(Player p, Monster m)
{
    if (p.getDeff() != true)
    {
        p.setHealth(p.getHealth() - m.getAttack() / 2);
        if (m.getHealth() < 100)
        {
            m.setHealth(m.getHealth() + m.getAttack()*30/100);
        }
        if (m.getHealth() > 100)
        {
            m.setHealth(100);
        }
    }
    else
    {
        cout << "Enemy has deffence on" << endl;
        p.setDeff(false);
    }
}

void leechPlayerVsPlayer(Player p1, Player p2){
    if (p1.getDeff() != true)
    {
        p1.setHealth(p1.getHealth() - p2.getAttack() / 2);
        if (p2.getHealth() < 100)
        {
            p2.setHealth(p2.getHealth() + p2.getAttack()*30/100);
        }
        if (p2.getHealth() > 100)
        {
            p2.setHealth(100);
        }
    }
    else
    {
        cout << "Enemy has deffence on" << endl;
        p1.setDeff(false);
    }
}

void leechPlayerVsMonster(Monster m, Player p){
    if (m.getDeff() != true)
    {
        m.setHealth(m.getHealth() - p.getAttack() / 2);
        if (p.getHealth() < 100)
        {
            p.setHealth(p.getHealth() + p.getAttack()*30/100);
        }
        if (p.getHealth() > 100)
        {
            p.setHealth(100);
        }
    }
    else
    {
        cout << "Enemy has deffence on" << endl;
        m.setDeff(false);
    }
}

// end moves

void TurnPlayerVsMonster(Player &p, Monster &m, int nrCom)
{
    Moves attackBase, heal, defend, attackSpecial;
    attackBase.setSp(15);
    heal.setSp(3);
    defend.setSp(5);
    attackSpecial.setSp(4);

    switch ((nrCom))
    {
    case 1:
        if (m.getDeff() != true)
        {
            m.setHealth(m.getHealth() - p.getAttack());
        }
        else
        {
            cout << "Enemy has deffence on" << endl;
            m.setDeff(false);
        }
        break;
    case 2:
        if (p.getHealth() < 100)
        {
            p.setHealth(p.getHealth() + 10);
        }
        if (p.getHealth() > 100)
        {
            p.setHealth(100);
        }
        break;
    case 3:
        p.setDeff(true);
        break;
    case 4:
        m.setHealth(m.getHealth() - 2 * p.getAttack());
        m.setDeff(false);
        break;
    default:
        cout << "No move selected, turn lost:(" << endl;
        break;
    }
}

void TurnPlayerVsPlayer(Player &p1, Player &p2, int nrCom)
{
    Moves attackBase, heal, defend, attackSpecial;
    attackBase.setSp(15);
    heal.setSp(3);
    defend.setSp(5);
    attackSpecial.setSp(4);

    switch ((nrCom))
    {
    case 1:
        if (p2.getDeff() != true)
        {
            p2.setHealth(p2.getHealth() - p1.getAttack());
        }
        else
        {
            cout << "Enemy has deffence on" << endl;
            p2.setDeff(false);
        }
        break;
    case 2:
        if (p1.getHealth() < 100)
        {
            p1.setHealth(p1.getHealth() + 10);
        }
        if (p1.getHealth() > 100)
        {
            p1.setHealth(100);
        }
        break;
    case 3:
        p1.setDeff(true);
        break;
    case 4:
        p2.setHealth(p2.getHealth() - 2 * p1.getAttack());
        p2.setDeff(false);
        break;
    default:
        cout << "No move selected, turn lost, be more careful:(" << endl;
        break;
    }
}

void TurnMonster(Monster &m, Player &p, int nrCom)
{
    Moves attackBase, heal, defend, attackSpecial;
    attackBase.setSp(15);
    heal.setSp(3);
    defend.setSp(5);
    attackSpecial.setSp(4);

    switch ((nrCom))
    {
    case 1: // attack base
        if (p.getDeff() != true)
        {
            p.setHealth(p.getHealth() - m.getAttack());
        }
        else
        {
            cout << "Enemy has deffence on" << endl;
            p.setDeff(false);
        }
        break;
    case 2: // attack special
        p.setHealth(p.getHealth() - 2 * m.getAttack());
        p.setDeff(false);
        break;
    case 3: // heal
        if (m.getHealth() < 100)
        {
            m.setHealth(m.getHealth() + 10);
        }
        if (m.getHealth() > 100)
        {
            m.setHealth(100);
        }
        break;
    case 4: // shield
        m.setDeff(true);
        break;
    default:
        cout << "No move selected, turn lost, be more careful:(" << endl;
        break;
    }
}

int gameOnPvE(Player p, Monster m)
{

    // Scenarios:
    // 1. Player won
    // 2. Monster won
    // 3. Game still on

    int answ;

    if (m.getHealth() <= 0)
        answ = 1;
    else if (p.getHealth() <= 0)
        answ = 2;
    else
        answ = 3;

    return answ;
}

int gameOnPvP(Player p1, Player p2)
{

    // Scenarios:
    // 1. Player1 won
    // 2. Player2 won
    // 3. Game still on

    int answ;

    if (p2.getHealth() <= 0)
        answ = 1;
    else if (p1.getHealth() <= 0)
        answ = 2;
    else
        answ = 3;

    return answ;
}

int main()
{
    Player p1, p2;
    Monster m1;
    int moveP, moveM, answerNewGame, gameMode, moveP1, moveP2;
    bool newGame = true;

    while (newGame == true)
    {
        cout << "Select game mode: " << endl
             << "1. PvP" << endl
             << "2. PvE" << endl
             << "Select one: ";
        cin >> gameMode;

        while (gameMode != 1 && gameMode != 2)
        {
            cout << "Select a possible instruction: ";
            cin >> gameMode;
        }
        if (gameMode == 1)
        {
            while (gameOnPvP(p1, p2) == 3)
            {

                cout << "Number for move(1-attack, 2-heal, 3-shield, 4-special attack): " << endl;
                cout << "Player 1: ";
                cin >> moveP1;
                cout << "Player 2: ";
                cin >> moveP2;

                cout << "Player 1 used: ";

                switch (moveP1)
                {
                case 1:
                    cout << "Basic attack";
                    break;

                case 2:
                    cout << "Heal";
                    break;

                case 3:
                    cout << "Shield";
                    break;

                case 4:
                    cout << "Special attack";
                    break;

                default:
                    break;
                }

                cout << endl;

                TurnPlayerVsPlayer(p1, p2, moveP1);

                if (p2.getHealth() <= 0)
                {
                    p2.setHealth(0);

                    cout << "Health Player 1: " << p1.getHealth() << endl
                         << "Health Player 2: " << p2.getHealth() << endl;

                    if (gameOnPvP(p1, p2) == 1)
                    {
                        cout << "Player 1 won! Congratulations!" << endl;
                    }
                }
                else
                {
                    cout << "Player 2 used: ";

                    switch (moveP2)
                    {
                    case 1:
                        cout << "Basic attack";
                        break;

                    case 2:
                        cout << "Heal";
                        break;

                    case 3:
                        cout << "Shield";
                        break;

                    case 4:
                        cout << "Special attack";
                        break;

                    default:
                        break;
                    }

                    cout << endl;

                    TurnPlayerVsPlayer(p2, p1, moveP2);

                    if (p1.getHealth() < 0)
                        p1.setHealth(0);

                    cout << "Health Player 1: " << p1.getHealth() << endl
                         << "Health Player 2: " << p2.getHealth() << endl;

                    if (gameOnPvP(p1, p2) == 2)
                    {
                        cout << "Player 2 won! Congratulations!" << endl;
                    }
                }
            }
        }
        else
        {

            while (gameOnPvE(p1, m1) == 3)
            {

                cout << "Number for move(1-attack, 2-heal, 3-shield, 4-special attack): ";
                cin >> moveP;

                cout << "Player used: ";

                switch (moveP)
                {
                case 1:
                    cout << "Basic attack";
                    break;

                case 2:
                    cout << "Heal";
                    break;

                case 3:
                    cout << "Shield";
                    break;

                case 4:
                    cout << "Special attack";
                    break;

                default:
                    cout << "Turn lost, be more careful!";
                    break;
                }

                cout << endl;

                TurnPlayerVsMonster(p1, m1, moveP);

                if (m1.getHealth() <= 0)
                {
                    m1.setHealth(0);

                    cout << "Health Player: " << p1.getHealth() << endl
                         << "Health Monster: " << m1.getHealth() << endl;

                    if (gameOnPvE(p1, m1) == 1)
                        cout << "Player won! Congratulations!" << endl;
                }
                else
                {
                    srand((unsigned)time(NULL));

                    if (m1.getDeff() == true)
                    {
                        moveM = 1 + (rand() % 3);
                    }
                    else if (m1.getHealth() == 100)
                    {
                        do
                        {
                            moveM = 1 + (rand() % 4);
                        } while (moveM != 3);
                    }
                    else
                    {
                        moveM = 1 + (rand() % 4);
                    }

                    cout << "Monster used: ";

                    switch (moveM)
                    {
                    case 1:
                        cout << "Basic attack";
                        break;

                    case 2:
                        cout << "Special attack";
                        break;

                    case 3:
                        cout << "Heal";
                        break;

                    case 4:
                        cout << "Shield";
                        break;

                    default:
                        break;
                    }

                    cout << endl;

                    TurnMonster(m1, p1, moveM);

                    if (p1.getHealth() < 0)
                        p1.setHealth(0);

                    cout << "Health Player: " << p1.getHealth() << endl
                         << "Health Monster: " << m1.getHealth() << endl;

                    if (gameOnPvE(p1, m1) == 2)
                        cout << "Monster won! You'll get them next time" << endl;
                }
            }
        }

        cout << "Another game?" << endl
             << "1-yes, 2-no" << endl
             << "Answer: ";
        cin >> answerNewGame;

        while (answerNewGame != 1 && answerNewGame != 2)
        {
            cout << "Select a possible instruction: ";
            cin >> answerNewGame;
        }

        if (answerNewGame == 1)
        {
            p1.setHealth(100);
            m1.setHealth(100);
            p2.setHealth(100);
        }

        if (answerNewGame == 2)
        {
            cout << "-------End of game-------" << endl;
            newGame = false;
        }
    }

    return 0;
}

// coditions for sp(take the move declarations from turn functions, so u can decrement sp, you have to initialize them at the start of the game);
// for this you can create 2 more fct, moveMonster and MovePlayer, just to have constructors and getter and setters;
// use them to construct the sp for the moves and decrement them properly;

// make it able to sellect nr of monsters and players;

// add bufs to attacks and stuff;

// make attack their own fct;

//attacks follow the rule target-attacker

//make fireball with tic dmg for mage;