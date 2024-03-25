#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class Book
{
private:
    string title;
    string author;
    string ISBN;
    bool available;
    string issuedTo; // Name of the student who issued the book

public:
    Book() {}
    Book(const string &title, const string &author, const string &ISBN)
        : title(title), author(author), ISBN(ISBN), available(true) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    bool isAvailable() const { return available; }
    string getIssuedTo() const { return issuedTo; }
    void setIssuedTo(const string &studentName) { issuedTo = studentName; }
    void setAvailable(bool availability) { available = availability; }
};

class Student
{
private:
    string name;
    int rollNo;
    string branch;
    int year;
    vector<string> issuedBooks; // Vector to store ISBNs of issued books

public:
    Student() {}
    Student(const string &name, int rollNo, const string &branch, int year)
        : name(name), rollNo(rollNo), branch(branch), year(year) {}

    string getName() const { return name; }
    int getRollNo() const { return rollNo; }
    string getBranch() const { return branch; }
    int getYear() const { return year; }

    void issueBook(const string &ISBN)
    {
        issuedBooks.push_back(ISBN);
        cout << "Book with ISBN " << ISBN << " issued to student " << name << ".\n";
    }

    vector<string> getIssuedBooks() const
    {
        return issuedBooks;
    }
};

class Library
{
private:
    vector<Book> books;
    vector<Student> students;

public:
    void addBook(const Book &book)
    {
        books.push_back(book);
        cout << "Book added successfully.\n";
    }

    void addStudent(const Student &student)
    {
        students.push_back(student);
        cout << "Student added successfully.\n";
    }

    void searchBooks(const string &query)
    {
        bool found = false;
        for (const auto &book : books)
        {
            if (book.getTitle() == query || book.getAuthor() == query || book.getISBN() == query)
            {
                cout << "Book found:\n";
                displayBookDetails(book);
                found = true;
            }
        }
        if (!found)
        {
            cout << "Book not found.\n";
        }
    }

    void displayAllBooks()
    {
        if (books.empty())
        {
            cout << "Library is empty.\n";
        }
        else
        {
            cout << "Books available in the library:\n";
            for (const auto &book : books)
            {
                displayBookDetails(book);
            }
        }
    }

    void displayIssuedBooksByStudent(const string &studentName)
    {
        bool found = false;
        for (const auto &student : students)
        {
            if (student.getName() == studentName)
            {
                found = true;
                cout << "Books issued to student " << studentName << ":\n";
                for (const auto &ISBN : student.getIssuedBooks())
                {
                    auto it = find_if(books.begin(), books.end(), [&](const Book &book)
                                      { return book.getISBN() == ISBN; });
                    if (it != books.end())
                    {
                        displayBookDetails(*it);
                    }
                }
                break;
            }
        }
        if (!found)
        {
            cout << "Student not found.\n";
        }
    }

    void checkoutBook(const string &ISBN, const string &studentName)
    {
        auto it = find_if(books.begin(), books.end(), [&](const Book &book)
                          { return book.getISBN() == ISBN && book.isAvailable(); });
        if (it != books.end())
        {
            it->setAvailable(false);
            it->setIssuedTo(studentName);
            for (auto &student : students)
            {
                if (student.getName() == studentName)
                {
                    student.issueBook(ISBN);
                    break;
                }
            }
            cout << "Book checked out successfully to " << studentName << ".\n";
        }
        else
        {
            cout << "Book not available for checkout or not found.\n";
        }
    }

    void returnBook(const string &ISBN)
    {
        auto it = find_if(books.begin(), books.end(), [&](const Book &book)
                          { return book.getISBN() == ISBN && !book.isAvailable(); });
        if (it != books.end())
        {
            it->setAvailable(true);
            it->setIssuedTo(""); // Resetting issuedTo field
            cout << "Book returned successfully.\n";
        }
        else
        {
            cout << "Book not found or already returned.\n";
        }
    }

private:
    void displayBookDetails(const Book &book)
    {
        cout << "Title: " << book.getTitle() << "\n";
        cout << "Author: " << book.getAuthor() << "\n";
        cout << "ISBN: " << book.getISBN() << "\n";
        cout << "Available: " << (book.isAvailable() ? "Yes" : "No") << "\n";
        if (!book.isAvailable())
        {
            cout << "Issued to: " << book.getIssuedTo() << "\n";
        }
        cout << endl;
    }
};

int main()
{
    // Library library;

    // library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565"));
    // library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "9780061120084"));
    // library.addBook(Book("1984", "George Orwell", "9780451524935"));
    // library.addBook(Book("Pride and Prejudice", "Jane Austen", "9780141439518"));
    // library.addBook(Book("The Catcher in the Rye", "J.D. Salinger", "9780316769488"));
    // library.addBook(Book("The Hobbit", "J.R.R. Tolkien", "9780345339683"));
    // library.addBook(Book("The Da Vinci Code", "Dan Brown", "9780307474278"));
    // library.addBook(Book("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", "9780590353427"));
    // library.addBook(Book("The Lord of the Rings", "J.R.R. Tolkien", "9780261102385"));
    // library.addBook(Book("The Alchemist", "Paulo Coelho", "9780061122415"));
    // library.addBook(Book("The Little Prince", "Antoine de Saint-Exupéry", "9780156012195"));

    // library.addStudent(Student("Aarav", 101, "Computer Science", 1));
    // library.addStudent(Student("Aarohi", 102, "Electrical Engineering", 2));
    // library.addStudent(Student("Aisha", 103, "Mechanical Engineering", 3));
    // library.addStudent(Student("Advait", 104, "Civil Engineering", 4));
    // library.addStudent(Student("Aditi", 105, "Chemical Engineering", 1));
    // library.addStudent(Student("Amit", 106, "Computer Science", 2));
    // library.addStudent(Student("Amrita", 107, "Electronics Engineering", 3));
    // library.addStudent(Student("Anaya", 108, "Information Technology", 4));
    // library.addStudent(Student("Aniket", 109, "Computer Science", 1));
    // library.addStudent(Student("Manya", 110, "Electrical Engineering", 2));

    Library library;

    // Open the file containing book data
    ifstream bookFile("books.txt");
    if (!bookFile.is_open())
    {
        cout << "Error opening books file!" << endl;
        return 1;
    }

    // Read book data from file and add to the library
    string title, author, ISBN;
    while (getline(bookFile, title) && getline(bookFile, author) && getline(bookFile, ISBN))
    {
        library.addBook(Book(title, author, ISBN));
    }
    bookFile.close();

    // Open the file containing student data
    ifstream studentFile("students.txt");
    if (!studentFile.is_open())
    {
        cout << "Error opening students file!" << endl;
        return 1;
    }

    // Read student data from file and add to the library
    string name, branch;
    int rollNo, year;
    while (studentFile >> name >> rollNo >> branch >> year)
    {
        library.addStudent(Student(name, rollNo, branch, year));
    }
    studentFile.close();

    int choice;
    string query, studentName;
    do
    {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Search for a book\n";
        cout << "2. Display all books\n";
        cout << "3. Checkout a book\n";
        cout << "4. Return a book\n";
        cout << "5. Display books issued by student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter title, author, or ISBN to search: ";
            cin.ignore();
            getline(cin, query);
            library.searchBooks(query);
            break;
        case 2:
            library.displayAllBooks();
            break;
        case 3:
            cout << "Enter the ISBN of the book to checkout: ";
            cin >> query;
            cout << "Enter the student's name: ";
            cin.ignore();
            getline(cin, studentName);
            library.checkoutBook(query, studentName);
            break;
        case 4:
            cout << "Enter the ISBN of the book to return:";
            cin >> query;
            library.returnBook(query);
            break;
        case 5:
            cout << "Enter the student's name to display issued books: ";
            cin.ignore();
            getline(cin, studentName);
            library.displayIssuedBooksByStudent(studentName);
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
