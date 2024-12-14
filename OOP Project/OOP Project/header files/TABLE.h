#pragma once
#include <iostream>
#include <string>
#include "header files/COLUMN.h"

class Table{
private:
	std::string tableName = "";
	Column* columns = nullptr;
	int columnCount = 0;

public:
	//constructor with parameters
	Table(const std::string& name, Column* columns, int count) {
		this->setTableName(name);
		this->setColumns(columns, count);
	}

	//copy constructor
	Table(const Table& table) {
	
		this->tableName = table.tableName;
		this->columnCount = table.columnCount;

		if (table.columns != nullptr && table.columnCount > 0) {
			this->columns = new Column[table.columnCount];
			for (int i = 0; i < table.columnCount; i++) {
				this->columns[i] = table.columns[i]; 
			}
		}
		else {
			this->columns = nullptr; 
		}
	}


	//destructor
	~Table() {
		delete[] this->columns;
		this->columns = nullptr;
	}

	//getters
	std::string getTableName() const {
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
	void setTableName(const std::string& newTableName) {
		if (newTableName.empty())
			throw "Table name cannot be empty!";
		this->tableName = newTableName;
	}

	void setColumns(Column* cols, int count) {
		if (cols == nullptr || count <= 0)
			throw "Invalid columns or count!";
		
		if (this->columns) {
			delete[] this->columns;
			this->columns = nullptr;
		}

		this->columns = new Column[count];
		for (int i = 0; i < count; i++)
			this->columns[i] = cols[i];
		this->columnCount = count;
	}

	//print info
	void printTableInfo() const {
		if(this->columns == nullptr){
			return;
		}
		else {
			std::cout << "\nTable: " << this->tableName;
			for (int i = 0; i < columnCount; i++) {
				std::cout << "\nColumn " << i + 1 << ":";
				this->columns[i].printInfo();
			}
		}
	}
};