#ifndef __LIBRARY_HANDLER_HPP
#define __LIBRARY_HANDLER_HPP

#include "library.hpp"
#include "book.hpp"

class LibraryHandler {
private:
    const char ADMIN_PASSWORD[6]{"admin"}; 
    Library m_library;
    bool m_isAdmin;
    
    //function that clears the input if it is in error state
    std::istream& clearInput(std::istream& is = std::cin) const;

    //helper functions to handle each command
    void handleListAll();
    void handleFind() const;
    void handleAdd();
    void handleRemove();
    void handleShowText() const;
public:
    //default constructor
    LibraryHandler() : m_isAdmin(false), m_library(Library()) {}

    //selector that checks if the current user is admin
    bool isAdmin() const { return m_isAdmin; }

    //mutator that reads the library from a binary file
    void readLibrary();

    //mutator that saves the changes, made to the library, in binary file
    void saveLibrary();

    //mutator that authenticates the user
    void authenticate();

    //the main method of this class that reads the input commands and executes them accordingly
    void readCommands();

    void printListOfCommands() const;
};

#endif