#pragma once
#include <iostream>
#include <string>
#include <string.h>


/*TO DO : 
1. set specific throw in setters
*/

class Column {
private:
	std::string name = "";
	std::string type = "";
	int size = 0;
	std::string defaultValue = "";

	//static variables for "magic values"
	static int NAME_MIN_SIZE;
	static int MIN_SIZE;
	static int MAX_DIMENSION;

public:
	//default constructor
	Column() {}

	//constructor with all parameters
	Column(const std::string& name, const std::string& type, int size, const std::string& defaultValue) {
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
	std::string getName() const {
		return this->name;
	}

	std::string getType() {
		return this->type;
	}

	int getSize() {
		return this->size;
	}

	std::string getDefaultValue() {
		return this->defaultValue;
	}

	//setters
	void setName(std::string newName){
		if (newName.empty() || newName.length() < NAME_MIN_SIZE)
			throw "Invalid name!";
		this->name = newName;
	}

	void setType(std::string newType) {
		if (newType != "integer" && newType != "text")
			throw "Invalid type. Please enter integer or text!";
		this->type = newType;
	}

	void setSize(int newSize){
		if (newSize <= MIN_SIZE)
			throw "Column size must be bigger than 0!";
		this->size = newSize;
	}

	void setDefaultValue(std::string newDefaultValue) {
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
		std::cout << std::endl;
		std::cout << "Column name: " << this->name << std::endl;
		std::cout << "Column type: " << this->type << std::endl;
		std::cout << "Column size: " << this->size << std::endl;
		std::cout << "Default value: " << this->defaultValue << std::endl;
		std::cout << std::endl;
	}
};

int Column::NAME_MIN_SIZE = 0;
int Column::MIN_SIZE = 0;
int Column::MAX_DIMENSION = 50;