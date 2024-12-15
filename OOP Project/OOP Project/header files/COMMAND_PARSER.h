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
    const char* matrix[4][2] = {
        {"INSERT", "SELECT (cel_putin_o_coloana, ...) | ALL FROM nume_tabela [WHERE nume_coloan? = valoare]"},
        {"INSERT", "INSERT INTO nume_tabela VALUES(...); valorile sunt separate prin, ?i au num?rul ?i ordinea exacta ca defini?ia tabelului;"},
        {"UPDATE", "UPDATE nume_tabela SET nume_coloan? = valoare WHERE nume_coloan? = valoare"},
        {"CREATE", "CREATE TABLE table_name [IF NOT EXISTS] ((column_1_name,type,size, default_value), (column_2_name,type,size, default_value), …) - the command should receive at least 1 column;"}
    };

    //static variables to replace the "magic" numbers
    static int NUMBER_OF_COMMANDS;

public:
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
    char** getVector() {
        return this->vector;
    }

    void coutVector() {
        for (int i = 0; i < this->nrvector; i++)
            cout << this->vector[i] << "--";
        cout << endl;
    }

    void validation() {





    }

};

//initialized static int with 4 (number of total commands)
int Command_parser::NUMBER_OF_COMMANDS = 4;