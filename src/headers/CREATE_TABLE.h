#pragma once
#include <iostream>
#include <string>

class Table{
private:
    int rows = 0;
    int columns = 0;
    int** dynamic_matrix = nullptr;
    std::string name = "";

    //function to dynamically allocate the matrix
    void allocateDynamicMatrix(){
        dynamic_matrix = new int*[rows];
        for(int i = 0; i < rows; i++){
            dynamic_matrix[i] = new int[columns];
            for(int j = 0; j < columns; j++)
                dynamic_matrix[i][j] = 0;
        }
    }

public:
    //CONSTRUCTOR
    Table(int rows, int columns, const std::string& name){
        this->setRows(rows);
        this->setColumns(columns);
        this->setName(name);
        //name has & to avoid creating a copy of it
        this->allocateDynamicMatrix();
    }

    //COPY CONSTRUCTOR
    Table(const Table& table){
        this->rows = table.rows;
        this->columns = table.columns;
        this->name = table.name;

        //Allocate memory for the new matrix
        this->allocateDynamicMatrix();

        //Copy each element from the source matrix
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->columns; j++){
                this->dynamic_matrix[i][j] = table.dynamic_matrix[i][j];
            }
        }
    }

    //DESTRUCTOR
    ~Table(){
        if(this->dynamic_matrix){
            for(int i = 0; i < this->rows; i++)
                delete[] this->dynamic_matrix[i];
            delete[] this->dynamic_matrix;
        }
        dynamic_matrix = nullptr;
        
    }

    //SETTERS
    void setRows(int rows){
        if(rows < 0)
            throw std::invalid_argument("Index has to be positive!");
        this->rows = rows;
    }

    void setColumns(int columns){
        if(columns < 0)
            throw std::invalid_argument("Index has to be positive!");
        this->columns = columns;
    }

    void setName(const std::string& name){
        if(name.empty())
            throw std::invalid_argument("Name cannot be empty!");
        this->name = name;
    }

    void setValue(int row, int col, int value) {
        if (row < 0 || row >= this->rows || col < 0 || col >= this->columns) {
            throw std::out_of_range("Index out of bounds.");
        }
        this->dynamic_matrix[row][col] = value;
    }

    //GETTERS
    int getRows(){
        return this->rows;
    }

    int getColumns(){
        return this->columns;
    }

    std::string getName(){
        return this->name;
    }

    int getValue(int row, int col) const {
        if (row < 0 || row >= this->rows || col < 0 || col >= this->columns) {
            throw std::out_of_range("Index out of bounds.");
        }
        return this->dynamic_matrix[row][col];
    }

    //test printing
    void printMatrix() const {
        std::cout << "Table: " << this->name << "\n";
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                std::cout << this->dynamic_matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    
};