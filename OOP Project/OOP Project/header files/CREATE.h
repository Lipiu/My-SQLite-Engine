#pragma once
#include <iostream>
#include <string>
#include "Command_parser.h"
#include "Table.h"
#include "Column.h"

using namespace std;

//TO DO:
//prea multe while loops, trebuie optimizat
//functia este in clasa, trebuie ordonat in fisier cpp

class CREATE {
public:
    // Method to handle the CREATE command process
    static void executeCreateCommand(const char* input) {
        Command_parser parser(input);  // Parse the input

        // Check if the command is "CREATE" (3 corresponds to CREATE)
        if (parser.getComVal() == 3) {
            string tableName;
            int columnCount;

            // Get table name from the user
            cout << "Enter table name: ";
            //getline(cin, tableName);
            while (true) {
                getline(cin, tableName);
                if (tableName.empty()) {
                    cout << "Table name cannot be empty. Try again: ";
                }
                else
                    break;
            }


            // Get the number of columns
            cout << "Enter the number of columns: ";
            while (true) {
                cin >> columnCount;
                if (columnCount <= 0) {
                    cout << "Column count must be STRICTLY greater than 0. Try a positive integer: ";
                    continue;
                }
                break;
            }

            // Create an array of columns
            Column* columns = new Column[columnCount];
            cin.ignore();  // To ignore leftover newline character after integer input

            for (int i = 0; i < columnCount; ++i) {
                string name, type, defaultValue;
                int size;

                cout << "Column " << i + 1 << ":\n";

                // Input column name
                cout << "Enter column name: ";

                getline(cin, name);

                // Input column type (either "integer" or "text")
                cout << "Enter column type (integer/text): ";
                while (true) {
                    getline(cin, type);
                    if (type == "integer" || type == "text") {
                        break;
                    }
                    cout << "Invalid type! Please enter 'integer' or 'text': ";
                }

                // Input column size (for integer it's the size of the number, for text it's the string length)
                cout << "Enter column size: ";
                while (true) {
                    cin >> size;
                    if (size <= 0) {
                        cout << "Size must be greater than 0. Try again: ";
                        continue;
                    }
                    break;
                }
                cin.ignore();  // To ignore leftover newline character after integer input

                // Input default value (for "integer" it must be a valid integer, for "text" it's a string)
                cout << "Enter default value: ";
                getline(cin, defaultValue);

                try {
                    // Create and set column details
                    Column column(name, type, size, defaultValue);
                    columns[i] = column;
                }
                catch (const char* error) {
                    cout << "Error: " << error << endl;
                    --i;  // Retry the current column if there's an error
                }
            }

            // Now that we have all the columns, create a Table object
            try {
                Table table(tableName, columns, columnCount);
                table.printTableInfo();  // Display the created table information
            }
            catch (const char* error) {
                cout << "Error creating table: " << error << endl;
            }

            // Clean up dynamic memory for columns
            delete[] columns;
        }
        else {
            cout << "Invalid command. Please use a CREATE command.\n";
        }
    }
};