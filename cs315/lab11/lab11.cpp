#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "OpenHash.h"
#include "ClosedHash.h"

bool validSpot(int spot) {
    if (spot > 48 || spot < 0) return false;
    int col = spot % 7;
    if (col != 2 && col != 3 && col != 4) {
        int row = spot / 7;
        if (row != 2 && row != 3 && row != 4) {
            return false;
        }
    }
    return true;
}


void makeMove(std::vector<bool>& board, std::vector<int>& move) {
    board[move[0]] = false;
    board[move[1]] = false;
    board[move[2]] = true;
}

std::vector<int>& createMove(std::vector<int>& newMove, int i, int j, int k) {

    newMove.clear();

    newMove.push_back(i);
    newMove.push_back(j);
    newMove.push_back(k);

    return newMove;
}

bool validMove(std::vector<bool>& board, int full1, int full2, int empty) {
    return board[full1] == true && board[full2] == true && board[empty] == false;
}
std::vector<std::vector<int> >& currentMoves(std::vector<std::vector<int> >& curMoves, std::vector<bool>& board) {
    int j, k;
    std::vector<int> newMoves;
    for (int i = 0; i < 49; ++i) {
        if ( validSpot(i) ) {
            if (i % 7 + 2 < 7) {
                j = i + 1;
                k = i + 2;
                if ( validSpot(j) && validSpot(k) ) {
                    // check horizontal 
                    if (validMove(board, i, j, k)) curMoves.push_back(createMove(newMoves, i, j, k));
                    else if (validMove(board, k, j, i)) curMoves.push_back(createMove(newMoves, k, j, i));
                }
            }
            if (i / 7 + 2 < 7) {
                j = i + 7;
                k = i + 14;
                if ( validSpot(j) && validSpot(k) ) {
                    // check vertical
                    if (validMove(board, i, j, k)) curMoves.push_back(createMove(newMoves, i, j, k));
                    else if (validMove(board, k, j, i)) curMoves.push_back(createMove(newMoves, k, j, i));
                }
            }
        }
    }
    return curMoves;
}

bool solved(std::vector<bool>& board) {
    int count = 0;
    for (int i = 0; i < 49; ++i) {
        if ( validSpot(i) ) {
            if (board[i] == true) ++count;
            if (count > 1) return false;
        }
    }
    return true;
}

std::string boardToString(std::vector<bool>& board) {
    std::string result = "";
    for (int i = 0; i < 49; ++i) {
        result += board[i] ? 1 : 0;
    }
    return result;
}
bool closedHSolve(std::vector<bool>& board, std::vector<std::vector<int> >& moves, ClosedHash& H) {
    if ( solved(board) ) return true;
    std::vector<std::vector<int> > curMoves;
    currentMoves(curMoves, board);
    std::vector<bool> newBoard;
    if ( !H.contains(boardToString(board)) ) {
        for (std::vector<std::vector<int> >::iterator it = curMoves.begin(); it != curMoves.end(); ++it) {
            newBoard = board;
            makeMove(newBoard, *it);
            if ( closedHSolve(newBoard, moves, H) ) {
                moves.push_back(*it);
                return true;
            }
            else {
                H.insert(boardToString(board));
            }
        }
    }
    return false;
}

bool openHSolve(std::vector<bool>& board, std::vector<std::vector<int> >& moves, OpenHash& H) {
    if ( solved(board) ) return true;
    std::vector<std::vector<int> > curMoves;
    currentMoves(curMoves, board);
    std::vector<bool> newBoard;
    if ( !H.contains(boardToString(board)) ) {
        for (std::vector<std::vector<int> >::iterator it = curMoves.begin(); it != curMoves.end(); ++it) {
            newBoard = board;
            makeMove(newBoard, *it);
            if ( openHSolve(newBoard, moves, H) ) {
                moves.push_back(*it);
                return true;
            }
            else {
                H.insert(boardToString(board));
            }
        }
    }
    return false;
}

bool solve(std::vector<bool>& board, std::vector<std::vector<int> >& moves) {
    if ( solved(board) ) return true;
    std::vector<std::vector<int> > curMoves;
    currentMoves(curMoves, board);
    std::vector<bool> newBoard;
    for (std::vector<std::vector<int> >::iterator it = curMoves.begin(); it != curMoves.end(); ++it) {
        newBoard = board;
        makeMove(newBoard, *it);
        if ( solve(newBoard, moves) ) {
            moves.push_back(*it);
            return true;
        }
    }
    return false;
}

// Input: Takes in a reference to an  empty board and the name of a file that contains numbers that
// represent the filled positions.
// Output: The empty board is updated with the positions from the file
void loadBoard(std::vector<bool>& board, char* file) {
    std::ifstream inFile;
    inFile.open(file, std::ios::in);


    if (!inFile) {
        std::cerr << "Can't open input file " << file << std::endl;
        exit(1);
    }

    int nextPos;
    while ( !inFile.eof() ) {
        inFile >> nextPos;
        board[nextPos] = true;
    }
    
    inFile.close();
}

int main(int argc, char** argv) {

    double startTime, endTime;
    bool isSolved;

    for (int i = 1; i <= 3; ++i) {
        std::cout << "Board " << i << std::endl;
        int j = i < 3 ? 1 : 2;
        for ( ; j <= 3; ++j) {
            std::vector<bool> board(49, false);
            std::vector<std::vector<int> > moves;
            loadBoard(board, argv[i]);

            startTime = clock();
            switch (j) {
                case 1:
                    std::cout << "No hash table" << std::endl;
                    isSolved = solve(board, moves);
                    break;
                case 2: 
                    {
                        std::cout << "Open hash table" << std::endl;
                        OpenHash oh;
                        isSolved = openHSolve(board, moves, oh);
                        break;
                    }
                case 3:
                    {
                        std::cout << "Closed hash table" << std::endl;
                        ClosedHash ch;
                        isSolved = closedHSolve(board, moves, ch);
                        break;
                    }
            }
            endTime = clock();
            std::cout << "Time: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << std::endl;

            if (isSolved) {
                for (std::vector<std::vector<int> >::iterator it = moves.begin(); it != moves.end(); ++it) {
                    std::cout << "(" << (*it)[0] << " " << (*it)[1] << " " << (*it)[2] << ")";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "No solution" << std::endl;
            }
        }
        std::cout << std::endl;
    }
}
