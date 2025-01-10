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
	CREATE(Command_parser f) {
      //setVectorFromCommandParser(p);
        this->vector = f.getVector();
        this->nrCuv = f.getNrvector();
        
	}
    ~CREATE() { 
        for (int i = 0; i < nrCuv; i++)
        { delete[] vector[i]; }
        delete[] vector;
    }

   //methods
    void verifica() const{
        for (int i = 0; i < this->nrCuv; i++)
            cout << this->vector[i]<<" " << "asta e din create" << " ";
        if (strcmp(vector[1], "TABLE") == 0)
            cout << "evrica";
       
        
    }

   
};