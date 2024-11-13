#include<iostream>
#include<string>


using namespace std;


void comanda(char m[256]) {
	const char* matrix[15][30] = {
	{"SELECT","SELECT (cel_putin_o_coloana, ...) | ALL FROM nume_tabela [WHERE nume_coloană = valoare]"},

	{"INSERT","INSERT INTO nume_tabela VALUES(...); valorile sunt separate prin, și au numărul și ordinea exacta ca definiția tabelului;"},

	{"UPDATE","UPDATE nume_tabela SET nume_coloană = valoare WHERE nume_coloană = valoare"},
	{"CREATE","CREATE TABLE table_name [IF NOT EXISTS] ((column_1_name,type,size, default_value), (column_2_name,type,size, default_value), …) - the command should receive at least 1 column;"}
	};

	for (int j = 0; j < 3; j++) {
		if (strcmp(m, matrix[j][0]) == 0) {
			cout << matrix[j][1] << endl;
			return;
		}
	}
	cout << "Introduceti o comanda valida" << endl;;


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