#include <fstream>
#include <ctime>
#include "FileProcessor.h"

using namespace std;

FileProcessor::FileProcessor(){

}

//overloaded constructor that takes input from inputFile
FileProcessor::FileProcessor(string inputFile){
    int line;
    ifstream file(inputFile);
    file >> L;
    file >> N;
    file >> V;
    file >> m_coinProbability;
    file >> m_nothingProbability;
    file >> m_goombaProbability;
    file >> m_koopaProbability;
    file >> m_mushroomProbability;
}

FileProcessor::~FileProcessor(){

}

//mutators and accessors for FileProcessor
int FileProcessor::getL(){
    return L;
}

int FileProcessor::getN(){
    return N;
}

int FileProcessor::getV(){
    return V;
}

int FileProcessor::getCoinProbability(){
    return m_coinProbability;
}

int FileProcessor::getNothingProbability(){
    return m_nothingProbability;
}

int FileProcessor::getGoombaProbability(){
    return m_goombaProbability;
}

int FileProcessor::getKoopaProbability(){
    return m_koopaProbability;
}   

int FileProcessor::getMushroomProbability(){
    return m_mushroomProbability;
}
