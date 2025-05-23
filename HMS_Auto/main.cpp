#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <limits>
#include "utils.h"

using namespace std;

class HospitalManagementSystem {
private:
    map<string, Hospital> hospitals;
    vector<Connection> connections;

public:
    // Constructor: loads data from files when the system starts
    HospitalManagementSystem() {
        loadData();
    }

    // Loads both hospitals and connections from files
    void loadData() {
        bool hospitalsLoaded = HospitalUtils::loadHospitals(hospitals);
        bool connectionsLoaded = HospitalUtils::loadConnections(connections);
        
        if (!hospitalsLoaded && !connectionsLoaded) {
            cout << "Starting with empty database (files will be created automatically)" << endl;
        }
    }

    // Main menu loop for the program
    void run() {
        // If there are no hospitals, ask user if they want sample data
        if (hospitals.empty()) {
            cout << "Welcome to Hospital Management System!" << endl;
            cout << "No hospitals found in database." << endl;
            
            char init_sample;
            cout << "Would you like to initialize with sample data? (y/n): ";
            cin >> init_sample;
            cin.ignore();

            if (init_sample == 'y' || init_sample == 'Y') {
                HospitalUtils::initializeSampleData(hospitals, connections);
                HospitalUtils::pauseScreen();
            }
        }

        int choice;
        while (true) {
            // Show menu options
            HospitalUtils::displayHeader("HOSPITAL MANAGEMENT SYSTEM");
            cout << "1. View Hospitals" << endl;
            cout << "2. Add Hospital" << endl;
            cout << "3. Update Hospital" << endl;
            cout << "4. Delete Hospital" << endl;
            cout << "5. Link Hospitals" << endl;
            cout << "6. View Network Graph" << endl;
            cout << "7. Add Multiple Hospitals" << endl;
            cout << "8. Help" << endl;
            cout << "9. Exit" << endl;
            HospitalUtils::displaySeparator();

            choice = HospitalUtils::getValidInteger("Enter your choice (1-9): ", 1, 9);

            // Execute the chosen action
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
                    addMultipleHospitals();
                    break;
                case 8:
                    showHelp();
                    break;
                case 9:
                    exitSystem();
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }

            HospitalUtils::pauseScreen();
        }
    }

private:
    // Menu option implementations
    void viewHospitals() {
        HospitalUtils::viewHospitals(hospitals);
    }

    void addHospital() {
        if (HospitalUtils::addHospital(hospitals)) {
            cout << "\nHospital added successfully!" << endl;
        } else {
            cout << "\nFailed to add hospital. Please try again." << endl;
        }
    }

    void updateHospital() {
        if (HospitalUtils::updateHospital(hospitals)) {
            cout << "\nHospital updated successfully!" << endl;
        } else {
            cout << "\nUpdate operation cancelled or failed." << endl;
        }
    }

    void deleteHospital() {
        if (HospitalUtils::deleteHospital(hospitals, connections)) {
            cout << "\nHospital deleted successfully!" << endl;
        } else {
            cout << "\nDelete operation cancelled or failed." << endl;
        }
    }

    void linkHospitals() {
        if (HospitalUtils::linkHospitals(hospitals, connections)) {
            cout << "\nHospitals linked successfully!" << endl;
        } else {
            cout << "\nLink operation cancelled or failed." << endl;
        }
    }

    void viewGraph() {
        HospitalUtils::viewGraph(hospitals, connections);
    }

    void addMultipleHospitals() {
        if (HospitalUtils::addMultipleHospitals(hospitals)) {
            cout << "\nMultiple hospitals added successfully!" << endl;
        } else {
            cout << "\nOperation cancelled or failed." << endl;
        }
    }

    void showHelp() {
        HospitalUtils::displayHelp();
    }

    void exitSystem() {
        HospitalUtils::displayHeader("SYSTEM SHUTDOWN");
        
        // Save all data before exiting
        bool hospitalsSaved = HospitalUtils::saveHospitals(hospitals);
        bool connectionsSaved = HospitalUtils::saveConnections(connections);
        
        if (hospitalsSaved && connectionsSaved) {
            cout << "All data saved successfully!" << endl;
        } else {
            cout << "Warning: There was an issue saving some data!" << endl;
        }
        
        // Display summary statistics
        cout << "\nSession Summary:" << endl;
        cout << "- Total Hospitals: " << hospitals.size() << endl;
        cout << "- Total Connections: " << connections.size() << endl;
        
        if (!hospitals.empty()) {
            cout << "- Hospital IDs: ";
            bool first = true;
            for (const auto& pair : hospitals) {
                if (!first) cout << ", ";
                cout << pair.first;
                first = false;
            }
            cout << endl;
        }
        
        cout << "\nThank you for using Hospital Management System!" << endl;
        cout << "All data has been saved to CSV files." << endl;
    }
};

// The main function: program starts here
int main() {
    try {
        // Create the system object and run it
        HospitalManagementSystem hms;
        hms.run();
    }
    catch (const exception& e) {
        cout << "An error occurred: " << e.what() << endl;
        cout << "Press Enter to exit...";
        cin.get();
        return 1;
    }
    catch (...) {
        cout << "An unknown error occurred!" << endl;
        cout << "Press Enter to exit...";
        cin.get();
        return 1;
    }
    
    return 0;
}