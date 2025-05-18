#ifndef DATA_H
#define DATA_H

#include <string>

using namespace std;

struct Item
{
    int id;
    string name;
    int quantity;
    string regDate;
};

// Declare as extern so it can be defined in a single .cpp file
extern string filename;

#endif // DATA_H