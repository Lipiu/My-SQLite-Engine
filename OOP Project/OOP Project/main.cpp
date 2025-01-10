#include "header files/COMMAND_PARSER.h"
#include "header files/CREATE.h"
#include "header files/DISPLAY.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    while (true) {
        char comandala[256];
        cout << "Enter a command: ";
        cin.getline(comandala, 256); // Use getline to handle input better

        Command_parser p(comandala); // Create the initial object
        int commandType = p.getComVal();

        // Handle invalid command
        while (commandType < 0) {
            cout << "Invalid command, please try again: ";
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
        case 4:
            if (strcmp(p.getVector()[0], "CREATE") == 0) {
                CREATE c(p);
                cout << "CREATE command executed." << endl;
            }
            else if (strcmp(p.getVector()[0], "DISPLAY") == 0) {
                DISPLAY d(p);
                d.verifyDisplayCommand(); // Verify and process the DISPLAY command
            }
            break;
        default:
            cout << "Unknown command type!" << endl;
            break;
        }
        cout << endl; // Add spacing between iterations
    }
    return 0;
}
