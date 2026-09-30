#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"


/* Get next available Book ID */

int get_next_book_id(void)
{
    struct Book *temp;
    int id = 1;

    while(1)
    {
        temp = book_head;

        while(temp != NULL)
        {
            if(temp->id == id)
                break;

            temp = temp->next;
        }

        if(temp == NULL)
            return id;

        id++;
    }
}


/* Add New Book */

void add_book(void)
{
    struct Book *new_book;
    struct Book *temp;

    new_book = malloc(sizeof(struct Book));

    if(new_book == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    new_book->id = get_next_book_id();

    printf("\nEnter Book Title: ");
    scanf(" %[^\n]", new_book->title);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", new_book->author);

    printf("Enter Quantity: ");
    scanf("%d", &new_book->quantity);

    if(new_book->quantity < 0)
    {
        printf("Invalid quantity.\n");
        free(new_book);
        return;
    }

    new_book->next = NULL;

    if(book_head == NULL)
    {
        book_head = new_book;
    }
    else
    {
        temp = book_head;

        while(temp->next != NULL)
            temp = temp->next;

        temp->next = new_book;
    }

    printf("\nBook added successfully.\n");
    printf("Book ID: %d\n", new_book->id);
}


/* Update Book */

void update_book(void)
{
    char choice;
    struct Book *temp = NULL;
    int id;

    if(book_head == NULL)
    {
        printf("\nNo books available.\n");
        return;
    }

    printf("\nA. By Book ID\n");
    printf("B. By Book Name\n");
    printf("C. Back to Main Menu\n");

    printf("Enter Your Choice: ");
    scanf(" %c", &choice);

    if(choice == 'A' || choice == 'a')
    {
        printf("Enter Book ID: ");
        scanf("%d", &id);

        temp = book_head;

        while(temp != NULL)
        {
            if(temp->id == id)
                break;

            temp = temp->next;
        }
    }
    else if(choice == 'B' || choice == 'b')
    {
        char title[MAX_TITLE];

        printf("Enter Book Name: ");
        scanf(" %[^\n]", title);

        temp = book_head;

        while(temp != NULL)
        {
            if(strcmp(temp->title, title) == 0)
                break;

            temp = temp->next;
        }
    }
    else
    {
        return;
    }

    if(temp == NULL)
    {
        printf("Book not found.\n");
        return;
    }

    printf("\nCurrent Details:\n");
    printf("ID       : %d\n", temp->id);
    printf("Title    : %s\n", temp->title);
    printf("Author   : %s\n", temp->author);
    printf("Quantity : %d\n", temp->quantity);

    printf("\nEnter New Book Title: ");
    scanf(" %[^\n]", temp->title);

    printf("Enter New Author Name: ");
    scanf(" %[^\n]", temp->author);

    printf("Enter New Quantity: ");
    scanf("%d", &temp->quantity);

    if(temp->quantity < 0)
    {
        printf("Invalid quantity.\n");
        return;
    }

    printf("Book updated successfully.\n");
}


/* Remove Book */

void remove_book(void)
{
    char choice;
    struct Book *temp;
    struct Book *prev;
    int id;

    if(book_head == NULL)
    {
        printf("\nNo books available.\n");
        return;
    }

    printf("\nA. By Book ID\n");
    printf("B. By Book Name\n");
    printf("C. Back to Main Menu\n");

    printf("Enter Your Choice: ");
    scanf(" %c", &choice);

    if(choice == 'A' || choice == 'a')
    {
        printf("Enter Book ID: ");
        scanf("%d", &id);

        temp = book_head;
        prev = NULL;

        while(temp != NULL)
        {
            if(temp->id == id)
                break;

            prev = temp;
            temp = temp->next;
        }
    }
    else if(choice == 'B' || choice == 'b')
    {
        char title[MAX_TITLE];

        printf("Enter Book Name: ");
        scanf(" %[^\n]", title);

        temp = book_head;
        prev = NULL;

        while(temp != NULL)
        {
            if(strcmp(temp->title, title) == 0)
                break;

            prev = temp;
            temp = temp->next;
        }
    }
    else
    {
        return;
    }

    if(temp == NULL)
    {
        printf("Book not found.\n");
        return;
    }

    /*
       Don't delete a book which is currently issued.
    */

    struct Issue *issue = issue_head;

    while(issue != NULL)
    {
        if(issue->book_id == temp->id && issue->returned == 0)
        {
            printf("Cannot remove this book.\n");
            printf("The book is currently issued.\n");
            return;
        }

        issue = issue->next;
    }

    if(prev == NULL)
        book_head = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    printf("Book removed successfully.\n");
}


/* Search Book */

void search_book(void)
{
    char choice;
    struct Book *temp;
    int found = 0;

    if(book_head == NULL)
    {
        printf("\nNo books available.\n");
        return;
    }

    printf("\nA. By Book ID\n");
    printf("B. By Book Name\n");
    printf("C. By Author Name\n");
    printf("D. Back to Main Menu\n");

    printf("Enter Your Choice: ");
    scanf(" %c", &choice);

    if(choice == 'A' || choice == 'a')
    {
        int id;

        printf("Enter Book ID: ");
        scanf("%d", &id);

        temp = book_head;

        while(temp != NULL)
        {
            if(temp->id == id)
            {
                printf("\nID       : %d\n", temp->id);
                printf("Title    : %s\n", temp->title);
                printf("Author   : %s\n", temp->author);
                printf("Quantity : %d\n", temp->quantity);

                found = 1;
                break;
            }

            temp = temp->next;
        }
    }

    else if(choice == 'B' || choice == 'b')
    {
        char title[MAX_TITLE];

        printf("Enter Book Name: ");
        scanf(" %[^\n]", title);

        temp = book_head;

        while(temp != NULL)
        {
            if(strcmp(temp->title, title) == 0)
            {
                printf("\nID       : %d\n", temp->id);
                printf("Title    : %s\n", temp->title);
                printf("Author   : %s\n", temp->author);
                printf("Quantity : %d\n", temp->quantity);

                found = 1;
            }

            temp = temp->next;
        }
    }

    else if(choice == 'C' || choice == 'c')
    {
        char author[MAX_AUTHOR];

        printf("Enter Author Name: ");
        scanf(" %[^\n]", author);

        temp = book_head;

        while(temp != NULL)
        {
            if(strcmp(temp->author, author) == 0)
            {
                printf("\nID       : %d\n", temp->id);
                printf("Title    : %s\n", temp->title);
                printf("Author   : %s\n", temp->author);
                printf("Quantity : %d\n", temp->quantity);

                found = 1;
            }

            temp = temp->next;
        }
    }

    else
    {
        return;
    }

    if(found == 0)
        printf("\nBook not found.\n");
}


/* View All Books */

void view_books(void)
{
    struct Book *temp;

    if(book_head == NULL)
    {
        printf("\nNo books available.\n");
        return;
    }

    printf("\n");
    printf("-----------------------------------------------------------------\n");
    printf("ID\tTitle\t\t\tAuthor\t\t\tQuantity\n");
    printf("-----------------------------------------------------------------\n");

    temp = book_head;

    while(temp != NULL)
    {
        printf("%d\t%-20s\t%-20s\t%d\n",
               temp->id,
               temp->title,
               temp->author,
               temp->quantity);

        temp = temp->next;
    }

    printf("-----------------------------------------------------------------\n");
}
