#pragma once
#include <iostream>
#include "COLUMN.h"
#include "CREATE_TABLE.h"

//have to implement: choose which table to delete

class DROP {
public:
	void dropTable(Table*& table) {
		if (table != nullptr) {
			cout << "Table to delete: " << table->getTableName() << endl;
			delete table;
			table = nullptr;
		}
		else
			cout << "Wrong command...";
	}
};