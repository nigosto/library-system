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
            if (password[i] != '\r')
            {
                std::cout << '*';
            }
            overflow = false;
            while (i == std::strlen(ADMIN_PASSWORD) && password[i] != '\r')
            {
                overflow = true;
                password[i] = getch();
                if (password[i] != '\r')
                {
                    std::cout << '*';
                }
            }
        } while (password[i] != '\r' && i < std::strlen(ADMIN_PASSWORD) + 1);

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
                if (password[j] != '\r')
                {
                    std::cout << '*';
                }
                overflow = false;
                while (j == std::strlen(ADMIN_PASSWORD) && password[j] != '\r')
                {
                    overflow = true;
                    password[j] = getch();
                    if (password[j] != '\r')
                    {
                        std::cout << '*';
                    }
                }
            } while (password[j] != '\r' && j < std::strlen(ADMIN_PASSWORD) + 1);

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
    char command[10]{'\0'};
    do
    {
        std::cout << "Enter command: ";
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.getline(command, 10);

        if (std::strcmp(command, "LIST ALL") == 0)
        {
            std::cout << "Choose criteria of sorting (title, author, rating): ";

            char criteria[7]{'\0'};
            if (!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cin.getline(criteria, 7);

            while (std::strcmp(criteria, "title") && std::strcmp(criteria, "author") && std::strcmp(criteria, "rating"))
            {
                std::cout << "Unrecognized criteria! Please enter again: ";
                if (!std::cin)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::cin.getline(criteria, 7);
            }

            if (std::strcmp(criteria, "title") == 0)
            {
                m_library.sortByTitle();
            }
            else if (std::strcmp(criteria, "author") == 0)
            {
                m_library.sortByAuthor();
            }
            else if (std::strcmp(criteria, "rating") == 0)
            {
                m_library.sortByRating();
            }

            std::cout << "Choose sorting order (ascending/descending): ";
            char order[11]{'\0'};

            if (!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cin.getline(order, 11);

            while (std::strcmp(order, "ascending") && std::strcmp(order, "descending"))
            {
                std::cout << "Unrecognized order! Please enter again: ";
                if (!std::cin)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::cin.getline(order, 11);
            }

            if (std::strcmp(order, "descending") == 0)
            {
                m_library.reverse();
            }
            std::cout << "---------------------" << std::endl;
            m_library.printnl();
            std::cout << "---------------------" << std::endl;
        }
        else if (std::strcmp(command, "FIND") == 0)
        {
            std::cout << "Choose search criteria (title, author, ISBN, description): ";

            char criteria[12]{'\0'};
            if (!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cin.getline(criteria, 12);

            while (std::strcmp(criteria, "title") && std::strcmp(criteria, "author") && std::strcmp(criteria, "ISBN") && std::strcmp(criteria, "description"))
            {
                std::cout << "Unrecognized criteria! Please enter again: ";
                if (!std::cin)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::cin.getline(criteria, 12);
            }

            std::cout << "Search: ";
            char param[MAX_DESCRIPTION_SIZE]{'\0'};

            if (!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cin.getline(param, MAX_DESCRIPTION_SIZE);

            if (std::strcmp(criteria, "title") == 0)
            {
                if (m_library.findByTitle(param))
                {
                    std::cout << "---------------------" << std::endl;
                    std::cout << *(m_library.findByTitle(param)) << std::endl;
                    std::cout << "---------------------" << std::endl;
                }
                else
                {
                    std::cout << "Could't find book!" << std::endl;
                }
            }
            else if (std::strcmp(criteria, "author") == 0)
            {
                if (m_library.findByAuthor(param))
                {
                    std::cout << "---------------------" << std::endl;
                    std::cout << *(m_library.findByAuthor(param)) << std::endl;
                    std::cout << "---------------------" << std::endl;
                }
                else
                {
                    std::cout << "Could't find book!" << std::endl;
                }
            }
            else if (std::strcmp(criteria, "ISBN") == 0)
            {
                if (m_library.findByISBN(param))
                {
                    std::cout << "---------------------" << std::endl;
                    std::cout << *(m_library.findByISBN(param)) << std::endl;
                    std::cout << "---------------------" << std::endl;
                }
                else
                {
                    std::cout << "Could't find book!" << std::endl;
                }
            }
            else if (std::strcmp(criteria, "description") == 0)
            {
                if (m_library.findByDescription(param))
                {
                    std::cout << "---------------------" << std::endl;
                    std::cout << *(m_library.findByDescription(param)) << std::endl;
                    std::cout << "---------------------" << std::endl;
                }
                else
                {
                    std::cout << "Could't find book!" << std::endl;
                }
            }
        } else if (std::strcmp(command, "ADD") == 0 && m_isAdmin) {
            //TODO
        } else if (std::strcmp(command, "REMOVE") == 0 && m_isAdmin) {
            //TODO
        } else if(std::strcmp(command, "SHOW TEXT") == 0 && std::cin) {
            //TODO
        } else if(std::strcmp(command, "END")) {
            std::cout<<"Unrecognized command!"<<std::endl;
        }
    } while (std::strcmp(command, "END"));
}

void LibraryHandler::printListOfCommands() const
{
    std::cout << "---------------------" << std::endl;
    std::cout << "List of commands:" << std::endl;
    std::cout << "1. LIST ALL" << std::endl;
    std::cout << "2. FIND" << std::endl;
    std::cout << "3. SHOW TEXT" << std::endl;
    if (m_isAdmin)
    {
        std::cout << "4. ADD" << std::endl;
        std::cout << "5. REMOVE" << std::endl;
        std::cout << "6. EXIT" << std::endl;
    }
    else
    {
        std::cout << "4. EXIT" << std::endl;
    }
    std::cout << "---------------------" << std::endl;
}