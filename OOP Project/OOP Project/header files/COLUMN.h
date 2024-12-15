#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

/*TO DO : 
1. set specific throw in setters
*/

class Column {
private:
	string name = "";
	string type = "";
	int size = 0;
	string defaultValue = "";

	//static variables for "magic values"
	static int NAME_MIN_SIZE;
	static int MIN_SIZE;
	static int MAX_DIMENSION;

public:
	//default constructor
	Column() {}

	//constructor with all parameters
	Column(const string& name, const string& type, int size, const string& defaultValue) {
		this->setName(name);
		this->setType(type);
		this->setSize(size);
		this->setDefaultValue(defaultValue);
	}

	//copy constructor
	Column(const Column& column) {
		this->name = column.name;
		this->type = column.type;
		this->size = column.size;
		this->defaultValue = column.defaultValue;
	}


	//destructor (not needed bc we use string not char*)
	

	//getters
	string getName() const {
		return this->name;
	}

	string getType() {
		return this->type;
	}

	int getSize() {
		return this->size;
	}

	string getDefaultValue() {
		return this->defaultValue;
	}

	//setters
	void setName(string newName){
		if (newName.empty() || newName.length() < NAME_MIN_SIZE)
			throw "Invalid name!";
		this->name = newName;
	}

	void setType(string newType) {
		if (newType != "integer" && newType != "text")
			throw "Invalid type. Please enter integer or text!";
		this->type = newType;
	}

	void setSize(int newSize){
		if (newSize <= MIN_SIZE)
			throw "Column size must be bigger than 0!";
		this->size = newSize;
	}

	void setDefaultValue(string newDefaultValue) {
		if (this->type == "integer") {
			for (int i = 0; i < newDefaultValue.length(); i++) {
				char c = newDefaultValue[i];
				if (c < '0' || c > '9') //compare to ASCII values
					throw "Invalid default value for integer type!";
			}
		}
		else if(this->type == "text"){
			if (newDefaultValue.length() > MAX_DIMENSION)
				throw "Default value exceeds the allowed dimension for text type (50).";
		}
		this->defaultValue = newDefaultValue;
	}

	//print function for testing
	void printInfo() {
		cout << endl;
		cout << "Column name: " << this->name << endl;
		cout << "Column type: " << this->type << endl;
		cout << "Column size: " << this->size << endl;
		cout << "Default value: " << this->defaultValue << endl;
		cout << endl;
	}
};

//initialized static int variables
int Column::NAME_MIN_SIZE = 0;
int Column::MIN_SIZE = 0;
int Column::MAX_DIMENSION = 50;