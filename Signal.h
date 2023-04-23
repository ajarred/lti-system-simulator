#ifndef SIGNAL_H
#define SIGNAL_H
#include <iostream>
#include <string>

class Signal
{
    private:
        double *signalArray;
        int index = 0;
        int duration = 0;

    public:
        Signal();

        Signal(const std::string &fileName);

        double* getSignalArray();

        int getDuration();

        int getIndex();

        void setIndex(int newIndex);

        void processFile(const std::string &fileName);

        void destroySignalArray();

        void displaySignalContent();
};

#endif 
