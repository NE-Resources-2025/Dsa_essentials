#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "data.cpp"

// I need to be able to split
vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    // istringstream converts a string into a stream
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
};

// Further date validation
bool isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    return false;
}

// Date validation func
bool validateDate(const string &date) {
    vector<string> dateParts = split(date, '/');
    if (dateParts.size() != 3) {
        cout << "Date format should be dd/mm/yyyy" << endl;
        return false; // Invalid date format
    }

    // stoi -> string to int
    int day = stoi(dateParts[0]);
    int month = stoi(dateParts[1]);
    int year = stoi(dateParts[2]);

    if (month < 1 || month > 12)
    {
        cout << "Invalid months passed" << endl;
        return false;
    }
    if (year < 1)
    {
        cout << "Invalid years passed" << endl;
        return false;
    }

    int daysInEachMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day < 1 || day > daysInEachMonth[month - 1])
    {
        cout << "Invalid days passed" << endl;
        return false;
    }

    return true; // Valid date
}

// Patient constraint validation
bool validatePatientRegistration (int id, string &dob, Patient *patientsHead) {
    
    // Date validator
    if (!validateDate(dob)) {
        cout << "Invalid date of birth" << endl;
        return false; // Invalid date
    }

    // Looping thru the linked list to see if the id doesn't exist yet
    while (patientsHead != NULL) {
        if (patientsHead->patient_id == id) {
            cout << "Patient ID already exists" << endl;
            return false; // Patient ID already exists
        }
        patientsHead = patientsHead->next;
    }
    return true; // Valid patient registration
}

// Doctor constraint validation
bool validateDoctorRegistration(int id, Doctor *doctorsHead)
{
    // Loop through the linked list starting from *doctorsHead to check if id is not duplicated
    while (doctorsHead != NULL)
    {
        if (doctorsHead->doctor_id == id)
        {
            cout << "Doctor with that id already exists" << endl;
            return false;
        }
        doctorsHead = doctorsHead->next;
    }
    return true;
}

// Appointment constraint validation
bool validateAppointmentRegistration(int id, int patientId, int doctorId, string &date, Patient *patientsHead, Doctor *doctorsHead, Appointment *appointmentsHead)
{
    if (!validateDate(date))
    {
        return false;
    }

    // Loop through the linked list starting from *patientsHead to check if id is not duplicated
    while (appointmentsHead != NULL)
    {
        if (appointmentsHead->appointment_id == id)
        {
            cout << "Appointment with that id already exists" << endl;
            return false;
        }
        appointmentsHead = appointmentsHead->next;
    }

    // Loop through the patients to check if the patient exists and if not return false
    while (patientsHead != NULL)
    {
        if (patientsHead->patient_id == patientId)
        {
            break;
        }
        patientsHead = patientsHead->next;
    }
    if (patientsHead == NULL)
    {
        cout << "Patient with that id does not exist" << endl;
        return false;
    }

    // Validate if doctor exists and if not return false
    while (doctorsHead != NULL)
    {
        if (doctorsHead->doctor_id == doctorId)
        {
            break;
        }
        doctorsHead = doctorsHead->next;
    }
    if (doctorsHead == NULL)
    {
        cout << "Doctor with that id does not exist" << endl;
        return false;
    }

    return true;
}

/* ======================================================= */
// Display funcs
void displayPatients (struct Patient *patientsHead) {
    struct Patient *temp = patientsHead;

    while (temp != NULL) {
        cout << "Patient ID: " << temp->patient_id 
             << ", Name: " << temp->name
             << ", Date of Birth: " << temp->dob
             << ", Gender: " << temp->gender
             << " -------------------------" << endl;
        patientsHead = patientsHead->next;
        temp = temp->next;
    }
}

void displayDoctors(struct Doctor *head)
{
    struct Doctor *temp = head;

    // Iterate the entire linked list and print the data
    while (temp != NULL)
    {
        cout << "Doctor ID: " << head->doctor_id
             << ", Name: " << head->name
             << ", Specialization: " << head->specialization
             << endl;
        head = head->next;
        temp = temp->next;
    }
}

void displayAppointments(struct Appointment *head)
{
    struct Appointment *temp = head;

    // Iterate the entire linked list and print the data
    while (temp != NULL)
    {
        cout << "Appointment ID: " << head->appointment_id
             << ", P_ID: " << head->patient_id
             << ", D_ID: " << head->doctor_id
             << ", DATE: " << head->date
             << endl;
        head = head->next;
        temp = temp->next;
    }
}

/* ============================================================== */
// Functions to add nodes to others in the linked list

void addPatient(struct Patient **head, int id, string name, string dob, string gender) {
    struct Patient *newNode = new Patient();
    newNode->patient_id = id;
    newNode->name = name;
    newNode->dob = dob;
    newNode->gender = gender;
    newNode->next = (*head); // Point the new node to the current head
    (*head) = newNode; // Update the head to point to the new node

    // Append to CSV
    ofstream file("patients.csv", ios::app); // ios::app opens in append mode and makes sure the file is created if it doesn't exist
    if (file.is_open())
    {
        file << id << "," << name << "," << dob << "," << gender << "\n";
        file.close();
        cout << "Patient saved to CSV!" << endl;
    }
    else
    {
        cerr << "Error: Could not open patients.csv" << endl;
    }
}

void addDoctor(Doctor **head, int id, string name, string specialization)
{
    struct Doctor *newNode = new Doctor();
    newNode->doctor_id = id;
    newNode->name = name;
    newNode->specialization = specialization;
    newNode->next = (*head);
    (*head) = newNode;

    // Append to CSV
    ofstream file("doctors.csv", ios::app); // ios::app opens in append mode and makes sure the file is created if it doesn't exist
    if (file.is_open())
    {
        file << id << "," << name << "," << specialization << "\n";
        file.close();
        cout << "Doctor saved to CSV!" << endl;
    }
    else
    {
        cerr << "Error: Could not open doctors.csv" << endl;
    }
}

void addAppointment(Appointment **head, int id, int doctor_id, int patient_id, string date)
{
    struct Appointment *newNode = new Appointment();
    newNode->appointment_id = id;
    newNode->doctor_id = doctor_id;
    newNode->date = date;
    newNode->patient_id = patient_id;
    newNode->next = (*head);
    (*head) = newNode;
}
