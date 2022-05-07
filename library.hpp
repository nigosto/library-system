#ifndef __LIBRARY_HPP
#define __LIBRARY_HPP

#include <iostream>
#include "book.hpp"

class Library
{
private:
    Book *m_books;
    size_t m_capacity;
    size_t m_size;

    // swap function, needed for the copy assignment
    void swap(Library &other);

    // function that resizes the array of books when there is not enough capacity
    void resize();

public:
    // constructor with default parameters which is used when you want to initialize empty Library or pass an array of Books as argument
    Library(Book *_books = nullptr, size_t _capacity = 0, size_t _size = 0);

    // constructor with only 1 argument - capacity, used when you want to initialize empty Library, but you want to specify its initial capacity
    Library(size_t capacity);

    // copy constructor, destructor and copy assignment (rule of 3)
    Library(const Library &other);
    ~Library();
    Library &operator=(const Library &other);

    // selector for the size
    size_t size() const { return m_size; }

    // selector that checks if the library has no books
    bool empty() const { return size() == 0; }

    //selectors for printing all books of the library on a separate line
    void print(std::ostream &os = std::cout) const;
    void printnl(std::ostream &os = std::cout) const;

    // mutator inserting book
    void insert(const Book &book);

    // mutator that finds a book by its ISBN and removes it from the library (that either includes or excludes its text file)
    void remove(const char *_isbn, bool removeFile = false);

    // mutator that gets a book by its position in the array
    Book &at(size_t position);

    // syntaxis sugar for 'at'
    Book &operator[](size_t position) { return at(position); }

    // mutators that sort the array in ascending order by title, author or rating
    void sortByTitle();
    void sortByAuthor();
    void sortByRating();

    // mutator that reverses the order of the books in the array
    void reverse();

    // mutators that search a book by its name, author or ISBN and returns pointer to that book (or a nullptr if it could not find such book)
    Book *findByTitle(const char* _title);
    Book *findByAuthor(const char* _author, size_t& _size);
    Book *findByISBN(const char* _isbn);

    // mutator that searches a book by part of its Description and returns pointer to that book (or a nullptr if it could not find such book)
    Book *findByDescription(const char* _description);
};

#endif