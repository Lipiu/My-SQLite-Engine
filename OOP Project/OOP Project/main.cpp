
//THIS FILE IS TEMPORARY AND WILL BE DELETED IN THE FINAL VERSION OF THE PROJECT

#include <iostream>
#include <string>
#include "COLUMN.h"
#include "CREATE_TABLE.h"
#include "DROP_TABLE.h"
#include "CREATE_INDEX.h"


int main() {
    try {
        // Initialize static variables for the Column class
        Column::NAME_MIN_SIZE = 1;
        Column::MIN_SIZE = 1;
        Column::MAX_DIMENSION = 50;

        std::cout << "===== Table and Column Test Program =====\n";

        // Create table
        std::string tableName;
        std::cout << "Enter table name: ";
        std::getline(std::cin, tableName);

        // Validate and set table name
        if (tableName.empty()) {
            throw std::invalid_argument("Table name cannot be empty!");
        }

        // Dynamically create an array of columns
        int columnCount;
        std::cout << "Enter number of columns: ";
        std::cin >> columnCount;
        if (columnCount <= 0) {
            throw std::invalid_argument("Column count must be greater than 0!");
        }

        Column* columns = new Column[columnCount];
        std::cin.ignore(); // Clear newline character after reading an integer

        // Fill columns with user input
        for (int i = 0; i < columnCount; ++i) {
           std:: string name, type, defaultValue;
            int size;

            std::cout << "\n--- Column " << i + 1 << " ---\n";

            // Column name
            std::cout << "\nEnter column name: ";
            std::getline(std::cin, name);

            // Column type
            std::cout << "Enter column type (integer/text): ";
            std::getline(std::cin, type);

            // Column size
            std::cout << "Enter column size: ";
            std::cin >> size;

            // Default value
            std::cin.ignore();
            std::cout << "Enter default value: ";
            std::getline(std::cin, defaultValue);

            // Create and set column
            columns[i].setName(name);
            columns[i].setType(type);
            columns[i].setSize(size);
            columns[i].setDefaultValue(defaultValue);
        }

        // Create table
        Table* table = new Table(tableName, columns, columnCount);

        // Print table information
        std::cout << std::endl;
        std::cout << "\n===== Table Information =====\n";
        table->printTableInfo();

        // Clean up dynamically allocated columns
        delete[] columns;

        DROP drop;

        std::cout << "\nDo you want to delete (DROP) the table? yes or no: ";
        std::string userChoice;
        std::getline(std::cin, userChoice);

        if (userChoice == "yes" || userChoice == "Yes") {
            drop.dropTable(table);
            std::cout << "Table " << tableName << " was deleted";
        }
        else
            std::cout << "\nTable was not deleted." << std::endl;

        if (table == nullptr)
            std::cout << "\nNo table Exists currently." << std::endl;
        else
            std::cout << "\nTable still exists." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const char* msg) {
        std::cerr << "Error: " << msg << std::endl;
    }
    std::cout << "\n===== Program End =====\n";

    return 0;
}

