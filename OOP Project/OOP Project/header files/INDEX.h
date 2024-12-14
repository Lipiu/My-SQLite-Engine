#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "TABLE.h"

class Index {
private:
    std::string indexName;
    std::string columnName;
    Table* table;

public:
    // ctor
    Index(const std::string& indexName, const std::string& columnName, Table* table) {
        this->setIndexName(indexName);
        this->setColumnName(columnName);
        this->setTable(table);
    }

    // setters
    std::string getIndexName() const {
        return this->indexName;
    }

    std::string getColumnName() const {
        return this->columnName;
    }

    Table* getTable() const {
        return this->table;
    }

    // setters
    void setIndexName(const std::string& newIndexName) {
        if (newIndexName.empty()) {
            throw "Index name cannot be empty!";
        }
        this->indexName = newIndexName;
    }

    void setColumnName(const std::string& newColumnName) {
        if (newColumnName.empty()) {
            throw "Column name cannot be empty!";
        }
        this->columnName = newColumnName;
    }

    void setTable(Table* newTable) {
        if (newTable == nullptr) {
            throw "Table cannot be null!";
        }
        this->table = newTable;
    }

    // print  the index information
    void printIndexInfo() const {
        std::cout << "Index Name: " << this->indexName << std::endl;
        std::cout << "Column Name: " << this->columnName << std::endl;
        std::cout << "Table Name: " << this->table->getTableName() << std::endl;
    }
};

void CreateIndexCommand(char* command, Table* table) {
    const char* keyword = "CREATE INDEX ";

    // xheck if the command starts with the correct keyword
    if (strncmp(command, keyword, strlen(keyword)) != 0) {
        throw "Invalid command. CREATE INDEX expected.";
    }

    char* indexNameStart = command + strlen(keyword);
    char* onKeyword = strstr(indexNameStart, " ON ");
    if (!onKeyword) {
        throw "Missing ON keyword or syntax error.";
    }

    *onKeyword = '\0'; // Null-terminate the index name substring
    std::string indexName = indexNameStart;

    char* columnNameStart = onKeyword + 4; //going past " ON"
    char* columnNameEnd = strchr(columnNameStart, '\0');
    if (!columnNameEnd || columnNameStart == columnNameEnd) {
        throw "Invalid column name or syntax error.";
    }

    std::string columnName = columnNameStart;

    // check if the column exists 
    bool columnExists = false;
    for (int i = 0; i < table->getColumnCount(); ++i) {
        if (table->getColumns(i).getName() == columnName) {
            columnExists = true;
            break;
        }
    }

    if (!columnExists) {
        throw "Specified column does not exist in the table.";
    }

    
    Index* index = new Index(indexName, columnName, table);
    std::cout << "Index created successfully!" << std::endl;
    index->printIndexInfo();

   
    delete index;
}
