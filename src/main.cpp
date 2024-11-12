#include <iostream>
#include "headers/TABLE.h"

int main() {
    try {
        Table table(3, 4, "Test Table");

        table.setValue(0, 0, 1);
        table.setValue(0, 1, 2);
        table.setValue(0, 2, 3);
        table.setValue(0, 3, 4);
        table.setValue(1, 0, 5);
        table.setValue(1, 1, 6);
        table.setValue(1, 2, 7);
        table.setValue(1, 3, 8);
        table.setValue(2, 0, 9);
        table.setValue(2, 1, 10);
        table.setValue(2, 2, 11);
        table.setValue(2, 3, 12);
		
        table.printMatrix();

        // Attempting to set a value out of bounds will throw an exception
        try {
            table.setValue(3, 0, 999);
        } catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }

        // Test invalid table size (negative rows)
        try {
            Table invalidTable(-1, 4, "Invalid Table");  
        } catch (const std::invalid_argument& e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
