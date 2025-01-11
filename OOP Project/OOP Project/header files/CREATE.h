#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#include "Command_parser.h" 
#include "Column.h"

/*
* VALID COMMANDS EXAMPLES:
CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))


CREATE TABLE students IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))
*/

class CREATE {
private:
    Command_parser p;
    char* tableName = nullptr;
    int columnCount = 0;
    char** vector = nullptr;
    int nrCuv = 0;
    Column* columns = nullptr;


    //constructor
public:
    CREATE(Command_parser& f) {
        //setVectorFromCommandParser(p);
        this->nrCuv = f.getNrvector();
        //this->vector = f.getVector();
        char** sourceVector = f.getVector();

        this->vector = new char* [nrCuv + 1];
        for (int i = 0; i < nrCuv; i++) {
            this->vector[i] = new char[strlen(sourceVector[i]) + 1];
            strcpy(this->vector[i], sourceVector[i]);
        }
        this->vector[nrCuv] = nullptr;
        //VERIFICATION METHODS  
        verificaTABLE();
        verificaNume();
    }

    ~CREATE() {
        // Free each string in the vector
        for (int i = 0; i < nrCuv; i++) {
            delete[] vector[i];
        }
        delete[] vector;

        if (columns) {
            delete[] columns;
        }
    }

    void verificaTABLE() {
        if (this->vector[1] != nullptr && strcmp(this->vector[1], "TABLE") == 0) {
            cout << "Valid command: TABLE" << endl;
        }
        else {
            cout << "Command typing error" << endl;
        }
    }

    void verificaNume() {
        if (this->vector[2] != nullptr) {
            if (this->vector[2][0] >= '0' && this->vector[2][0] <= '9') {
                cout << "Table name cannot start with digits." << endl;
                return;
            }
            else {
                cout << "Valid table name." << endl;
            }
        }
        else {
            cout << "Name does not exist." << endl;
        }
    }

    void parseColumn() {
        cout << "Entering parseColumn()" << endl;
        int startIndex = 3; // Starting index of column definitions
        columnCount = 0;

        // Count the number of columns based on '(' in the input
        for (int i = startIndex; i < nrCuv; i++) {
            if (vector[i][0] == '(') {
                columnCount++;
            }
        }

        // Allocate memory for columns
        this->columns = new Column[columnCount];
        int columnIndex = 0;

        // Parse each column definition
        for (int i = startIndex; i < nrCuv; i++) {
            if (vector[i][0] == '(') {
                char* columnString = new char[strlen(vector[i]) + 1];
                strcpy(columnString, vector[i]);

                // Remove outer parentheses
                char* start = columnString + 1;
                columnString[strlen(columnString) - 1] = '\0';

                // Tokenize the column definition
                char* attributes[4] = { nullptr };
                int attrIndex = 0;
                char* tok = strtok(start, ",");
                while (tok != nullptr && attrIndex < 4) {
                    while (*tok == ' ') tok++; // Trim leading spaces
                    char* end = tok + strlen(tok) - 1;
                    while (end > tok && *end == ' ') *end-- = '\0'; // Trim trailing spaces

                    attributes[attrIndex] = tok;
                    attrIndex++;
                    tok = strtok(nullptr, ",");
                }

                // Verify and assign attributes
                if (attrIndex == 4) {
                    this->columns[columnIndex++] = Column(attributes[0], attributes[1], attributes[2], attributes[3]);
                }
                else {
                    cout << "Invalid column definition: " << vector[i] << endl;
                }

                delete[] columnString;
            }
        }
    }

    void displayColumns() {
        for (int i = 0; i < this->columnCount; i++) {
            this->columns[i].printInfo();
        }
    }

    char** getVector() {
        return this->vector;
    }
    // Getter for the number of columns
    int getColumnCount() const {
        return columnCount;
    }

    // Getter for the columns array
    Column* getColumns() const {
        return columns;
    }
};