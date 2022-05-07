#ifndef __BOOK_HPP
#define __BOOK_HPP

#include <iostream>

constexpr size_t MAX_NAMES_SIZE{256};
constexpr size_t MAX_DESCRIPTION_SIZE{1025};
constexpr size_t ISBN_LENGTH{14};
constexpr double EPS = 1.0 / (1 << 30);

class Book
{
private:
    // every char array is static in order to be stored in binary files correctly
    char m_title[MAX_NAMES_SIZE];
    char m_author[MAX_NAMES_SIZE];

    // filename must end in ".txt"
    char m_filename[MAX_NAMES_SIZE];
    char m_description[MAX_DESCRIPTION_SIZE];

    // rating scale from 1 to 5
    double m_rating;

    // stores exactly 13 digits and it can have 0s at the start
    char m_isbn[ISBN_LENGTH];

    char* extractText() const;
public:
    // constructor with default parameters
    Book(const char *_title = "<unknown>", const char *_author = "<unknown>", const char *_filename = "unknown.txt", const char *_description = "No description", double _rating = 1, const char *_isbn = "0000000000000");

    // selectors for member variables
    const char *title() const { return m_title; }
    const char *author() const { return m_author; }
    const char *filename() const { return m_filename; }
    const char *description() const { return m_description; }
    double rating() const { return m_rating; }
    const char *isbn() const { return m_isbn; }

    // selectors for output
    void print(std::ostream &os = std::cout) const;
    void printnl(std::ostream &os = std::cout) const;

    //selectors that output the text of the book from its corresponding file
    void showTextByPages(size_t rows) const;
    void showTextBySentences() const;

    // mutators for setting member variables
    void setTitle(const char *_title);
    void setAuthor(const char *_author);
    void setFilename(const char *_filename);
    void setDescription(const char *_description);
    void setRating(double _rating);
    void setIsbn(const char *_isbn);

    // friend function predefinig the operator for stream input
    friend std::istream &operator>>(std::istream &is, Book &book);
};

//predefining the operator for stream output 
std::ostream &operator<<(std::ostream &os, const Book &book);

#endif