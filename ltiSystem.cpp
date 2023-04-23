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
    int nonRecursiveCoefficient, recursiveCoefficient;

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
        "Non-recursive coefficient must be an integer" << std::endl;
        return;
    }
    if(!(std::floor(integerCheck) == integerCheck))
    {
        std::cerr << "Error: Invalid system file\n"
        "Non-recursive coefficient must be an integer" << std::endl;
        return;
    }
    // std::cout << "integercheck:" << integerCheck << '\n';
    if (integerCheck <= 1)
    {
        std::cerr << "Error: Invalid system file\n" 
        "Non-recursive coefficient must be "
        "greater than 0" << std::endl;
        return;
    }
    nonRecursiveCoefficient = integerCheck;
    nonRecursiveCoefficient -= 1;
    // std::cout << "non-recursive coeff:" << nonRecursiveCoefficient << '\n';

    std::getline(file, line);
    ss.clear();
    ss.str(line);
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
    // std::cout << "integercheck:" << integerCheck << '\n';
    if (integerCheck <= 0)
    {
        std::cerr << "Error: Invalid system file\n" 
        "Recursive coefficient must be "
        "greater than 0" << std::endl;
        return;
    }
    recursiveCoefficient = integerCheck;
    // std::cout << "recursive coeff:" << recursiveCoefficient << '\n';

    sizeb = nonRecursiveCoefficient+1;
    // std::cout << "sizeb = " << sizeb << '\n';
    bCoeff = new double[sizeb];
    for (int i=0; i<sizeb; i++)
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
        // std::cout << "bcoeff " << i << " " << bCoeff[i] << '\n';
    }

    sizea = recursiveCoefficient;
    // std::cout << "sizea = " << sizea << '\n';
    aCoeff = new double[sizea];
    for (int i=0; i<sizea; i++)
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
        // std::cout << "acoeff " << i+1 << " " << aCoeff[i] << '\n';
    }
    file.close();
}

void ltiSystem::compute_outputs(double* input_samples, int nSamples, double* output_samples)
{
    for (int n = 0; n < nSamples; n++) 
    {
        double inputNumber, bSumProduct = 0, aSumProduct = 0, computedOutput;
        inputNumber = input_samples[n];
        bSumProduct = bCoeff[0]*inputNumber;
        for (int i=1; i<sizeb; i++)
        {
            bSumProduct += bCoeff[i]*inputs[i-1];
        }
        for (int i=0; i<sizea; i++)
        {
            aSumProduct += aCoeff[i]*outputs[i];
        }
        computedOutput = bSumProduct - aSumProduct;
        for (int i=sizeb-1; i>=1; i--)
        {
            inputs[i] = inputs[i-1];
        }
        inputs[0] = inputNumber;
        for (int i=sizea-1; i>=1; i--)
        {
            outputs[i] = outputs[i-1];
        }
        outputs[0] = computedOutput;
        output_samples[n] = computedOutput;
    }
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
    inputs = new double[sizeb];
    outputs = new double[sizea];
    for (int i=0; i<sizeb; i++)
    {
        inputs[i] = 0;
    }
    for (int i=0; i<sizea; i++)
    {
        outputs[i] = 0;
    }
}

void ltiSystem::clearMemory()
{
    for (int i=0; i<sizeb; i++)
    {
        inputs[i]=0;
    }
    for (int i=0; i<sizea; i++)
    {
        outputs[i]=0;
    }
}