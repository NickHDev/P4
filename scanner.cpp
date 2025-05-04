/*
Author: Nicholas Hieb
Date Created: 3/05/2025 Date Modified: 4/10/2025
This is the scanner to parse the input and return tokens.
*/
#include <iostream>
#include <fstream>
#include <string>
#include "token.h"
#include "scanner.h"
inputChar nextChar;
int lineNum = 0;
// Scanner Driver that takes in a file and returns a token
// OR3 and in class code
token_t scanner(FILE *input)
{
    int state = 0;
    int nextState;
    token_t tk;
    std::string S = "";

    while (state >= 0 && state < 1000)
    {
        nextState = Table[state][nextChar.colNum];
        if (nextState < 0)
        {
            printf("SCANNER ERROR: %s %d\n", S.c_str(), lineNum);
            exit(1);
        }
        if (nextState >= 1000)
        {
            switch (nextState)
            {
            case 1000:
                tk.id = EOF_tk;
                break;
            case 1001:
                tk.id = t1_tk;
                break;
            case 1002:
                tk.id = t2_tk;
                break;
            case 1003:
                tk.id = t3_tk;
                break;
            default:
                break;
            }
            tk.name = S;
            tk.lineNum = nextChar.lineNum;
            return tk;
        }
        else
        {
            if (nextChar.c != ' ')
            {
                S.push_back(nextChar.c);
            }
            state = nextState;
            nextChar = filter(input);
        }
    }
    return tk;
}
// Filter the next character and return a character struct
// OR2
inputChar filter(FILE *input)
{
    inputChar ic;
    char c = fgetc(input);
    int colNum = getColNum(c);
    // This is to skip over comments
    while (colNum == 6)
    {
        c = fgetc(input);
        colNum = getColNum(c);
    }

    if (colNum >= 0 && colNum <= 5)
    {   
        ic.c = c;
        ic.colNum = colNum;
        ic.lineNum = lineNum;
        if (c == '\n')
        {
            lineNum++;
        }
        return ic;
    }
    else
    {
        printf("SCANNER ERROR: %c %d\n", c, lineNum);
        exit(1);
    }
}
// Column number of the character that returns a int
// OR1
int getColNum(char c)
{
    if (isspace(c))
    {
        return 5;
    }
    else if (c >= 33 && c <= 41)
    {
        return 4;
    }
    else if (c == '+')
    {
        return 3;
    }
    else if (isdigit(c))
    {
        return 2;
    }
    else if (isupper(c))
    {
        return 1;
    }
    else if (islower(c))
    {
        return 1;
    }
    else if (c == EOF || c == '\n' || c == '\0')
    {
        return 0;
    }
    else if (c == '*')
    {
        return 6;
    }
    else if (c == '/')
    {
        return 7;
    }
    else
    {
        printf("SCANNER ERROR: %c %d\n", c, lineNum);
        return -1;
    }
}
// Set the lookahead
// OR1
void setLookAhead(FILE *input)
{
    nextChar = filter(input);
}