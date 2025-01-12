
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
    const char* matrix[5][2] = {
        {"SELECT", "SELECT (cel_putin_o_coloana, ...) | ALL FROM nume_tabela [WHERE nume_coloan? = valoare]"},
        {"INSERT", "INSERT INTO nume_tabela VALUES(...); valorile sunt separate prin, ?i au num?rul ?i ordinea exacta ca defini?ia tabelului;"},
        {"UPDATE", "UPDATE nume_tabela SET nume_coloan? = valoare WHERE nume_coloan? = valoare"},
        {"CREATE", "CREATE TABLE table_name [IF NOT EXISTS] ((column_1_name,type,size, default_value), etc"},
        {"DISPLAY", "DISPLAY TABLE table_name"}
    };

    //static variables to replace the "magic" numbers
    static int NUMBER_OF_COMMANDS;

public:
    //Default constructor
    Command_parser(){}

    //CONSTRUCTORS AND DESTRUCTORS
    Command_parser(const char* comanda) {
        this->modifyCommand(comanda);
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
        //VERIFICATIONS
        
    }

    void modifyCommand(const char* input) {
        char* copy = new char[strlen(input) + 1];
        int pozitie = -1;
        // Find the first '('
        for (int i = 0; i < strlen(input); i++) {
            if (input[i] == '(') {
                pozitie = i;
                break;
            }
        }
        // If '(' is not found, consider the entire input
        if (pozitie == -1) {
            pozitie = strlen(input);
        }
        // Copy characters up to '(', preserving spaces
        int j = 0;
        for (int i = 0; i < pozitie; i++) {
            copy[j++] = input[i];
        }
        // Copy characters from '(' onward, skipping spaces
        for (int i = pozitie; i < strlen(input); i++) {
            if (input[i] != ' ') {
                copy[j++] = input[i];
            }
        }
        copy[j] = '\0';
        // Free dynamically allocated memory
        this->setVector(copy);
        delete[] copy;
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
        if (strcmp(tempV[0], "0") != 0) {

            if (isValidCommand == false) {
                cout << "Enter a valid command" << endl << "Enter a command(0 to stop): ";
            }
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

    void distrugere() {
        //cout << "DISTRUGERE";
        for (int i = 0; i < this->nrvector; i++) {
            if (this->vector[i] != nullptr)
                delete[] this->vector[i];
            this->vector[i] = nullptr;
        }

        //vector deletion

        this->nrvector = 0;
        //VERIFICATIONS

    }
};

//initialized static int with 4 (number of total commands)
int Command_parser::NUMBER_OF_COMMANDS = 5;







