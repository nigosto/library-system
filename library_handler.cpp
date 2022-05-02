#include "library_handler.hpp"
#include "library.hpp"
#include "book.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cassert>
#include <limits>
#include <stdio.h>
#include <conio.h>

//THIS CODE IS NOT MINE
//it checks on which platform the program is being run and changes the new line character accordingly
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
char newLine = '\r';
#elif __APPLE__
char newLine = '\r';
#elif __linux__
char newLine = '\n';
#elif __unix__
char newLine = '\n';
#else
#error "Unknown compiler"
#endif

void LibraryHandler::readLibrary()
{
    std::ifstream is{
        "library.bin",
        std::ios::in | std::ios::binary};

    is.seekg(0, std::ios::end);
    std::streampos size = is.tellg() / sizeof(Book);
    is.seekg(0);

    Book *books = new Book[size];
    for (size_t i = 0; i < size; i++)
    {
        is.read(reinterpret_cast<char *>(&books[i]), sizeof(Book));
    }

    m_library = Library(books, size, size);
    delete[] books;
    is.close();
}

void LibraryHandler::saveLibrary()
{
    std::ofstream os{
        "library.bin",
        std::ios::out | std::ios::binary};

    for (size_t i = 0; i < m_library.size(); i++)
    {
        os.write(reinterpret_cast<const char *>(&m_library[i]), sizeof(Book));
    }

    os.close();
}

void LibraryHandler::authenticate()
{
    char answer[4]{'\0'};
    std::cout << "Are you an administrator? (type yes/no): ";
    std::cin.getline(answer, 4);
    while (!std::cin || std::strcmp(answer, "yes") != 0 && std::strcmp(answer, "no") != 0)
    {
        std::cout
            << "Unrecognized answer, please type yes/no again: ";
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.getline(answer, 4);
    }

    if (std::strcmp(answer, "yes") == 0)
    {
        char *password = new char[std::strlen(ADMIN_PASSWORD) + 2]{'\0'};
        std::cout
            << "Please enter your password: ";
        bool overflow = false;
        size_t i = -1;
        do
        {
            i++;
            password[i] = getch();
            if (password[i] != newLine)
            {
                std::cout << '*';
            }
            overflow = false;
            while (i == std::strlen(ADMIN_PASSWORD) && password[i] != newLine)
            {
                overflow = true;
                password[i] = getch();
                if (password[i] != newLine)
                {
                    std::cout << '*';
                }
            }
        } while (password[i] != newLine && i < std::strlen(ADMIN_PASSWORD) + 1);

        std::cout << std::endl;

        while (overflow || std::strncmp(password, ADMIN_PASSWORD, std::strlen(ADMIN_PASSWORD)) != 0)
        {
            for (size_t k = 0; k < std::strlen(ADMIN_PASSWORD) + 1; k++)
            {
                password[k] = '\0';
            }

            std::cout << "Incorrect password! Please try again: ";
            size_t j = -1;
            do
            {
                j++;

                password[j] = getch();
                if (password[j] != newLine)
                {
                    std::cout << '*';
                }
                overflow = false;
                while (j == std::strlen(ADMIN_PASSWORD) && password[j] != newLine)
                {
                    overflow = true;
                    password[j] = getch();
                    if (password[j] != newLine)
                    {
                        std::cout << '*';
                    }
                }
            } while (password[j] != newLine && j < std::strlen(ADMIN_PASSWORD) + 1);

            std::cout << std::endl;
        }

        m_isAdmin = true;
        std::cout << "Welcome back, administrator!" << std::endl;
        delete[] password;
    }
    else
    {
        std::cout << "Welcome!" << std::endl;
    }
}

void LibraryHandler::readCommands()
{
    // m_library.printnl();
    //  TODO
}