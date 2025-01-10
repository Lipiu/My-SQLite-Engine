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

        this->vector = new char* [nrCuv];
        for (int i = 0; i < nrCuv; i++) {
            this->vector[i] = new char[strlen(sourceVector[i]) + 1];
            strcpy(this->vector[i], sourceVector[i]);
        }
    }

    ~CREATE() {
        for (int i = 0; i < nrCuv; i++) {
            delete[] vector[i];
        }
        delete[] vector;
    }

        //methods
        void verifica() const {
        for (int i = 0; i < this->nrCuv; i++)
            cout << this->vector[i] << " " << "asta e din create" << " ";
        if (strcmp(vector[1], "TABLE") == 0)
            cout << "evrica";
    }

        // Tokenizes the input string and stores words in vector
        void setVector(const char* input) {
        char* tempInput = new char[strlen(input) + 1];
        strcpy(tempInput, input);

        int i = 0;
        char* token = strtok(tempInput, " ");  // Tokenize the input string
        while (token != nullptr) {
            this->vector[i] = new char[strlen(token) + 1];
            strcpy(this->vector[i], token);  // Store each word in the vector
            i++;
            token = strtok(nullptr, " ");  // Get the next word
        }

        // Clean up
        delete[] tempInput;
    }

    // Method to verify if the second word is "TABLE"
    void verifica() {
        if (this->vector[1] != nullptr && strcmp(this->vector[1], "TABLE") == 0) {
            cout << "merge" << endl;
        }
        else {
            cout << ":(" << endl;
        }
    }

    // Getter for vector
    char** getVector() {
        return this->vector;
    }
    
};