#include "header files/COMMAND_PARSER.h"
#include "header files/CREATE.h"
#include "header files/DISPLAY.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    char comandala[256];
    while (strcmp(comandala,"0")!=0) {
        
        cout << "Enter a command(0 to stop): ";
        cin.getline(comandala, 256); // Use getline to handle input better

        Command_parser p(comandala); // Create the initial object
        int commandType = p.getComVal();

        // Handle invalid command
        while (commandType < 0&& strcmp(comandala, "0") != 0) {
            
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
                c.parseColumn();

                p.distrugere();
                break;
            }
        case 4:
            if (strcmp(p.getVector()[0], "DISPLAY") == 0) {
                DISPLAY d(p);
                d.verifyDisplayCommand(); // Verify and process the DISPLAY command
            }
        default: break;
        }
        cout << endl; // Add spacing between iterations
        p.coutVector();
    }
   
    return 0;
}
