#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <iostream>

class sudokuTable{
    std::vector<std::vector<int>> table = std::vector<std::vector<int>>(9, std::vector<int>(9,0));;
    
    bool checkRow(int, int);
    bool checkCol(int, int);
    bool checkBox(int, int, int);


public:
    /*the check methods should be private
    the initial input should be public
    printer should be public
    the method to solve the table should be public, but

    */
   
    sudokuTable(std::vector<std::vector<int>>&);
    sudokuTable();
    sudokuTable(const sudokuTable&);
    bool solveTable(int, int);
    
    friend std::ostream& operator<<(std::ostream&, const sudokuTable&); 
    ~sudokuTable();
};

#endif