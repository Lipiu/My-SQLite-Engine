#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FileHandler {
private:
    string fileName;
    ofstream outputFile;

public:
    // Default constructor
    FileHandler() {}

    // Parameterized constructor
    FileHandler(const string& fileName) {
        outputFile.open(fileName, ios::app);
        if (!outputFile.is_open()) {
            cerr << "Error: failed to open file " << this->fileName << endl;
            throw runtime_error("Failed to open file: " + this->fileName);
        }
        this->setFileName(fileName);
    }

    //Getter for fileName (in case we need)
    string getFileName() const {
        return fileName;
    }

    // Setter for fileName (in case we need)
    void setFileName(const string& newFileName) {
        if (newFileName.empty()) {
            throw invalid_argument("File name cannot be empty");
        }
        fileName = newFileName;
    }

    // Method to write to file
    void writeToFile(const string& data) {
        if (!outputFile.is_open()) {
            throw runtime_error("File is not open");
        }
        outputFile << data << endl;
    }
};
