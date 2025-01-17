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
    FileHandler() : fileName("output.txt") {}

    // Parameterized constructor
    FileHandler(const string& fileName) {
        this->setFileName(fileName);
        openFile();
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

    // Method for opening the file
    void openFile() {
        outputFile.open(fileName, ios::app); // Open in append mode
        if (!outputFile) {
            throw runtime_error("Could not open the file");
        }
    }

    // Method to write to file
    void writeToFile(const string& data) {
        if (!outputFile.is_open()) {
            throw runtime_error("File is not open");
        }
        outputFile << data << endl;
    }

    // Check if file is open
    bool isFileOpen() const {
        return outputFile.is_open();
    }
};
