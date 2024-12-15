
#include"header files/COMMAND_PARSER.h"
#include <iostream>
#include <string>



using namespace std;

void comanda() {
    char* c[20];
    char comandala[256];
    cout << "introduceti o comanda: " << endl;
    cin.get(comandala, 256);
    cin.get(); //solved the exit code 3
    Command_parser p(comandala);
    //p.coutVector();
    //p.validation();
}


int main() {
    /*while(true){
    comanda();
    }*/
    while (true) {
        char* c[20];
        char comandala[256];
        cout << "introduceti o comanda: ";
        cin.get(comandala, 256);
        cin.get(); //solved the exit code 3
        Command_parser p(comandala);
        p.coutVector();
        //p.validation();
    }
}




