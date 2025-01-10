#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#include "Command_parser.h"
#include "Column.h"

/*
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
        verificaTABLE();
        verificaNume();
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

        //method

      

    // Method to verify if the second word is "TABLE"
    void verificaTABLE() {
        if (this->vector[1] != nullptr && strcmp(this->vector[1], "TABLE") == 0) {
            cout << "merge" << endl;
        }
        else {
            cout << "Command typing error" << endl;
        }
    }
    void verificaNume() {
        if (this->vector[2] != nullptr ) {
            cout << "merge" << endl;
        }
        else {
            cout << "Table needs a valid name" << endl;
        }

    }

    // Getter for vector
    char** getVector() {
        return this->vector;
    }
    
};