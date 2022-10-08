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
    for(int i = row/3; i < row/3+3; i++){
        for(int j = col/3; i < col/3+3; j++){
            if(table[row][col] == num)
                return false;
        }
    }
    return true;
}

bool sudokuTable::solveTable(int x, int y){
    //should recursively go through the table, find empty (0) values and try every number for a solution 
    if(table[x][y] == 0){
        for(int i = 1; i <= 9; ++i){
            
        }
    }else{
        
    }
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