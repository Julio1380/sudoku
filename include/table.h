#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <iostream>

class sudokuTable{
    std::vector<std::vector<int>> table;
    std::vector<std::vector<int>> solution;
    std::vector<std::vector<int>> keyValues;
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
    void generateTable(int, int);
    void generatePuzzle();
    
public:

    bool enterValue(int,int,int);
    void createNewPuzzle();
    int getDifficulty();
    bool checkSolved();
    int getSize();
    int getValue(int,int);
    void checkPuzzle();
    void checkRow(int);
    void checkCol(int);
    void checkTile(int, int);
    sudokuTable(std::vector<std::vector<int>>&);
    sudokuTable(int);
    sudokuTable(const sudokuTable&);
    sudokuTable& operator=(const sudokuTable&);
    void solveTable(int, int, int&);
    friend std::ostream& operator<<(std::ostream&, const sudokuTable&); 
    void getHint();
    void copySolution();
    ~sudokuTable();
};

#endif