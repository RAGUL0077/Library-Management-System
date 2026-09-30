# Library Management System in C

## Project Description

The Library Management System is a console-based application developed using the C programming language. It is designed to manage basic library operations such as adding books, updating book details, removing books, searching for books, issuing books to users, returning books, and maintaining issued-book records.

The system uses structures and linked lists to store and manage book and issue records dynamically. File handling is used to save the records permanently so that the data can be loaded when the program is started again.

## Objectives

The main objective of this project is to develop a simple and efficient library management system using C programming concepts. The project demonstrates the practical use of structures, pointers, dynamic memory allocation, linked lists, functions, and file handling.

## Features

The system provides the following features:

1. Add New Book
2. Update Book Details
3. Remove Book
4. Search Book
5. View All Books
6. Issue Book
7. Return Book
8. List Issued Books
9. Save Records
10. Exit

## Book Management

Each book record contains:

- Book ID
- Book Title
- Author Name
- Quantity

The system automatically assigns a unique Book ID to each new book. Books can be added, updated, removed, searched, and displayed.

Books can be searched using:

- Book ID
- Book Name
- Author Name

## Issue Management

The system allows a book to be issued to a user by recording:

- Issue ID
- Book ID
- User ID
- User Name
- Issue Date
- Due Date
- Return Date
- Fine Amount

When a book is issued, its available quantity is reduced. The issue date is generated automatically and the due date is set to 7 days after the issue date.

## Return Management

When a book is returned, the system records the return date and compares it with the due date.

If the book is returned late, a fine is calculated.

The fine calculation is:

Fine Amount = Number of Late Days × ₹5

After the book is returned, its available quantity is increased.

## Data Structures Used

The project uses structures to represent book and issue records.

A singly linked list is used to dynamically store multiple book and issue records.

Dynamic memory allocation using `malloc()` is used to create new records at runtime.

## File Handling

File handling is used to store data permanently.

Two files are used:

- `books.dat` - stores book records
- `issues.dat` - stores issued-book records

The saved data is loaded when the program starts and can be saved whenever the user selects the Save option.

## Technologies Used

- C Programming Language
- Structures
- Pointers
- Singly Linked Lists
- Dynamic Memory Allocation
- File Handling
- Functions
- Date and Time Functions

## Project Structure
```text
Library-Management-System/
│
├── main.c
├── library.h
├── book.c
├── issue.c
├── file.c
├── books.dat
└── issues.dat
```

## Compilation

Compile using cc.main.c

