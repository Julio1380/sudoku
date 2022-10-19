#include <iostream>
#include <vector>
#include "table.h"
//main, coordinates the actual running of the program

int main(){
    std::vector<std::vector<int>> sample_table = {
    {0, 4, 0, 0, 0, 0, 3, 0, 0},
    {0, 0, 3, 0, 1, 8, 0, 0, 5},
    {5, 0, 0, 3, 4, 0, 0, 1, 0},
    {0, 0, 7, 2, 0, 0, 6, 9, 0},
    {2, 0, 0, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 3, 0, 0, 4, 0},
    {6, 0, 9, 0, 0, 5, 0, 2, 0},
    {0, 0, 0, 6, 2, 0, 0, 0, 0}};

    //sample sudoku table for test purposes
    sudokuTable test = sudokuTable(sample_table);
    
    if(test.solveTable(0,0)==false){
        std::cout << "No solution found." << std::endl;
        
    }else{
        std::cout << "Solution found." << std::endl;
    }
    std::cout << test<< std::endl;

    
    return 0;
}