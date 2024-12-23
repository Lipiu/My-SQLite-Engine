
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
using namespace std;


class Command_parser {
private:
    char* vector[20];
    int nrvector = 0;
    int comVal = -1;
    const char* matrix[4][2] = {
        {"SELECT", "SELECT (cel_putin_o_coloana, ...) | ALL FROM nume_tabela [WHERE nume_coloan? = valoare]"},
        {"INSERT", "INSERT INTO nume_tabela VALUES(...); valorile sunt separate prin, ?i au num?rul ?i ordinea exacta ca defini?ia tabelului;"},
        {"UPDATE", "UPDATE nume_tabela SET nume_coloan? = valoare WHERE nume_coloan? = valoare"},
        {"CREATE", "CREATE TABLE table_name [IF NOT EXISTS] ((column_1_name,type,size, default_value), (column_2_name,type,size, default_value), �) - the command should receive at least 1 column;"}
    };

    //static variables to replace the "magic" numbers
    static int NUMBER_OF_COMMANDS;

public:
    //CONSTRUCTORS AND DESTRUCTORS
    Command_parser(const char* comanda) {
        this->setVector(comanda);
    }
    ~Command_parser() {
        //cout << "DISTRUGERE";
        for (int i = 0; i < this->nrvector; i++) {
            if (this->vector[i] != nullptr)
                delete[] this->vector[i];
            this->vector[i] = nullptr;
        }

        //vector deletion

        this->nrvector = 0;

    }
    //SETTER

    void setVector(const char* input) {
        char* tempV[20]; // temporary vector
        if (input == nullptr)
            throw "Introduceti o comanda";
        //CREATED A TEMPORARY COMMAND
        char* tempCom = new char[strlen(input) + 1];
        strcpy(tempCom, input);
        int i = 0;
        char* p = strtok(tempCom, " "); //SPLIT THE COMMAND IN INDIVIDUAL WORDS
        while (p != NULL) {
            tempV[i] = new char[strlen(p) + 1]; //ALLOCATED SPACE FOR ONE WORD IN TEMPORARY VECTOR
            strcpy(tempV[i], p);
            p = strtok(NULL, " ");
            i++;
        }
        //tempV[i] = NULL;
        int nr = i; //FINISHED SETTING UP THE TEMPORARY VECTOR

        delete[] tempCom; //DELETED THE TEMPORARY COMMAND

        //COMMAND VALIDATION:
        bool isValidCommand = false;
        for (int j = 0; j < NUMBER_OF_COMMANDS; j++) {
            if (strcmp(tempV[0], this->matrix[j][0]) == 0) {
                cout << this->matrix[j][1] << endl;
                for (int i = 0; i < nr; i++) {
                    this->vector[i] = new char[strlen(tempV[i]) + 1];
                    strcpy(this->vector[i], tempV[i]);
                }
                this->vector[nr] = nullptr;
                this->nrvector = nr;
                isValidCommand = true;
                this->comVal = j;
                //j = 5;
                break;
            }
        }
        if (!isValidCommand) {
            cout << "Introduceti o comanda valida!" << endl;
        }
        for (int i = 0; i < nr; i++)
            if (tempV[i] != nullptr)
                delete tempV[i];
    }
    //GETTER
    int getNrvector() {
        int nr = this->nrvector;
        return nr;
    }

    char** getVector() {
        char** copie = new char* [this->nrvector];  // Allocate memory for the array of char* pointers
        for (int i = 0; i < this->nrvector; i++) {
            copie[i] = new char[strlen(this->vector[i]) + 1];  // Allocate memory for each string
            strcpy(copie[i], this->vector[i]);  // Copy the string from vector to copie
        }
        return copie;  // Return the array of char* pointers
    }
    int getComVal() {
        return this->comVal;
    }
    //METHODS
    void coutVector() {
        for (int i = 0; i < this->nrvector; i++)
            cout << this->vector[i] << "--";
        cout << endl;
        if (this->comVal == 1)
            cout << "COMANDA ESTE VALIDA" << endl;
    }

    void validation() {





    }

};

//initialized static int with 4 (number of total commands)
int Command_parser::NUMBER_OF_COMMANDS = 4;







