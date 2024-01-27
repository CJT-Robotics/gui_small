#include "DataRepository.h"
#include "window.h"
#include "synchronization.h"
#include <thread>
#include "transferNode.h"

void launchWindow(){
    initWindow();
}


void launchNode(int argc, char *argv[]){
    initNode(argc,argv);
}

int main(int argc, char *argv[]){

    std::thread window(launchWindow);
    std::thread node(launchNode,argc,argv);

    printLine("All threads up and running!");
    printLine("Close window & strg+c for complete shutdown!");

    window.join();
    node.join();
    printLine("<<<Shutdown>>>");

    return 0;
}