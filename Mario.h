#ifndef MARIO_H
#define MARIO_H

#include <iostream>
using namespace std;

class Mario{
    public:
        Mario();
        Mario(int V);
        ~Mario();
        bool isAlive();
        void move();
        void kill();
        void gainLevel();
        void loseLevel();
        void gainLife();
        void loseLife();
        void gainCoin();
        bool fightKoopa(Mario &mario);
        bool fightGoomba(Mario &mario);
        bool fightBoss(Mario &mario, bool levelStatus);
        int move(Mario &m1, int* marioPosition, int gridSize, int currentLevel, int mPL, int mLives, int mKills, bool levelStatus, bool livesLeft, char*** newWorld, bool enemyStatus);


        //accessors and mutators
        int getPowerLevel();
        void setPowerLevel(int powerLevel);
        int getLives();
        void setLives(int lives);
        int getCoins();
        void setCoins(int coins);
        int getKills();
        void setKills(int lives);
        bool getWon();
        void setWon(bool won);
        string getMove();
        string getAction();
        
    private:
        int m_powerLevel;
        int m_lives;
        int m_coins; 
        int m_kills;
        string m_move;
        string m_action;
        bool m_win;
};
#endif