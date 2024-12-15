#include"header files/COMMAND_PARSER.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    char comandala[256];
    cout << "introduceti o comanda: ";
    cin.get(comandala, 256);
    cin.get(); //solved the exit code 3

    Command_parser p(comandala); // Create the initial object
    int a = p.getComVal();

    while (a < 0) {
        cout << "introduceti o comanda: ";
        cin.get(comandala, 256);
        cin.get();

        // Reuse the existing object and set a new vector
        p.setVector(comandala);
        a = p.getComVal();
    }

    cout << p.getComVal() << endl;

    switch (p.getComVal()) {
    case 0:
        cout << "select command";
        break;
    case 1:
        cout << "insert command";
        break;
    case 2:
        cout << "update command";
        break;
    case 3:
        cout << "create command";
        break;
    }

    return 0;
}
