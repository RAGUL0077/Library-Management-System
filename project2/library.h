#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_NAME 100

struct Book
{
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int quantity;
    struct Book *next;
};

struct Issue
{
    int issue_id;
    int book_id;
    int user_id;
    char user_name[MAX_NAME];

    char issue_date[20];
    char due_date[20];
    char return_date[20];

    float fine;
    int returned;

    struct Issue *next;
};

extern struct Book *book_head;
extern struct Issue *issue_head;

/* Book functions */
void add_book(void);
void update_book(void);
void remove_book(void);
void search_book(void);
void view_books(void);

/* Issue functions */
void issue_book(void);
void return_book(void);
void list_issued_books(void);

/* File functions */
void save_data(void);
void load_data(void);

/* Utility */
int get_next_book_id(void);
int get_next_issue_id(void);

#endif
