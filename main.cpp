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

void extractSystem(const string& filename, ltiSystem& newSystem) 
{
    // Extract coefficients of an LTI system from filename
    ltiSystem tempSystem(filename);
    // If successful, LTI system will be simulated
    if (tempSystem.isValidSystem())
    {
        // Replaces current system if a new one is validated
        newSystem = tempSystem;
        cout << "valid system" << "\n";
        // Output "new system" to logfile
        // Output "ready" to logfile
        // Clear initial conditions to 0.0
        // Display info if successful
        cout << "Extracted LTI system from file: " << filename << '\n';
    }
    else 
    {
        cout << "Failed to extract LTI system from file:" << filename << '\n';
    }
}

void extractSignal(const string& filename) 
{
    // Extract a signal from filename
    // Signal serves as input (x) to LTI system, one sample at a time
    // Ignore starting index
    // Log each input-output (x,y) pair with \t 
    // If duration < 10, print in console
    // Else provide summary of number of inputs simulated
    cout << "Extracted input signal from file: " << filename << '\n';
}

void clearMemory()
{
    // Clear memory of previous inputs & outputs to 0
    // Log "clear"
    cout << "Memory cleared\n";
}

void inputNumber(double &number) 
{
    // Print error if LTI system has been defined
    // Input number as next input to system
    // Next output is computed
    // Print output to screen
    // Log input-output with \t 
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

    ltiSystem newSystem;

    // test
    // Signal x("test.txt");
    // ltiSystem y("lab5.system");

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
            extractSystem(userInput.substr(7), newSystem);
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
            inputNumber(number);
        }
    }

    return 0;
}