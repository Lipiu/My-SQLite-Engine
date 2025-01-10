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
    char** vector;
    int nrCuv = 0;

public:
    //constructor
    CREATE(Command_parser& f) {
        //setVectorFromCommandParser(p);
        this->nrCuv = f.getNrvector();
        //this->vector = f.getVector();
        char** sourceVector = f.getVector();

        this->vector = new char* [nrCuv+1];
        for (int i = 0; i < nrCuv; i++) {
            this->vector[i] = new char[strlen(sourceVector[i]) + 1];
            strcpy(this->vector[i], sourceVector[i]);
        }
        this->vector[nrCuv] = nullptr;
        //VERIFICATION METHODS
        verifySecondWordTable();
        verifyTableName();
    }

    ~CREATE() {
        // Free each string in the vector
        for (int i = 0; i < nrCuv; i++) {
            delete[] vector[i];
            vector[i] = nullptr;  // Optional: Set each element to nullptr
        }

        // Free the array of pointers itself
        delete[] vector;
        vector = nullptr;  // Optional: Set vector to nullptr after deletion
    }


    // Method to verify if the second word is "TABLE"
    void verifySecondWordTable() {
        if (this->vector[1] != nullptr && strcmp(this->vector[1], "TABLE") == 0) {
            cout << "TABLE este al doilea cuvant..." << endl;
        }
        else {
            cout << "Eroare. TABLE nu este al doilea cuvant..." << endl;
        }
    }

    // Method to verify if the name exists and is valid
    /*
    * The table name cannot start with a digit but can have one if it is not the first character
    * 1table -> invalid
    * table1 -> valid
    */
    void verifyTableName() {
        if (this->vector[2] != nullptr) {
            char* tableName = this->vector[2];

            if (tableName[0] >= '0' && tableName[0] <= '9') {
                cout << "Table name cannot start with digits." << endl;
                return;
            }
            else
                cout << "Valid table name." << endl;
        }
        else
            cout << "Name does not exist." << endl;
    }


    // Getter for vector
    char** getVector() {
        return this->vector;
    }

};