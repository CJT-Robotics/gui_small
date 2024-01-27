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

DataRepository::DataRepository(){}

//no private constructor defined
