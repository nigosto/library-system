#include "library.hpp"
#include "book.hpp"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

void toLowerCase(char *str)
{
    for (size_t i = 0; i < std::strlen(str); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] += 'a' - 'A';
        }
    }
}

void Library::swap(Library &other)
{
    std::swap(m_books, other.m_books);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_size, other.m_size);
}

void Library::resize()
{
    size_t newCapacity = m_capacity + m_capacity / 2;
    if (newCapacity <= 1)
    {
        newCapacity = 2;
    }
    Book *newBooks = new Book[newCapacity];
    for (size_t i = 0; i < m_size; i++)
    {
        newBooks[i] = m_books[i];
    }
    m_capacity = newCapacity;
    delete[] m_books;
    m_books = newBooks;
}

Library::Library(Book *_books, size_t _capacity, size_t _size) : m_capacity(_capacity), m_size(_size), m_books(new Book[_capacity])
{
    for (size_t i = 0; i < _size; i++)
    {
        m_books[i] = _books[i];
    }
}

Library::Library(size_t capacity) : m_capacity(capacity), m_books(new Book[capacity]), m_size(0) {}

Library::Library(const Library &other) : m_capacity(other.m_capacity), m_size(other.m_size), m_books(new Book[other.m_capacity])
{
    for (size_t i = 0; i < other.m_size; i++)
    {
        m_books[i] = other.m_books[i];
    }
}

Library::~Library()
{
    delete[] m_books;
}

Library &Library::operator=(const Library &other)
{
    Library copy(other);
    swap(copy);
    return *this;
}

void Library::insert(const Book &book)
{
    if (m_size >= m_capacity)
    {
        resize();
    }
    m_books[m_size++] = book;
}

void Library::remove(const char *_isbn, bool removeFile)
{
    // TODO
}

Book &Library::at(size_t position)
{
    assert(position < m_size);
    return m_books[position];
}

void Library::sortByTitle()
{
    for (size_t i = 0; i < m_size - 1; i++)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < m_size; j++)
        {
            if (std::strcmp(m_books[j].title(), m_books[minIndex].title()) < 0)
            {
                minIndex = j;
            }
        }
        std::swap(m_books[minIndex], m_books[i]);
    }
}

void Library::sortByAuthor()
{
    for (size_t i = 0; i < m_size - 1; i++)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < m_size; j++)
        {
            if (std::strcmp(m_books[j].author(), m_books[minIndex].author()) < 0)
            {
                minIndex = j;
            }
        }
        std::swap(m_books[minIndex], m_books[i]);
    }
}

void Library::sortByRating()
{
    for (size_t i = 0; i < m_size - 1; i++)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < m_size; j++)
        {
            if (m_books[j].rating() < m_books[minIndex].rating())
            {
                minIndex = j;
            }
        }
        std::swap(m_books[minIndex], m_books[i]);
    }
}

void Library::reverse()
{
    std::reverse(m_books, m_books + m_size);
}

Book *Library::findByTitle(const char *_title)
{
    char *_titleCopy = new char[std::strlen(_title) + 1]{'\0'};
    std::strcpy(_titleCopy, _title);
    toLowerCase(_titleCopy);
    for (size_t i = 0; i < m_size; i++)
    {
        char title[MAX_NAMES_SIZE]{'\0'};
        std::strcpy(title, m_books[i].title());
        toLowerCase(title);
        if (std::strcmp(title, _titleCopy) == 0)
        {
            return &m_books[i];
        }
    }
    delete[] _titleCopy;
    return nullptr;
}

Book *Library::findByAuthor(const char *_author)
{
    char *_authorCopy = new char[std::strlen(_author) + 1]{'\0'};
    std::strcpy(_authorCopy, _author);
    toLowerCase(_authorCopy);
    for (size_t i = 0; i < m_size; i++)
    {
        char author[MAX_NAMES_SIZE]{'\0'};
        std::strcpy(author, m_books[i].author());
        toLowerCase(author);
        if (std::strcmp(author, _authorCopy) == 0)
        {
            return &m_books[i];
        }
    }
    delete[] _authorCopy;
    return nullptr;
}

Book *Library::findByISBN(const char *_isbn)
{
    for (size_t i = 0; i < m_size; i++)
    {
        if (std::strcmp(m_books[i].isbn(), _isbn) == 0)
        {
            return &m_books[i];
        }
    }
    return nullptr;
}

Book *Library::findByDescription(const char *_description)
{
    char *_descriptionCopy = new char[std::strlen(_description) + 1]{'\0'};
    std::strcpy(_descriptionCopy, _description);
    toLowerCase(_descriptionCopy);
    for (size_t i = 0; i < m_size; i++)
    {
        char description[MAX_DESCRIPTION_SIZE]{'\0'};
        std::strcpy(description, m_books[i].description());
        toLowerCase(description);
        if (std::strstr(description, _descriptionCopy))
        {
            return &m_books[i];
        }
    }
    delete[] _descriptionCopy;
    return nullptr;
}

void Library::print(std::ostream &os) const
{
    for (size_t i = 0; i < m_size-1; i++)
    {
        m_books[i].printnl(os);
    }
    m_books[m_size-1].print(os);
}

void Library::printnl(std::ostream &os) const {
    print(os);
    os<<std::endl;
}