#pragma once
#include <iostream>
#include <string>

class Table{
private:
    int rows = 0;
    int numberOfRows = 0;
    int columns = 0;
    int numberOfColumns = 0;
    int** dynamic_matrix = nullptr;
    std::string name = "";

public:
    //CONSTRUCTOR
    Table(int rows, int numberOfRows, int columns, int numberOfColumns, int** dynamic_matrix, std::string name){
        this->setRows(rows);
        this->setNumberOfRows(numberOfRows);
        this->setColumns(columns);
        this->setNumberOfColumns(numberOfColumns);
        this->setDynamicMatrix(rows, columns);
        this->setName(name);
    }

    //DESTRUCTOR
    ~Table(){
        for(int i = 0; i < rows; i++)
            delete[] this->rows;
        delete[] this->columns;
    }

    //SETTERS
    void setRows(int rows){
        if(rows < 0)
            throw "Index has to be positive";
        this->rows = rows;
    }

    void setNumberOfRows(int numberOfRows){
        if(numberOfRows < 0)
            throw "Index has to be positive";
    }

    void setColumns(int columns){
        if(columns < 0)
            throw "Index has to be positive";
        this->columns = columns;
    }

    void setNumberOfColumns(int numberOfColumns){
        if(numberOfColumns < 0)
            throw "Index has to be positive";
    }

    void setDynamicMatrix(int row, int col){
        if (row > 0 && row < rows && col > 0 && col < rows) 
            dynamic_matrix[row][col];
        throw "Index out of bounds";
    }

    void setName(std::string name){
        if(name.empty())
            throw "Invalid name";
        this->name = name;
    }

    

    //GETTERS
    int getRows(){
        return this->rows;
    }

    int getNumberOfRows(){
        return this->numberOfRows;
    }

    int getColumns(){
        return this->columns;
    }

    int getNumberOfColumns(){
        return this->numberOfColumns;
    }

    int getDynamicMatrix(){
        //dynamic allocation of the matrix
        int** dynamic_matrix = new int*[rows];
        for(int i = 0; i < rows; i++)
            dynamic_matrix[i] = new int[columns];
    }

    std::string getName(){
        return this->name;
    }
    
};