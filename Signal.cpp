#include "Signal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>

Signal::Signal()
{

}

Signal::Signal(const string &fileName)
{
    processFile(fileName);
}

double* Signal::getSignalArray()
{
    return signalArray;
}

int Signal::getDuration()
{
    return duration;
}

int Signal::getIndex()
{
    return index;
}

void Signal::setIndex(int newIndex)
{
    index = newIndex;
}

void Signal::processFile(const string &fileName)
{
    ifstream file;
    string line;
    double indexCheck;
    double data;
    vector<double>signalVector;

    file.open (fileName, ios::in);
    if (!file)
    {
        cerr << "Error: " << fileName
        << " cannot be opened" << endl;
        exit(1);
    }
    cout << fileName << " is open\n";

    getline(file,line);
    stringstream ss(line);

    if (!(ss >> indexCheck))
    {
        cerr << "Error: Invalid file signal" << endl;
        exit(1);
    }

    if(floor(indexCheck)==indexCheck)
    {
        if(!(ss >> data))
        {
            index = 0;
            data = indexCheck;
            signalVector.push_back(data);
        }
        else
        {
            index = indexCheck;
            signalVector.push_back(data);
        }
    }
    else
    {
        index = 0;
        data = indexCheck;
        signalVector.push_back(data);
    }

    while (getline(file, line))
    {
        if (!line.empty())
        {
            stringstream ss(line);
            while (ss >> data)
            {
                signalVector.push_back(data);
            }
            if(!ss.eof())
            {
                break;
            }
        }
    }

    file.close();
    duration = signalVector.size();
    signalArray = new double[duration];
    copy(signalVector.begin(), signalVector.end(), signalArray);

    cout << "Signal of duration " <<
    duration << " extracted from " <<
    fileName << "\n\n";
}

void Signal::destroySignalArray()
{
    delete[] signalArray;
}

void Signal::displaySignalContent()
{
    cout << "Index: " << index << '\n'
    << "Duration: " << duration << '\n';
    if (duration<20)
    {
        for (int i = 0; i < duration; i++)
        {
            cout << signalArray[i] << '\n';
        }
    }
    cout << '\n';
}
