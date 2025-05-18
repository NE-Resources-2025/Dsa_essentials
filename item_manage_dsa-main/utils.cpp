#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

bool openFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        // Don't output an error, just return false
        // The main function will handle creating the file if needed
        return false;
    }
    else
    {
        file.close(); // Close the file after checking
        return true;
    }
}

vector<string> split(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
};

bool isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return true;
    }
    return false;
}

bool validateDate(const string &date)
{
    vector<string> parts = split(date, '-');
    if (parts.size() != 3)
    {
        cout << "Error: Date format should be dd-mm-yyyy" << endl;
        return false;
    }

    // Check if parts are numeric before converting
    for (const auto &part : parts) {
        for (char c : part) {
            if (!isdigit(c)) {
                cout << "Error: Date parts must be numeric" << endl;
                return false;
            }
        }
    }

    try {
        int day = stoi(parts[0]);
        int month = stoi(parts[1]);
        int year = stoi(parts[2]);

        if (month < 1 || month > 12)
        {
            cout << "Error: Month must be between 1 and 12" << endl;
            return false;
        }
        if (year < 1)
        {
            cout << "Error: Year must be positive" << endl;
            return false;
        }

        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (month == 2 && isLeapYear(year))
        {
            daysInMonth[1] = 29; // February has 29 days in leap years
        }

        if (day < 1 || day > daysInMonth[month - 1])
        {
            cout << "Error: Day must be between 1 and " << daysInMonth[month - 1] 
                 << " for month " << month << endl;
            return false;
        }

        return true;
    }
    catch (const std::exception &e) {
        cout << "Error: Invalid date format. Please use dd-mm-yyyy" << endl;
        return false;
    }
}

bool addItem(Item item)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile)
    {
        cerr << "Error opening file: " << filename << endl;
        return false; // Fixed: was returning 1
    }
    outputFile << item.id << "," << item.name << "," << item.quantity << "," << item.regDate << endl;
    return true; // Added: return a proper value
}

void listItems()
{
    vector<Item> items;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Could not open the file " << filename << endl;
        exit(0);
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string token;
        Item item;

        if (getline(iss, token, ','))
        {
            item.id = stoi(token);
        }
        if (getline(iss, token, ','))
        {
            item.name = token;
        }
        if (getline(iss, token, ','))
        {
            item.quantity = stoi(token);
        }
        if (getline(iss, token, ','))
        {
            item.regDate = token;
        }

        items.push_back(item);
    }
    file.close();
    for (const auto &item : items)
    {
        cout << "Item ID: " << item.id
             << "\t Item Name: " << item.name
             << "\t Quantity: " << item.quantity
             << "\t Reg Date: " << item.regDate << endl;
    }
}

void help()
{
    cout << "---------------------------------------------------" << endl;
    cout << "*                 Command syntaxes                *" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "itemadd <item_id> <item_name> <quantity> <registration_date> - Adds an item\n";
    cout << "itemslist - Lists all items\n";
    cout << "help - Shows this help message\n";
}

string toLowerCase(const string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void processCommand(const string &input)
{
    istringstream iss(input);
    string command;
    iss >> command;
    
    // Convert command to lowercase
    string cmd = toLowerCase(command);

    if (cmd == "itemadd")
    {
        Item item;
        string dateString;

        if (iss >> item.id >> item.name >> item.quantity >> dateString)
        {
            if (!validateDate(dateString))
            {
                cout << endl << "Invalid date format. ";
                help();
                return;
            }
            item.regDate = dateString;
            if (addItem(item)) {
                cout << "Success! Item added: " << endl;
                cout << "  ID: " << item.id << endl;
                cout << "  Name: " << item.name << endl;
                cout << "  Quantity: " << item.quantity << endl;
                cout << "  Registration Date: " << item.regDate << endl;
            }
        }
        else
        {
            cerr << "Invalid arguments for itemadd command." << endl;
            cout << "Usage: itemadd <item_id> <item_name> <quantity> <registration_date>" << endl;
            cout << "Example: itemadd 1 Laptop 5 01-05-2025" << endl;
        }
    }
    else if (cmd == "itemslist")
    {
        cout << "Listing all items..." << endl;
        listItems();
    }
    else if (cmd == "help")
    {
        help();
    }
    else if (cmd == "exit" || cmd == "quit")
    {
        cout << "Exiting program..." << endl;
        exit(0);
    }
    else
    {
        cerr << "Unknown command: '" << command << "'" << endl;
        help();
    }
}