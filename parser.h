#ifndef parser_h
#define parser_h
#include <iostream>
#include <fstream>
#include "scanner.h"
node_t* parser(std::FILE *);
node_t* S(token_t, std::FILE *);
node_t* A(token_t, std::FILE *);
node_t* B(token_t, std::FILE *);
node_t* C(token_t, std::FILE *);
node_t* D(token_t, std::FILE *);
node_t* E(token_t, std::FILE *);
node_t* F(token_t, std::FILE *);
node_t* G(token_t, std::FILE *);
void insert(node_t *&, node_t *);
bool checkArgs(std::string, std::string, std::string);
#endif