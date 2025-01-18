#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include "Command_parser.h"
#include "TABLE.h"

using namespace std;

class INSERT {
private:
    Command_parser p;
    char* tableName = nullptr;
    char** values = nullptr; // Dynamically allocated array for parsed values
    int nrCuv = 0;
    char** vector = nullptr;
    int valueCount = 0;

public:
    // ctor
    INSERT(Command_parser& f) {
        this->nrCuv = f.getNrvector();
        char** sourceVector = f.getVector();
        this->vector = new char* [nrCuv + 1];
        for (int i = 0; i < nrCuv; i++) {
            this->vector[i] = new char[strlen(sourceVector[i]) + 1];
            strcpy(this->vector[i], sourceVector[i]);
        }
        this->vector[nrCuv] = nullptr;

        verifyInsertCommand();
    }

    // Destructor
    ~INSERT() {
        for (int i = 0; i < nrCuv; i++) {
            delete[] this->vector[i];
        }
        delete[] this->vector;

        if (values) {
            for (int i = 0; i < valueCount; i++) {
                delete[] values[i];
            }
            delete[] values;
        }
    }

    // Check the syntax of the INSERT command
    void verifyInsertCommand() {
        // Check if the command starts with "INSERT"
        if (this->vector[0] == nullptr || strcmp(this->vector[0], "INSERT") != 0) {
            cout << "Wrong command: missing or incorrect 'INSERT' keyword" << endl;
            return;
        }

        // Check if the second word of the command is "INTO"
        if (this->vector[1] == nullptr || strcmp(this->vector[1], "INTO") != 0) {
            cout << "Wrong command: missing or incorrect 'INTO' keyword" << endl;
            return;
        }

        // Check if the table name is valid
        if (this->vector[2] == nullptr || this->vector[2][0] == '(') {
            cout << "Wrong command: missing table name" << endl;
            return;
        }

        if (isdigit(this->vector[2][0])) {
            cout << "Wrong command: table name cannot start with a number" << endl;
            return;
        }

        this->tableName = this->vector[2];

        // Check for  "VALUES" keyword
        if (this->vector[3] == nullptr || strcmp(this->vector[3], "VALUES") != 0) {
            cout << "Wrong command: missing or incorrect 'VALUES' keyword" << endl;
            return;
        }

        // Check for  parantheses
        if (this->vector[4] == nullptr || this->vector[4][0] != '(' || this->vector[4][strlen(this->vector[4]) - 1] != ')') {
            cout << "Wrong command: missing or incorrect parentheses around values" << endl;
            return;
        }

        parseValues();
    }

    // Parse the values provided in the command
    void parseValues() {
        char* valueStr = this->vector[4];
        int length = strlen(valueStr);

        // Remove surrounding parantheses
        char* temp = new char[length - 1];
        strncpy(temp, valueStr + 1, length - 2);
        temp[length - 2] = '\0';

        // Allocate memory for parsed values
        const int MAX_VALUES = 50;
        values = new char* [MAX_VALUES];
        valueCount = 0;

        char* token = strtok(temp, ",");
        while (token != nullptr) {
            values[valueCount] = new char[strlen(token) + 1];
            strcpy(values[valueCount], token);
            valueCount++;
            token = strtok(nullptr, ",");
        }

        delete[] temp;

        printInsertInfo();
    }

    // Print details
    void printInsertInfo() {
        cout << "Table: " << tableName << endl;
        cout << "Number of columns: " << valueCount << endl;

        for (int i = 0; i < valueCount; i++) {
            cout << "Column " << i + 1 << " value: " << values[i] << endl;
        }
    }
};
