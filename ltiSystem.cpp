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
        return;
    }
    std::cout << fileName << " is open\n";

    std::getline(file, line);
    std::stringstream ss(line);

    if (!(ss >> integerCheck))
    {
        std::cerr << "Error: Invalid system file\n" 
        "Recursive coefficient must be an integer" << std::endl;
        return;
    }
    
    if(!(std::floor(integerCheck) == integerCheck))
    {
        std::cerr << "Error: Invalid system file\n"
        "Recursive coefficient must be an integer" << std::endl;
        return;
    }

    // test
    std::cout << "integercheck:" << integerCheck << '\n';

    if (integerCheck <= 1)
    {
        std::cerr << "Error: Invalid system file\n" 
        "Recursive coefficient must be "
        "greater than 0" << std::endl;
        return;
    }

    recursiveCoefficient = integerCheck;
    recursiveCoefficient -= 1;

    std::cout << "recursive coeff:" << recursiveCoefficient << '\n';

    std::getline(file, line);
    ss.clear();
    ss.str(line);

    if (!(ss >> integerCheck))
    {
        std::cerr << "Error: Invalid system file\n" 
        "Non-recursive coefficient must be an integer" << std::endl;
        return;
    }
    
    if(!(std::floor(integerCheck) == integerCheck))
    {
        std::cerr << "Error: Invalid system file\n"
        "Non-recursive coefficient must be an integer" << std::endl;
        return;
    }

    // test
    std::cout << "non-recursive coeff:" << integerCheck << '\n';

    if (integerCheck <= 0)
    {
        std::cerr << "Error: Invalid system file\n" 
        "Non-recursive coefficient must be "
        "greater than 0" << std::endl;
        return;
    }

    nonRecursiveCoefficient = integerCheck;

    std::cout << "non-recursive coeff:" << nonRecursiveCoefficient << '\n';

    file.close();
}

void ltiSystem::compute_outputs()
{
    std::cout << "test\n";
}