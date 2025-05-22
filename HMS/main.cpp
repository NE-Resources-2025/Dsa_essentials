#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Hospital {
    string name;
    string location;
    int patients;

    Hospital() : patients(0) {}
    Hospital(string n, string l, int p) : name(n), location(l), patients(p) {}
};

struct Connection {
    string hospital1;
    string hospital2;
    double distance;

    Connection() : distance(0.0) {}
    Connection(string h1, string h2, double d) : hospital1(h1), hospital2(h2), distance(d) {}
};

class HospitalManagementSystem {
private:
    map<string, Hospital> hospitals;
    vector<Connection> connections;
    const string HOSPITALS_FILE = "hospitals.csv";
    const string CONNECTIONS_FILE = "hospital_connections.csv";

public:
    HospitalManagementSystem() {
        loadData();
    }

    void loadData() {
        loadHospitals();
        loadConnections();
    }

    void loadHospitals() {
        ifstream file(HOSPITALS_FILE);
        if (!file.is_open()) {
            return; // File doesn't exist yet
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
    }

    void loadConnections() {
        ifstream file(CONNECTIONS_FILE);
        if (!file.is_open()) {
            return; // File doesn't exist yet
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
    }

    string removeQuotes(string str) {
        if (str.length() >= 2 && str[0] == '"' && str[str.length()-1] == '"') {
            return str.substr(1, str.length()-2);
        }
        return str;
    }

    void saveHospitals() {
        ofstream file(HOSPITALS_FILE);
        if (!file.is_open()) {
            cout << "Error: Could not save hospitals data!" << endl;
            return;
        }

        file << "hospital_id,name,location,patients" << endl;
        for (const auto& pair : hospitals) {
            file << pair.first << ","
                 << "\"" << pair.second.name << "\","
                 << "\"" << pair.second.location << "\","
                 << pair.second.patients << endl;
        }
        file.close();
        cout << "Hospitals data saved successfully!" << endl;
    }

    void saveConnections() {
        ofstream file(CONNECTIONS_FILE);
        if (!file.is_open()) {
            cout << "Error: Could not save connections data!" << endl;
            return;
        }

        file << "hospital1,hospital2,distance" << endl;
        for (const auto& conn : connections) {
            file << conn.hospital1 << "," << conn.hospital2 << "," << conn.distance << endl;
        }
        file.close();
        cout << "Hospital connections saved successfully!" << endl;
    }

    void viewHospitals() {
        if (hospitals.empty()) {
            cout << "\nNo hospitals registered yet." << endl;
            return;
        }

        cout << "\n" << string(60, '=') << endl;
        cout << "REGISTERED HOSPITALS" << endl;
        cout << string(60, '=') << endl;

        for (const auto& pair : hospitals) {
            cout << "Hospital ID: " << pair.first << endl;
            cout << "Name: " << pair.second.name << endl;
            cout << "Location: " << pair.second.location << endl;
            cout << "Number of Patients: " << pair.second.patients << endl;
            cout << string(40, '-') << endl;
        }
    }

    void addHospital() {
        cout << "\n--- ADD NEW HOSPITAL ---" << endl;

        string hospital_id, name, location;
        int patients;

        cout << "Enter Hospital ID (e.g., H1, H2): ";
        cin >> hospital_id;
        cin.ignore(); // Clear the input buffer

        // Convert to uppercase
        transform(hospital_id.begin(), hospital_id.end(), hospital_id.begin(), ::toupper);

        if (hospitals.find(hospital_id) != hospitals.end()) {
            cout << "Hospital " << hospital_id << " already exists!" << endl;
            return;
        }

        cout << "Enter Hospital Name: ";
        getline(cin, name);

        cout << "Enter Hospital Location: ";
        getline(cin, location);

        cout << "Enter Number of Patients: ";
        cin >> patients;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid number of patients. Using 0 as default." << endl;
            patients = 0;
        }

        hospitals[hospital_id] = Hospital(name, location, patients);
        saveHospitals();
        cout << "Hospital " << hospital_id << " added successfully!" << endl;
    }

    void updateHospital() {
        if (hospitals.empty()) {
            cout << "\nNo hospitals to update." << endl;
            return;
        }

        cout << "\n--- UPDATE HOSPITAL ---" << endl;
        viewHospitals();

        string hospital_id;
        cout << "Enter Hospital ID to update: ";
        cin >> hospital_id;
        cin.ignore();

        transform(hospital_id.begin(), hospital_id.end(), hospital_id.begin(), ::toupper);

        if (hospitals.find(hospital_id) == hospitals.end()) {
            cout << "Hospital " << hospital_id << " not found!" << endl;
            return;
        }

        Hospital& hospital = hospitals[hospital_id];

        cout << "\nCurrent details for " << hospital_id << ":" << endl;
        cout << "Name: " << hospital.name << endl;
        cout << "Location: " << hospital.location << endl;
        cout << "Patients: " << hospital.patients << endl;

        cout << "\nEnter new details (press Enter to keep current value):" << endl;

        string new_name, new_location, new_patients_str;

        cout << "New Name [" << hospital.name << "]: ";
        getline(cin, new_name);
        if (!new_name.empty()) {
            hospital.name = new_name;
        }

        cout << "New Location [" << hospital.location << "]: ";
        getline(cin, new_location);
        if (!new_location.empty()) {
            hospital.location = new_location;
        }

        cout << "New Number of Patients [" << hospital.patients << "]: ";
        getline(cin, new_patients_str);
        if (!new_patients_str.empty()) {
            try {
                hospital.patients = stoi(new_patients_str);
            } catch (const exception& e) {
                cout << "Invalid number, keeping current value." << endl;
            }
        }

        saveHospitals();
        cout << "Hospital " << hospital_id << " updated successfully!" << endl;
    }

    void deleteHospital() {
        if (hospitals.empty()) {
            cout << "\nNo hospitals to delete." << endl;
            return;
        }

        cout << "\n--- DELETE HOSPITAL ---" << endl;
        viewHospitals();

        string hospital_id;
        cout << "Enter Hospital ID to delete: ";
        cin >> hospital_id;
        cin.ignore();

        transform(hospital_id.begin(), hospital_id.end(), hospital_id.begin(), ::toupper);

        if (hospitals.find(hospital_id) == hospitals.end()) {
            cout << "Hospital " << hospital_id << " not found!" << endl;
            return;
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
                        return conn.hospital1 == hospital_id || conn.hospital2 == hospital_id;
                    }),
                connections.end()
            );

            saveHospitals();
            saveConnections();
            cout << "Hospital " << hospital_id << " deleted successfully!" << endl;
        } else {
            cout << "Deletion cancelled." << endl;
        }
    }

    void linkHospitals() {
        if (hospitals.size() < 2) {
            cout << "\nNeed at least 2 hospitals to create a link." << endl;
            return;
        }

        cout << "\n--- LINK HOSPITALS ---" << endl;
        viewHospitals();

        string hospital1, hospital2;
        double distance;

        cout << "Enter first Hospital ID: ";
        cin >> hospital1;
        transform(hospital1.begin(), hospital1.end(), hospital1.begin(), ::toupper);

        cout << "Enter second Hospital ID: ";
        cin >> hospital2;
        transform(hospital2.begin(), hospital2.end(), hospital2.begin(), ::toupper);

        if (hospitals.find(hospital1) == hospitals.end()) {
            cout << "Hospital " << hospital1 << " not found!" << endl;
            return;
        }

        if (hospitals.find(hospital2) == hospitals.end()) {
            cout << "Hospital " << hospital2 << " not found!" << endl;
            return;
        }

        if (hospital1 == hospital2) {
            cout << "Cannot link a hospital to itself!" << endl;
            return;
        }

        // Check if link already exists
        bool linkExists = false;
        for (const auto& conn : connections) {
            if ((conn.hospital1 == hospital1 && conn.hospital2 == hospital2) ||
                (conn.hospital1 == hospital2 && conn.hospital2 == hospital1)) {
                linkExists = true;
                break;
            }
        }

        if (linkExists) {
            cout << "Link between " << hospital1 << " and " << hospital2 << " already exists!" << endl;
            return;
        }

        cout << "Enter distance in km: ";
        cin >> distance;

        if (cin.fail() || distance <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid distance value!" << endl;
            return;
        }

        connections.push_back(Connection(hospital1, hospital2, distance));
        saveConnections();
        cout << "Successfully linked " << hospital1 << " and " << hospital2
             << " with distance " << distance << " km!" << endl;
    }

    void viewGraph() {
        if (hospitals.empty()) {
            cout << "\nNo hospitals to display." << endl;
            return;
        }

        cout << "\n" << string(50, '=') << endl;
        cout << "HOSPITAL NETWORK GRAPH" << endl;
        cout << string(50, '=') << endl;

        cout << "Hospitals:" << endl;
        for (const auto& pair : hospitals) {
            cout << "  " << pair.first << ": " << pair.second.name << endl;
        }

        cout << "\nConnections:" << endl;
        if (connections.empty()) {
            cout << "  No connections established yet." << endl;
        } else {
            for (const auto& conn : connections) {
                cout << "  " << conn.hospital1 << " <-> " << conn.hospital2
                     << ": " << conn.distance << " km" << endl;
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

    void initializeSampleData() {
        cout << "Initializing sample data..." << endl;

        hospitals["H1"] = Hospital("Central Hospital", "Downtown", 150);
        hospitals["H2"] = Hospital("East Medical Center", "East District", 200);
        hospitals["H3"] = Hospital("South General Hospital", "South Area", 180);
        hospitals["H4"] = Hospital("West Regional Hospital", "West Side", 120);

        connections.push_back(Connection("H1", "H2", 5.0));
        connections.push_back(Connection("H1", "H4", 3.0));
        connections.push_back(Connection("H2", "H3", 7.0));

        saveHospitals();
        saveConnections();
        cout << "Sample data initialized successfully!" << endl;
    }

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void pauseScreen() {
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    void run() {
        // Check if this is first run and offer to initialize sample data
        if (hospitals.empty()) {
            cout << "Welcome to Hospital Management System!" << endl;
            char init_sample;
            cout << "Would you like to initialize with sample data? (y/n): ";
            cin >> init_sample;
            cin.ignore();

            if (init_sample == 'y' || init_sample == 'Y') {
                initializeSampleData();
            }
        }

        int choice;
        while (true) {
            cout << "\n" << string(50, '=') << endl;
            cout << "HOSPITAL MANAGEMENT SYSTEM" << endl;
            cout << string(50, '=') << endl;
            cout << "1. View the registered Hospitals and their details" << endl;
            cout << "2. Add a hospital and its details" << endl;
            cout << "3. Update hospital details" << endl;
            cout << "4. Delete hospital" << endl;
            cout << "5. Link hospital to another hospital" << endl;
            cout << "6. View the graph of the hospitals and their edges" << endl;
            cout << "7. Exit" << endl;
            cout << string(50, '-') << endl;

            cout << "Enter your choice (1-7): ";
            cin >> choice;
            cin.ignore(); // Clear input buffer

            switch (choice) {
                case 1:
                    viewHospitals();
                    break;
                case 2:
                    addHospital();
                    break;
                case 3:
                    updateHospital();
                    break;
                case 4:
                    deleteHospital();
                    break;
                case 5:
                    linkHospitals();
                    break;
                case 6:
                    viewGraph();
                    break;
                case 7:
                    cout << "Thank you for using Hospital Management System!" << endl;
                    return;
                default:
                    cout << "Invalid choice. Please enter a number between 1-7." << endl;
            }

            pauseScreen();
        }
    }
};

int main() {
    HospitalManagementSystem hms;
    hms.run();
    return 0;
}