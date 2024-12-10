#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "CREATE_TABLE.h" 

using namespace std;

//Example of insert command : INSERT INTO studenti VALUES (1,”John”,”1001”)


void InsertCommand(char* command, Table& table) {
    const char* keyword = "INSERT INTO ";

    
    //We check if the command is written properly   


    if (strncmp(command, keyword, strlen(keyword)) != 0) {
        throw "Invalid command. INSERT INTO expected.";
    }
    

    
    char* valuesStart = strstr(command, "VALUES(");
    if (!valuesStart) {
        throw "Missing VALUES keyword or syntax error.";
    }

    valuesStart += 7; // Move past "VALUES("
    char* valuesEnd = strchr(valuesStart, ')');
    if (!valuesEnd) {
        throw "Missing closing parenthesis for VALUES.";
    }

    *valuesEnd = '\0'; // Null-terminate the values substring

    // Parse the values
    char* token = strtok(valuesStart, ",");
    string* parsedValues = new string[table.getColumnCount()];
    int count = 0;

    while (token && count < table.getColumnCount()) {
        parsedValues[count++] = token;
        token = strtok(nullptr, ",");
    }

    // Check if the number of values matches the no of columns from the table
    if (count != table.getColumnCount()) {
        delete[] parsedValues;
        throw "Error: No. of values does not match the table no. of colums.";
    }


    cout << "Insert command processed successfully with values: ";
    for (int i = 0; i < table.getColumnCount(); ++i) {
        cout << parsedValues[i] << (i == table.getColumnCount() - 1 ? "\n" : ", ");
    }

    
    delete[] parsedValues;
}
