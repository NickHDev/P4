/*
Author: Nicholas Hieb
Date Created: 3/05/2025
This is the header file for the token struct and the inputChar struct.
*/
#ifndef token_h
#define token_h
#include <string>
const std::string tokenNames[] = {"t1", "t2", "t3", "EOF"};
// Table that holds the state transitions
const int Table[6][6] =
    {
        {1000, 1, -1, 3, 5, 0},
        {-2, -2, 2, -2, -2, -2},
        {1003, 1003, 2, 1003, 1003, 1003},
        {-3, -3, 4, -3, -3, -3},
        {1002, 1002, 4, 1002, 1002, 1002},
        {1001, 1001, 1001, 1001, 1001, 1001}};
// Enum for the token Identifier
enum tokenID
{
    t1_tk,
    t2_tk,
    t3_tk,
    EOF_tk
};
struct token_t
{
    tokenID id;
    std::string name;
    int lineNum;
};

struct inputChar
{
    char c;
    int colNum;
    int lineNum;
};

#endif