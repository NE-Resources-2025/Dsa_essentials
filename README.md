# INTEGRATED SITUATION

## Context:
Ruhengeri Referral Hospital (RRH) needs a system to manage patient records, doctor appointments, and medical staff data. As a software engineer, you're tasked with developing a C++ program to handle these operations using linked lists and file storage (CSV).

## TASK
Develop a Healthcare Management System with the following features:

## Requirements:
### Command-Driven Interface
- The program should run until the user enters `exit`.

### Core Features
#### Add Patient && Add Doctor:
- **Command:** Entering as prompted
- **Validation:** Ensure `id` is unique and `dob` format is `DD/MM/YYYY`.

#### Save/Load Data:
- Save all data to `patients.csv`, `doctors.csv`, and `appointments.csv` on exit.
- Load data from these files when the program starts.

#### Exam-Specific Constraints
**Data Structures**: Use linked lists (no arrays/vectors).
**File I/O**: Save/Load CSV files