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

Signal::Signal(const std::string &fileName)
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

void Signal::processFile(const std::string &fileName)
{
    std::ifstream file;
    std::string line;
    double indexCheck;
    double data;
    std::vector<double> signalVector;

    file.open(fileName, std::ios::in);
    if (!file)
    {
        std::cerr << "Error: " << fileName
        << " cannot be opened" << std::endl;
        return;
    }
    std::cout << fileName << " is open\n";

    std::getline(file, line);
    std::stringstream ss(line);

    if (!(ss >> indexCheck))
    {
        std::cerr << "Error: Invalid file signal" << std::endl;
        return;
    }

    if(std::floor(indexCheck) == indexCheck)
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

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            std::stringstream ss(line);
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
    std::copy(signalVector.begin(), signalVector.end(), signalArray);

    std::cout << "Signal of duration " <<
    duration << " extracted from " <<
    fileName << "\n";
}

void Signal::destroySignalArray()
{
    delete[] signalArray;
}

void Signal::displaySignalContent()
{
    std::cout << "Index: " << index << '\n'
    << "Duration: " << duration << '\n';
    if (duration < 20)
    {
        for (int i = 0; i < duration; i++)
        {
            std::cout << signalArray[i] << '\n';
        }
    }
    std::cout << '\n';
}
