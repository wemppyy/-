#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#define LOG_OPERATION(operation, book) { \
    std::ofstream logFile("library.log", std::ios::app); \
    if (logFile.is_open()) { \
        logFile << operation << ": " << (book).getTitle() << " by " << (book).getAuthor() << std::endl; \
        logFile.close(); \
    } \
}

#define FIND_BOOK_BY_AUTHOR(manager, author) { \
    bool found = false; \
    for (const auto& book : manager.getBooks()) { \
        if (book.getAuthor() == author) { \
            std::cout << "Found: " << book.getTitle() << " by " << book.getAuthor() << std::endl; \
            found = true; \
        } \
    } \
    if (!found) { \
        std::cout << "No books found by " << author << std::endl; \
    } \
}

namespace Library {
    class Book {
    private:
        std::string title;
        std::string author;
        int year;
        std::string genre;

    public:
        Book(std::string t, std::string a, int y, std::string g)
            : title(t), author(a), year(y), genre(g) {}

        void setTitle(const std::string& t) { title = t; }
        std::string getTitle() const { return title; }

        void setAuthor(const std::string& a) { author = a; }
        std::string getAuthor() const { return author; }

        void setYear(int y) { year = y; }
        int getYear() const { return year; }

        void setGenre(const std::string& g) { genre = g; }
        std::string getGenre() const { return genre; }

        void changeYear(int newYear) { year = newYear; }
    };
}

namespace Management {
    class LibraryManager {
    private:
        std::vector<Library::Book> books;

    public:
        void addBook(const Library::Book& book) {
            books.push_back(book);
            LOG_OPERATION("Added", book);
        }

        void removeBook(const std::string& title) {
            auto it = std::remove_if(books.begin(), books.end(),
                        [&title](const Library::Book& b) { return b.getTitle() == title; });
            if (it != books.end()) {
                LOG_OPERATION("Removed", *it);
                books.erase(it, books.end());
            }
        }

        Library::Book* searchBook(const std::string& title) {
            for (auto& book : books) {
                if (book.getTitle() == title) {
                    return &book;
                }
            }
            return nullptr;
        }

        void listBooks() const {
            for (const auto& book : books) {
                std::cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor()
                          << ", Year: " << book.getYear() << ", Genre: " << book.getGenre() << std::endl;
            }
        }

        void sortByTitle() {
            std::sort(books.begin(), books.end(), [](const Library::Book& a, const Library::Book& b) {
                return a.getTitle() < b.getTitle();
            });
        }

        void sortByAuthor() {
            std::sort(books.begin(), books.end(), [](const Library::Book& a, const Library::Book& b) {
                return a.getAuthor() < b.getAuthor();
            });
        }

        void sortByYear() {
            std::sort(books.begin(), books.end(), [](const Library::Book& a, const Library::Book& b) {
                return a.getYear() < b.getYear();
            });
        }

        std::vector<Library::Book>& getBooks() {
            return books;
        }
    };
}

int main() {
    Management::LibraryManager libraryManager;

    Library::Book book1("1984", "George Orwell", 1949, "Dystopian");
    Library::Book book2("The Great Gatsby", "F. Scott Fitzgerald", 1925, "Classic");
    Library::Book book3("To Kill a Mockingbird", "Harper Lee", 1960, "Fiction");

    libraryManager.addBook(book1);
    libraryManager.addBook(book2);
    libraryManager.addBook(book3);

    std::cout << "Books in the library:\n";
    libraryManager.listBooks();

    std::cout << "\nSorted by author:\n";
    libraryManager.sortByAuthor();
    libraryManager.listBooks();

    std::cout << "\nSorted by title:\n";
    libraryManager.sortByTitle();
    libraryManager.listBooks();

    std::cout << "\nSorted by year:\n";
    libraryManager.sortByYear();
    libraryManager.listBooks();

    std::cout << "\nRemoving 'The Great Gatsby' from the library.\n";
    libraryManager.removeBook("The Great Gatsby");

    std::cout << "\nBooks in the library after removal:\n";
    libraryManager.listBooks();

    std::cout << "\nSearching for books by 'Harper Lee':\n";
    FIND_BOOK_BY_AUTHOR(libraryManager, "Harper Lee");

    return 0;
}
