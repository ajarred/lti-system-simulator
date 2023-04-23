#include "ltiSystem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

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
    std::cout << "integercheck:" << integerCheck << '\n';

    if (integerCheck <= 0)
    {
        std::cerr << "Error: Invalid system file\n" 
        "Non-recursive coefficient must be "
        "greater than 0" << std::endl;
        return;
    }

    nonRecursiveCoefficient = integerCheck;

    std::cout << "non-recursive coeff:" << nonRecursiveCoefficient << '\n';

    sizea = recursiveCoefficient+1;
    std::cout << "sizea = " << sizea << '\n';
    aCoeff = new double[sizea];

    for (int i=0; i <= recursiveCoefficient; i++)
    {
        if (!std::getline(file, line))
        {
            std::cerr << "Error: Invalid system file\n"
            "Not enough coefficients provided" << std::endl;
            return;
        }
        
        std::stringstream ss(line);
        double value;
        if (!(ss >> value))
        {
            std::cerr << "Error: Invalid system file\n"
            "Coefficient must be a double" << std::endl;
            return;
        }
        aCoeff[i] = value;

        // test
        std::cout << "acoeff " << i << " " << aCoeff[i] << '\n';
    }

    sizeb = nonRecursiveCoefficient;
    std::cout << "sizeb = " << sizeb << '\n';
    bCoeff = new double[nonRecursiveCoefficient];

    for (int i=0; i < nonRecursiveCoefficient; i++)
    {
        if (!std::getline(file, line))
        {
            std::cerr << "Error: Invalid system file\n"
            "Not enough coefficients provided" << std::endl;
            return;
        }
        
        std::stringstream ss(line);
        double value;
        if (!(ss >> value))
        {
            std::cerr << "Error: Invalid system file\n"
            "Coefficient must be a double" << std::endl;
            return;
        }
        bCoeff[i] = value;

        // test
        std::cout << "bcoeff " << i+1 << " " << bCoeff[i] << '\n';
    }

    file.close();
}

void ltiSystem::compute_outputs(double* input_samples,int nSamples, double* output_samples)
{
    std::cout << "test\n";
}

bool ltiSystem::isValidSystem() 
{
    if (aCoeff == nullptr || bCoeff == nullptr) 
    {
        return false;
    }

    if (sizea <= 0 || sizeb <= 0) 
    {
        return false;
    }

    if (aCoeff[0] == 0.0) 
    {
        return false;
    }

    return true;
}

void ltiSystem::initializeSystem()
{
    inputs = new double[sizea-1];
    outputs = new double[sizea-1];
    for (int i=0; i<sizea-1; i++)
    {
        inputs[i] = 0;
        std::cout << "x(n" << i-2 << ") = " << inputs[i] << '\n';
        outputs[i] = 0;
        std::cout << "y(n" << i-2 << ") = " << outputs[i] << '\n';
    }
}