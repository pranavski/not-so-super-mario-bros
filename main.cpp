#include "Mario.h"
#include "Level.h"
#include "FileProcessor.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    //creating a new FileProcessor object
    FileProcessor* File = new FileProcessor("input.txt");
    ofstream outputFile("outputFile.txt");

    //getting all the values from input.txt
    int L = File->getL();
    int N = File->getN();
    int V = File->getV();
    int coin = File->getCoinProbability();
    int nothing = File->getNothingProbability();
    int goomba = File->getGoombaProbability();
    int koopa = File->getKoopaProbability();
    int mushroom = File->getMushroomProbability();

    //create a new mario object
    Mario mario(V);
    int moveCounter = 0;
    char*** newWorld = new char**[4];
    int* marioPosition = new int[1];
    bool levelStatus = false;
    bool livesLeft = true;
    bool enemyStatus = false;
    int currentLevel = 0;
    Level* level = new Level();

    newWorld = level->world(L,N,coin,nothing,goomba,koopa,mushroom);
    level->toString(currentLevel, N);

    int moveStatus = 1; 
    
    outputFile << level->toString(L, N);

    while (moveStatus != 0 && mario.getLives() > 0){

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(newWorld[currentLevel][i][j] == 'H'){
                    marioPosition[0] = i;
                    marioPosition[1] = j;
                }
            }
        }
        outputFile << "Current Level: " << currentLevel << "." << endl;
        outputFile << "Mario at index: " << marioPosition[0] << ", " << marioPosition[1] << "." << endl;
        outputFile << "Mario's power level: " << mario.getPowerLevel() << "." << endl;
        moveStatus = mario.move(mario, marioPosition, N, currentLevel, mario.getPowerLevel(), mario.getLives(), mario.getKills(), levelStatus, livesLeft, newWorld, enemyStatus);
        outputFile << mario.getAction();
        outputFile << "\n";
        outputFile << "Mario has " << mario.getLives() << " lives." << endl;
        outputFile << "Mario has " << mario.getCoins() << " coins." << endl;
        outputFile << "Mario will move " << mario.getMove() << endl;
        outputFile << "\n";
        outputFile << level->currentLevelToString(currentLevel,N);
        outputFile << "\n";
        outputFile << "\n";



    
        if(moveStatus == 3){
            currentLevel++;
            moveStatus = 1;
            if(currentLevel == L){
                break; //ends if the current level is equal to the level passed
            }
            level->currentLevelToString(currentLevel, N);
        }
    
    

        level->currentLevelToString(currentLevel, N);
    }

    if(mario.getLives() == 0){ //checks how many lives mario has to end the game
        outputFile << endl << "You lose!" << endl;
    }
    else{
        outputFile << endl << "Mario saved the princess!" << endl;
    }
}