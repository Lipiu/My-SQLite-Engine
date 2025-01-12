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
    Column* columns;


    //constructor
public:
    CREATE(Command_parser& f) {
        
        this->nrCuv = f.getNrvector();
        char** sourceVector = f.getVector();
        this->vectorComanda = new char* [nrCuv + 1];
        for (int i = 0; i < nrCuv; i++) {
            this->vectorComanda[i] = new char[strlen(sourceVector[i]) + 1];
            strcpy(this->vectorComanda[i], sourceVector[i]);
        }
        this->vectorComanda[nrCuv] = nullptr;
     //verification methods 
        verificaTABLE();
        
    }

    ~CREATE() {
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

   //column parser - the program dosent verify if the column syntax is fully proper yet. 
    void parseColumnB() {

        const int MAX_ELEMENTS = 20; // Maximum number of components to extract
        const int MAX_COMPONENT_SIZE = 50; // Maximum size of each component


        char* vector[MAX_ELEMENTS];


        for (int j = 0; j < MAX_ELEMENTS; j++) {
            vector[j] = new char[MAX_COMPONENT_SIZE];
            vector[j][0] = '\0';
        }

        int index = 0; // Tracks components in `vector`
        int pos = 0;   // Tracks position within the current substring
        bool insideParentheses = false;
        if (this->vectorComanda[3] == nullptr) {
            cout << "no columns introduced";
        }
        else {
            for (int i = 0; i < strlen(this->vectorComanda[3]); i++) {
                if (this->vectorComanda[3][i] == '(') {
                    insideParentheses = true;
                    pos = 0;
                }
                else if (this->vectorComanda[3][i] == ')') {
                    insideParentheses = false;
                    if (pos > 0 && index < MAX_ELEMENTS) {
                        vector[index][pos] = '\0';
                        index++;
                    }
                }
                else if (insideParentheses && this->vectorComanda[3][i] != ',' && this->vectorComanda[3][i] != ' ') {
                    if (index < MAX_ELEMENTS && pos < MAX_COMPONENT_SIZE - 1) {
                        vector[index][pos++] = this->vectorComanda[3][i];
                    }
                }
                else if (this->vectorComanda[3][i] == ',' && insideParentheses) {
                    if (pos > 0 && index < MAX_ELEMENTS) {
                        vector[index][pos] = '\0';
                        index++;
                        pos = 0;
                    }
                }
            }

            
            this->columns = new Column[20];
            int colindex = 0;
            int a = 0;

            if ((index - 1) % 4 != 0)
                cout << "Not enough atributes in the columns";
            else {
                for (int k = 0; k < (index - 1) / 4; k++) {
                    this->columns[colindex] = Column((vector[a]), (vector[a + 1]), (vector[a + 2]), (vector[a + 3]));
                    this->columns[colindex].printInfo();
                    colindex++;
                    a = a + 4;
                }
            }
            for (int j = 0; j < MAX_ELEMENTS; j++) {
                delete[] vector[j];
            }
        }


    }
 
    //de facut variabila statica in loc de 4 LINIA 137
};