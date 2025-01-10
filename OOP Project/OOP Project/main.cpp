#include "header files/COMMAND_PARSER.h"
#include "header files/CREATE.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    char comandala[256];
    cout << "Enter a command: ";
    cin.getline(comandala, 256);

    Command_parser p(comandala);
    int commandValue = p.getComVal();

    // Ensure a valid command is provided
    while (commandValue < 0) {
        cout << "Enter a valid command: ";
        cin.getline(comandala, 256);
        p.setVector(comandala);
        commandValue = p.getComVal();
    }

    if (commandValue == 3) { // CREATE command
        CREATE createCommand(p);

        cout << "Testing verificaTABLE method:" << endl;
        createCommand.verificaTABLE();

        cout << "Testing verificaNume method:" << endl;
        createCommand.verificaNume();

        //cout << "Testing parseColumn method:" << endl;
        //createCommand.parseColumn();     

        cout << "Displaying parsed columns:" << endl;
        createCommand.displayColumns();
    }

    return 0;
}
