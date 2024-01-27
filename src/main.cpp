

#include "DataRepository.h"
#include "window.h"
#include "synchronization.h"
#include <thread>
#include "publisher.h"
#include "subscriber.h"

void launchWindow(){
    initWindow();
}

void launchPublisher(int argc, char *argv[]){
    initPublisher(argc,argv);
}

void launchSubscriber(int argc, char *argv[]){
    initSubscriber(argc,argv);
}

int main(int argc, char *argv[]){

    std::thread window(launchWindow);
    std::thread publisher(launchPublisher,argc,argv);
    std::thread subscriber(launchSubscriber,argc,argv);

    printLine("All threads up and running!");

    window.join();
    publisher.join();
    subscriber.join();

    printLine("<<<Shutdown>>>");

    return 0;
}