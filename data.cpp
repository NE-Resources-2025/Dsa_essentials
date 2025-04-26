#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Linked list to store patient info
struct Patient {
    int patient_id;
    string name;
    string dob;
    string gender;

    struct Patient *next; // Pointer to the next patient in the list
};

struct Doctor {
    int doctor_id;
    string name;
    string specialization;

    struct Doctor *next; // Pointer to the next doctor in the list
};

struct Appointment {
    int appointment_id;
    int patient_id;
    int doctor_id;
    string date;
    string time;

    struct Appointment *next; // Pointer to the next appointment in the list
};