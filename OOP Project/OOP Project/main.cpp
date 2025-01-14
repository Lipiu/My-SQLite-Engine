﻿#include "header files/COMMAND_PARSER.h"
#include "header files/CREATE.h"
#include "header files/DISPLAY.h"
#include "header files/DROP_TABLE.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    char comandala[256] = "";

    // Opening the output.txt file
    ofstream file("output.txt");
    if (!file.is_open()) {
        cerr << "Unable to open the file...";
        exit(1);
    }

    while (strcmp(comandala, "0") != 0) {
        cout << "Enter a command (0 to stop): ";
        cin.getline(comandala, 256);

        Command_parser p(comandala); // Create the initial object
        int commandType = p.getComVal();

        // Handle invalid command
        while (commandType < 0 && strcmp(comandala, "0") != 0) {
            cin.getline(comandala, 256);
            p.setVector(comandala);
            commandType = p.getComVal();
        }

        switch (commandType) {
        case 0:
            cout << "Select command not implemented yet." << endl;
            break;
        case 1:
            cout << "Insert command not implemented yet." << endl;
            break;
        case 2:
            cout << "Update command not implemented yet." << endl;
            break;
        case 3:
            if (strcmp(p.getVector()[0], "CREATE") == 0) {
                CREATE c(p);
                break;
            }
        case 4:
            if (strcmp(p.getVector()[0], "DISPLAY") == 0) {
                DISPLAY d(p);
                d.verifyDisplayCommand(); // Verify and process the DISPLAY command
                break;
            }
        case 5:
            if (strcmp(p.getVector()[0], "DROP") == 0) {
                int nrWords = p.getNrvector();
                string* words = new string[nrWords];
                for (int i = 0; i < nrWords; i++) {
                    words[i] = p.getVector()[i];
                }

                
                DROP drop(words, nrWords);
                drop.verifyDropCommand();

                delete[] words; // Clean up the dynamically allocated memory
                break;
            }
        default:
            cout << "Unrecognized command type." << endl;
            break;
        }
    }

    return 0;
}
