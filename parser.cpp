/*
Author: Nicholas Hieb
Date Created: 4/05/2025
This is the test file to get tokens.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include "scanner.h"
#include "parser.h"

int tempVarCount = 0;
std::string copyString = "";
int nTimes = 1;
// Function to get tokens from the scanner and print them out
// OR3 and OR1
node_t *parser(std::FILE *input)
{
    token_t tk;
    node_t *node = new node_t;
    // setLookAhead(input);
    tk = scanner(input);
    insert(node, S(tk, input));
    // STOP ASSEMBLY CODE GEN AND SET TEMP VARS TO 0
    printf("STOP\n");
    if (tempVarCount > 0)
    {
        for (int i = 1; i <= tempVarCount; i++)
        {
            printf("temp%d 0\n", i);
        }
    }
    return node;
}
// S will be the start of the parse tree
// OR3
// S -> A ( B B )
node_t *S(token_t tk, std::FILE *input)
{
    // printf("S\n");
    node_t *nodeS = new node_t;
    nodeS->level = 'S';
    insert(nodeS, A(tk, input));
    insert(nodeS, B(tk, input));
    insert(nodeS, B(tk, input));
    return nodeS;
}

node_t *A(token_t tk, std::FILE *input)
{
    node_t *nodeA = new node_t;
    char currentChar = tk.name.back();
    if (currentChar != '(')
    {
        if (currentChar == '"')
        {
            nodeA->str = tk.name;
            nodeA->tkID = tokenNames[tk.id];
            nodeA->lineNum = tk.lineNum;
            nodeA->level = 'A';
            tk = scanner(input);
            insert(nodeA, A(tk, input));
            return nodeA;
        }
        else if (tk.id == t2_tk)
        {
            nodeA->str = tk.name;
            nodeA->tkID = tokenNames[tk.id];
            nodeA->lineNum = tk.lineNum;
            nodeA->isDecl = true;
            nodeA->level = 'A';
            tk = scanner(input);
            insert(nodeA, A(tk, input));
            return nodeA;
        }
        else if (currentChar == '\0') // gets empty token but does not currently work since our lookahead
        {
            nodeA->str = "Empty";
            nodeA->tkID = tokenNames[tk.id];
            nodeA->lineNum = tk.lineNum;
            nodeA->level = 'A';
            setLookAhead(input);
            tk = scanner(input);
            insert(nodeA, A(tk, input));
            return nodeA;
        }
        else
        {
            printf("Error: Invalid character in A\n");
            exit(1);
        }
    }
    else
    {
        node_t *nodeIN = new node_t;
        nodeIN->str = "(";
        nodeIN->tkID = tokenNames[tk.id];
        nodeIN->lineNum = tk.lineNum;
        nodeIN->level = 'A';
        insert(nodeA, nodeIN);
        return nodeA;
    }
    return nodeA;
}

node_t *B(token_t tk, std::FILE *input)
{
    tk = scanner(input);
    node_t *nodeB = new node_t;
    nodeB->level = 'B';
    char currentChar = tk.name.back();
    if (currentChar == '"' || currentChar == '\0')
    {
        insert(nodeB, S(tk, input));
        return nodeB;
    }
    else if (currentChar == '#' || currentChar == '!')
    {
        insert(nodeB, C(tk, input));
        return nodeB;
    }
    else if (currentChar == '$')
    {
        insert(nodeB, D(tk, input));
        return nodeB;
    }
    else if (currentChar == 39) //'
    {
        insert(nodeB, E(tk, input));
        return nodeB;
    }
    else if (tk.id == t2_tk)
    {
        insert(nodeB, G(tk, input));
        return nodeB;
    }
    else if (currentChar == '(')
    {
        insert(nodeB, S(tk, input));
        return nodeB;
    }
    else if (currentChar == ')')
    {
        node_t *nodeIN = new node_t;
        nodeIN->str = ")";
        nodeIN->tkID = tokenNames[tk.id];
        nodeIN->lineNum = tk.lineNum;
        nodeIN->level = 'A';
        insert(nodeB, nodeIN);
        insert(nodeB, B(tk, input));
        return nodeB;
    }
    else
    {
        perror("Invalid in B");
        exit(1);
    }
}
node_t *C(token_t tk, std::FILE *input)
{
    node_t *nodeC = new node_t;
    nodeC->str = tk.name;
    nodeC->tkID = tokenNames[tk.id];
    nodeC->lineNum = tk.lineNum;
    nodeC->level = 'C';
    char currentChar = tk.name.back();
    if (currentChar == '#')
    {
        tk = scanner(input);

        // Allocate memory for the identifier, read in a number, and assign the value to the identifier [ASSEMBLY CODE]
        std::string temp = tk.name;
        temp.at(0) = 'X';
        for (int i = 0; i < nTimes; i++)
        {
            tempVarCount += 1;
            printf("READ temp%d\n", tempVarCount);
            printf("COPY %s temp%d\n", temp.c_str(), tempVarCount);
        }
        nTimes = 1;

        insert(nodeC, C(tk, input));
        return nodeC;
    }
    else if (currentChar == '!')
    {
        tk = scanner(input);

        // Negates the following argument [ASSEMBLY CODE]
        std::string temp = tk.name;
        temp.at(0) = 'X';
        for (int i = 0; i < nTimes; i++)
        {
            printf("LOAD %s\n", temp.c_str());
            printf("MULT -1\n");
            printf("STORE %s\n", temp.c_str());
        }
        nTimes = 1;

        insert(nodeC, F(tk, input));
        return nodeC;
    }
    else if (tk.id == t2_tk)
    {
        nodeC->isDecl = true;
        return nodeC;
    }
    else
    {
        perror("Error in C");
        exit(1);
    }
}
node_t *D(token_t tk, std::FILE *input)
{
    node_t *nodeD = new node_t;
    nodeD->str = tk.name;
    nodeD->tkID = tokenNames[tk.id];
    nodeD->lineNum = tk.lineNum;
    nodeD->level = 'D';
    char currentChar = tk.name.back();
    if (currentChar == '$')
    {
        tk = scanner(input);

        // Print out the value of the identifier or immediate number to the screen [ASSEMBLY CODE]
        if (tk.id == t2_tk)
        {
            std::string temp = tk.name;
            temp.at(0) = 'X';
            for (int i = 0; i < nTimes; i++)
            {
                printf("WRITE %s\n", temp.c_str());
            }
        }
        else if (tk.id == t3_tk)
        {
            std::string temp = "";
            temp.insert(0, tk.name, 1);
            for (int i = 0; i < nTimes; i++)
            {
                printf("WRITE %s\n", temp.c_str());
            }
        }
        nTimes = 1;

        insert(nodeD, F(tk, input));
        return nodeD;
    }
    else
    {
        perror("Error in D");
        exit(1);
    }
}
node_t *E(token_t tk, std::FILE *input)
{
    node_t *nodeE = new node_t;
    nodeE->str = tk.name;
    nodeE->tkID = tokenNames[tk.id];
    nodeE->lineNum = tk.lineNum;
    nodeE->level = 'E';
    char currentChar = tk.name.back();
    if (currentChar == 39)
    {
        // If the first argument is strictly greater than the second argument
        // Repeat the fourth argument n times, where n is the third argument
        // [ASSEMBLY CODE]
        std::string firstArg = "";
        std::string secondArg = "";
        std::string thirdArg = "";
        tk = scanner(input);

        // First Arg [ASSEMBLY CODE]
        char tempChar = tk.name.at(0);
        firstArg.insert(0, tk.name, 1);
        if (islower(tempChar))
            firstArg.insert(0, 1, '-');

        insert(nodeE, F(tk, input));
        tk = scanner(input);

        // Second Arg [ASSEMBLY CODE]
        tempChar = tk.name.at(0);
        secondArg.insert(0, tk.name, 1);
        if (islower(tempChar))
            secondArg.insert(0, 1, '-');

        insert(nodeE, F(tk, input));
        tk = scanner(input);

        // Third Arg [ASSEMBLY CODE]
        tempChar = tk.name.at(0);
        thirdArg.insert(0, tk.name, 1);
        if (islower(tempChar))
            thirdArg.insert(0, 1, '-');

        insert(nodeE, F(tk, input));

        // Run check to see if we run arg n times [ASSEMBLY CODE]
        if(checkArgs(firstArg, secondArg, thirdArg) == true)
        {
            nTimes = std::atoi(thirdArg.c_str());
        }
        insert(nodeE, B(tk, input));
        return nodeE;
    }
    else
    {
        perror("Error in E");
        exit(1);
    }
}
node_t *F(token_t tk, std::FILE *input)
{
    node_t *nodeF = new node_t;
    nodeF->str = tk.name;
    nodeF->tkID = tokenNames[tk.id];
    nodeF->lineNum = tk.lineNum;
    nodeF->level = 'F';
    char currentChar = tk.name.back();
    if (tk.id == t2_tk || tk.id == t3_tk)
    {
        return nodeF;
    }
    else if (currentChar == '&') // Addition operator
    {
        tk = scanner(input);

        // [ASSEMBLY CODE]
        std::string temp = tk.name;
        temp.at(0) = 'X';

        insert(nodeF, F(tk, input));
        tk = scanner(input);

        // Addition or subtraction [ASSEMBLY CODE]
        std::string tempNumStr = "";
        char tempChar = tk.name.at(0);
        tempNumStr.insert(0, tk.name, 1);
        if (isupper(tempChar)) // Positive
        {
            for (int i = 0; i < nTimes; i++)
            {
                printf("LOAD %s\n", temp.c_str());
                printf("ADD %s\n", tempNumStr.c_str());
                printf("STORE %s\n", temp.c_str());
            }
        }
        else if (islower(tempChar)) // Negative
        {
            for (int i = 0; i < nTimes; i++)
            {
                printf("LOAD %s\n", temp.c_str());
                printf("SUB %s\n", tempNumStr.c_str());
                printf("STORE %s\n", temp.c_str());
            }
        }
        nTimes = 1;

        insert(nodeF, F(tk, input));
        return nodeF;
    }
    else
    {
        perror("Error in F");
        exit(1);
    }
}
node_t *G(token_t tk, std::FILE *input)
{
    node_t *nodeG = new node_t;
    nodeG->str = tk.name;
    nodeG->tkID = tokenNames[tk.id];
    nodeG->lineNum = tk.lineNum;
    nodeG->level = 'G';
    char currentChar = tk.name.back();
    if (tk.id == t2_tk)
    {
        copyString = tk.name;
        copyString.at(0) = 'X';
        tk = scanner(input);
        insert(nodeG, G(tk, input));
        return nodeG;
    }
    else if (currentChar == '%')
    {
        tk = scanner(input);

        // Assignment operator [ASSEMBLY CODE]
        char tempChar = tk.name.at(0);
        std::string tempStr = "";
        tempStr.insert(0, tk.name, 1);
        if (isupper(tempChar)) // positive int
        {
            for (int i = 0; i < nTimes; i++)
            {
                printf("LOAD %s\n", tempStr.c_str());
                printf("STORE %s\n", copyString.c_str());
            }
        }
        else if (islower(tempChar)) // negative int
        {
            for (int i = 0; i < nTimes; i++)
            {
                printf("LOAD -%s\n", tempStr.c_str());
                printf("STORE %s\n", copyString.c_str());
            }
        }
        nTimes = 1;

        insert(nodeG, F(tk, input));
        return nodeG;
    }
    else
    {
        perror("Invalid in G");
        exit(1);
    }
}
// inserting the node into the tree in the correct order with only one child
void insert(node_t *&node, node_t *newNode)
{
    if (node == nullptr)
    {
        node = newNode;
    }
    else
    {
        insert(node->child, newNode);
    }
}

bool checkArgs(std::string firstArg, std::string secondArg, std::string thirdArg)
{
    int num1 = std::atoi(firstArg.c_str());
    int num2 = std::atoi(secondArg.c_str());
    int num3 = std::atoi(thirdArg.c_str());

    if (num1 > num2)
        return true;
    else
        return false;
}