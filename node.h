#ifndef node_h
#define node_h
#include <string>
struct node_t
{
    std::string str;
    std::string tkID;
    bool isDecl;
    int lineNum;
    char level;
    node_t *child;
};
#endif
