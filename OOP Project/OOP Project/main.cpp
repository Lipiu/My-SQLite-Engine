#include <iostream>
#include "TABLE.h"
#include "COLUMN.h"

int main() {
    try {
        // Create columns
        Column col1("id", "integer", 1000, "0");
        Column col2("nume", "text", 128, "");
        Column col3("grupa", "text", 50, "1000");

        // Display column info for testing
        std::cout << "Testing individual columns:" << std::endl;
        col1.printInfo();
        col2.printInfo();
        col3.printInfo();

        // Create array of columns
        Column columns[] = { col1, col2, col3 };

        // Create a table using columns
        std::cout << "\nCreating table:" << std::endl;
        Table table("students", columns, 3);

        // Print table info
        std::cout << "\nDisplaying table info:" << std::endl;
        table.printTableInfo();

    }
    catch (const char* ex) {
        std::cerr << "\nException: " << ex << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "\nException: " << ex.what() << std::endl;
    }

    return 0;
}
