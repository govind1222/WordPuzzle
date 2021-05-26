# Word Puzzle Program 

## Overview 
This was a project done to gain experience in the C++ language. The program is a word search
puzzle - given a grid of letters and a list of words to look for, the program locates the
word in the grid and gives the location of the starting letter in the grid as well as its
orientation. 

For example,

```text
The word HELLO was found at (1, 1) - right
```

If the word is found multiple times,

```text
The word HELLO was found # times
```

If the word is not found,

```text
The word HELLO was not found
```

## Running the program
The program takes as input the path of 2 ".txt" files. The first file is the grid of 
letters. The first line of this file is formatted as such,

```text
R C
```

where R and C are numbers that indicate the number of rows and columns, respectively, 
in the grid of letters. Then follows an R x C grid of letters. 

The second file is the list of words to search for. The program will iterate through this
list of words and search for it in the grid.