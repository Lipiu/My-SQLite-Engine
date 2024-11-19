#pragma once
#include <iostream>
#include <string>
#include "COLUMN.h"
using namespace std;

class Table{
private:
	string tableName = "";
	Column* columns = nullptr;
	int columnCount = 0;

public:
	//constructor with parameters
	Table(const string& name, Column* columns, int count) {
		this->setTableName(name);
		this->setColumns(columns, count);
	}

	//copy constructor
	Table(const Table& table) {
		this->setTableName(table.getTableName());
		this->setColumns(table.columns, table.columnCount);
	}

	//destructor
	~Table() {
		if (this->tableName.empty())
			cout << "Destructor called for: UNNAMED table";
		else
			cout << "Destructor called for: " << this->tableName;

		delete[] this->columns;
		this->columns = nullptr;
	}

	//getters
	string getTableName() const {
		return this->tableName;
	}

	Column& getColumns(int index) {
		if (index < 0 || index >= columnCount)
			throw "Index out of bounds!";
		return this->columns[index];
	}

	int getColumnCount() {
		return this->columnCount;
	}

	//setters
	string setTableName(const string& newTableName) {
		if (newTableName.empty() || newTableName.length() <= 0)
			throw "Invalid table name";
		this->tableName = newTableName;
	}

	void setColumns(Column* cols, int count) {
		if (cols == nullptr || count <= 0)
			throw "Invalid columns or count!";
		
		delete[] this->columns;
		this->columns = nullptr;

		this->columns = new Column[count];
		for (int i = 0; i < count; i++)
			this->columns[i] = cols[i];
		this->columnCount = count;
	}

	//print info
	void printTableInfo() const {
		std::cout << "\nTable: " << this->tableName;
		for (int i = 0; i < columnCount; i++) {
			std::cout << "\nColumn " << i + 1 << ":";
			this->columns[i].printInfo();
		}
	}
};