#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "data.cpp"
#include "utils.cpp"

using namespace std;

/**
 * Main Hospital Management System class
 * This is the driver class that coordinates all operations
 */
class HospitalManagementSystem {
private:
    map<string, Hospital> hospitals;
    vector<Connection> connections;

public:
    /**
     * Constructor - Initialize the system by loading existing data
     */
    HospitalManagementSystem() {
        loadData();
    }

    /**
     * Destructor - Ensure data is saved when program ends
     */
    ~HospitalManagementSystem() {
        saveData();
    }

    /**
     * Load data from CSV files
     */
    void loadData() {
        HospitalUtils::loadHospitals(hospitals);
        HospitalUtils::loadConnections(connections);
    }

    /**
     * Save data to CSV files
     */
    void saveData() {
        HospitalUtils::saveHospitals(hospitals);
        HospitalUtils::saveConnections(connections);
    }

    /**
     * Display the main menu
     */
    void displayMenu() {
        cout << "\n" << string(50, '=') << endl;
        cout << "HOSPITAL MANAGEMENT SYSTEM" << endl;
        cout << string(50, '=') << endl;
        cout << "1. View the registered Hospitals and their details" << endl;
        cout << "2. Add a hospital and its details" << endl;
        cout << "3. Update hospital details" << endl;
        cout << "4. Delete hospital" << endl;
        cout << "5. Link hospital to another hospital" << endl;
        cout << "6. View the graph of the hospitals and their edges" << endl;
        cout << "7. Help" << endl;
        cout << "8. Exit" << endl;
        cout << string(50, '-') << endl;
    }

    /**
     * Get user choice with validation
     */
    int getUserChoice() {
        return HospitalUtils::getValidInteger("Enter your choice (1-8): ", 1, 8);
    }

    /**
     * Handle menu choice
     */
    void handleChoice(int choice) {
        switch (choice) {
            case 1:
                HospitalUtils::viewHospitals(hospitals);
                break;
            case 2:
                HospitalUtils::addHospital(hospitals);
                break;
            case 3:
                HospitalUtils::updateHospital(hospitals);
                break;
            case 4:
                HospitalUtils::deleteHospital(hospitals, connections);
                break;
            case 5:
                HospitalUtils::linkHospitals(hospitals, connections);
                break;
            case 6:
                HospitalUtils::viewGraph(hospitals, connections);
                break;
            case 7:
                HospitalUtils::displayHelp();
                break;
            case 8:
                cout << "\nSaving data and exiting..." << endl;
                saveData();
                cout << "Thank you for using Hospital Management System!" << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
        HospitalUtils::pauseScreen();
    }

    /**
     * Initialize sample data if needed
     */
    void checkForSampleDataInitialization() {
        if (hospitals.empty()) {
            cout << "Welcome to Hospital Management System!" << endl;
            cout << "No existing data found." << endl;
            
            char init_sample;
            cout << "Would you like to initialize with sample data? (y/n): ";
            cin >> init_sample;
            cin.ignore();

            if (init_sample == 'y' || init_sample == 'Y') {
                HospitalUtils::initializeSampleData(hospitals, connections);
                HospitalUtils::pauseScreen();
            }
        }
    }

    /**
     * Main program loop
     */
    void run() {
        // Welcome message and sample data initialization
        checkForSampleDataInitialization();

        int choice;
        do {
            displayMenu();
            choice = getUserChoice();
            handleChoice(choice);
        } while (choice != 8);
    }

    /**
     * Get system statistics for debugging/info purposes
     */
    void displaySystemInfo() {
        cout << "\n=== SYSTEM INFORMATION ===" << endl;
        cout << "Total Hospitals: " << hospitals.size() << endl;
        cout << "Total Connections: " << connections.size() << endl;
        cout << "Data Files: hospitals.csv, hospital_connections.csv" << endl;
    }
};

/**
 * Main function - Entry point of the program
 */
int main() {
    try {
        // Create and run the hospital management system
        HospitalManagementSystem hms;
        hms.run();
    }
    catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        cerr << "Press Enter to exit..." << endl;
        cin.get();
        return 1;
    }
    catch (...) {
        cerr << "An unknown error occurred!" << endl;
        cerr << "Press Enter to exit..." << endl;
        cin.get();
        return 1;
    }

    return 0;
}