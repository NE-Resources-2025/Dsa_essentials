# Hospital Management System 🏥

A comprehensive C++ application for managing hospitals and their network connections using graph data structures and CSV file storage.

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Data Structures](#data-structures)
- [Time Complexities](#time-complexities)
- [Installation & Usage](#installation--usage)
- [File Structure](#file-structure)
- [API Reference](#api-reference)
- [Sample Data](#sample-data)
- [Contributing](#contributing)

## 🎯 Overview

This system manages hospitals as nodes in a weighted graph where:
- **Nodes**: Hospitals with unique IDs (H1, H2, H3...)
- **Edges**: Connections between hospitals with distances in kilometers
- **Storage**: CSV files for data persistence
- **Operations**: Full CRUD functionality with input validation

## ✨ Features

### Core Functionality
- ✅ **Hospital Management**: Add, view, update, delete hospital records
- ✅ **Network Management**: Link hospitals with distance-based connections
- ✅ **Graph Visualization**: ASCII representation of hospital network
- ✅ **Data Persistence**: Automatic CSV file storage and retrieval
- ✅ **Input Validation**: Robust error handling and data validation
- ✅ **Help System**: Comprehensive user guidance

### User Interface
- 🖥️ **Menu-driven interface** with 8 options
- 🔄 **Interactive prompts** with retry mechanisms
- 📊 **Formatted data display** with clear separators
- ❓ **Built-in help system** for user guidance

## 🏗️ System Architecture

### Three-Layer Architecture --- Separation of Concerns
- **data.cpp**: Data structures and model definitions
- **utils.cpp**: Business logic, CRUD operations, file I/O
- **main.cpp**: User interface and program flow control

## 📊 Data Structures

### Primary Data Structures

| Structure | Type | Purpose | Access Pattern |
|-----------|------|---------|----------------|
| `hospitals` | `map<string, Hospital>` | Hospital storage | Key-based lookup |
| `connections` | `vector<Connection>` | Graph edges | Sequential access |

### Hospital Structure
```cpp
struct Hospital {
    string name;        // Hospital name
    string location;    // Physical location
    int patients;       // Number of patients
    
    // Methods: display(), isValid()
}
```
### Connection structure
```
struct Connection {
string hospital1;   // First hospital ID
string hospital2;   // Second hospital ID
double distance;    // Distance in kilometers

    // Methods: display(), involves(), isSameAs(), isValid()
}
```
### Compiling
# Single command compilation
g++ -o hospital_system *.cpp

# Or compile individually
g++ -c data.cpp -o data.o
g++ -c utils.cpp -o utils.o  
g++ -c main.cpp -o main.o
g++ data.o utils.o main.o -o hospital_system

## 🏥 Hospital Operations (using `std::map`)

| Operation         | Time Complexity   | Space Complexity | Description                    |
|------------------|-------------------|------------------|--------------------------------|
| Add Hospital      | O(log n)          | O(1)              | Insert into balanced BST       |
| Find Hospital     | O(log n)          | O(1)              | Search in balanced BST         |
| Update Hospital   | O(log n)          | O(1)              | Find + modify                  |
| Delete Hospital   | O(log n + m)      | O(1)              | Remove + update connections    |
| View All Hospitals| O(n)              | O(1)              | Iterate through map            |

## 🔗 Connection Operations (using `std::vector`)

| Operation          | Time Complexity      | Space Complexity | Description                          |
|-------------------|----------------------|------------------|--------------------------------------|
| Add Connection     | O(m) + O(1)          | O(1)              | Check duplicates + insert            |
| Find Connections   | O(m)                 | O(1)              | Linear search                         |
| Delete Connections | O(m)                 | O(1)              | Linear search + remove                |
| View Graph         | O(n + m)             | O(1)              | Display all nodes + edges             |

## 📁 File Operations

| Operation         | Time Complexity   | Space Complexity | Description             |
|------------------|-------------------|------------------|-------------------------|
| Load from CSV     | O(n) or O(m)      | O(n) or O(m)      | Read all records        |
| Save to CSV       | O(n) or O(m)      | O(1)              | Write all records       |

> **Note**:
> - `n` = number of hospitals
> - `m` = number of connections
> - The map ensures sorted access, and the vector enables flexible connection management.  

## 🛡️ Input Validation

### Hospital ID Validation
- Must start with **'H'** followed by numbers (e.g., `H1`, `H2`, `H10`)
- **Case-insensitive** input (automatically converted to uppercase)
- **Checks for uniqueness** before insertion

### Distance Validation
- Must be a **positive decimal number**
- Valid **range: 0.1 km to 10,000 km**
- **Self-loops prevented** (a hospital can't connect to itself)

### Data Validation
- **Hospital names** and **locations** must not be empty
- **Patient count** must be a **non-negative integer**
- **Trims** whitespace from string inputs

## 🚨 Error Handling

### File Operations
- **Graceful handling** of missing CSV files
- Clear error messages for **file read/write** failures
- **Automatic file creation** on first run

### Input Errors
- Invalid numeric input prompts **retry**
- **Range validation** for all numeric fields
- **Required field** checks for strings

### Data Integrity
- **Duplicate connections** are not allowed
- **Orphaned connections** are cleaned up when a hospital is deleted
- **Consistency checks** before saving data

## 📄 License

This project is created for **educational purposes**.  
Feel free to **use and modify** for learning, teaching, and academic projects.

- **Author:** AKUZWE SHEJA Edwige
- **Last Updated:** 2025
- **Version:** 1.0.0