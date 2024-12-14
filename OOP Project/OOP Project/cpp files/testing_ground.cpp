
//THIS FILE IS TEMPORARY AND WILL BE DELETED IN THE FINAL VERSION OF THE PROJECT

#include <iostream>
#include <string>
#include "COLUMN.h"
#include "header files/TABLE.h"
#include "header files/DROP_TABLE.h"

using namespace std;

int main() {
    try {
        // Initialize static variables for the Column class
        Column::NAME_MIN_SIZE = 1;
        Column::MIN_SIZE = 1;
        Column::MAX_DIMENSION = 50;

        cout << "===== Table and Column Test Program =====\n";

        // Create table
        string tableName;
        cout << "Enter table name: ";
        getline(cin, tableName);

        // Validate and set table name
        if (tableName.empty()) {
            throw invalid_argument("Table name cannot be empty!");
        }

        // Dynamically create an array of columns
        int columnCount;
        cout << "Enter number of columns: ";
        cin >> columnCount;
        if (columnCount <= 0) {
            throw invalid_argument("Column count must be greater than 0!");
        }

        Column* columns = new Column[columnCount];
        cin.ignore(); // Clear newline character after reading an integer

        // Fill columns with user input
        for (int i = 0; i < columnCount; ++i) {
            string name, type, defaultValue;
            int size;

            cout << "\n--- Column " << i + 1 << " ---\n";

            // Column name
            cout << "\nEnter column name: ";
            getline(cin, name);

            // Column type
            cout << "Enter column type (integer/text): ";
            getline(cin, type);

            // Column size
            cout << "Enter column size: ";
            cin >> size;

            // Default value
            cin.ignore();
            cout << "Enter default value: ";
            getline(cin, defaultValue);

            // Create and set column
            columns[i].setName(name);
            columns[i].setType(type);
            columns[i].setSize(size);
            columns[i].setDefaultValue(defaultValue);
        }

        // Create table
        Table* table = new Table(tableName, columns, columnCount);

        // Print table information
        cout << endl;
        cout << "\n===== Table Information =====\n";
        table->printTableInfo();

        // Clean up dynamically allocated columns
        delete[] columns;

        DROP drop;

        cout << "\nDo you want to delete (DROP) the table? yes or no: ";
        string userChoice;
        getline(cin, userChoice);

        if (userChoice == "yes" || userChoice == "Yes") {
            drop.dropTable(table);
            cout << "Table " << tableName << " was deleted";
        }
        else
            cout << "\nTable was not deleted." << endl;

        if (table == nullptr)
            cout << "\nNo table Exists currently." << endl;
        else
            cout << "\nTable still exists." << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const char* msg) {
        cerr << "Error: " << msg << endl;
    }
}



cout << "\n===== Program End =====\n";
return 0;
}
