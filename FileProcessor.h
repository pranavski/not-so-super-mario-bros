#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
using namespace std;

class FileProcessor{
    public:
        FileProcessor(); //default constructor 
        FileProcessor(string fileName); //overloaded constructor
        ~FileProcessor(); //default destructor
        char** populate();
        char** levelArray;
        
        //accessors
        int getL();
        int getN();
        int getV();
        int getCoinProbability();
        int getNothingProbability();
        int getGoombaProbability();
        int getKoopaProbability();
        int getMushroomProbability();

    private:
        int L;
        int N;
        int V;
        int m_coinProbability;
        int m_nothingProbability;
        int m_goombaProbability;
        int m_koopaProbability;
        int m_mushroomProbability;

        
};


#endif