/*
Author: Nicholas Hieb
Date Created: 3/05/2025
This is our main file to get input from the user or file and parse the file and output the scanned tokens.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "semantics.h"

void traversePreOrder(node_t *root, char currentLevel, int currentNumLevel);
// Main function to get the input from user or file and scan the file
int main(int argc, char *argv[])
{
    std::string input, output;
    int lineNum = 0;
    FILE *fileptr = NULL;
    node_t *tree = new node_t;

    if (argc == 1)
    {
        // Get input from user
        std::cout << "Keep typeing until 'ctrl + d' is entered to end input: \n";
        while (std::cin >> input)
        {
            output += input + "\n";
        }
        fileptr = fmemopen((void *)output.c_str(), output.size(), "r");
        tree = parser(fileptr);
        checkSemantics(tree);
    }
    else if (argc == 2)
    {
        // Get input from file
        fileptr = fopen(argv[1], "r");
        if (!fileptr)
        {
            std::cerr << "Error: File not found" << std::endl;
            return 1;
        }
        else
        {
            tree = parser(fileptr);
            //traversePreOrder(tree, 'S', 0);
            checkSemantics(tree);
        }
    }
    else
    {
        std::cerr << "Error: Too many arguments" << std::endl;
        return 1;
    }
}

// For pre-order traversal we can use recursion and print before function calls.
// Source: OR3 https://www.w3schools.com/dsa/dsa_algo_binarytrees_preorder.php
void traversePreOrder(node_t *root, char currentCharLevel, int currentNumLevel)
{
    switch (root->level)
    {
    case 'S':
        currentCharLevel = 'S';
        currentNumLevel = 0;
        break;
    case 'A':
        currentCharLevel = 'A';
        currentNumLevel = 1;
        break;
    case 'B':
        currentCharLevel = 'B';
        currentNumLevel = 1;
        break;
    case 'C':
        currentCharLevel = 'C';
        currentNumLevel = 2;
        break;
    case 'D':
        currentCharLevel = 'D';
        currentNumLevel = 2;
        break;
    case 'E':
        currentCharLevel = 'E';
        currentNumLevel = 2;
        break;
    case 'F':
        currentCharLevel = 'F';
        currentNumLevel = 3;
        break;
    case 'G':
        currentCharLevel = 'G';
        currentNumLevel = 2;
        break;
    default:
        break;
    }

    if (root == nullptr)
    {
        printf("Error: Null pointer\n");
        return;
    }
    if (root->child != nullptr)
    {
        if(currentCharLevel == root->level)
        {
            std::cout << std::string(currentNumLevel * 2, ' ') << currentCharLevel << std::endl;
        }
        std::cout << std::string(currentNumLevel * 3, ' ') << root->tkID << " " << root->str << std::endl;
        traversePreOrder(root->child, currentCharLevel, currentNumLevel);
    }
    else
    {
        std::cout << std::string(currentNumLevel * 2, ' ') << currentCharLevel << std::endl;
        std::cout << std::string(currentNumLevel * 3, ' ') << root->tkID << " " << root->str << std::endl;
    }
}