#include <iostream>
#include <vector>
#include <stack>
#include "table.h"
//main, coordinates the actual running of the program

int main(){

    sudokuTable puzzle(1);
    
    // Main loop

    while(1){
        std::cout<< "Sudoku!"<< std::endl;
        int diff;
        do{
            std::cout << "Please select a difficulty (1-3):\n\t1. Easy\n\t2. Medium\n\t3. Hard" << std::endl;
            std::cin >> diff;
        }while(diff < 1 || diff > 3);

        int size;

        do{
            std::cout << "Please select a puzzle size (1-3):\n\t1. 4 numbers\n\t2. 9 numbers\n\t3. 16 numbers" << std::endl;
            std::cin >> size;
        }while(size < 1 || size > 3);
        switch(size){
            case 1:
                puzzle = sudokuTable(4);
                break;

            case 2:
                puzzle = sudokuTable(9);
                break;
            
            case 3:
                puzzle = sudokuTable(16);
                break;
            
        }

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
            std::cout << std::endl;z
            std::cout << puzzle << std::endl;

            // Select an action
            do{
                std::cout << "Choose an action (1-6): \n\t1. Enter a value to the table\n\t2. Remove a value from the table\n\t3. Get Help (Fills one square)\n\t4. Check puzzle\n\t5. Give Up\n\t6. Exit Sudoku" << std::endl;
                std::cin >> sudokuOption;
            }while(sudokuOption < 1 || sudokuOption > 6);

            switch(sudokuOption){
                case 1:
                    
                    // Ask for user input and validate. 

                    do{
                        std::cout << "Pick a row (1 - " << puzzle.getSize() << ")." << std::endl;
                        std::cin >> rowSelect;
                    }while(rowSelect < 1 || rowSelect > puzzle.getSize());

                    do{
                        std::cout << "Pick a column (1 - " << puzzle.getSize() << ")." << std::endl;
                        std::cin >> colSelect;
                    }while(colSelect < 1 || colSelect > puzzle.getSize());

                    do{
                        std::cout << "Enter a value to place in that tile (1 - " << puzzle.getSize() << ")." << std::endl;
                        std::cin >> value;
                    }while(value < 1 || value > puzzle.getSize());

                    // Shift coordinate select to 0 index
                    rowSelect--;
                    colSelect--;

                    puzzle.enterValue(value, rowSelect, colSelect);

                    break;
                case 2:

                    do{
                        std::cout << "Pick a row (1 - " << puzzle.getSize() << ")." << std::endl;
                        std::cin >> rowSelect;
                    }while(rowSelect < 1 || rowSelect > puzzle.getSize());

                    do{
                        std::cout << "Pick a column (1 - " << puzzle.getSize() << ")." << std::endl;
                        std::cin >> colSelect;
                    }while(colSelect < 1 || colSelect > puzzle.getSize());

                    puzzle.enterValue(0, rowSelect, colSelect);
                    break;

                case 3:
                    puzzle.getHint();
                    break;
                
                case 4:
                    do{
                        std::cout << "Select a check option (1-5): \n\t1. Single Tile \n\t2. Row\n\t3. Column\n\t4. Entire Puzzle \n\t 5.Return to Menu" << std::endl;
                        std::cin >> checkSelect;
                    }while(checkSelect < 0 || checkSelect > 5);
                    
                    switch(checkSelect){
                        case 1:
                            do{
                                std::cout << "Pick a row (1 - " << puzzle.getSize() << ")." << std::endl;
                                std::cin >> rowSelect;
                            }while(rowSelect < 1 || rowSelect > puzzle.getSize());

                            do{
                                std::cout << "Pick a column (1 - " << puzzle.getSize() << ")." << std::endl;
                                std::cin >> colSelect;
                            }while(colSelect < 1 || colSelect > puzzle.getSize());
                            puzzle.checkTile(rowSelect, colSelect);
                            break;

                        case 2: 
                            do{
                                std::cout << "Pick a row (1 - " << puzzle.getSize() << ")." << std::endl;
                                std::cin >> rowSelect;
                            }while(rowSelect < 1 || rowSelect > puzzle.getSize());

                            puzzle.checkRow(rowSelect);
                            break;

                        case 3:

                            do{
                                std::cout << "Pick a column (1 - " << puzzle.getSize() << ")." << std::endl;
                                std::cin >> colSelect;
                            }while(colSelect < 1 || colSelect > puzzle.getSize());
                            
                            puzzle.checkCol(colSelect);
                            break;

                        case 4:

                            puzzle.checkPuzzle();

                        case 5:
                            continue;
                    }

                    break;
                
                case 5: 
                    std::cout << "Solution:" << std::endl;
                    puzzle.copySolution();
                    std::cout << puzzle << std::endl;
                    break;
                
                case 6: 
                    return 0 ;
            }
        }

    }
    return 0;
}