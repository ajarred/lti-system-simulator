#include "Signal.h"
#include "ltiSystem.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// filter user input
string to_lowercase(string str) 
{
    transform(str.begin(), str.end(), str.begin(), 
    [](unsigned char c){ return tolower(c); });
    return str;
}

void displayHelp() 
{
    cout << "Available commands:\n"
    << "help              : provid information how to use the program\n"
    << "system filename   : extract coefficients of an LTI system from filename\n"
    << "signal filename   : load input signal from filename\n"
    << "[number]          : input a floating point number as next input of the system\n"
    << "clear             : clear previous inputs and outputs of the system\n"
    << "cls               : clear the console screen\n"
    << "exit              : exit the program\n";
}

void extractSystem(const string& filename, ltiSystem& newSystem, ostream& outStream) 
{
    ltiSystem tempSystem(filename);
    newSystem = tempSystem;
    outStream << "new system\n";
    outStream << "ready\n";
    newSystem.initializeSystem();
}

void extractSignal(const string& filename, ltiSystem& newSystem, ostream& outStream) 
{
    if (!newSystem.isValidSystem())
    {
        cout << "No LTI system defined. Please extract a system from a file first.\n";
        return;
    }
    Signal inputSignal(filename);
    int duration = inputSignal.getDuration();
    double* input_samples = inputSignal.getSignalArray();
    double* output_samples = new double[duration];
    newSystem.compute_outputs(input_samples,duration,output_samples);
    for (int i=0; i<duration; i++)
    {
        outStream << input_samples[i] << '\t' << output_samples[i] << '\n';
    }
    if (duration<10)
    {
        for (int i=0; i<duration; i++)
        {
            cout << input_samples[i] << '\t' << output_samples[i] << '\n';
        }
    }
    else 
    {
        cout << duration << " inputs simulated\n";
    }
    delete[] input_samples;
    delete[] output_samples;
}

void clearMemory(ltiSystem& newSystem, ostream& outStream)
{
    if (!newSystem.isValidSystem())
    {
        cout << "No LTI system defined. Please extract a system from a file first.\n";
        return;
    }
    newSystem.clearMemory();
    outStream << "clear\n";
}

void inputNumber(double &numberInput, ltiSystem& newSystem, ostream& outStream) 
{
    if (!newSystem.isValidSystem())
    {
        cout << "No LTI system defined. Please extract a system from a file first.\n";
        return;
    }
    double numberOutput;
    newSystem.compute_outputs(numberInput,numberOutput);
    cout << numberOutput << '\n';
    outStream << numberInput << '\t' << numberOutput << '\n';
}

void ltiSystemSimulator()
{
    ltiSystem newSystem;

    ofstream logFile("ltisim-log.txt", ios::app);
    ostream& outStream = logFile.is_open() ? logFile : cout;
    if (!logFile.is_open()) 
    {
        cerr << "Log file cannot be opened\n"
        << "Contents will not be logged" << endl;
    }

    cout << "LTI System Simulator\n" << 
    "Type \"help\" for more information\n";

    while (true)
    {
        cout << "ltisim> ";
        
        string userInput;
        getline(cin, userInput);
        userInput = to_lowercase(userInput);

        if (userInput == "help") 
        {
            displayHelp();
        } 
        else if (userInput.substr(0, 6) == "system") 
        {
            extractSystem(userInput.substr(7), newSystem, logFile);
        } 
        else if (userInput.substr(0, 6) == "signal") 
        {
            extractSignal(userInput.substr(7), newSystem, logFile);
        } 
        else if (userInput == "clear")
        {
            clearMemory(newSystem, logFile);
        }
        else if (userInput == "cls") 
        {
            system("cls");
        } 
        else if (userInput == "exit") 
        {
            break;
        } 
        else 
        {
            double number;
            stringstream ss(userInput);
            if (!(ss >> number)) 
            {
                cout << "Invalid command. Type \"help\" for a list of commands\n";
                continue;
            }
            inputNumber(number,newSystem,logFile);
        }
    }
    logFile.close();
}

int main(int argc, char* argv[])
{
    ltiSystemSimulator();
    return 0;
}