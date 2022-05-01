#include "library_handler.hpp"
#include "library.hpp"
#include "book.hpp"
#include <fstream>

void LibraryHandler::readLibrary()
{
    std::ifstream is {
        "library.bin",
        std::ios::in | std::ios::binary
    };

    is.seekg(0, std::ios::end);
    std::streampos size = is.tellg() / sizeof(Book);
    is.seekg(0);

    Book* books = new Book[size];
    for (size_t i = 0; i < size; i++)
    {
        is.read(reinterpret_cast<char*>(&books[i]), sizeof(Book));
    }

    m_library = Library(books, size, size);
    delete[] books;
    is.close();
}

void LibraryHandler::saveLibrary()
{
    std::ofstream os {
        "library.bin",
        std::ios::out | std::ios::binary
    };

    for (size_t i = 0; i < m_library.size(); i++)
    {
        os.write(reinterpret_cast<const char*>(&m_library[i]), sizeof(Book));
    }

    os.close();
}

void LibraryHandler::authenticate()
{
    //TODO
}

void LibraryHandler::readCommands()
{
    m_library.printnl();
    //TODO
}