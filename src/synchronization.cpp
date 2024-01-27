#include "synchronization.h"

#include <string>
#include <mutex>
#include <iostream>

using namespace std;

mutex printMutex;

void print(string s){
    lock_guard<mutex> lock(printMutex);
    cout << s;
}

mutex printLineMutex;

void printLine(string s){
    lock_guard<mutex> lock(printLineMutex);
    cout << s << endl;
}