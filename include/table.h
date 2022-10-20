#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <iostream>

class sudokuTable{
    std::vector<std::vector<int>> table;
    int solutions;
    int size;
    bool checkRow(int, int);
    bool checkCol(int, int);
    bool checkBox(int, int, int);
    void clearTable();
    void generateTable(int, int);
    
public:
    /*the check methods should be private
    the initial input should be public
    printer should be public
    the method to solve the table should be public, but

    */
   
    sudokuTable(std::vector<std::vector<int>>&);
    sudokuTable(int);
    sudokuTable(const sudokuTable&);
    sudokuTable& operator=(const sudokuTable&);
    bool solveTable(int, int);
    friend std::ostream& operator<<(std::ostream&, const sudokuTable&); 
    ~sudokuTable();
};

#endif