#include "header files/COMMAND_PARSER.h"
#include "header files/CREATE.h"
#include "header files/DISPLAY.h"
#include "header files/DROP_TABLE.h"
#include "header files/FILE.h"
#include "header files/INSERT.h"
#include "header files/DELETE.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    char comandala[256] = "";
    FileHandler fileHandler("output.txt");

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
            // Log the message to file
            fileHandler.writeToFile("Select command not implemented yet.");
            break;
        case 1:
            if (strcmp(p.getVector()[0], "INSERT") == 0) {
                INSERT insertCommand(p);
                // Log the INSERT command to file
                fileHandler.writeToFile("INSERT command executed.");
                break;
            }
        case 2:
            cout << "Update command not implemented yet." << endl;
            fileHandler.writeToFile("Update command not implemented yet.");
            break;
        case 3:
            if (strcmp(p.getVector()[0], "CREATE") == 0) {
                CREATE c(p);
                // Log successful CREATE command to file
                fileHandler.writeToFile("CREATE command executed.");
                break;
            }
        case 4:
            if (strcmp(p.getVector()[0], "DISPLAY") == 0) {
                DISPLAY d(p);
                d.verifyDisplayCommand(); // Verify and process the DISPLAY command
                // Log the DISPLAY command to file
                fileHandler.writeToFile("DISPLAY command executed.");
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
                // Log the DROP command to file
                fileHandler.writeToFile("DROP command executed.");

                delete[] words; // Clean up the dynamically allocated memory
                break;
            }
        case 6:
            if (strcmp(p.getVector()[0], "DELETE") == 0) {
                DELETE d(p);
                // Log successful DELETE command to file
                fileHandler.writeToFile("DELETE command executed.");
                break;
            }
        case 7:
        default:

            break;
        }
    }

    return 0;
}
