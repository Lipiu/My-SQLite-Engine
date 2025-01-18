#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include "Command_parser.h" 
#include "Column.h"
#include "TABLE.h"
using namespace std;


class DELETE {
private:
    static int commandNumber;
    Command_parser p;
    char* tableName = nullptr;
    int columnCount = 0;
    char** vectorComanda = nullptr;
    int nrCuv = 0;


public:
    //constructor
    DELETE(Command_parser& f) {

        this->nrCuv = f.getNrvector();
        char** sourceVector = f.getVector();
        this->vectorComanda = new char* [nrCuv + 1];
        for (int i = 0; i < nrCuv; i++) {
            this->vectorComanda[i] = new char[strlen(sourceVector[i]) + 1];
            strcpy(this->vectorComanda[i], sourceVector[i]);
        }
        this->vectorComanda[nrCuv] = nullptr;
        verificaFrom();
    }
    //methods

    void verificaFrom() {
        if (this->nrCuv>1&&strcmp(this->vectorComanda[1], "FROM") != 0) {
            cout << "wrong keyword:missing or incorect syntax"<<endl;
            return;
        }
        else
            if(this->nrCuv>1)
        verificaNume();
    }
    void verificaNume() {
        if (this->vectorComanda[2] == nullptr || strcmp(this->vectorComanda[2], "WHERE") == 0) {
            cout << "missing table name" << endl;
            return;
        }
        else
            verificaWhere();
    }
    void verificaWhere() {
        if (this->vectorComanda[3] == nullptr) {
            cout << "missing WHERE"<<endl;
            return;
        }
        if ((strcmp(this->vectorComanda[3], "WHERE") != 0)) {
            cout << "wrong table name" << endl;
            return;
        }

    }
};