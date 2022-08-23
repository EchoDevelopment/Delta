#include <iostream>

#include "lexer/lexer.h"
#include "tree/grow.h"
#include "util.h"

int main(void)
{
    try
    {
        std::vector<Token> x = lex(growLexMap("lex.tree"), readFile("test.txt"));
        for (auto token : x)
        {
            std::cout << token.type << ", " << token.value << std::endl;
        }
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    
}