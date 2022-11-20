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
    solution = std::vector<std::vector<int>>(size,std::vector<int>(size,0));
    hasValidTable = false;
}

//constructor from existing table
sudokuTable::sudokuTable(std::vector<std::vector<int>>& sourceTable){
    size = sourceTable.size();
    table = std::vector<std::vector<int>>(size,std::vector<int>(size,0));
    solution = std::vector<std::vector<int>>(size,std::vector<int>(size,0));
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            table[i][j] = sourceTable[i][j];
            solution[i][j] = sourceTable[i][j];
        }
    }
    int val = 0;
    solveTable(0,0,val);
    if(val = 1){
        hasValidTable = true;
    }
}

sudokuTable& sudokuTable::operator=(const sudokuTable& other){
    size = other.size;
    table = std::vector<std::vector<int>>(size, std::vector<int>(size,0));
    solution = std::vector<std::vector<int>>(size,std::vector<int>(size,0));
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            table[i][j] = other.table[i][j];
            solution[i][j] = other.table[i][j];
        }
    }
    
    hasValidTable = other.hasValidTable;
    return *this;
}

//Destructor
sudokuTable::~sudokuTable(){

}

//Copy constructor
sudokuTable::sudokuTable(const sudokuTable& oldTable){
    size = oldTable.size;
    solution = std::vector<std::vector<int>>(size,std::vector<int>(size,0));
    table = std::vector<std::vector<int>>(size,std::vector<int>(size,0));
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            table[i][j] = oldTable.table[i][j];
            solution[i][j] = oldTable.table[i][j];
        }
    }
    hasValidTable = oldTable.hasValidTable;
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
            solution[i][j] = 0;
        }
    }
    hasValidTable = false;
}

//Recursively goes through the table, uses RNG to generate values and checks if the value is present. Uses a vector to track if the value has already been attempted
void sudokuTable::generateTable(int row, int col){
    if(row == (size-1) && col == size){
        hasValidTable = true;
        return;
    }
    if(col == size){
        generateTable(row+1, 0);
    }
    std::vector<bool> checked(9, false);
    int amountChecked = 0;
    
    //random number generator
    std::random_device seed;
    std::mt19937 newSeed(seed());
    std::uniform_int_distribution<std::mt19937::result_type> num(1,size);

    int val;

    while(amountChecked<size){
        val = num(newSeed);
        if(checked[val-1] == false){
            checked[val-1] = true;
            amountChecked++;
            if(checkRow(val, row) && checkCol(val, col) && checkBox(val, row, col)){
                table[row][col] = val;
                generateTable(row, col+1);
                if(hasValidTable == true){
                    return;
                }
                table[row][col] = 0;
            }
        }   
    }    
}

//goes through the table and finds random coordinates, 
//once more than one solution can be found, undo the last modification and change the difficulty

void sudokuTable::generatePuzzle(){
    std::random_device seed;
    std::mt19937 newSeed(seed());
    std::uniform_int_distribution<std::mt19937::result_type> num(0,size-1);

    int solutions = 1, removals = 0, lastRow, lastCol, lastVal;

    while(solutions == 1){
        lastRow = num(newSeed);
        lastCol = num(newSeed);
        lastVal = table[lastRow][lastCol];
        if(lastVal == 0){
            continue;
        }
        table[lastRow][lastCol] = 0;
        solutions = 0;
        removals++;
        solveTable(0,0, solutions); 
    }
    table[lastRow][lastCol] = lastVal;
    if(removals < 50){
        rating = Easy;
    }else if(removals<55){
        rating = Medium;
    }else{
        rating = Hard;
    }
}

//Enters values into the table coordinates, modifies the table.
void sudokuTable::enterValue(int value, int row, int col){
    table[row][col] = value;
}

//Clears the table and generates a new puzzle in the table. 
void sudokuTable::createNewPuzzle(){
    clearTable();
    generateTable(0,0);
    generatePuzzle();
}

//returns the difficulty of the puzzle
int sudokuTable::getDifficulty(){
    return rating;
}

//checks if the table is solved
bool sudokuTable::checkSolved(){
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            if(table[i][j] != solution[i][j]){
                return false;
            }
        }
    }
    return true;
}

//returns a table that shows all wrong numbers
std::vector<std::vector<int>> sudokuTable::invalidSquares(){
    std::vector<std::vector<int>> invalid(size, std::vector<int>(size, 0));
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            if(table[i][j] != 0 && table[i][j] != solution[i][j]){
                invalid[i][j] = 1;
            }
        }
    }
}

//recursively go through the table, find empty (0) values and try every number to find the amount of solutions. Table is not modified as a result.
void sudokuTable::solveTable(int row, int col, int& numSolutions){
    if(numSolutions == 2){
        return;
    }
    if(row == (size-1) && col == size){
        numSolutions++;
        if(numSolutions ==1){
            solution = table;
        }
    }else if(col == size){
        solveTable(row+1, 0, numSolutions);
    }else if(table[row][col] !=0){
        solveTable(row, col+1, numSolutions);
    }else{
        for(int i =1; i <= size; ++i){
            if(checkRow(i, row) && checkCol(i,col) && checkBox(i, row, col)){
                table[row][col] = i;
                solveTable(row, col+1, numSolutions);

            }
        }
        table[row][col] = 0;
    }
    return;
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