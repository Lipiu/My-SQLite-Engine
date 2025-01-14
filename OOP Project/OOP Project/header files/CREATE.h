#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include "Command_parser.h" 
#include "Column.h"
#include "TABLE.h"
using namespace std;

/*
* VALID COMMANDS EXAMPLES:
CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))
CREATE TABLE students IF NOT EXISTS ((id, integer, 1000, 0), (nume, text, 128, ''), (grupa, text,50,'1000'))
*/

class CREATE {
private:
    static int commandNumber;
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
        verificaTABLE();
        //verification methods 

    }
public:


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

            verificaNume();
        }
        else
            if (this->vectorComanda[1] != nullptr)
                cout << "wrong command name (missing keywords)" << endl;



    }

    void verificaNume() {
        if (this->vectorComanda[2] != nullptr) {
            if (this->vectorComanda[2][0] == '(') {
                cout << "wrong command (missing table name)" << endl;
                return;
            }
            if (this->vectorComanda[2][0] >= '0' && this->vectorComanda[2][0] <= '9') {
                cout << "Table name cannot start with digits." << endl;
                return;
            }
            else {
                this->tableName = vectorComanda[2];
                if (nrCuv == 7)
                    verificaIFNOT();
                if (nrCuv == 7 || nrCuv == 4)
                    verificaParanteze();
                else
                    cout << "wrong command: wrong table name (has space)" << endl;
            }
        }
        else {
            cout << "wrong command (missing table name)" << endl;
        }
    }

    void verificaIFNOT() {
        std::string verificare = this->vectorComanda[3] + std::string(this->vectorComanda[4]) + this->vectorComanda[5];

        if (verificare == "IFNOTEXISTS") {
            verificaParanteze();
        }
        else {
            cout << this->vectorComanda[3] << this->vectorComanda[4] << this->vectorComanda[5]
                << " WRONG SPELLING " << endl
                << verificare;
        }
    }

    void verificaParanteze() {
        if (this->vectorComanda[this->nrCuv - 1] != nullptr) {
            if ((this->vectorComanda[this->nrCuv - 1][0] == '(' && this->vectorComanda[this->nrCuv - 1][1] != '(') || (this->vectorComanda[this->nrCuv - 1][strlen(vectorComanda[this->nrCuv - 1]) - 2] != ')' && this->vectorComanda[this->nrCuv - 1][strlen(vectorComanda[this->nrCuv - 1]) - 1] == ')')) {
                cout << "wrong command (missing ())" << endl;
                return;
            }
            else
                parseColumnB();
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
        if (this->vectorComanda[this->nrCuv - 1] == nullptr) {
            cout << "no columns introduced" << endl;
        }
        else {
            for (int i = 0; i < strlen(this->vectorComanda[this->nrCuv - 1]); i++) {
                if (this->vectorComanda[this->nrCuv - 1][i] == '(') {
                    insideParentheses = true;
                    pos = 0;
                }
                else if (this->vectorComanda[this->nrCuv - 1][i] == ')') {
                    insideParentheses = false;
                    if (pos > 0 && index < MAX_ELEMENTS) {
                        vector[index][pos] = '\0';
                        index++;
                    }
                }
                else if (insideParentheses && this->vectorComanda[this->nrCuv - 1][i] != ',' && this->vectorComanda[this->nrCuv - 1][i] != ' ') {
                    if (index < MAX_ELEMENTS && pos < MAX_COMPONENT_SIZE - 1) {
                        vector[index][pos++] = this->vectorComanda[this->nrCuv - 1][i];
                    }
                }
                else if (this->vectorComanda[this->nrCuv - 1][i] == ',' && insideParentheses) {
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

            if ((index - 1) % commandNumber != 0)
                cout << "wrong command (incomplete columns description)" << endl;
            else {
                for (int k = 0; k < (index - 1) / 4; k++) {
                    this->columns[colindex] = Column((vector[a]), (vector[a + 1]), (vector[a + 2]), (vector[a + 3]));

                    if (columns[colindex].getValid() == 1) {
                        colindex++;
                        a = a + 4;

                    }
                    else
                        return;
                }
                this->columnCount = colindex;
            }
            for (int j = 0; j < MAX_ELEMENTS; j++) {
                delete[] vector[j];
            }
        }
        int ok = 1;


        if (this->columnCount != 0 && ok == 1) {
            Table t(this->tableName, this->columns, this->columnCount);
            t.printTableInfo();
        }
    }

};
int CREATE::commandNumber = 4;