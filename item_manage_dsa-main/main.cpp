#include <iostream>
#include <fstream>
#include "utils.h" // Include utils.h instead of utils.cpp
#include "data.h"  // Include data.h for the Item structure

using namespace std;

int main()
{
    // Ensure the file exists
    if (!openFile(filename)) {
        // Create the file if it doesn't exist
        ofstream createFile(filename);
        if (createFile.is_open()) {
            createFile.close();
            cout << "Created new items file: " << filename << endl;
        } else {
            cerr << "Failed to create items file. Check permissions." << endl;
            return 1;
        }
    }

    cout << "=============================================================" << endl;
    cout << "**********=   WELCOME TO ITEM MANAGEMENT SYSTEM     =********" << endl;
    cout << "**********=   Developed by Remy Tresor - RCA   =********" << endl;
    cout << "=============================================================" << endl;

    cout << "The commands available are: itemslist, itemadd and help\n"
         << "Use help to view command usage" << endl;

    // Show help on startup to make it clear what to do
    help();
    
    string input;
    while (true)
    {
        cout << ">> " << flush; // Add flush to ensure prompt is displayed
        if (!getline(cin, input))
        {
            break;
        }
        
        // Skip empty commands
        if (input.empty()) {
            continue;
        }
        
        processCommand(input);
        cout << endl; // Add a blank line for better readability
    }

    return 0;
}