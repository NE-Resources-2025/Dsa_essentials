#ifndef DATA_H
#define DATA_H

#include <string>
#include <iostream>

using namespace std;

/**
 * Hospital struct representing a hospital entity
 */
struct Hospital {
    string name;
    string location;
    int patients;

    // Default constructor
    Hospital() : patients(0) {}
    
    // Parameterized constructor
    Hospital(string n, string l, int p) : name(n), location(l), patients(p) {}
    
    // Display hospital information
    void display() const {
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Number of Patients: " << patients << endl;
    }
    
    // Validate hospital data
    bool isValid() const {
        return !name.empty() && !location.empty() && patients >= 0;
    }
};

/**
 * Connection struct representing a connection between two hospitals
 */
struct Connection {
    string hospital1;
    string hospital2;
    double distance;

    // Default constructor
    Connection() : distance(0.0) {}
    
    // Parameterized constructor
    Connection(string h1, string h2, double d) : hospital1(h1), hospital2(h2), distance(d) {}
    
    // Display connection information
    void display() const {
        cout << hospital1 << " <-> " << hospital2 << ": " << distance << " km" << endl;
    }
    
    // Check if connection involves a specific hospital
    bool involves(const string& hospitalId) const {
        return hospital1 == hospitalId || hospital2 == hospitalId;
    }
    
    // Check if this connection is the same as another (bidirectional)
    bool isSameAs(const Connection& other) const {
        return (hospital1 == other.hospital1 && hospital2 == other.hospital2) ||
               (hospital1 == other.hospital2 && hospital2 == other.hospital1);
    }
    
    // Validate connection data
    bool isValid() const {
        return !hospital1.empty() && !hospital2.empty() && 
               hospital1 != hospital2 && distance > 0;
    }
};

#endif // DATA_H