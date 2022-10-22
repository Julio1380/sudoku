#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <iostream>

class sudokuTable{
    std::vector<std::vector<int>> table;
    std::vector<std::vector<int>> solution;
    int size;
    bool hasValidTable;
    enum difficulties{
        Easy,
        Medium, 
        Hard
    };
    difficulties rating;
    bool checkRow(int, int);
    bool checkCol(int, int);
    bool checkBox(int, int, int);
    void clearTable();
    
public:

    void enterValue(int,int,int);
    void generateTable(int, int);
    void generatePuzzle();
    int getDifficulty();
    sudokuTable(std::vector<std::vector<int>>&);
    sudokuTable(int);
    sudokuTable(const sudokuTable&);
    sudokuTable& operator=(const sudokuTable&);
    void solveTable(int, int, int&);
    friend std::ostream& operator<<(std::ostream&, const sudokuTable&); 
    ~sudokuTable();
};

#endif