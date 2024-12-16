#include"header files/COMMAND_PARSER.h"
#include <iostream>
#include <string>


using namespace std;


int main() {
    int a;
    char* c[20];
    char comandala[256];
    cout << "introduceti o comanda: ";
    cin.get(comandala, 256);
    cin.get(); //solved the exit code 3
    Command_parser p(comandala);
    a = p.getComVal();
    //p.coutVector();
    while (a < 0) {
        char comandala[256];
        cout << "introduceti o comanda: ";
        cin.get(comandala, 256);
        cin.get();
        Command_parser p(comandala);
        //p.coutVector();
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

}