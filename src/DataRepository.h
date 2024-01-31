#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <mutex>


class DataRepository{
    private:
        static DataRepository* instance;
        bool onExit;
        std::mutex onExitMutex;
        static std::mutex mu;
        DataRepository();
        //DataRepository(DataRepository const&) = delete;
        DataRepository& operator =(DataRepository const&) = delete;

        //secondary variables


    public:
        static DataRepository& getInstance();
        void exit();
        bool getExitStatus();
        //secondary thread-safe get-set functions

};




#endif