#include "Level.h"
#include "FileProcessor.h"
#include "Mario.h"

using namespace std;

Level::Level(){

}

Level::~Level(){

}


char**Level::populate(int gridSize, int coin, int nothing, int goomba, int koopa, int mushroom){
    m_levelArray = new char*[gridSize];
    for(int i = 0; i < gridSize; i++){
        m_levelArray[i] = new char[gridSize];
    }

    int rangeNothing = coin + nothing;
    int rangeGoomba = rangeNothing + goomba;
    int rangeKoopa = rangeGoomba + koopa;
    int rangeMushroom = rangeKoopa + mushroom;

    //populate the grid using the percentage from random chance
    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j <gridSize; j++){
            int randomChance = rand() % 100 + 1;
            if(coin >= randomChance){
                m_levelArray[i][j] = 'c';
            }
            else if(rangeNothing >= randomChance){
                m_levelArray[i][j] = 'x';
            }
            else if(rangeGoomba >= randomChance){
                m_levelArray[i][j] = 'g';
            }
            else if(rangeKoopa >= randomChance){
                m_levelArray[i][j] = 'k';
            }
            else if(rangeMushroom >= randomChance){
                m_levelArray[i][j] = 'm';
            }
            else{
                m_levelArray[i][j] = 'x';
            }
        }
    }    

    return m_levelArray;
}


char*** Level::world(int levels, int gridSize, int coin, int nothing, int goomba, int koopa, int mushroom){
    

    //3d array for the grid for the game
    m_newWorld = new char**[levels];
    for(int i = 0; i < levels; i++){
        m_newWorld[i] = new char*[levels];
        for(int j = 0; j < gridSize; j++){
            m_newWorld[i][j] = new char[gridSize];
            for(int k = 0; k < gridSize; k++){
                m_newWorld[i][j][k] = ' ';
            }
        }
    }

    //populate the grid 
    for(int i = 0; i < levels; i++){
        m_newWorld[i] = populate(gridSize, coin, nothing, goomba, koopa, mushroom);
        if(i < levels - 1){
            placeItems(gridSize, i, m_newWorld); 
        }else{
            placeItemsNoWarp(gridSize, i, m_newWorld); //ignoring the warp pipe
        }
    }

    return m_newWorld;
}

int* Level::placeItems(int gridSize, int level, char*** newWorld){
    int* marioPosition = new int[1];
    
    //assigning 2 each of mario warp and boss's locations to a random spot in the grid
    int marioRandom1 = rand() % gridSize;
    int marioRandom2 = rand() % gridSize;
    int warpRandom1 = rand() % gridSize;
    int warpRandom2 = rand() % gridSize;
    int bossRandom1 = rand() % gridSize;
    int bossRandom2 = rand() % gridSize;

    while(true){ //loop through as long as none of the positions match
        if(marioRandom1 != warpRandom1 && marioRandom1 != bossRandom1 && warpRandom1 != bossRandom1 && marioRandom2 != warpRandom2 && marioRandom2 != bossRandom2 && warpRandom2 != bossRandom2){
            newWorld[level][marioRandom1][marioRandom2] = 'H';
            newWorld[level][warpRandom1][warpRandom2] = 'w';
            newWorld[level][bossRandom1][bossRandom2] = 'H';

            marioPosition[0] = marioRandom1;
            marioPosition[1] = marioRandom2;

            break;
        }
        else{
            // if they match, then re assign the random value positions
            marioRandom1 = (rand()%gridSize);
            marioRandom2 = (rand()%gridSize);

            warpRandom1 = (rand()%gridSize);
            warpRandom2 = (rand()%gridSize);

            bossRandom1 = (rand()%gridSize);
            bossRandom2 = (rand()%gridSize);
        }
    }

    return marioPosition;
}

int* Level::placeItemsNoWarp(int gridSize, int level, char*** newWorld){ //place Mario, the warp pipe, and the boss in the Level
    int* marioPosition = new int[2]; 
   
    //creating random positions for mario and the boss
    int marioRandom3 = rand()%gridSize;
    int marioRandom4 = rand()%gridSize;
    int bossRandom3 = (rand()%gridSize);
    int bossRandom4 = (rand()%gridSize);

    while (bool notSame = true) { //making sure that the values for mario and boss are not the same
        if (marioRandom3 != bossRandom3 && marioRandom4 != bossRandom4){
            newWorld[level][marioRandom3][marioRandom4] = 'H';
            newWorld[level][bossRandom3][bossRandom4] = 'b';
            break;
        }
        else {
            //otherwise, reassign the positions of mario and boss
            marioRandom3 = (rand()%gridSize);
            marioRandom4 = (rand()%gridSize);
            bossRandom3 = (rand()%gridSize);
            bossRandom4 = (rand()%gridSize);
            notSame = true;
        }
    }
    
    //storing the grid position into marioRandom
    marioPosition[0] = marioRandom3;
    marioPosition[1] = marioRandom4;
    return marioPosition;
}

string Level::toString(int levels, int gridSize){ //method that displays the grid in string format
    string s = "";
    for(int i = 0; i < levels; i++){
        for(int j = 0; j < gridSize; j++){
            for(int k = 0; k < gridSize; k++){
                s+= m_newWorld[i][j][k];
            }
            s+="\n";
        }
        s+="\n";
        s+="\n";
    }

    return s;
}

string Level::currentLevelToString(int level, int gridSize){ //prints only the current level to string formalt
    string s = "";
    for (int j = 0; j < gridSize; j++) {
        for(int k = 0; k < gridSize; k++){
            s += m_newWorld[level][j][k];
        }
        s += "\n";
    }
    return s;
}