#include <iostream>
#include <fstream>
#include "book.hpp"
#include "library.hpp"
#include "library_handler.hpp"

int main() {
    LibraryHandler handler;

    handler.authenticate();
    handler.printListOfCommands();
    handler.readLibrary();

    handler.readCommands();

    handler.saveLibrary();
    
    return 0;
}