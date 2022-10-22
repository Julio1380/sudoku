#include <iostream>
#include <vector>
#include "table.h"
//main, coordinates the actual running of the program

int main(){

    //sample sudoku table for test purposes
    sudokuTable test(9);
    
    test.generateTable(0,0);
    test.generatePuzzle();
 
    std::cout << test<< std::endl;

    
    return 0;
}