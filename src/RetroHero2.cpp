#include <iostream>
#include <cstdlib>
using namespace std;

class Player
{
private:
    int health;
    int attack;
    bool deff, confusion, fog, onFire;

public:
    Player()
    {
        this->health = 100;
        this->attack = 10;
        this->deff = false;
        this->confusion = false;
        this->fog = false;
        this->onFire = false;
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

    bool getOnFire(){
        return onFire;
    }

    bool setOnFire(bool newOnFire){
        this->onFire = newOnFire;
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

// moves:

void slash(Player &p1, Player &p2)
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

void heal(Player &p)
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

void shield(Player &p)
{
    p.setDeff(true);
}

void MegaSlash(Player &p1, Player &p2)
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

void buffStrength(Player &p)
{
    // buff by 20%, might reduce it
    p.setAttack(p.getAttack() + ((p.getAttack() * 20) / 100));
}

void megaHeal(Player &p)
{
    // i m thinking of implementing this for a mage support class
    if (p.getHealth() < 100)
    {
        p.setHealth(p.getHealth() + 25);
    }
    if (p.getHealth() > 100)
    {
        p.setHealth(100);
    }
}

void fog(Player &p)
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

void confusion(Player &p)
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

void leech(Player &p1, Player &p2){
    if (p1.getDeff() != true)
    {
        p1.setHealth(p1.getHealth() - (p2.getAttack() + p2.getAttack() / 2));
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

void fireBall(Player &p1, Player &p2){
    int decision;

    srand((unsigned)time(NULL));
    decision = 1 + (rand() % 20);

    if(p1.getDeff() == true){
        cout << "Enemy had shield on" << endl;
        p1.setDeff(false);
    }
    else{
         p1.setHealth(p1.getHealth() - (p2.getAttack() + p2.getAttack() / 2));
    }

    if(decision % 4 == 0){
        if(p1.getOnFire() == false){
            cout << "Enemy has been set on fire" << endl;
            p1.setOnFire(true);
        }
        else cout << "Enemy is already on fire" << endl;
    }
    else cout << "Enemy was not set on fire:((" << endl;
}

// end moves

void TurnPlayerVsMonster(Player &p, Player &m, int nrCom)
{
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

void TurnMonster(Player &m, Player &p, int nrCom)
{
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

int gameOnPvE(Player p, Player m)
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
    int moveP, moveM, answerNewGame, gameMode, moveP1, moveP2;
    bool newGame = true;

/*
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
*/
    
    while(p1.getHealth() > 0){
        
        int decision;
        cout << endl << "Move: ";
        cin >> decision;

        if(decision == 1){
            slash(p1, p2);
        }
        if(decision == 2){
            heal(p1);
        }
        if(decision == 3){
            shield(p1);
            if(p1.getDeff() == true)cout << "Shield on bitch" << endl;
        }
        if(decision == 4){
            MegaSlash(p1, p2);
        }
        if(decision == 5){
             cout << "Strength then: " << p1.getAttack() << endl;
            buffStrength(p1);
            cout << "Strength now: " << p1.getAttack() << endl;
        }
        if(decision == 6){
            megaHeal(p1);
        }
        if(decision == 7){
            fog(p1);
            if(p1.getFog() == true)cout << "Fog on bitch" << endl;
        }
        if(decision == 8){
            confusion(p1);
            if(p1.getConfusion() == true)cout << "Confusion on bitch" << endl;
        }
        if(decision == 9){
            leech(p1, p2);
            cout << "P1: " << p1.getHealth() << endl << "P2: " << p2.getHealth() << endl;
        }
        if(decision == 10){
            fireBall(p1, p2);
        }

        cout << "P1 HP:" << p1.getHealth() << endl;
    }

    cout << "-------Game Over-------";
    
}

//attacks follow the rule target-attacker

//make the fireball continuous dmg work(after queue of moves is empty, check if setOnFire is true and reduce the hp by 2-5 points(randomised))
