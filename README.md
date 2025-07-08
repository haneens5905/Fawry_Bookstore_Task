# Fawry Quantum Bookstore – C++ Console Project

This project is a simple console application that simulates a basic online bookstore. It was created as part of the Fawry Quantum Full Stack Development Internship Challenge.

The idea is to show how object-oriented programming (OOP) can be used to manage different types of books, handle purchases, keep track of stock, and remove outdated books from the system.

---

## 💡 Project Purpose

The goal of this program is to demonstrate how a real-world concept like a bookstore can be implemented using core C++ concepts, including:

- Classes and inheritance
- Abstract classes and virtual functions
- Polymorphism using `dynamic_cast`
- Exception handling
- Basic inventory management

It’s a small simulation but touches on important software engineering ideas.

---

## 📚 Book Types in the System

The system supports 3 types of books:

### 1. PaperBook  
- These are physical books that can be shipped.
- They have limited stock.
- You must provide an address when buying.

### 2. EBook  
- These are digital books sent by email.
- No stock limit.
- Only email is needed (address is ignored).

### 3. ShowcaseBook  
- These books are for display only and **cannot** be purchased.
- Any attempt to buy them throws an error.

All these classes inherit from a common abstract class called `Book`.

---

## 🔁 How the Program Works

1. **Adding Books**  
   The system starts by adding three books to the inventory: one of each type.

2. **Displaying Books**  
   All current books are shown in the console with their type, title, year, price, and stock (if applicable).

3. **Buying Books**  
   It simulates different purchase scenarios:
   - Successful PaperBook and EBook purchases
   - Trying to buy a display-only ShowcaseBook (shows error)
   - Trying to buy more PaperBooks than are in stock (shows error)

4. **Removing Outdated Books**  
   The system removes books that are too old (in this case, more than 40 years old from the current year 2025).

5. **Final Inventory**  
   After purchases and removals, the remaining inventory is displayed.

---

## 📂 Files

- `Fawry_Qantum_Bookstore.cpp`: The main and only source file containing the entire logic of the bookstore.

---

## ✅ Example Output:

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

Removing outdated books (older than 40 years)...
Removing outdated book: "Ancient Codex" (1970)...

Current Books in Inventory:
PaperBook: "C++ Foundations" (2010). Price: 2500 LE, Stock: 3
EBook: "Mastering STL" (2022). Price: 5000 LE

