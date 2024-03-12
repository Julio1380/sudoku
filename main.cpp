#include <iostream>
#include <vector>
#include <stack>
#include "table.h"
//main, coordinates the actual running of the program

int getRowInput(int);
int getColInput(int);

int main(){

    sudokuTable puzzle(1);
    
    // Main loop

    std::cout<< "Sudoku!"<< std::endl;
    while(1){
        int diff;
        bool isSolved = false;
        do{
            std::cout << "Please select a difficulty (1-3):\n\t1. Easy\n\t2. Medium\n\t3. Hard" << std::endl;
            std::cin >> diff;
        }while(diff < 1 || diff > 3);

        int size;

        do{
            std::cout << "Please select a puzzle size (1-2):\n\t1. 4 numbers\n\t2. 9 numbers" << std::endl;
            std::cin >> size;
        }while(size < 1 || size > 2);
        switch(size){
            case 1:
                puzzle = sudokuTable(4);
                break;

            case 2:
                puzzle = sudokuTable(9);
                break;
            
        }
        size = puzzle.getSize();
        diff--;
        puzzle.createNewPuzzle();

        while(puzzle.getDifficulty() != diff){
            puzzle.createNewPuzzle();
        }

        std::vector<int> lastMove;
        std::stack<std::vector<int>> moveList;
        
        // Game Loop
        int sudokuOption, rowSelect, colSelect, value, checkSelect;
        while(1){
            std::cout << std::endl;
            std::cout << puzzle << std::endl;

            // Select an action
            do{
                std::cout << "Choose an action (1-7): \n\t1. Enter a value to the table\n\t2. Remove a value from the table\n\t3. Undo Last Move \n\t4. Get Help (Fills one tile)\n\t5. Check puzzle\n\t6. Give Up\n\t7. Exit Sudoku" << std::endl;
                std::cin >> sudokuOption;
            }while(sudokuOption < 1 || sudokuOption > 7);

            switch(sudokuOption){
                case 1: // Enter value to location
                    
                    // Ask for user input and validate. 
                    rowSelect = getRowInput(size);
                    colSelect = getColInput(size);

                    do{
                        std::cout << "Enter a value to place in that tile (1 - " << size << ")." << std::endl;
                        std::cin >> value;
                    }while(value < 1 || value > size);

                    lastMove.push_back(rowSelect);
                    lastMove.push_back(colSelect);
                    lastMove.push_back(puzzle.getValue(rowSelect, colSelect));
                    if(puzzle.enterValue(value, rowSelect, colSelect)){
                        moveList.push(lastMove);

                    }else{
                        std::cout << "Invalid location, tile is part of original puzzle." << std::endl;
                    }
                    lastMove.clear();

                    break;
                case 2: // Clear value from location
                    rowSelect = getRowInput(size);
                    colSelect = getColInput(size);

                    if(puzzle.enterValue(0, rowSelect, colSelect)){
                        moveList.push(lastMove);

                    }else{
                        std::cout << "Invalid location, tile is part of original puzzle." << std::endl;
                    }
                    break;
                case 3: // Undo, restores state before previous move
                    if(moveList.empty()){
                        std::cout << "No moves to Undo." << std::endl;
                        break;
                    }
                    lastMove = moveList.top();
                    moveList.pop();
                    puzzle.enterValue(lastMove[2], lastMove[0], lastMove[1]);
                    break;        

                case 4:
                    puzzle.getHint();
                    break;
                
                case 5: // Check Puzzle
                    do{
                        std::cout << "Select a check option (1-5): \n\t1. Single Tile \n\t2. Row\n\t3. Column\n\t4. Entire Puzzle \n\t5.Return to Menu" << std::endl;
                        std::cin >> checkSelect;
                    }while(checkSelect < 0 || checkSelect > 5);
                    
                    switch(checkSelect){
                        case 1:
                            rowSelect = getRowInput(size);
                            colSelect = getColInput(size);
                            puzzle.checkTile(rowSelect, colSelect);
                            break;

                        case 2: 
                            rowSelect = getRowInput(size);
                            puzzle.checkRow(rowSelect);
                            break;

                        case 3:
                            colSelect = getColInput(size);
                            puzzle.checkCol(colSelect);
                            break;

                        case 4:
                            puzzle.checkPuzzle();
                            break;

                        case 5:
                            continue;
                    }

                    break;
                
                case 6: // Show Solution
                    std::cout << "Solution:" << std::endl;
                    puzzle.copySolution();
                    std::cout << puzzle << std::endl;
                    break;
                
                case 7: // Exit
                    return 0;
            }

            if(puzzle.checkSolved()){
                std::cout << "Solved!" << std::endl;
                char newPuzzle;
                do{
                    std::cout << "Play Again?\nY\tN" << std::endl;
                    std::cin >> newPuzzle;
                }while(newPuzzle != 'Y' && newPuzzle != 'N' && newPuzzle != 'y' && newPuzzle != 'n');
                if(newPuzzle == 'Y' || newPuzzle == 'y'){
                    break;
                }else{
                    return 0;
                }
            }
        }

    }
    return 0;
}

// Asks the user for input to select a row. Requested input is from 1-size, then is shfited to 0 indexed.
int getRowInput(int size){
    int row;
    do{
        std::cout << "Pick a row (1 - " << size << ")." << std::endl;
        std::cin >> row;
    }while(row < 1 || row > size);

    row--;
    return row;
}

// Asks the user for input to select a column. Requested input is from 1-size, then is shfited to 0 indexed.
int getColInput(int size){
    int col;
    do{
        std::cout << "Pick a column (1 - " << size << ")." << std::endl;
        std::cin >> col;
    }while(col < 1 || col > size);

    col--;
    return col;
}