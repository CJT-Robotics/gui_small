
#include "DataRepository.h"
#include "window.h"
#include "synchronization.h"
#include <thread>
#include "transferNode.h"
#include "controller_stationary.h"

#include <iostream>
#include <string>

using namespace std;

void launchControllerStationary(){
    initControlerStationary();
}

void launchWindow(){
    initWindow();
}


void launchNode(int argc, char *argv[]){
    initNode(argc,argv);
}

int main(int argc, char *argv[]){

    std::thread window(launchWindow);
    std::thread node(launchNode,argc,argv);
    std::thread controller_stat(launchControllerStationary);

    printLine("\033[1;41m All threads up and running! \033[0m\n");
    printLine("\033[1;41m 2 x strg+c for complete shutdown! \033[0m\n");

    window.join();
    node.join();
    controller_stat.join();

    printLine("<<<Shutdown>>>");

    return 0;
}