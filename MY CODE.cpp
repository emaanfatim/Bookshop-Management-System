#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits> // Include for numeric_limits
using namespace std;
// Global variables
string book_ID[20], book_name[20], book_author[20];
int book_pr[20];
int total = 0;
// User data structure
struct User {
    string username;
    string password;
};
// Map to store users
map<string, User> users;

// Function to register a new user
void registerUser() {
    User newUser;
    cout << "Enter username: ";
    cin >> newUser.username;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter password: ";
    cin >> newUser.password;
    if (users.find(newUser.username) == users.end()) {
        users[newUser.username] = newUser;
        cout << "User registered successfully." << endl;
    }
    else {
        cout << "Username already exists. Please choose another username." << endl;
    }
}

// Function to authenticate a user
bool authenticateUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Clear input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Check if username exists and password matches
    if (users.find(username) != users.end() && users[username].password == password) {
        cout << "Login successful. Welcome, " << username << "!" << endl;
        return true;
    }
    else {
        cout << "Invalid username or password. Please try again." << endl;
        return false;
    }
}


// Function for displaying book data
void showdata() {
    ifstream rfile("books.txt");
    int i = 0;
    total = 0;
    if (rfile.is_open()) {
        while (rfile >> book_name[i] >> book_author[i] >> book_ID[i] >> book_pr[i]) {
            i++;
            total++;
        }
    }
    for (int i = 0; i < total; i++) {
        cout << "\t\tThe detail of book\t" << i + 1 << "\n\n";
        cout << "\tBook ID:\t";
        cout << book_ID[i] << endl;
        cout << "\tBook Author:\t";
        cout << book_author[i] << endl;
        cout << "\tBook Price:\t";
        cout << book_pr[i] << endl;
        cout << "\tBook Name:\t";
        cout << book_name[i] << endl;
        cout << "\n\n";
    }
}

// Function for adding books
void addbook() {
    int ch = 0;
    fstream upfile("books.txt", ios::out | ios::app);
    cout << "Enter number of books you want to add: ";
    cin >> ch;
    if (total != 0) {
        total = total + ch;
        for (int i = total - ch; i < total; i++) {
            cout << "\t\tEnter the detail of book\n\n";
            cout << "\tBook Name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, book_name[i]);
            cout << "\tBook ID: ";
            cin >> book_ID[i];
            cout << endl; // Ensure book ID and author are displayed on separate lines
            cout << "\tEnter book author: ";
            cin.ignore(); // Clear input buffer
            getline(cin, book_author[i]); // Allowing spaces in author name
            cout << endl; // Clearing input buffer
            cout << "\tEnter book price: ";
            cin >> book_pr[i];
            cout << endl; // Clearing input buffer
            upfile << book_name[i] << "\t" << book_author[i] << "\t" << book_ID[i] << "\t" << book_pr[i] << "\n";
        }
    }
    else {
        for (int i = 0; i < ch; i++) {
            cout << "\t\tEnter the detail of book\n\n";
            cout << "\tBook Name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, book_name[i]);
            cout << "\tBook ID: ";
            cin >> book_ID[i];
            cout << endl; // Ensure book ID and author are displayed on separate lines
            cout << "\tEnter book author: ";
            cin.ignore(); // Clear input buffer
            getline(cin, book_author[i]); // Allowing spaces in author name
            cout << endl; // Clearing input buffer
            cout << "\tEnter book price: ";
            cin >> book_pr[i];
            cout << endl; // Clearing input buffer
            upfile << book_name[i] << "\t" << book_author[i] << "\t" << book_ID[i] << "\t" << book_pr[i] << "\n";
        }
        total = total + ch;
    }
    upfile.close();
}

// Function for searching data
void searchdata() {
    int choice;
    cout << "Select search criteria:\n";
    cout << "1. Search by book ID\n";
    cout << "2. Search by book name\n";
    cout << "3. Search by author name\n";
    cin >> choice;

    bool found = false;
    string searchQuery;
    cout << "Enter search query: ";
    cin.ignore(); // Clear input buffer
    getline(cin, searchQuery);

    switch (choice) {
    case 1:
        for (int i = 0; i < total; i++) {
            if (searchQuery == book_ID[i]) {
                found = true;
                cout << "\t\t\tThe book number is \n\n"
                    << i + 1 << endl;
                cout << "\tBook ID: " << book_ID[i] << endl;
                cout << "\tBook Author: " << book_author[i] << endl;
                cout << "\tBook Price: " << book_pr[i] << endl;
                cout << "\tBook Name: " << book_name[i] << endl;
            }
        }
        break;
    case 2:
        for (int i = 0; i < total; i++) {
            if (searchQuery == book_name[i]) {
                found = true;
                cout << "\t\t\tThe book number is \n\n"
                    << i + 1 << endl;
                cout << "\tBook ID: " << book_ID[i] << endl;
                cout << "\tBook Author: " << book_author[i] << endl;
                cout << "\tBook Price: " << book_pr[i] << endl;
                cout << "\tBook Name: " << book_name[i] << endl;
            }
        }
        break;
    case 3:
        for (int i = 0; i < total; i++) {
            if (searchQuery == book_author[i]) {
                found = true;
                cout << "\t\t\tThe book number is \n\n"
                    << i + 1 << endl;
                cout << "\tBook ID: " << book_ID[i] << endl;
                cout << "\tBook Author: " << book_author[i] << endl;
                cout << "\tBook Price: " << book_pr[i] << endl;
                cout << "\tBook Name: " << book_name[i] << endl;
            }
        }
        break;
    default:
        cout << "Invalid choice." << endl;
        return;
    }

    if (!found) {
        cout << "No matching records found." << endl;
    }
}

// Function for updating book data
void updateData() {
    string bookID;
    cout << "Enter the book ID to update: ";
    cin >> bookID;

    bool found = false;
    for (int i = 0; i < total; i++) {
        if (bookID == book_ID[i]) {
            found = true;
            cout << "Enter new details for the book:\n";
            cout << "Book Name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, book_name[i]);
            cout << "Book Author: ";
            getline(cin, book_author[i]);
            cout << "Book Price: ";
            cin >> book_pr[i];
            cout << "Book ID: " << book_ID[i] << endl; // ID remains unchanged
            cout << "Book updated successfully." << endl;
            break;
        }
    }

    if (!found) {
        cout << "Book ID not found. Update failed." << endl;
    }
}

// Function for deleting book data
void deleteData() {
    string bookID;
    cout << "Enter the book ID to delete: ";
    cin >> bookID;

    bool found = false;
    for (int i = 0; i < total; i++) {
        if (bookID == book_ID[i]) {
            found = true;
            // Shift elements to left to remove the book data
            for (int j = i; j < total - 1; j++) {
                book_ID[j] = book_ID[j + 1];
                book_name[j] = book_name[j + 1];
                book_author[j] = book_author[j + 1];
                book_pr[j] = book_pr[j + 1];
            }
            total--;
            cout << "Book deleted successfully." << endl;
            break;
        }
    }

    if (!found) {
        cout << "Book ID not found. Deletion failed." << endl;
    }
}

// Main function
int main() {
    // Sample users for testing (can be replaced with file-based storage)
    users["user1"] = { "user1", "password1" };
    users["user2"] = { "user2", "password2" };

    int value;
    while (true) {
        cout << "\n~~~~~~~~~~"
            << "~~~~~~~~~~"
            << "WELCOME~~~~~"
            << "~~~~~~~~~~"
            << "~~~\n\n";
        cout << "Enter your choice\n";
        cout << "\t1. Register\n";
        cout << "\t2. Login\n";
        cout << "\t3. Show data\n";
        cout << "\t4. Enter book-name, book-ID, book-authr, book-no \n";
        cout << "\t5. Search data\n";
        cout << "\t6. Update data\n";
        cout << "\t7. Delete data\n";
        cout << "\t8. Exit \n";
        cin >> value;
        switch (value) {
        case 1:
            registerUser();
            break;
        case 2:
            if (authenticateUser()) {
                // Proceed with authenticated actions (e.g., adding books)
                // Add your authenticated functionalities here
                int authChoice;
                cout << "Authentication successful. You are now logged in." << endl;
                while (true) {
                    cout << "\n~~Authenticated Menu~~\n";
                    cout << "Enter your choice:\n";
                    cout << "\t1. Show data\n";
                    cout << "\t2. Enter book data\n";
                    cout << "\t3. Logout\n";
                    cin >> authChoice;
                    switch (authChoice) {
                    case 1:
                        showdata();
                        break;
                    case 2:
                        addbook();
                        break;
                    case 3:
                        cout << "Logging out..." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                    if (authChoice == 3) {
                        break;
                    }
                }
            }
            break;
        case 3:
            showdata();
            break;
        case 4:
            addbook();
            break;
        case 5:
            searchdata();
            break;
        case 6:
            updateData();
            break;
        case 7:
            deleteData();
            break;
        case 8:
            exit(0);
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
    return 0;
}