# INTEGRATED SITUATION

## Context:
Ruhengeri Referral Hospital (RRH) needs a system to manage patient records, doctor appointments, and medical staff data. As a software engineer, you're tasked with developing a C++ program to handle these operations using linked lists and file storage (CSV).

## TASK
Develop a Healthcare Management System with the following features:

## Requirements:
### Command-Driven Interface
- The program should run until the user enters `exit`.
- Commands are case-insensitive (e.g., `ADD` or `add`).

### Core Features
#### Add Patient:
- **Command:** `add_patient <id>,<name>,<dob>,<gender>`
- **Example:** `add_patient 101,John Doe,12-05-1990,M`
- **Validation:** Ensure `id` is unique and `dob` format is `DD-MM-YYYY`.

#### Add Doctor:
- **Command:** `add_doctor <id>,<name>,<specialization>`
- **Example:** `add_doctor 201,Dr. Smith,Cardiology`

#### List Records:
- **Command:** `list_patients`, `list_doctors`, `list_appointments`
- Display records in alphabetical order (by name).

#### Save/Load Data:
- Save all data to `patients.csv`, `doctors.csv`, and `appointments.csv` on exit.
- Load data from these files when the program starts.

### Error Handling
If a command is invalid, display:  
`Error: Invalid command. Type 'help' for a list of commands.`

### Help Command
**Command:** `help`  
Displays:
```bash
Commands:
- add_patient <id>,<name>,<dob>,<gender>
- add_doctor <id>,<name>,<specialization>
- list_patients
- list_doctors
- exit
```

#### Expected Output Format
```bash
RRH HEALTHCARE SYSTEM (v1.0)  
Type 'help' for commands.  
> add_patient 101,Alice,01-01-2000,F  
Patient added successfully!  
> list_patients  
ID  | Name  | DoB        | Gender  
101 | Alice | 01-01-2000 | F  
> exit  
Saving data... Goodbye!  
```

#### Exam-Specific Constraints
**Data Structures**: Use linked lists (no arrays/vectors).
**File I/O**: Save/Load CSV files with the exact format:
```text
id,name,dob,gender  
101,Alice,01-01-2000,F  
```
**Sorting**: Implement alphabetical sorting for list commands (e.g., bubble sort for linked lists).

