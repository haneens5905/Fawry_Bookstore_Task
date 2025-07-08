// Fawry Quantum Bookstore
// developed by Haneen Soliman
// this program simulates a basic online bookstore system.

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// abstract class for rest of book types
class Book {
protected:
    string ISBN;
    string title;
    int year;
    double price;
public:
    Book(string isbn, string t, int yr, double pr) {
        ISBN = isbn;
        title = t;
        year = yr;
        price = pr;
    }

    virtual bool forSale() const = 0;

    virtual void buyBook(int quantity, const string &email, const string &address) = 0;

    string getISBN() const {
        return ISBN;
    }

    string getTitle() const {
        return title;
    }

    int getYear() const {
        return year;
    }

    double getPrice() const {
        return price;
    }

    virtual ~Book() {}
};


class PaperBook : public Book {
    int stock;
public:
    PaperBook(string isbn, string t, int yr, double pr, int st) : Book(isbn, t, yr, pr) {
        stock = st;
    }

    int getStock() const {
        return stock;
    }

    bool forSale() const override {
        return true;
    }

    bool isStockEnough(int amount) const {
        return stock >= amount;
    }

    void buyBook(int quantity, const string &email, const string &address) override {
        if (quantity <= 0 ) {
            throw invalid_argument("Cannot purchase, quantity must have positive value.");
        }

        if (!isStockEnough(quantity)) {
            throw runtime_error("Cannot purchase, not enough stock.");
        }

        stock -= quantity;
        cout << "x" << quantity << " \"" << title << "\" has been shipped to address: " << address << endl;
    }

};


class EBook : public Book {
    string fileType;
public:
    EBook(string isbn, string t, int yr, double pr, string file) : Book(isbn, t, yr, pr) {
        fileType = file;
    }

    bool forSale() const override {
        return true;
    }

    void buyBook(int quantity, const string &email, const string &address) override {
        if (quantity <= 0 ) {
            throw invalid_argument("Cannot purchase, quantity must have positive value.");
        }

        // we assume that only one book is downloaded per email, so quantity parameter is not used
        cout << "\"" << title << "\" has been sent via email as \'." << fileType << "\' to email: " << email << endl;
    }
};


class ShowcaseBook : public Book {
public:
    ShowcaseBook(string isbn, string t, int yr, double pr) : Book(isbn, t, yr, pr) {}

    bool forSale() const override {
        return false;
    }

    void buyBook(int quantity, const string &email, const string &address) override {
        throw runtime_error("Cannot purchase, this book is for display only.");
    }
};


class Inventory {
    vector<Book*> inventory;
public:
    void addBook(Book* book) {
        if (book != nullptr)
            inventory.push_back(book);
    }

    void removeOutdatedBook(int currentYear, int threshold) {
        for (int i = 0; i < inventory.size();) {
            Book* book = inventory[i];
            int ageOfBook = currentYear - book->getYear();

            if (ageOfBook > threshold) {
                cout << "Removing outdated book: \"" << book->getTitle()<< "\" (" << book->getYear() << ")..." << endl;
                delete book;
                inventory.erase(inventory.begin() + i); // remove book and stay at same index
            }
            else {
                i++; // move to next book if current book is not outdated
            }
        }
    }

    Book* findBook(const string& isbn) {
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i]->getISBN() == isbn) {
                return inventory[i];
            }
        }
        return nullptr;
    }

    void displayBooks() const {
        cout << "Current Books in Inventory: " << endl;
        for (int i = 0; i < inventory.size(); i++) {
            Book* book = inventory[i];

            // figure out the book’s type by dynamic casting it
            string bookType;
            if (dynamic_cast<PaperBook*>(book)) {
                bookType = "PaperBook";
            } else if (dynamic_cast<EBook*>(book)) {
                bookType = "EBook";
            } else if (dynamic_cast<ShowcaseBook*>(book)) {
                bookType = "ShowcaseBook";
            } else {
                bookType = "Unknown";
            }

            cout << bookType << ": \"" << inventory[i]->getTitle() << "\" (" << inventory[i]->getYear() << "). ";
            cout << "Price: " << inventory[i]->getPrice() << " LE";

            // check if it's a PaperBook to show stock
            PaperBook* paperbook = dynamic_cast<PaperBook*>(book);
            if (paperbook != nullptr) {
                cout << ", Stock: " << paperbook->getStock();
            }

            cout << endl;
        }
    }

    ~Inventory() {
        for (int i = 0; i < inventory.size(); i++) {
            delete inventory[i];
        }
    }
};


int main() {
    Inventory inventory;

    // add books to inventory
    cout << "\nAdding books to the inventory..." << endl;
    cout << endl;

    inventory.addBook(new PaperBook("P001", "C++ Foundations", 2010, 2500.0, 5));
    inventory.addBook(new EBook("E002", "Mastering STL", 2022, 5000.0, "PDF"));
    inventory.addBook(new ShowcaseBook("S003", "Ancient Codex", 1970, 750.0));

    // display inventory
    inventory.displayBooks();

    // try buying a paperbook
    cout << "\nBuying a PaperBook (valid purchase):" << endl;
    Book* paper = inventory.findBook("P001");
    if (paper) {
        try {
            paper->buyBook(2, "haneen@gmail.com", "Maadi Street");
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    // try buying an ebook
    cout << "\nBuying an EBook (valid purchase):" << endl;
    Book* ebook = inventory.findBook("E002");
    if (ebook) {
        try {
            ebook->buyBook(1, "haneen@gmail.com", "email sent, no address needed");
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    // try buying a showcase book (should throw error)
    cout << "\nTrying to buy a ShowcaseBook (should fail):" << endl;
    Book* showcase = inventory.findBook("S003");
    if (showcase) {
        try {
            showcase->buyBook(1, "haneen@gmail.com", "display-only, no address needed");
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    // try buying too many papaerbooks (should fail)
    cout << "\nTrying to buy more PaperBooks than stock (should fail):" << endl;
    if (paper) {
        try {
            paper->buyBook(10, "haneen@gmail.com", "Maadi Street");
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    cout << endl;
    // display inventory again to see updated stock
    inventory.displayBooks();

    // remove outdated books (older than 40 years from 2025)
    cout << "\nRemoving outdated books (older than 40 years)..." << endl;
    inventory.removeOutdatedBook(2025, 40);

    cout << endl;
    // final inventory check
    inventory.displayBooks();

    return 0;
}

/*
 Expected Output :

Adding books to the inventory...

Current Books in Inventory:
PaperBook: "C++ Foundations" (2010). Price: 2500 LE, Stock: 5
EBook: "Mastering STL" (2022). Price: 5000 LE
ShowcaseBook: "Ancient Codex" (1970). Price: 750 LE

Buying a PaperBook (valid purchase):
x2 "C++ Foundations" has been shipped to address: Maadi Street

Buying an EBook (valid purchase):
"Mastering STL" has been sent via email as '.PDF' to email: haneen@gmail.com

Trying to buy a ShowcaseBook (should fail):
Error: Cannot purchase, this book is for display only.

Trying to buy more PaperBooks than stock (should fail):
Error: Cannot purchase, not enough stock.

Current Books in Inventory:
PaperBook: "C++ Foundations" (2010). Price: 2500 LE, Stock: 3
EBook: "Mastering STL" (2022). Price: 5000 LE
ShowcaseBook: "Ancient Codex" (1970). Price: 750 LE

Removing outdated books (older than 40 years)...
Removing outdated book: "Ancient Codex" (1970)...

Current Books in Inventory:
PaperBook: "C++ Foundations" (2010). Price: 2500 LE, Stock: 3
EBook: "Mastering STL" (2022). Price: 5000 LE
*/