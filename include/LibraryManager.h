#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H
#include <vector>
#include <string>
#include <iostream>
#include "Logger.h"

// Custom Exception for Library
class NoCopiesException : public std::exception {
public:
    const char* what() const noexcept override { return "Error: No copies available for this book."; }
};

struct Book {
    std::string id, title, author;
    int totalCopies, availableCopies;
};

class LibraryManager {
private:
    std::vector<Book> books;
    std::string filename = "../data/books.txt";
    std::string transLog = "../logs/transaction.log";
    Logger* logger;
    
    void logTransaction(std::string user, std::string bookID, std::string action);
    int findBookIndex(std::string id);
    
public:
    LibraryManager(Logger* logRef);
    void addBook(std::string id, std::string title, std::string author, int copies);
    void issueBook(std::string bookID, std::string user);
    void returnBook(std::string bookID, std::string user);
    void listBooks();
    void saveBooks();
    void loadBooks();
};
#endif
