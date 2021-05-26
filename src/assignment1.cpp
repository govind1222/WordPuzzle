/*
 * assignment1.cpp
 *
 * This application will search for a given word among a matrix of chars
 * in all 8 directions. The files will be read by ifstream objects
 * The location of the word, if found, will be displayed through cout
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

enum direction {
    LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP
};

const int MAX = 50;

struct wordGame {
    int version = 2;
    int numberRows;
    int numberColumns;
    char puzzle[MAX][MAX];
};

struct wordFind {
    string word;
    bool found = false;
    int row;
    int column;
    direction where;
    int foundCount;
};

// find the word that is part of the wordFind structure inside the wordGame structure.
// If the word is found the wordFind structure will be updated.
void findWord(wordGame &game, wordFind &theFind) {
    theFind.found = false;
    theFind.foundCount = 0;
    int wordSize = theFind.word.size();
    int index = 0;
    int numMatch = 0;
    int j = 0;
    vector<string> directionValues = { "right", "left", "down", "up",
                                       "right/down", "right/up", "left/down", "left/up" };
    //fold lowercase letters to uppercase
    string tempString = "";
    for (int i = 0; i < wordSize; i++) {
        if (theFind.word.at(i) >= 'A' && theFind.word.at(i) <= 'Z') {
            tempString.push_back(theFind.word.at(i));
        } else {
            char upperCaseLetter = theFind.word.at(i) - 32;
            tempString.push_back(upperCaseLetter);
        }
    }
    theFind.word = tempString;

    string reverseWord = theFind.word;
    reverse(reverseWord.begin(), reverseWord.end());

    //direction == LEFT_RIGHT - searches for the word from left to right
    for (int i = 0; i < game.numberRows; i++) {
        index = 0;
        for (j = 0; j < game.numberColumns; j++) {
            if (index < wordSize) {
                if (game.puzzle[i][j] == theFind.word.at(index)) {
                    numMatch++;
                    index++;
                } else {
                    if (numMatch != 0) {
                        j--;
                    }
                    numMatch = 0;
                    index = 0;
                }
                if (wordSize == numMatch) {
                    theFind.found = true;
                    theFind.foundCount++;
                    theFind.row = i + 1;
                    theFind.column = j - wordSize + 2;
                    theFind.where = LEFT_RIGHT;
                    numMatch = 0;
                }
            }
        }
    }

    //direction == RIGHT_LEFT - searches for the word from right to left
    for (int i = 0; i < game.numberRows; i++) {
        index = 0;
        for (j = game.numberColumns - 1; j >= 0; j--) {
            if (index < wordSize) {
                if (game.puzzle[i][j] == theFind.word.at(index)) {
                    numMatch++;
                    index++;
                } else {
                    if (numMatch != 0) {
                        j++;
                    }
                    numMatch = 0;
                    index = 0;
                }
                if (wordSize == numMatch) {
                    theFind.found = true;
                    theFind.foundCount++;
                    theFind.row = i + 1;
                    theFind.column = j + wordSize;
                    theFind.where = RIGHT_LEFT;
                    numMatch = 0;
                }
            }
        }
    }

    //direction == DOWN - searches for the word from top to down
    for (int i = 0; i < game.numberColumns; i++) {
        index = 0;
        for (j = 0; j < game.numberRows; j++) {
            if (index < wordSize) {
                if (game.puzzle[j][i] == theFind.word.at(index)) {
                    numMatch++;
                    index++;
                } else {
                    if (numMatch != 0) {
                        j--;
                    }
                    numMatch = 0;
                    index = 0;
                }
                if (wordSize == numMatch) {
                    theFind.found = true;
                    theFind.foundCount++;
                    theFind.row = j - wordSize + 2;
                    theFind.column = i + 1;
                    theFind.where = DOWN;
                    numMatch = 0;
                }
            }
        }
    }

    //direction == UP - searches for the word from top to down
    for (int i = 0; i < game.numberColumns; i++) {
        index = 0;
        for (j = game.numberRows - 1; j >= 0; j--) {
            if (index < wordSize) {
                if (game.puzzle[j][i] == theFind.word.at(index)) {
                    numMatch++;
                    index++;
                } else {
                    if (numMatch != 0) {
                        j++;
                    }
                    numMatch = 0;
                    index = 0;
                }
                if (wordSize == numMatch) {
                    theFind.found = true;
                    theFind.foundCount++;
                    theFind.row = j + wordSize;
                    theFind.column = i + 1;
                    theFind.where = UP;
                    numMatch = 0;
                }
            }
        }
    }

    //direction == RIGHT_DOWN - searches for the word diagonally, rightward and down
    for (int i = 1 - game.numberRows; i < game.numberColumns; i++) {
        index = 0;
        for (j = 0; j < game.numberRows; j++) {
            if ((i + j) >= 0 && (i + j) < game.numberColumns) {
                if (index < wordSize) {
                    if (game.puzzle[j][i + j] == theFind.word.at(index)) {
                        numMatch++;
                        index++;
                    } else {
                        numMatch = 0;
                        index = 0;
                    }
                    if (wordSize == numMatch) {
                        theFind.found = true;
                        theFind.foundCount++;
                        theFind.column = i + j - wordSize + 2;
                        theFind.row = j - wordSize + 2;
                        theFind.where = RIGHT_DOWN;
                        numMatch = 0;
                    }
                }
            }
        }
    }

    //direction == RIGHT_UP - searches for the word diagonally, rightward and up
    for (int i = 0; i < game.numberRows * 2; i++) {
        index = 0;
        for (j = 0; j <= i; j++) {
            int temp = i - j;
            if (temp < game.numberRows && j < game.numberColumns) {
                if (index < wordSize) {
                    if (game.puzzle[temp][j] == theFind.word.at(index)) {
                        numMatch++;
                        index++;
                    } else {
                        if (numMatch != 0) {
                            temp--;
                            j--;
                        }
                        numMatch = 0;
                        index = 0;
                    }
                    if (wordSize == numMatch) {
                        theFind.found = true;
                        theFind.foundCount++;
                        theFind.row = temp + wordSize;
                        theFind.column = j - wordSize + 2;
                        theFind.where = RIGHT_UP;
                        numMatch = 0;
                    }
                }
            }
        }
    }

    //direction == LEFT_DOWN - searches for the word diagonally, leftward and down
    for (int i = 0; i < game.numberRows * 2; i++) {
        index = 0;
        for (j = 0; j <= i; j++) {
            int temp = i - j;
            if (temp < game.numberRows && j < game.numberColumns) {
                if (index < wordSize) {
                    if (game.puzzle[temp][j] == reverseWord.at(index)) {
                        numMatch++;
                        index++;
                    } else {
                        if (numMatch != 0) {
                            temp--;
                            j--;
                        }
                        numMatch = 0;
                        index = 0;
                    }
                    if (wordSize == numMatch) {
                        theFind.found = true;
                        theFind.foundCount++;
                        theFind.row = temp + 1;
                        theFind.column = j + 1;
                        theFind.where = LEFT_DOWN;
                        numMatch = 0;
                    }
                }
            }
        }
    }

    //direction == LEFT_UP - searches for the word diagonally, leftward and up
    for (int i = 1 - game.numberRows; i < game.numberColumns; i++) {
        index = 0;
        for (j = 0; j < game.numberRows; j++) {
            if ((i + j) >= 0 && (i + j) < game.numberColumns) {
                if (index < wordSize) {
                    if (game.puzzle[j][i + j] == reverseWord.at(index)) {
                        numMatch++;
                        index++;
                    } else {
                        if (numMatch != 0) {
                            //i--;
                            j--;
                        }
                        numMatch = 0;
                        index = 0;
                    }
                    if (wordSize == numMatch) {
                        theFind.found = true;
                        theFind.foundCount++;
                        theFind.column = i + j + 1;
                        theFind.row = j + 1;
                        theFind.where = LEFT_UP;
                        numMatch = 0;
                    }
                }
            }
        }
    }

    //prints out the results of the word search
    if (theFind.foundCount == 0) {
        cout << "The word " << theFind.word << " was not found" << endl;
    } else if (theFind.foundCount == 1) {
        cout << "The word " << theFind.word << " was found at (" << theFind.row
             << ", " << theFind.column << ") - "
             << directionValues.at(theFind.where) << endl;
    } else if (theFind.foundCount > 1) {
        cout << "The word " << theFind.word << " was found "
             << theFind.foundCount << " times" << endl;
    }
}

//read the puzzle from the input file and update the wordGame structure.
bool readPuzzle(wordGame &game, const string& inputFileName) {

    ifstream input;
    input.open(inputFileName);

    //checks to see if the file is opened
    if (!input.is_open()) {
        return false;
    }

    //reading in the number of rows and columns
    input >> game.numberRows;
    input >> game.numberColumns;

    //checking to see if number of rows and columns is within range 1...MAX
    if (game.numberRows < 1 || game.numberRows > MAX || game.numberColumns < 1
        || game.numberColumns > MAX) {
        return false;
    }

    //reading in the lines of characters
    string text;
    int index = 0;
    input >> text;
    int numRows = 0;
    int numColumns = 0;

    while (input) {
        numRows++;
        for (int i = 0; i < game.numberColumns; i++) {
            //checks to make sure that all characters are uppercase
            if (text.at(i) >= 'A' && text.at(i) <= 'Z') {
                game.puzzle[index][i] = text.at(i);
            } else {
                char upperCaseLetter = text.at(i) - 32;
                game.puzzle[index][i] = upperCaseLetter;
            }
            numColumns++;
        }
        index++;
        input >> text;
    }

    //checking for end of file conditions
    if ((numRows != game.numberRows)
        || ((numColumns / numRows) != game.numberColumns)) {
        return false;
    }

    input.close();
    return true;
}

// display the contents of the puzzle
void displayPuzzle(wordGame &game) {
    for (int row = 0; row < game.numberRows; row++) {
        for (int col = 0; col < game.numberColumns; col++) {
            cout << game.puzzle[row][col];
        }
        cout << endl;
    }
}

//main is the driver for the entire program. this function
//calls readPuzzle(), displayPuzzle(), and findWord()
int main() {
    ifstream input;
    string text;
    string inputFileNameOne;
    string inputFileNameTwo;
    wordGame game;
    wordFind theFind;

    //reading in file names
    cin >> inputFileNameOne;
    cin >> inputFileNameTwo;

    //the next 2 if statements checks to see if the files were successfully opened
    if (!readPuzzle(game, inputFileNameOne)) {
        cout << "The puzzle file \"" << inputFileNameOne
             << "\" could not be opened or is invalid" << endl;
        return 0;
    }

    input.open(inputFileNameTwo);
    cout << "The puzzle from file \"" << inputFileNameOne << "\"" << endl;
    displayPuzzle(game);

    if (!input.is_open()) {
        cout << "The puzzle file \"" << inputFileNameTwo
             << "\" could not be opened or is invalid" << endl;
        return 0;
    }

    input >> text;
    while (input) {
        theFind.word = text;
        findWord(game, theFind);
        input >> text;
    }
    input.close();
    return 0;
}
