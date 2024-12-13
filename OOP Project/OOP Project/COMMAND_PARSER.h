#pragma once
//primeste string si punem ce e in main
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void free_vector(char* vector[20])
//Frees the command vector 
{
    for (int i = 0; vector[i] != NULL; ++i) {
        delete[] vector[i];
    }
}

void vectorizare(char m[256], char* vector[20])
//takes the command input and creates a vector with each individual term 
{
    int i = 0;
    char* p = strtok(m, " ");
    while (p != NULL) {
        vector[i] = new char[strlen(p) + 1];
        strcpy(vector[i], p);
        p = strtok(NULL, " ");
        i++;
    }
    vector[i] = NULL;
}

void comanda(char m[256]) {
    const char* matrix[4][2] = {
        {"SELECT", "SELECT (cel_putin_o_coloana, ...) | ALL FROM nume_tabela [WHERE nume_coloan? = valoare]"},
        {"INSERT", "INSERT INTO nume_tabela VALUES(...); valorile sunt separate prin, ?i au num?rul ?i ordinea exacta ca defini?ia tabelului;"},
        {"UPDATE", "UPDATE nume_tabela SET nume_coloan? = valoare WHERE nume_coloan? = valoare"},
        {"CREATE", "CREATE TABLE table_name [IF NOT EXISTS] ((column_1_name,type,size, default_value), (column_2_name,type,size, default_value), …) - the command should receive at least 1 column;"}
    };

    for (int j = 0; j < 4; j++) {
        if (strcmp(m, matrix[j][0]) == 0) {
            cout << matrix[j][1] << endl;
            return;
        }
    }
    cout << "Introduceti o comanda valida" << endl;
}

int main() {
    char input[256];
    char* vectorulMeu[20];

    while (true) {
        cout << "ENTER A COMMAND (0 to stop): ";
        cin.get(input, 256);
        cin.get(); // Clear the newline from the input buffer

        if (strcmp(input, "0") == 0) {
            break;
        }

        vectorizare(input, vectorulMeu);//SEPARATES THE COMMANDS INTO INDIVIDUAL TERMS CORRESPONDING TO VECTOR INDEXES FOR EASIER ACCES

        for (int i = 0; vectorulMeu[i] != NULL; i++) {
            cout << vectorulMeu[i] << endl; // Print each term of the whole command - is temporary just for testing purposes
        }

        comanda(vectorulMeu[0]);

        free_vector(vectorulMeu);
    }

    return 0;
}
//TO DO:
//BETTER MEMORY ALLOCATION
//IMPLEMENT EVERY COMMAND 
//CREATE A SWITCH CASE TO HANDLE THE ERRORS IN THE COMMAND'S CLASS