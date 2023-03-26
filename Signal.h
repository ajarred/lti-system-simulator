#ifndef SIGNAL_H
#define SIGNAL_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Signal
{
    private:
        double *signalArray;
        int index = 0;
        int duration = 0;

    public:
        Signal();

        Signal(const string &fileName);

        double* getSignalArray();

        int getDuration();

        int getIndex();

        void setIndex(int newIndex);

        void processFile(const string &fileName);

        void destroySignalArray();

        void displaySignalContent();
};

#endif // SIGNAL_H
