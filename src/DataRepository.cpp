#include "DataRepository.h"
#include <mutex>

using namespace std;

DataRepository* DataRepository::instance = nullptr;
mutex DataRepository::mu;


DataRepository& DataRepository::getInstance(){
    lock_guard<mutex> lock(mu);
    if(instance == nullptr){
        instance = new DataRepository();
    }

    return *instance;
}

DataRepository::DataRepository(){
    onExit = false;
}

void DataRepository::exit(){
    lock_guard<mutex> lock(onExitMutex);
    onExit = true;
}

bool DataRepository::getExitStatus(){
    lock_guard<mutex> lock(onExitMutex);
    return onExit;
}

//no private constructor defined
