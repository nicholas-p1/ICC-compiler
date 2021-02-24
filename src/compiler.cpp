#include <iostream>
#include <ast>
#include <stdexcept>

int main()
{
    try {

        // parse the AST
        AST *ast = parseAST();

        // write MIPS assembly to stdout
        ast->compile(std:cout);

    }
    
    // general error catcher
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
