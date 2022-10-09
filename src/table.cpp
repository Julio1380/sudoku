#include "../include/table.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>


//standard constructor
sudokuTable::sudokuTable(){

}

//constructor from existing table
sudokuTable::sudokuTable(std::vector<std::vector<int>>& sourceTable){
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            table[i][j] = sourceTable[i][j];
        }
    }
}

//destructor
sudokuTable::~sudokuTable(){

}

//copy constructor
sudokuTable::sudokuTable(const sudokuTable& oldTable){
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            table[i][j] = oldTable.table[i][j];
        }
    }
}

//takes in a number and a row index and pointer to the main sudoku table, returns if the value can validly be inserted into the row
bool sudokuTable::checkRow(int num, int row){
    for(int i = 0; i < 9; i ++){
        if(table[row][i] == num)
            return false;
    }
    return true;
}

//takes in a number and a column index and a pointer to the main sudoku table, returns if the value can validly be inserted into the column
bool sudokuTable::checkCol(int num, int col){
    for(int i = 0; i < 9; i ++){
        if(table[i][col] == num)
            return false;
    }
    return true;
}

//takes in a number, row index, and a column index, checks the 3x3 square of the sudoku table
bool sudokuTable::checkBox(int num, int row, int col){
    int x = row - row%3;
    int y = col - col%3;
    for(int i = x; i < x+3; i++){
        for(int j = y; j < y+3; j++){
            if(table[i][j] == num)
                return false;
        }
    }
    return true;
}

//recursively go through the table, find empty (0) values and try every number for a solution 
bool sudokuTable::solveTable(int row, int col){
    
    if(row == 8 && col == 9){
        return true;
    }
    if(col == 9){
        return solveTable(row+1, 0);
    }
    if(table[row][col] !=0){
        return solveTable(row, col+1);
    }
    // //iterates through the possible values at a given cell, if no numbers work, then it is invalid. Once the original case is reached and no numbers work, false.
    for(int i =1; i < 10; i ++){
        if(checkRow(i, row) && checkCol(i,col) && checkBox(i, row, col)){
            table[row][col] = i;
            std::cout << "row: " << row << " col: " << col << " num: " << i << std::endl;
            if(solveTable(row, col+1)){
                return true;
            }

        }
        
    }
    table[row][col] = 0;
    return false;
}

//prints the final sudoku table
std::ostream& operator<<(std::ostream& os, const sudokuTable& game){
    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9; j++){
            os << game.table[i][j] << " " ;
            if(j == 2 || j == 5){
                os << "| ";
            }
        }
        os << std::endl;
        if(i == 2 || i == 5){
            for(int x = 0; x<7; x++){
                os << "---";
            }
            os << std::endl;
        }

    }
    return os;
}