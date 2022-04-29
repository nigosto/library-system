#include "book.hpp"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cassert>

constexpr double EPS = 1.0/(1<<30);

Book::Book(const char *_title, const char *_author, const char *_filename, const char *_description, double _rating, const char *_isbn) {
    assert(std::strlen(_title) <= 255 && std::strlen(_author) <= 255 && std::strlen(_filename) <= 255 && std::strlen(_description) <= 1024 && std::strlen(_isbn) == 13 && ((_rating > 1 && _rating < 5) || std::fabs(_rating-1) < EPS || std::fabs(_rating-5) < EPS) && std::strstr(_filename, ".txt") == _filename + std::strlen(_filename) - 4);

    std::strcpy(m_title, _title);
    std::strcpy(m_author, _author);
    std::strcpy(m_filename, _filename);
    std::strcpy(m_description, _description);
    std::strcpy(m_isbn, _isbn);

    m_rating = _rating;
}

void Book::print(std::ostream &os) const {
    os << title() << ' ' << author() << ' ' << description() << ' ' << rating() << ' ' << isbn() << ' ' << filename();
}

void Book::printnl(std::ostream &os) const {
    print(os);
    os << std::endl;
}

void Book::setTitle(const char *_title) {
    assert(std::strlen(_title) <= 255);
    std::strcpy(m_title, _title);
}

void Book::setAuthor(const char *_author) {
    assert(std::strlen(_author) <= 255);
    std::strcpy(m_author, _author);
}

void Book::setFilename(const char *_filename) {
    assert(std::strlen(_filename) <= 255 && std::strstr(_filename, ".txt") == _filename + std::strlen(_filename) - 4);
    std::strcpy(m_filename, _filename);
}

void Book::setDescription(const char *_description) {
    assert(std::strlen(_description) <= 1024);
    std::strcpy(m_description, _description);
}

void Book::setRating(double _rating) {
    assert((_rating > 1 && _rating < 5) || std::fabs(_rating-1) < EPS || std::fabs(_rating-5) < EPS);
    m_rating = _rating;
}

void Book::setIsbn(const char *_isbn) {
    assert(std::strlen(_isbn) == 13);
    std::strcpy(m_isbn, _isbn);
}

std::ostream &operator<<(std::ostream &os, const Book &book) {
    return os << book.title() << ' ' << book.author() << ' ' << book.description() << ' ' << book.rating() << ' ' << book.isbn() << ' ' << book.filename() << std::endl;
}

std::istream &operator>>(std::istream &is, Book &book) {
    char title[MAX_NAMES_SIZE];
    char author[MAX_NAMES_SIZE];
    char filename[MAX_NAMES_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    double rating;
    char isbn[ISBN_LENGTH];

    is.getline(title, MAX_NAMES_SIZE).getline(author, MAX_NAMES_SIZE).getline(filename, MAX_NAMES_SIZE).getline(description, MAX_DESCRIPTION_SIZE) >> rating;
    is.ignore();
    is.getline(isbn, ISBN_LENGTH);

    book = Book(title, author, filename, description, rating, isbn);

    return is;
}