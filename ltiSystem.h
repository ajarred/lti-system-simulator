#ifndef LTISYSTEM_H
#define LTISYSTEM_H
#include <iostream>
#include <string>

class ltiSystem
{
    private:
        double* aCoeff; 
        double* bCoeff;

    public:
        ltiSystem();

        ltiSystem(const std::string &fileName);

        void processFile(const std::string& fileName);

        void compute_outputs();
};

#endif 