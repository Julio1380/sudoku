#include "../include/table.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
#include <random>


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

//Destructor
sudokuTable::~sudokuTable(){

}

//Copy constructor
sudokuTable::sudokuTable(const sudokuTable& oldTable){
    size = oldTable.size;
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            table[i][j] = oldTable.table[i][j];
        }
    }
}

//Recieves a number and its row. Checks whether that number is already present in the row.
bool sudokuTable::checkRow(int num, int row){
    for(int i = 0; i < size; i ++){
        if(table[row][i] == num)
            return false;
    }
    return true;
}

//Recieves a number and its column. Checks whether that number is already present in the column.
bool sudokuTable::checkCol(int num, int col){
    for(int i = 0; i < size; i ++){
        if(table[i][col] == num)
            return false;
    }
    return true;
}

//Recieves a number, its row, and its column. Checks whether that number is already present in the box.
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

//Clears the sudoku table to default value of 0
void sudokuTable::clearTable(){
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            table[i][j] = 0;
        }
    }
}

//Recursively goes through the table, uses RNG to generate values and checks if the value is present. Uses a vector to track if the value has already been attempted
void sudokuTable::generateTable(int row, int col){
    std::vector<bool> checked(9, false);
    int amountChecked = 0;
    
    //random number generator
    std::random_device seed;
    std::mt19937 newSeed(seed());
    std::uniform_int_distribution<std::mt19937::result_type> num(1,size);

    int val;

    while(amountChecked<size){
        val = num(newSeed);
        if(checked[val] == false){
            checked[val] = true;
            amountChecked++;
            if(checkRow(val, row) && checkCol(val, col) && checkBox(val, row, col)){
                
            }
        }   
    }
    
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