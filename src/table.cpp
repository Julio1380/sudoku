#include "../include/table.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>


//standard constructor for sudokuTable objects.
sudokuTable::sudokuTable(int nums){
    size = nums;
    table = std::vector<std::vector<int>>(size,std::vector<int>(size,0));
}

//constructor from existing table
sudokuTable::sudokuTable(std::vector<std::vector<int>>& sourceTable){
    size = sourceTable.size();
    table = std::vector<std::vector<int>>(size,std::vector<int>(size,0));
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            table[i][j] = sourceTable[i][j];
        }
    }
}

sudokuTable& sudokuTable::operator=(const sudokuTable& other){
    size = other.size;
    table = std::vector<std::vector<int>>(size, std::vector<int>(size,0));
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            table[i][j] = other.table[i][j];
        }
    }
    return *this;
}

//destructor
sudokuTable::~sudokuTable(){

}

//copy constructor
sudokuTable::sudokuTable(const sudokuTable& oldTable){
    size = oldTable.size;
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            table[i][j] = oldTable.table[i][j];
        }
    }
}

//takes in a number and a row index and pointer to the main sudoku table, returns if the value can validly be inserted into the row
bool sudokuTable::checkRow(int num, int row){
    for(int i = 0; i < size; i ++){
        if(table[row][i] == num)
            return false;
    }
    return true;
}

//takes in a number and a column index and a pointer to the main sudoku table, returns if the value can validly be inserted into the column
bool sudokuTable::checkCol(int num, int col){
    for(int i = 0; i < size; i ++){
        if(table[i][col] == num)
            return false;
    }
    return true;
}

//takes in a number, row index, and a column index, checks the 3x3 square of the sudoku table
bool sudokuTable::checkBox(int num, int row, int col){
    if(size == 6){
        int x = row - row % 2;
        int y = col - col % 3;
        for(int i = x; i < x+2; i++){
            for(int j = y; j < y+3; j++){
                if(table[i][j] == num)
                    return false;
            }
        }
    }else{
        int box = sqrt(size);
        int x = row - row%box;
        int y = col - col%box;
        for(int i = x; i < x+box; i++){
            for(int j = y; j < y+box; j++){
                if(table[i][j] == num)
                    return false;
            }
        }
    }
    return true;
}

//recursively go through the table, find empty (0) values and try every number for a solution 
bool sudokuTable::solveTable(int row, int col){

    if(row == (size-1) && col == size){
        return true;
    }
    if(col == size){
        return solveTable(row+1, 0);
    }
    if(table[row][col] !=0){
        return solveTable(row, col+1);
    }
    // //iterates through the possible values at a given cell, if no numbers work, then it is invalid. Once the original case is reached and no numbers work, false.
    for(int i =1; i <= size; i ++){
        if(checkRow(i, row) && checkCol(i,col) && checkBox(i, row, col)){
            table[row][col] = i;
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
    int borderLoc = sqrt(game.size);
    int under = game.size + borderLoc-1;
    for(int i = 0; i < game.size; i ++){
        for(int j = 0; j < game.size; j++){
            os << game.table[i][j] << " " ;
            if(j%borderLoc==borderLoc-1 && j != game.size-1){
                os << "| ";
            }
        }
        os << std::endl;
        if(i%borderLoc == borderLoc-1 && i != game.size-1){
            for(int x = 0; x<under; x++){
                os << "--";
            }
            os << std::endl;
        }

    }
    return os;
}