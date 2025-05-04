/*
Author: Nicholas Hieb
Date Created: 4/20/2025
This is our semantics file to traverse our grammar and only allow certain variable declarations
*/
#include "semantics.h"
static SymbolTable symTable;
// Traverse tree and process variable usage
void traverse(node_t *node)
{
    if (!node)
        return;

    // Check if it's a variable (t2)
    if (node->tkID == "t2")
    {
        if (node->isDecl)
        {
            symTable.insert(node); // Declaration of variable
            std::string temp = node->str;
            temp.at(0) = 'X';
            printf("%s 0\n", temp.c_str());
        }
        else
        {
            symTable.verify(node); // verify variable has been declared
        }
    }

    // Move through children
    traverse(node->child);
}

void checkSemantics(node_t *root)
{
    traverse(root);
    //symTable.print();
}
