#include "../include/LibraryManager.h"
#include <fstream>
#include <ctime>

LibraryManager::LibraryManager(Logger* logRef) : logger(logRef) { loadBooks(); }

void LibraryManager::logTransaction(std::string user, std::string bookID, std::string action) {
    std::ofstream file(transLog, std::ios::app);
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
    file << "[" << buf << "] " << user << " | " << bookID << " | " << action << "\n";
}

int LibraryManager::findBookIndex(std::string id) {
    for(size_t i=0; i<books.size(); ++i) if(books[i].id == id) return i;
    return -1;
}

void LibraryManager::addBook(std::string id, std::string title, std::string author, int copies) {
    if(findBookIndex(id) != -1) { std::cout << "Book exists.\n"; return; }
    books.push_back({id, title, author, copies, copies});
    saveBooks();
    logger->log("INFO", "Book Added: " + title);
}

void LibraryManager::issueBook(std::string bookID, std::string user) {
    int idx = findBookIndex(bookID);
    if(idx == -1) { std::cout << "Book not found.\n"; return; }
    
    // Exception Requirement
    if(books[idx].availableCopies <= 0) throw NoCopiesException();
    
    books[idx].availableCopies--;
    saveBooks();
    logTransaction(user, bookID, "ISSUED");
    logger->log("INFO", "Book Issued: " + bookID + " to " + user);
    std::cout << "Issued Successfully.\n";
}

void LibraryManager::returnBook(std::string bookID, std::string user) {
    int idx = findBookIndex(bookID);
    if(idx == -1) return;
    
    if(books[idx].availableCopies < books[idx].totalCopies) {
        books[idx].availableCopies++;
        saveBooks();
        logTransaction(user, bookID, "RETURNED");
        logger->log("INFO", "Book Returned: " + bookID);
        std::cout << "Returned Successfully.\n";
    }
}

void LibraryManager::listBooks() {
    for(const auto& b : books) 
        std::cout << b.id << " | " << b.title << " | " << b.availableCopies << "/" << b.totalCopies << "\n";
}

void LibraryManager::saveBooks() {
    std::ofstream f(filename);
    for(const auto& b : books) f << b.id << " " << b.title << " " << b.author << " " << b.totalCopies << " " << b.availableCopies << "\n";
}

void LibraryManager::loadBooks() {
    std::ifstream f(filename); books.clear();
    std::string i, t, a; int tc, ac;
    while(f >> i >> t >> a >> tc >> ac) books.push_back({i, t, a, tc, ac});
}
