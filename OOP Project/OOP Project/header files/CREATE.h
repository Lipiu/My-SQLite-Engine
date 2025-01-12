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
    char** vectorComanda = nullptr;
    int nrCuv = 0;
    Column* columns = nullptr;


    //constructor
public:
    CREATE(Command_parser& f) {
        //setVectorFromCommandParser(p);
        this->nrCuv = f.getNrvector();
        //this->vector = f.getVector();
        char** sourceVector = f.getVector();

        this->vectorComanda = new char* [nrCuv + 1];
        for (int i = 0; i < nrCuv; i++) {
            this->vectorComanda[i] = new char[strlen(sourceVector[i]) + 1];
            strcpy(this->vectorComanda[i], sourceVector[i]);
        }
        this->vectorComanda[nrCuv] = nullptr;
        //VERIFICATION METHODS  
        verificaTABLE();
        
    }

    ~CREATE() {
        // Free each string in the vector
        for (int i = 0; i < nrCuv; i++) {
            delete[] vectorComanda[i];
        }
        delete[] vectorComanda;

        if (columns) {
            delete[] columns;
        }
    }

    void verificaTABLE() {
        if (this->vectorComanda[1] != nullptr && strcmp(this->vectorComanda[1], "TABLE") == 0) {
            cout << "Valid command: TABLE" << endl;
            verificaNume();
        }
        else {
            cout << "Command typing error" << endl;
        }
        
    }

    void verificaNume() {
        if (this->vectorComanda[2] != nullptr) {
            if (this->vectorComanda[2][0] >= '0' && this->vectorComanda[2][0] <= '9') {
                cout << "Table name cannot start with digits." << endl;
                return;
            }
            else {
                cout << "Valid table name." << endl;
                parseColumnB();
            }
        }
        else {
            cout << "Name does not exist." << endl;
        }
    }

    
    void parseColumnB() {
       
        const int MAX_SIZE = 200;  // Maximum size for input string
        const int MAX_ELEMENTS = 20; // Maximum number of components to extract
        const int MAX_COMPONENT_SIZE = 50; // Maximum size of each component


        char* vector[MAX_ELEMENTS];

        // Allocate memory for each substring and initialize
        for (int j = 0; j < MAX_ELEMENTS; j++) {
            vector[j] = new char[MAX_COMPONENT_SIZE];
            vector[j][0] = '\0'; // Null-terminate initially
        }

        int index = 0; // Tracks components in `vector`
        int pos = 0;   // Tracks position within the current substring
        bool insideParentheses = false;

        for (int i = 0; i < strlen(this->vectorComanda[3]); i++) {
            if (this->vectorComanda[3][i] == '(') {
                insideParentheses = true;
                pos = 0; // Reset position for a new component
            }
            else if (this->vectorComanda[3][i] == ')') {
                insideParentheses = false;
                if (pos > 0 && index < MAX_ELEMENTS) {
                    vector[index][pos] = '\0'; // Null-terminate the string
                    index++;
                }
            }
            else if (insideParentheses && this->vectorComanda[3][i] != ',' && this->vectorComanda[3][i] != ' ') {
                if (index < MAX_ELEMENTS && pos < MAX_COMPONENT_SIZE - 1) { // Ensure bounds
                    vector[index][pos++] = this->vectorComanda[3][i];
                }
            }
            else if (this->vectorComanda[3][i] == ',' && insideParentheses) {
                if (pos > 0 && index < MAX_ELEMENTS) {
                    vector[index][pos] = '\0'; // Null-terminate
                    index++;
                    pos = 0; // Reset position for next substring
                }
            }
        }

        // Print extracted components
        cout << "Extracted components:" << endl;
        for (int i = 0; i < index; i++) {
            cout << vector[i] << endl;
        }
        Column l((vector[0]), (vector[1]), (vector[2]), (vector[3]));
        l.printInfo();
        // Free allocated memory
        for (int j = 0; j < MAX_ELEMENTS; j++) {
            delete[] vector[j];
        }
        
        
    }

 
 
    
};