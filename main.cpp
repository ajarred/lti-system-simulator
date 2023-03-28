#include "Signal.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

/*
compute_outputs ( double * acoef, double * bcoeff,
double * inputs, double * outputs, int sizea, int sizeb,
double * input_samples, int nSamples,
double * output_samples);
*/

/*
ltiSystem::compute_outputs ( double * input_samples,
int nSamples, double * output_samples);
// The LTI System arrays and their sizes would be
// implied parameters accessible to all member functions
// of the ltiSystem class.
*/

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

void extractSystem(const string& filename) 
{
    // Extract coefficients of an LTI system from filename
    cout << "Extracted LTI system from file: " << filename << '\n';
}

void extractSignal(const string& filename) 
{
    // Extract a signal from filename
    cout << "Extracted input signal from file: " << filename << '\n';
}

void clearMemory()
{
    // Clear memory
    cout << "Memory cleared\n";
}

void clearConsole() 
{
    system("cls");
}

void inputNumber(double &number) 
{
    // Input number to system
    cout << "Input number: " << number << '\n';
}

int main(int argc, char* argv[])
{
    if (argc != 1) 
    {
        cerr << "Error: incorrect number of command line arguments\n"
        << "Usage: " << argv[0] << endl;
        return 1;
    }

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
            extractSystem(userInput.substr(7));
        } 
        else if (userInput.substr(0, 6) == "signal") 
        {
            extractSignal(userInput.substr(7));
        } 
        else if (userInput == "clear")
        {
            clearMemory();
        }
        else if (userInput == "cls") 
        {
            clearConsole();
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
            else
            {
                inputNumber(number);
            }
        }
    }

    return 0;
}