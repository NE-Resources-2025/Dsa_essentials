#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "data.h"

using namespace std;

// Function declarations
bool openFile(string filename);
vector<string> split(const string &str, char delimiter);
bool isLeapYear(int year);
bool validateDate(const string &date);
bool addItem(Item item);
void listItems();
void help();
string toLowerCase(const string &str);
void processCommand(const string &input);

#endif // UTILS_H