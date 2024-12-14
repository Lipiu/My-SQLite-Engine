#pragma once
//primeste string si punem ce e in main
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>

using namespace std;



class Command_parser {
    char* vector[20];
    int nrvector = 0;
    const char* matrix[4][2] = {
        {"SELECT", "SELECT (cel_putin_o_coloana, ...) | ALL FROM nume_tabela [WHERE nume_coloan? = valoare]"},
        {"INSERT", "INSERT INTO nume_tabela VALUES(...); valorile sunt separate prin, ?i au num?rul ?i ordinea exacta ca defini?ia tabelului;"},
        {"UPDATE", "UPDATE nume_tabela SET nume_coloan? = valoare WHERE nume_coloan? = valoare"},
        {"CREATE", "CREATE TABLE table_name [IF NOT EXISTS] ((column_1_name,type,size, default_value), (column_2_name,type,size, default_value), …) - the command should receive at least 1 column;"}
    };




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
        char* tempV[20]; // vector temporar 
        if (input == nullptr)
            throw "Introduceti o comanda";
        //AM CREAT O COMANDA TEMPORARA
        char* tempCom = new char[strlen(input) + 1];
        strcpy(tempCom, input);
        int i = 0;
        char* p = strtok(tempCom, " "); //AM DESPARTIT COMANDA IN TERMINI INDIVIDUALI
        while (p != NULL) {
            tempV[i] = new char[strlen(p) + 1]; //aloc spatiu unui termen din vectorul temporar , si apoi il setez
            strcpy(tempV[i], p);
            p = strtok(NULL, " ");
            i++;
        }
        //tempV[i] = NULL;
        int nr = i; //AM TERMINAT DE SETAT VECTORUL TEMPORAR

        delete[] tempCom; //AM DAT DELETE LA COMANDA TEMPORARA

        //VALIDARE A COMENZII:
        for (int j = 0; j < 4; j++) {
            if (strcmp(tempV[0], this->matrix[j][0]) == 0) {
                cout << this->matrix[j][1] << endl;
                for (int i = 0; i < nr; i++) {
                    this->vector[i] = new char[strlen(tempV[i]) + 1];
                    strcpy(this->vector[i], tempV[i]);
                }
                this->vector[nr] = nullptr;
                this->nrvector = nr;
                break;
                //j = 5;
            }
            else {
                cout << "Intordu o comanda valida";
                j = 5;
            }
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