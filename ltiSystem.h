#ifndef LTISYSTEM_H
#define LTISYSTEM_H
#include <iostream>
#include <string>

class ltiSystem
{
    private:
        double* aCoeff; 
        double* bCoeff;
        double* inputs;
        double* outputs;
        int sizea;
        int sizeb;

    public:
        ltiSystem();

        ltiSystem(const std::string &fileName);

        void processFile(const std::string& fileName);

        void compute_outputs(double* input_samples,int nSamples,double* output_samples);

        bool isValidSystem();

        void initializeSystem();
};

#endif 