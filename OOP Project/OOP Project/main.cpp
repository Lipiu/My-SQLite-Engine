#include<iostream>
#include<string>

int main() {
    try {
        // Create columns
        Column col1("id", "integer", 1000, "0");
        Column col2("nume", "text", 128, "");
        Column col3("grupa", "text", 50, "1000");

using namespace std;


void comanda(char m[256]) {
	const char* matrix[15][30] = {
	{"SELECT","SELECT (cel_putin_o_coloana, ...) | ALL FROM nume_tabela [WHERE nume_coloană = valoare]"},

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

int main() {
	char input[256];
	const char valid[5] = "0";
	cout << "ENTER A COMMAND (0 to stop) : ";
	cin >> input;


	while (strcmp(input, valid) != 0) {
		if (strcmp(input, valid) != 0)
			comanda(input);
		cout << "ENTER A COMMAND (0 to stop) : ";
		cin >> input;

	}



}