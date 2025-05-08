#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>

#define FILE_NAME "items.csv"

using namespace std;

struct Item
{
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;
};

bool compareAlphabetically(const Item &a, const Item &b)
{
    return a.item_name < b.item_name;
}

void listItems()
{
    ifstream file(FILE_NAME);
    vector<Item> items;
    string line, item_id, item_name, item_quantity, item_registration_date;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            istringstream ss(line);
            if (ss >> item_id >> item_name >> item_quantity >> item_registration_date)
            {
                Item item = {
                    stoi(item_id),
                    item_name,
                    stoi(item_quantity),
                    item_registration_date};
                items.push_back(item);
            }
            else
            {
                cerr << "Invalid record: " << line << endl;
            }
        }

        if (!items.empty())
        {
            sort(items.begin(), items.end(), compareAlphabetically);
            cout << "\nInventory List (sorted by name):\n";
            cout << "--------------------------------\n";
            for (const auto &item : items)
            {
                cout << "ID: " << item.item_id << "\tName: " << item.item_name << "\tQuantity: "
                     << item.item_quantity << "\tReg Date: " << item.item_registration_date << endl;
            }
            cout << "--------------------------------\n";
        }
        else
        {
            cout << "No items found in " << FILE_NAME << ".\n";
        }
        file.close();
    }
    else
    {
        cerr << "Failed to open file: " << FILE_NAME << endl;
    }
}

void addItem(const Item &item)
{
    ofstream file(FILE_NAME, ios::app);
    if (file.is_open())
    {
        file << item.item_id << " " << item.item_name << " " << item.item_quantity << " "
             << item.item_registration_date << endl;
        cout << "Item '" << item.item_name << "' saved successfully!\n";
        file.close();
    }
    else
    {
        cerr << "Failed to open file: " << FILE_NAME << endl;
    }
}

string convertToLowercase(const string &str)
{
    string lowercase_str = str;
    for (char &c : lowercase_str)
    {
        c = tolower(c);
    }
    return lowercase_str;
}

// Check if item_id is unique in the file
bool isUniqueId(int id)
{
    ifstream file(FILE_NAME);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            istringstream ss(line);
            string file_id;
            if (ss >> file_id)
            {
                if (stoi(file_id) == id)
                {
                    file.close();
                    return false;
                }
            }
        }
        file.close();
    }
    return true;
}

// Validate date format (YYYY-MM-DD)
bool isValidDate(const string &date)
{
    regex datePattern("\\d{4}-\\d{2}-\\d{2}");
    return regex_match(date, datePattern);
}

int main()
{
    string command, user_input;

    // Welcome message
    cout << "================================\n";
    cout << "Welcome to the Inventory Manager!\n";
    cout << "Type 'help' for commands.\n";
    cout << "================================\n";

    while (true)
    {
        // Enhanced prompt
        cout << "\nCommand (itemadd, itemslist, help, exit): ";
        getline(cin, user_input);
        istringstream ss(user_input);
        command.clear();
        ss >> command;
        if (command.empty())
        {
            cerr << "Please enter a command.\n";
            continue;
        }
        command = convertToLowercase(command);

        if (command == "itemadd")
        {
            string item_id_str, item_name, item_quantity_str, item_registration_date;
            int item_id, item_quantity;

            // Interactive input with validation
            cout << "\nEnter Item Details:\n";

            // Item ID
            while (true)
            {
                cout << "Item ID (positive number): ";
                getline(cin, item_id_str);
                try
                {
                    item_id = stoi(item_id_str);
                    if (item_id <= 0)
                    {
                        cerr << "ID must be a positive number.\n";
                        continue;
                    }
                    if (!isUniqueId(item_id))
                    {
                        cerr << "ID " << item_id << " already exists. Choose another.\n";
                        continue;
                    }
                    break;
                }
                catch (...)
                {
                    cerr << "Invalid ID. Enter a number.\n";
                }
            }

            // Item Name
            cout << "Item Name: ";
            getline(cin, item_name);
            if (item_name.empty())
            {
                cerr << "Name cannot be empty. Using 'Unknown'.\n";
                item_name = "Unknown";
            }

            // Item Quantity
            while (true)
            {
                cout << "Quantity (non-negative number): ";
                getline(cin, item_quantity_str);
                try
                {
                    item_quantity = stoi(item_quantity_str);
                    if (item_quantity < 0)
                    {
                        cerr << "Quantity cannot be negative.\n";
                        continue;
                    }
                    break;
                }
                catch (...)
                {
                    cerr << "Invalid quantity. Enter a number.\n";
                }
            }

            // Registration Date
            while (true)
            {
                cout << "Registration Date (YYYY-MM-DD): ";
                getline(cin, item_registration_date);
                if (!isValidDate(item_registration_date))
                {
                    cerr << "Invalid date format. Use YYYY-MM-DD (e.g., 2023-10-01).\n";
                    continue;
                }
                break;
            }

            // Confirmation
            cout << "\nConfirm Item Details:\n";
            cout << "ID: " << item_id << "\nName: " << item_name << "\nQuantity: " << item_quantity
                 << "\nReg Date: " << item_registration_date << "\n";
            cout << "Save this item? (y/n): ";
            string confirm;
            getline(cin, confirm);
            if (convertToLowercase(confirm) != "y")
            {
                cout << "Item not saved.\n";
                continue;
            }

            // Create and save item
            Item item = {item_id, item_name, item_quantity, item_registration_date};
            addItem(item);
        }
        else if (command == "itemslist")
        {
            listItems();
        }
        else if (command == "help")
        {
            cout << "\nAvailable Commands:\n";
            cout << "--------------------------------\n";
            cout << "itemadd        : Add a new item interactively.\n";
            cout << "itemslist      : List all items, sorted by name.\n";
            cout << "help           : Show this help message.\n";
            cout << "exit           : Quit the program.\n";
            cout << "--------------------------------\n";
            cout << "Example: Type 'itemadd' to start adding an item.\n";
        }
        else if (command == "exit")
        {
            cout << "Thank you for using Inventory Manager. Goodbye!\n";
            break;
        }
        else
        {
            cerr << "Invalid command. Type 'help' for available commands.\n";
        }
    }

    return 0;
}