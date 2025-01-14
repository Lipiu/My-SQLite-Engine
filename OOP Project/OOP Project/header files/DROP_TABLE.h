#pragma once
#include <iostream>
#include <string>

using namespace std;

class DROP {
private:
    string tableName;    // Store the table name
    int nrWords = 0;     // Number of words in the command
    string* words = nullptr; // Array of command words

public:
    // Default ctor
    DROP() {
    }

    // Ctor
    DROP(string* inputWords, int count) {
        nrWords = count;
        words = new string[nrWords];
        for (int i = 0; i < nrWords; i++) {
            words[i] = inputWords[i];
        }
    }

    // Destructor
    ~DROP() {
        delete[] words;
    }

    // Method for verifying the DROP TABLE command
    void verifyDropCommand() {
        // Check if the command starts with "DROP"
        if (nrWords > 0 && words[0] == "DROP") {
            // Check if the second word is "TABLE"
            if (nrWords > 1 && words[1] == "TABLE") {
                // Check if a valid table name follows
                if (nrWords == 3) {
                    // Check if table name does not start with a number or contain spaces
                    if (isdigit(words[2][0])) {
                        cout << "Wrong command: table name cannot start with a number" << endl;
                    }
                    else if (words[2].find(' ') != string::npos) {
                        cout << "Wrong command: table name contains space" << endl;
                    }
                    else {
                        tableName = words[2];
                        cout << "Table to delete: " << tableName << endl;
                    }
                }
                // Check for too many table names
                else if (nrWords > 3) {
                    cout << "Wrong command: too many table names" << endl;
                }
                // Case where the table name is missing 
                else {
                    cout << "Wrong command: missing table name" << endl;
                }
            }
            // Handling incorrect or missing "TABLE" keyword
            else {
                cout << "Wrong command: missing or wrong TABLE keyword" << endl;
            }
        }
        // Handling invalid command format
        else {
            cout << "Wrong command: unrecognized format" << endl;
        }
    }
};
