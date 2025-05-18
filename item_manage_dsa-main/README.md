# Item Management System

A command-line application for managing inventory items with basic CRUD operations.

## Description

This Item Management System is a C++ console application that allows users to add and list inventory items. Each item has an ID, name, quantity, and registration date. The application provides a simple command-line interface for interacting with the inventory database stored in a CSV file.

## Features

- Add new items with ID, name, quantity, and registration date
- List all items in the inventory
- Date validation for proper format (dd-mm-yyyy)
- Simple command-line interface

## Prerequisites

- C++ compiler with C++11 support
- Basic knowledge of command-line operations

## Installation

1. Clone this repository or download the source files:
   ```
   git clone https://github.com/NE-templates/item_manage_dsa.git
   ```

2. Navigate to the project directory:
   ```
   cd item_manage_dsa
   ```

3. Compile the source code with static linking:
   ```
   g++ -std=c++11 -static-libgcc -static-libstdc++ data.cpp utils.cpp main.cpp -o a
   ```

## Usage

Run the compiled executable:
```
./a
```

### Available Commands

- `itemadd <item_id> <item_name> <quantity> <registration_date>` - Adds a new item
  - Example: `itemadd 1 Laptop 5 01-05-2025`
  
- `itemslist` - Lists all items in the inventory

- `help` - Displays available commands and their usage

- `exit` or `quit` - Exits the application

### Date Format

Dates must be provided in the format `dd-mm-yyyy`, for example:
- `01-05-2025` for May 1st, 2025
- `25-12-2024` for December 25th, 2024

## Project Structure

- `main.cpp` - Entry point for the application
- `data.h` - Contains the Item structure definition
- `data.cpp` - Defines global variables
- `utils.h` - Declares utility functions
- `utils.cpp` - Implements utility functions
- `items.csv` - Data storage file (created automatically if not present)

## Troubleshooting

### "Entry Point Not Found" Error

If you encounter a runtime error related to missing string function entry points, compile with static linking:
```
g++ -std=c++11 -static-libgcc -static-libstdc++ data.cpp utils.cpp main.cpp -o a
```

### File Access Issues

Make sure the program has appropriate read/write permissions in the directory where it runs. The application needs to create or modify the `items.csv` file.

## Future Enhancements

- Add item deletion functionality
- Add item update functionality
- Add search/filter capabilities
- Add data validation for item IDs and quantities
- Implement user authentication


## License

This project is open-source and available under the [MIT License](LICENSE).