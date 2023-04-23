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
    << " help             : show this help message\n"
    << " system filename  : load LTI system coefficients from specified file\n"
    << " signal filename  : load input signal from specified file\n"
    << " [number]         : input a floating point number\n"
    << " clear            : clear previous inputs \n"
    << " cls              : clear the console screen\n"
    << " exit             : exit the program\n";
}

void extractSystem(const string& filename, ltiSystem& newSystem, ofstream& logFile) 
{
    ltiSystem tempSystem(filename);
    if (!tempSystem.isValidSystem())
    {
        cout << "Failed to extract LTI system from file:" << filename << '\n';
        return;
    }
    newSystem = tempSystem;
    cout << "valid system" << "\n";
    // logFile << "new system\n";
    // logFile << "ready\n";
    newSystem.initializeSystem();
    cout << "Extracted LTI system from file: " << filename << '\n';
}

void extractSignal(const string& filename, ofstream& logFile) 
{
    // Extract a signal from filename
    Signal inputSignal(filename);
    // Signal serves as input (x) to LTI system, one sample at a time
    // Ignore starting index
    // Log each input-output (x,y) pair with \t 
    // If duration < 10, print in console
    // Else provide summary of number of inputs simulated
}

void clearMemory(ofstream& logFile)
{
    // Clear memory of previous inputs & outputs to 0
    // logFile << "Memory cleared\n";
    cout << "Memory cleared\n";
}

void inputNumber(double &number, ltiSystem& newSystem, ofstream& logFile) 
{
    if (!newSystem.isValidSystem())
    {
        cout << "No LTI system defined. Please extract a system from a file first.\n";
        return;
    }
    double* input_samples = new double[1];
    double* output_samples = new double[1];
    input_samples[0] = number;
    newSystem.compute_outputs(input_samples,1,output_samples);
    cout << output_samples[0] << '\n';
    // logFile << input_samples[0] << '\t' << output_samples[0] << '\n';
}

int main(int argc, char* argv[])
{
    if (argc != 1) 
    {
        cerr << "Error: incorrect number of command line arguments\n"
        << "Usage: " << argv[0] << endl;
        return 1;
    }

    ltiSystem newSystem;

    ofstream logFile("ltisim-log.txt", ios::app);
    if (!logFile.is_open()) 
    {
        cerr << "Log file cannot be opened\n"
        << "Contents will not be logged" << endl;
    }

    cout << "LTI System Simulator\n"
    << "Type \"help\" for more information\n";

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
            extractSignal(userInput.substr(7), logFile);
        } 
        else if (userInput == "clear")
        {
            clearMemory(logFile);
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
            }
            inputNumber(number,newSystem,logFile);
        }
    }

    return 0;
}