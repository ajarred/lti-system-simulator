#include "ltiSystem.h"
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>

ltiSystem::ltiSystem()
{

}

ltiSystem::ltiSystem(const std::string& fileName)
{
    processFile(fileName);
}

void ltiSystem::processFile(const std::string& fileName)
{
    std::ifstream file;
    std::string line;
    double integerCheck;
    int nonRecursiveCoefficient;
    int recursiveCoefficient;

    file.open(fileName, std::ios::in);
    if (!file)
    {
        std::cerr << "Error: " << fileName
        << " cannot be opened" << std::endl;
        std::exit(1);
    }
    std::cout << fileName << " is open\n";

    std::getline(file, line);
    std::stringstream ss(line);

    // double check
    if (!(ss >> integerCheck))
    {
        std::cerr << "Error: Invalid system file\n" 
        "Recursive coefficient must be an integer" << std::endl;
        exit(1);
    }

    // int check
    if(!(std::floor(integerCheck) == integerCheck))
    {
        std::cerr << "Error: Invalid system file\n"
        "Recursive coefficient must be an integer" << std::endl;
        exit(1);
    }

    // test
    std::cout << "integercheck:" << integerCheck << '\n';

    // >= 0 check
    if (integerCheck <= 1)
    {
        std::cerr << "Error: Invalid system file\n" 
        "Recursive coefficient must be "
        "greater than 0" << std::endl;
        exit(1);
    }

    recursiveCoefficient = integerCheck;
    recursiveCoefficient -= 1;

    std::cout << "recursive coeff:" << recursiveCoefficient << '\n';
}

void ltiSystem::compute_outputs()
{
    std::cout << "test\n";
}