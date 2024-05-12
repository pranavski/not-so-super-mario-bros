#include "Mario.h"
#include "FileProcessor.h"

using namespace std;

Mario::Mario(){
    m_powerLevel = 0;
    m_coins = 0;
    m_lives = 0;
    m_kills = 0;
    m_move = "";
    m_action = "";
}

//overloaded constructor to assign lives to the input value V
Mario::Mario(int V){
    m_powerLevel = 0;
    m_coins = 0;
    m_kills = 0;
    m_lives = V;
    m_move = "";
    m_action = "";
}

Mario::~Mario(){

}

bool Mario::isAlive(){
    if(getLives() > 0){
        return true;
    }else{
        return false;
    }
}

void Mario::kill(){
    m_kills++;
    if(m_kills == 7){
        gainLife();
        m_kills = 0;
    }
}

void Mario::gainLevel(){
    while(m_powerLevel <= 2){
        m_powerLevel++;
    }
}

void Mario::loseLevel(){
    m_powerLevel--;
    if(m_powerLevel == 0){
        loseLife();
    }
}

void Mario::gainLife(){
    m_lives++;
}

void Mario::loseLife(){
    m_lives--;
    m_kills = 0;
}

void Mario::gainCoin(){
    m_coins++;
    if(m_coins == 20){
        gainLife();
        m_coins = 0;
    }
}

bool Mario::fightKoopa(Mario &mario){
    m_powerLevel = mario.getPowerLevel();
    m_lives = mario.getLives();
    m_kills = mario.getKills();
    bool enemy = false;
    int random = rand() % 99 + 1;
    if(random <= 65){
        m_kills++;
        mario.setKills(m_kills);
        if(m_kills == 7){ // incrementing m_lives if mario already has 7 kills
            ++m_lives;
            mario.setLives(m_lives);
        }
        return true;
    }else{
        if(m_powerLevel == 0){ // checking condition at PL0
            if(m_lives > 1){
                --m_lives;
                mario.setLives(m_lives);
                m_kills = 0;
                mario.setKills(m_kills);
            }else{
                mario.setLives(0);
            }
        }else{
            --m_powerLevel;
            mario.setPowerLevel(m_powerLevel);
        }
    }
    return false;
}

bool Mario::fightGoomba(Mario &mario){
    m_powerLevel = mario.getPowerLevel();
    m_lives = mario.getLives();
    m_kills = mario.getKills();
    bool enemy = false;
    int random = rand() % 99 + 1;
    if(random <= 80){
        m_kills++;
        mario.setKills(m_kills);
        if(m_kills == 7){
            ++m_lives;
            mario.setLives(m_lives);
        }
        enemy = true;
        return true;
    }else{
        if(m_powerLevel == 0){
            if(1 < m_lives){
                --m_lives;
                mario.setLives(m_lives);
                m_kills = 0;
                mario.setKills(m_kills);
            }else{
                mario.setLives(0);
            }
        }else{
            --m_powerLevel;
            mario.setPowerLevel(m_powerLevel);
        }
    }
    return false;
}

bool Mario::fightBoss(Mario &mario,bool levelStatus){
    m_powerLevel = mario.getPowerLevel();
    m_lives = mario.getLives();
    m_kills = mario.getKills();

    bool exit = false;
    bool ret = false;

    
    while(exit == false){
        int random = rand() % 2;
        switch(random){
            case 0:
                exit = true;
                ret = true;
                ++m_kills;
                mario.setKills(m_kills);
                if(m_kills == 7){
                    ++m_lives;
                    m_kills = 0;
                    mario.setKills(m_kills);
                }
                break;
            case 1:
                if(m_powerLevel <= 1){
                    if(m_lives > 1){
                        --m_lives;
                        mario.setLives(m_lives);
                        m_kills = 0;
                        mario.setKills(m_kills);
                    }else{
                        exit = true;
                        ret = false;
                        mario.setLives(0);
                    }
                }else{
                    m_powerLevel = m_powerLevel - 2;
                    mario.setPowerLevel(m_powerLevel);
                }
                break;
        }
    }
    return ret;
}


int Mario::move(Mario &mario, int* marioPosition, int gridSize, int currentLevel, int powerLevel, int lives, int kills, bool level, bool livesLeft, char*** newWorld, bool enemy){
    int randMove = rand() % 4;
    int* nextMove = new int[2];
    bool enStatus = false;

    switch (randMove){ //randomly determine Mario's next move
        case 0:
            nextMove[0] = marioPosition[0]-1;
            nextMove[1] = marioPosition[1];
            if (nextMove[0] < 0){ //without this it gives segmentation fault
                nextMove[0] = gridSize - 1; 
            }
            m_move = "UP";
            break;
        case 1:
            nextMove[0] = marioPosition[0]+1;
            nextMove[1] = marioPosition[1];
            if (nextMove[0] > gridSize - 1){ //without this it gives a segmentation fault
                nextMove[0] = 0;
            }
            m_move = "Down";
            break;
        case 2:
            nextMove[0] = marioPosition[0];
            nextMove[1] = marioPosition[1]+1;
            if (nextMove[1] > gridSize - 1){ //without this it gives segmentation fault
                nextMove[1] = 0;
            }
            m_move = "Right";
            break;
        case 3:
            nextMove[0] = marioPosition[0];
            nextMove[1] = marioPosition[1]-1;
            if (nextMove[1] < 0){ //without this it gives segmentation fault
                nextMove[1] = gridSize - 1;
            }
            m_move = "Left";
            break;
        default:
            break;
    }
    switch (newWorld[currentLevel][nextMove[0]][nextMove[1]]){ //code for all the interactions Mario has with the environment and enemies.
        case 'c':
            mario.gainCoin();
            enStatus = true;
            m_action = "Mario found a coin!";
            break;
        case 'g':
            enStatus = mario.fightGoomba(mario);
            m_action = "Mario fought a Goomba.";
            break;
        case 'k':
            enStatus = mario.fightKoopa(mario);
            m_action = "Mario fought a Koopa.";
            break;
        case 'm':
            mario.gainLevel();
            enStatus = true;
            m_action = "Mario picked up a mushroom!";
            break;
        case 'x':
            m_action =  "Mario found nothing at this index.";
            enStatus = true;
            break;
        case 'b':
            enStatus = mario.fightBoss(mario, level);
            if(enStatus == true && mario.getLives() > 0){
                return 3; //next level
            }
            break;
        case 'w':
            level = true;
            enStatus = true;
            m_action = "Mario took a warp pipe to the next level.";
            return 3; //next level
        default:
            break;
    }

    if (enStatus == true){
        newWorld[currentLevel][marioPosition[0]][marioPosition[1]] = 'x'; //replace mario's previous position with an 'x'
        marioPosition[0] = nextMove[0];
        marioPosition[1] = nextMove[1];
        newWorld[currentLevel][nextMove[0]][nextMove[1]] = 'H'; // replace the interacted square with mario
        return 1; 
    }
    if(mario.getLives() == 0){
        return 0; //death
    }
    return 2; 
}


// mutators and accessors for mario's methods
int Mario::getPowerLevel(){
    return m_powerLevel;
}

void Mario::setPowerLevel(int powerLevel){
    m_powerLevel = powerLevel;
}

int Mario::getLives(){
    return m_lives;
}

void Mario::setLives(int lives){
    m_lives = lives;
}   

int Mario::getCoins(){
    return m_coins;
}

void Mario::setCoins(int coins){
    m_coins = coins;
}

int Mario::getKills(){
    return m_kills;
}

void Mario::setKills(int kills){
    m_kills = kills;
}

string Mario::getMove(){
    return m_move;
}

string Mario::getAction(){
    return m_action;
}