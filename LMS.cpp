#include <iostream>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string status; // Changed to "Available" or "Issued"
};

struct Issue {
    int bookId;
    string studentName;
    string issueDate;
    string returnDate;
};

Book books[100]; // Array to store books
int bookCount = 0; // Count of books in the array
queue<Issue> issueQueue; // Queue to manage book issues

// Function to add a new book
void addBook() {
    if(bookCount >= 100) {
        cout << "Library is full. Cannot add more books." << endl;
        return;
    }

    Book newBook;
    cout << "Enter book ID: ";
    cin >> newBook.id;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    newBook.status = "Available"; // Initialize status as "Available"

    books[bookCount] = newBook;
    bookCount++;
    cout << "Book added successfully." << endl;
}

// Function to search for a book
void searchBook() {
    string searchQuery;
    cout << "Enter book ID or title: ";
    cin.ignore();
    getline(cin, searchQuery);

    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (to_string(books[i].id) == searchQuery || books[i].title == searchQuery) {
            cout << "Book ID: " << books[i].id << endl;
            cout << "Book Title: " << books[i].title << endl;
            cout << "Book Author: " << books[i].author << endl;
            cout << "Book Status: " << books[i].status << endl;
            found = true;
            break; // No need to continue searching
        }
    }

    if (!found) {
        cout << "Book not found." << endl;
    }
}

// Function to issue a book
void issueBook() {
    int id;
    cout << "Enter book ID: ";
    cin >> id;

    for(int i = 0; i < bookCount; i++) {
        if(books[i].id == id && books[i].status == "Available") {
            Issue newIssue;
            newIssue.bookId = id;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, newIssue.studentName);
            cout << "Enter issue date: ";
            getline(cin, newIssue.issueDate);

            books[i].status = "Issued"; // Change status to "Issued"
            issueQueue.push(newIssue);
            cout << "Book issued successfully." << endl;
            return;
        }
    }
    cout << "Book not available or already issued." << endl;
}

// Function to return a book
void returnBook() {
    int id;
    cout << "Enter book ID: ";
    cin >> id;

    for(int i = 0; i < bookCount; i++) {
        if(books[i].id == id && books[i].status == "Issued") {
            Issue issue = issueQueue.front();
            issueQueue.pop();
            books[i].status = "Available"; // Change status back to "Available"
            cout << "Book returned successfully." << endl;
            return;
        }
    }
    cout << "Book not found or not issued." << endl;
}

// Function to delete a book
void deleteBook() {
    int id;
    cout << "Enter book ID: ";
    cin >> id;

    for(int i = 0; i < bookCount; i++) {
        if(books[i].id == id) {
            for(int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            cout << "Book deleted successfully." << endl;
            return;
        }
    }
    cout << "Book not found." << endl;
}

// Function to list all books
bool compareBooks(const Book&book1, const Book& book2) {
    return book1.title < book2.title;
}
// Function to merge two sorted arrays (used in Merge Sort)
void merge(Book arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Book leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (compareBooks(leftArr[i], rightArr[j])) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Function to perform Merge Sort
void mergeSort(Book arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to list all books (sorted by title using Merge Sort)
void listAllBooks() {
    // Sort thehe books using Merge Sort
    mergeSort(books, 0, bookCount - 1);

    cout << "List of all books:" << endl;
    for(int i = 0; i < bookCount; i++) {
        cout << "Book ID: " << books[i].id << endl;
        cout << "Book Title: " << books[i].title << endl;
        cout << "Book Author: " << books[i].author << endl;
        cout << "Book Status: " << books[i].status << endl;
    }
}

// Function to perform Quick Sort

int main() {
    int choice;

    while(true) {
        cout << "Library Management System" << endl;
        cout << "1. Add a new book" << endl;
        cout << "2. Search for a book" << endl;
        cout << "3. Issue a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Delete a book" << endl;
        cout << "6. List all books" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                issueBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                deleteBook();
                break;
            case 6:
                listAllBooks();
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}