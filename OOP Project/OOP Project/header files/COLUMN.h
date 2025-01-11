#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;


//static variables for "magic values"
static int NAME_MIN_SIZE = 0;
static int MIN_SIZE = 0;
static int MAX_DIMENSION = 50;

class Column {
private:
	string name = "";
	string type = "";
	int size = 0;
	string defaultValue = "";

public:
	//default constructor
	Column() {}

	//constructor with all parameters
	Column(const string& name, const string& type, const string& size, const string& defaultValue) {
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
			cout << "Invalid name!";
		this->name = newName;
	}

	void setType(string newType) {
		if (newType != "integer" && newType != "text" && newType!="float")
			cout << "Invalid type. Please enter integer or text!";
		this->type = newType;
	}

	void setSize(string newSize){
		int newIntSize = stoi(newSize);
		if (newIntSize <= MIN_SIZE)
			cout << "Column size must be bigger than 0!";
		this->size = newIntSize;
	}

	void setDefaultValue(string newDefaultValue) {
		cout << "Setting default value: " << newDefaultValue << " for type: " << this->type << endl;

		if (this->type == "integer") {
			if (newDefaultValue.empty()) {
				cout << "Default value for integer type cannot be empty!";
			}

			// Ensure all characters in newDefaultValue are numeric
			for (size_t i = 0; i < newDefaultValue.length(); i++) {
				char c = newDefaultValue[i];
				if (c < '0' || c > '9') { // Compare to ASCII values
					cout<< "Invalid default value for integer type!";
				}
			}
		}
		else if (this->type == "text") {
			if (newDefaultValue.length() > MAX_DIMENSION) {
				cout << "Default value exceeds the allowed dimension for text!";
			}
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
