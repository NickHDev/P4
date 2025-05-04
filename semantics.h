/*
Author: Nicholas Hieb
Date Created: 4/20/2025
This is our semantics header file to create our symbol table and its logic to insert, verify, and print the symbol table
*/
#ifndef SEMANTICS_H
#define SEMANTICS_H

#include <set>
#include <string>
#include <iostream>
#include "node.h"
#include "token.h"

class SymbolTable
{
private:
    std::set<std::string> table;

public:
    // Checks if the varible has already been inserted and if not insert it
    // OR5
    void insert(const node_t *node)
    {

        if (table.count(node->str))
        {
            exit(1);
        }
        else
        {
            table.insert(node->str);
        }
    }
    // This checks if our variable has been declared in the table
    // OR5
    void verify(const node_t *node)
    {

        if (!table.count(node->str))
        {
            std::cerr << "Semantic Error: Undefined variable -> " << node->str
                      << " (line " << node->lineNum << ")\n";
            exit(1);
        }
    }
    // Print the table
    // OR4 and OR5
    void print() const
    {
        std::cout << "\nSymbol Table:\n";
        for (const auto &var : table)
        {
            std::cout << var << std::endl;
        }
    }
};

void checkSemantics(node_t *root);

#endif
