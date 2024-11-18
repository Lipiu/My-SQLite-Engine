#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

/*TO DO : 
1. change "magic numbers" to static variables
	fix in setDefaultValues the variable maxDimension
2. set specific throw in setters
*/

class Column {
private:
	string name = "";
	string type = "";
	int size = 0;
	string defaultValue = "";

public:
	//default constructor
	Column() {
		cout << endl << "Default constructor";
	}

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
	~Column() {
		if (this->name != "")
			cout << "Destructor called for: " << this->name << endl;
		else
			cout << "Destructor called for: Unknown reason" << endl;
	}

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
		if (newName.empty() || newName.length() < 0)
			throw "Invalid name!";
		this->name = newName;
	}

	void setType(string newType) {
		if (newType != "integer" && newType != "text")
			throw "Invalid type. Please enter integer or text!";
		this->type = newType;
	}

	void setSize(int newSize){
		if (newSize <= 0)
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
			int maxDimension = 50; //have to fix this variable
			if (newDefaultValue.length() > maxDimension)
				throw "Default value exceeds the allowed dimension for text type!";
		}
		this->defaultValue = newDefaultValue;
	}

	//print function for testing
	void printInfo() {
		cout << "Column name: " << this->name << endl;
		cout << "Column type: " << this->type << endl;
		cout << "Column size: " << this->size << endl;
		cout << "Default value: " << this->defaultValue << endl;
	}
};