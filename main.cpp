#include <iostream>
#include <vector>
#include "table.h"
//main, coordinates the actual running of the program

int main(){
    std::vector<std::vector<int>> sample_table = {
    {8, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 6, 0, 0, 0, 0, 0},
    {0, 7, 0, 0, 9, 0, 2, 0, 0},
    {0, 5, 0, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 4, 5, 7, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 3, 0},
    {0, 0, 1, 0, 0, 0, 0, 6, 8},
    {0, 0, 8, 5, 0, 0, 0, 1, 0},
    {0, 9, 0, 0, 0, 0, 4, 0, 0}};

    //sample sudoku table for test purposes
    sudokuTable test = sudokuTable(sample_table);
    std::cout << test << std::endl;
    if(test.solveTable(0,0)==false){
        std::cout << "No solution found.";
        
    }else{
        std::cout << "Solution found.";
    }

    
    return 0;
}