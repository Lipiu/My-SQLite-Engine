#include <iostream>
#include <string>
#include <string.h>
#include "TABLE.h"
#include "COLUMN.h"
#include "COMMAND_PARSER.h"
#include "CREATE.h"
using namespace std;

class DISPLAY {
private:
    Command_parser p; //we need the verifySecondWordTable() from CREATE.h
    char* tableName = nullptr;
    int nrCuv = 0;
    char** vector;

public:
    //default constructor
    DISPLAY() {}

    DISPLAY(Command_parser& f) {
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

        //verifyDisplayCommand();
    }

    //destructor
    ~DISPLAY() {
        for (int i = 0; i < nrCuv; i++) {
            delete[] this->vector[i];
        }
        delete[] vector;
        vector = nullptr;
    }

    //getter
    char* getTableName() {
        return this->tableName;
    }

    void verifyDisplayCommand() {
        // Check if the first word is DISPLAY
        if (this->vector[0] != nullptr && strcmp(this->vector[0], "DISPLAY") == 0) {
            // Check if the second word is TABLE
            if (this->vector[1] != nullptr && strcmp(this->vector[1], "TABLE") == 0) {
                if (this->vector[2] != nullptr && this->vector[3] == nullptr) { // Validate table name and check if there is an extra name
                    if (isdigit(this->vector[2][0])) { // Check if the name starts with a number
                        cout << "Wrong command: table name cannot start with a number" << endl;
                    }
                    else {
                        this->tableName = this->vector[2];
                        cout << "Table to display: " << tableName << endl;
                    }
                }
                // Check if we have more than one name
                else if (this->vector[2] != nullptr && this->vector[3] != nullptr) {
                    cout << "Wrong command: too many table names" << endl;
                }
                // Handling the missing table name case
                else {
                    cout << "Wrong command: missing table name" << endl;
                }
            }
            // Handling the wrong keyword case
            else {
                cout << "Wrong command: missing or wrong TABLE keyword" << endl;
            }
        }
        else {
            cout << "Wrong command: unrecognized format" << endl;
        }
    }
};

