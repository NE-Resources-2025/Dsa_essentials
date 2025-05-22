#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "data.cpp"

using namespace std;

class HospitalUtils {
private:
    static const string HOSPITALS_FILE;
    static const string CONNECTIONS_FILE;

public:
    /**
     * String utility functions
     */
    static string removeQuotes(string str) {
        if (str.length() >= 2 && str[0] == '"' && str[str.length()-1] == '"') {
            return str.substr(1, str.length()-2);
        }
        return str;
    }
    
    static string toUpperCase(string str) {
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }
    
    static string trim(const string& str) {
        size_t first = str.find_first_not_of(' ');
        if (string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    /**
     * Input validation functions
     */
    static bool isValidHospitalId(const string& id) {
        if (id.empty()) return false;
        return id[0] == 'H' && id.length() >= 2; // starts with an H and has something else after it
    }
    
    static bool isValidDistance(double distance) {
        return distance > 0 && distance <= 10000; // Max 10,000 km
    }
    
    static int getValidInteger(const string& prompt, int min = 0, int max = INT_MAX) {
        int value;
        while (true) {
            cout << prompt;
            cin >> value;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number." << endl;
                continue;
            }
            
            if (value < min || value > max) {
                cout << "Value must be between " << min << " and " << max << endl;
                continue;
            }
            
            cin.ignore(); // Clear the input buffer
            return value;
        }
    }
    
    static double getValidDouble(const string& prompt, double min = 0.0, double max = 10000.0) {
        double value;
        while (true) {
            cout << prompt;
            cin >> value;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number." << endl;
                continue;
            }
            
            if (value < min || value > max) {
                cout << "Value must be between " << min << " and " << max << endl;
                continue;
            }
            
            cin.ignore(); // Clear the input buffer
            return value;
        }
    }

    /**
     * File I/O operations
     */
    static bool loadHospitals(map<string, Hospital>& hospitals) {
        ifstream file(HOSPITALS_FILE);
        if (!file.is_open()) {
            return false; // File doesn't exist yet
        }

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string hospital_id, name, location, patients_str;

            getline(ss, hospital_id, ',');
            getline(ss, name, ',');
            getline(ss, location, ',');
            getline(ss, patients_str, ',');

            // Remove quotes if present
            hospital_id = removeQuotes(hospital_id);
            name = removeQuotes(name);
            location = removeQuotes(location);
            patients_str = removeQuotes(patients_str);

            try {
                int patients = stoi(patients_str);
                hospitals[hospital_id] = Hospital(name, location, patients);
            } catch (const exception& e) {
                cout << "Error parsing hospital data: " << line << endl;
            }
        }
        file.close();
        return true;
    }

    static bool loadConnections(vector<Connection>& connections) {
        ifstream file(CONNECTIONS_FILE);
        if (!file.is_open()) {
            return false; // File doesn't exist yet
        }

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string hospital1, hospital2, distance_str;

            getline(ss, hospital1, ',');
            getline(ss, hospital2, ',');
            getline(ss, distance_str, ',');

            // Remove quotes if present
            hospital1 = removeQuotes(hospital1);
            hospital2 = removeQuotes(hospital2);
            distance_str = removeQuotes(distance_str);

            try {
                double distance = stod(distance_str);
                connections.push_back(Connection(hospital1, hospital2, distance));
            } catch (const exception& e) {
                cout << "Error parsing connection data: " << line << endl;
            }
        }
        file.close();
        return true;
    }

    static bool saveHospitals(const map<string, Hospital>& hospitals) {
        ofstream file(HOSPITALS_FILE);
        if (!file.is_open()) {
            cout << "Error: Could not save hospitals data!" << endl;
            return false;
        }

        file << "hospital_id,name,location,patients" << endl;
        for (const auto& pair : hospitals) {
            file << pair.first << ","
                 << "\"" << pair.second.name << "\","
                 << "\"" << pair.second.location << "\","
                 << pair.second.patients << endl;
        }
        file.close();
        return true;
    }

    static bool saveConnections(const vector<Connection>& connections) {
        ofstream file(CONNECTIONS_FILE);
        if (!file.is_open()) {
            cout << "Error: Could not save connections data!" << endl;
            return false;
        }

        file << "hospital1,hospital2,distance" << endl;
        for (const auto& conn : connections) {
            file << conn.hospital1 << "," << conn.hospital2 << "," << conn.distance << endl;
        }
        file.close();
        return true;
    }

    /**
     * Display functions
     */
    static void displayHeader(const string& title) {
        cout << "\n" << string(60, '=') << endl;
        cout << title << endl;
        cout << string(60, '=') << endl;
    }
    
    static void displaySeparator() {
        cout << string(40, '-') << endl;
    }
    
    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    static void pauseScreen() {
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    /**
     * CRUD Operations for Hospitals
     */
    static void viewHospitals(const map<string, Hospital>& hospitals) {
        if (hospitals.empty()) {
            cout << "\nNo hospitals registered yet." << endl;
            return;
        }

        displayHeader("REGISTERED HOSPITALS");

        for (const auto& pair : hospitals) {
            cout << "Hospital ID: " << pair.first << endl;
            pair.second.display();
            displaySeparator();
        }
    }

    static bool addHospital(map<string, Hospital>& hospitals) {
        displayHeader("ADD NEW HOSPITAL");

        string hospital_id, name, location;
        int patients;

        cout << "Enter Hospital ID (e.g., H1, H2): ";
        cin >> hospital_id;
        cin.ignore(); // Clear the input buffer

        // Convert to uppercase and validate
        hospital_id = toUpperCase(hospital_id);
        
        if (!isValidHospitalId(hospital_id)) {
            cout << "Invalid Hospital ID format! Use format like H1, H2, etc." << endl;
            return false;
        }

        if (hospitals.find(hospital_id) != hospitals.end()) {
            cout << "Hospital " << hospital_id << " already exists!" << endl;
            return false;
        }

        cout << "Enter Hospital Name: ";
        getline(cin, name);
        name = trim(name);
        
        if (name.empty()) {
            cout << "Hospital name cannot be empty!" << endl;
            return false;
        }

        cout << "Enter Hospital Location: ";
        getline(cin, location);
        location = trim(location);
        
        if (location.empty()) {
            cout << "Hospital location cannot be empty!" << endl;
            return false;
        }

        patients = getValidInteger("Enter Number of Patients: ", 0, 10000);

        Hospital newHospital(name, location, patients);
        if (!newHospital.isValid()) {
            cout << "Invalid hospital data!" << endl;
            return false;
        }

        hospitals[hospital_id] = newHospital;
        
        if (saveHospitals(hospitals)) {
            cout << "Hospital " << hospital_id << " added successfully!" << endl;
            return true;
        }
        
        return false;
    }

    static bool updateHospital(map<string, Hospital>& hospitals) {
        if (hospitals.empty()) {
            cout << "\nNo hospitals to update." << endl;
            return false;
        }

        displayHeader("UPDATE HOSPITAL");
        viewHospitals(hospitals);

        string hospital_id;
        cout << "Enter Hospital ID to update: ";
        cin >> hospital_id;
        cin.ignore();

        hospital_id = toUpperCase(hospital_id);

        if (hospitals.find(hospital_id) == hospitals.end()) {
            cout << "Hospital " << hospital_id << " not found!" << endl;
            return false;
        }

        Hospital& hospital = hospitals[hospital_id];

        cout << "\nCurrent details for " << hospital_id << ":" << endl;
        hospital.display();

        cout << "\nEnter new details (press Enter to keep current value):" << endl;

        string new_name, new_location, new_patients_str;

        cout << "New Name [" << hospital.name << "]: ";
        getline(cin, new_name);
        if (!new_name.empty()) {
            hospital.name = trim(new_name);
        }

        cout << "New Location [" << hospital.location << "]: ";
        getline(cin, new_location);
        if (!new_location.empty()) {
            hospital.location = trim(new_location);
        }

        cout << "New Number of Patients [" << hospital.patients << "]: ";
        getline(cin, new_patients_str);
        if (!new_patients_str.empty()) {
            try {
                int new_patients = stoi(new_patients_str);
                if (new_patients >= 0) {
                    hospital.patients = new_patients;
                } else {
                    cout << "Invalid number, keeping current value." << endl;
                }
            } catch (const exception& e) {
                cout << "Invalid number, keeping current value." << endl;
            }
        }

        if (saveHospitals(hospitals)) {
            cout << "Hospital " << hospital_id << " updated successfully!" << endl;
            return true;
        }
        
        return false;
    }

    static bool deleteHospital(map<string, Hospital>& hospitals, vector<Connection>& connections) {
        if (hospitals.empty()) {
            cout << "\nNo hospitals to delete." << endl;
            return false;
        }

        displayHeader("DELETE HOSPITAL");
        viewHospitals(hospitals);

        string hospital_id;
        cout << "Enter Hospital ID to delete: ";
        cin >> hospital_id;
        cin.ignore();

        hospital_id = toUpperCase(hospital_id);

        if (hospitals.find(hospital_id) == hospitals.end()) {
            cout << "Hospital " << hospital_id << " not found!" << endl;
            return false;
        }

        char confirm;
        cout << "Are you sure you want to delete " << hospital_id << "? (y/n): ";
        cin >> confirm;
        cin.ignore();

        if (confirm == 'y' || confirm == 'Y') {
            // Remove hospital
            hospitals.erase(hospital_id);

            // Remove all connections involving this hospital
            connections.erase(
                remove_if(connections.begin(), connections.end(),
                    [&hospital_id](const Connection& conn) {
                        return conn.involves(hospital_id);
                    }),
                connections.end()
            );

            bool hospitalsSaved = saveHospitals(hospitals);
            bool connectionsSaved = saveConnections(connections);
            
            if (hospitalsSaved && connectionsSaved) {
                cout << "Hospital " << hospital_id << " deleted successfully!" << endl;
                return true;
            }
        } else {
            cout << "Deletion cancelled." << endl;
        }
        
        return false;
    }

    /**
     * Connection operations
     */
    static bool linkHospitals(const map<string, Hospital>& hospitals, vector<Connection>& connections) {
        if (hospitals.size() < 2) {
            cout << "\nNeed at least 2 hospitals to create a link." << endl;
            return false;
        }

        displayHeader("LINK HOSPITALS");
        viewHospitals(hospitals);

        string hospital1, hospital2;
        double distance;

        cout << "Enter first Hospital ID: ";
        cin >> hospital1;
        hospital1 = toUpperCase(hospital1);

        cout << "Enter second Hospital ID: ";
        cin >> hospital2;
        hospital2 = toUpperCase(hospital2);

        if (hospitals.find(hospital1) == hospitals.end()) {
            cout << "Hospital " << hospital1 << " not found!" << endl;
            return false;
        }

        if (hospitals.find(hospital2) == hospitals.end()) {
            cout << "Hospital " << hospital2 << " not found!" << endl;
            return false;
        }

        if (hospital1 == hospital2) {
            cout << "Cannot link a hospital to itself!" << endl;
            return false;
        }

        // Check if link already exists
        Connection newConnection(hospital1, hospital2, 0);
        for (const auto& conn : connections) {
            if (conn.isSameAs(newConnection)) {
                cout << "Link between " << hospital1 << " and " << hospital2 << " already exists!" << endl;
                return false;
            }
        }

        distance = getValidDouble("Enter distance in km: ", 0.1, 10000.0);

        Connection connection(hospital1, hospital2, distance);
        if (!connection.isValid()) {
            cout << "Invalid connection data!" << endl;
            return false;
        }

        connections.push_back(connection);
        
        if (saveConnections(connections)) {
            cout << "Successfully linked " << hospital1 << " and " << hospital2
                 << " with distance " << distance << " km!" << endl;
            return true;
        }
        
        return false;
    }

    static void viewGraph(const map<string, Hospital>& hospitals, const vector<Connection>& connections) {
        if (hospitals.empty()) {
            cout << "\nNo hospitals to display." << endl;
            return;
        }

        displayHeader("HOSPITAL NETWORK GRAPH");

        cout << "Hospitals:" << endl;
        for (const auto& pair : hospitals) {
            cout << "  " << pair.first << ": " << pair.second.name << endl;
        }

        cout << "\nConnections:" << endl;
        if (connections.empty()) {
            cout << "  No connections established yet." << endl;
        } else {
            for (const auto& conn : connections) {
                cout << "  ";
                conn.display();
            }
        }

        // ASCII Art representation of the graph
        cout << "\nGraph Visualization:" << endl;
        cout << string(50, '-') << endl;

        if (!connections.empty()) {
            // Simple ASCII representation
            for (const auto& conn : connections) {
                cout << conn.hospital1 << " ----(" << conn.distance << "km)---- "
                     << conn.hospital2 << endl;
            }
        } else {
            // Show isolated hospitals
            for (const auto& pair : hospitals) {
                cout << "(" << pair.first << ")" << endl;
            }
        }
    }

    /**
     * Help system
     */
    static void displayHelp() {
        displayHeader("HELP - HOSPITAL MANAGEMENT SYSTEM");
        
        cout << "This system helps you manage hospitals and their connections in a network." << endl;
        cout << "\nFeatures Overview:" << endl;
        cout << "- Hospital Management: Add, view, update, and delete hospital records" << endl;
        cout << "- Network Management: Create connections between hospitals with distances" << endl;
        cout << "- Data Persistence: All data is saved to CSV files automatically" << endl;
        
        cout << "\nMenu Options Explained:" << endl;
        cout << "1. View Hospitals: Display all registered hospitals and their details" << endl;
        cout << "2. Add Hospital: Register a new hospital with ID, name, location, and patient count" << endl;
        cout << "3. Update Hospital: Modify existing hospital information" << endl;
        cout << "4. Delete Hospital: Remove a hospital and all its connections" << endl;
        cout << "5. Link Hospitals: Create a connection between two hospitals with distance" << endl;
        cout << "6. View Graph: Display the hospital network with all connections" << endl;
        cout << "7. Help: Show this help information" << endl;
        cout << "8. Exit: Save all data and exit the program" << endl;
        
        cout << "\nTips for Usage:" << endl;
        cout << "- Hospital IDs should follow format: H1, H2, H3, etc." << endl;
        cout << "- Distances should be positive numbers in kilometers" << endl;
        cout << "- Patient counts should be non-negative integers" << endl;
        cout << "- Data is automatically saved after each operation" << endl;
        cout << "- You can press Enter to keep current values when updating" << endl;
        
        cout << "\nFile Information:" << endl;
        cout << "- hospitals.csv: Contains hospital data" << endl;
        cout << "- hospital_connections.csv: Contains connection data" << endl;
        cout << "- Files are created automatically if they don't exist" << endl;
    }

    /**
     * Initialize sample data
     */
    static void initializeSampleData(map<string, Hospital>& hospitals, vector<Connection>& connections) {
        cout << "Initializing sample data..." << endl;

        hospitals["H1"] = Hospital("Central Hospital", "Downtown", 150);
        hospitals["H2"] = Hospital("East Medical Center", "East District", 200);
        hospitals["H3"] = Hospital("South General Hospital", "South Area", 180);
        hospitals["H4"] = Hospital("West Regional Hospital", "West Side", 120);

        connections.push_back(Connection("H1", "H2", 5.0));
        connections.push_back(Connection("H1", "H4", 3.0));
        connections.push_back(Connection("H2", "H3", 7.0));

        saveHospitals(hospitals);
        saveConnections(connections);
        cout << "Sample data initialized successfully!" << endl;
    }
};

// Static member definitions
const string HospitalUtils::HOSPITALS_FILE = "hospitals.csv";
const string HospitalUtils::CONNECTIONS_FILE = "hospital_connections.csv";

#endif // UTILS_H