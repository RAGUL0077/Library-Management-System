#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "library.h"


/* Get next Issue ID */

int get_next_issue_id(void)
{
    struct Issue *temp;
    int id = 1;

    while(1)
    {
        temp = issue_head;

        while(temp != NULL)
        {
            if(temp->issue_id == id)
                break;

            temp = temp->next;
        }

        if(temp == NULL)
            return id;

        id++;
    }
}


/* Get date after given number of days */

void get_date_after(int days, char *buffer)
{
    time_t now;
    struct tm date;

    time(&now);

    date = *localtime(&now);

    date.tm_mday += days;

    mktime(&date);

    strftime(buffer, 20, "%d-%m-%Y", &date);
}


/* Get today's date */

void get_today(char *buffer)
{
    time_t now;
    struct tm *date;

    time(&now);

    date = localtime(&now);

    strftime(buffer, 20, "%d-%m-%Y", date);
}


/* Convert date to time */

time_t convert_date(char *date_string)
{
    struct tm date = {0};

    sscanf(date_string,
           "%d-%d-%d",
           &date.tm_mday,
           &date.tm_mon,
           &date.tm_year);

    date.tm_mon -= 1;
    date.tm_year -= 1900;

    date.tm_hour = 12;

    return mktime(&date);
}


/* Issue Book */

void issue_book(void)
{
    int book_id;
    struct Book *book;
    struct Issue *new_issue;
    struct Issue *temp;

    printf("\nEnter Book ID: ");
    scanf("%d", &book_id);

    book = book_head;

    while(book != NULL)
    {
        if(book->id == book_id)
            break;

        book = book->next;
    }

    if(book == NULL)
    {
        printf("Book not found.\n");
        return;
    }

    if(book->quantity <= 0)
    {
        printf("Book is not available.\n");
        return;
    }

    new_issue = malloc(sizeof(struct Issue));

    if(new_issue == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    new_issue->issue_id = get_next_issue_id();
    new_issue->book_id = book_id;

    printf("Enter User ID: ");
    scanf("%d", &new_issue->user_id);

    printf("Enter User Name: ");
    scanf(" %[^\n]", new_issue->user_name);

    get_today(new_issue->issue_date);

    get_date_after(7, new_issue->due_date);

    strcpy(new_issue->return_date, "-");

    new_issue->fine = 0;
    new_issue->returned = 0;
    new_issue->next = NULL;

    if(issue_head == NULL)
    {
        issue_head = new_issue;
    }
    else
    {
        temp = issue_head;

        while(temp->next != NULL)
            temp = temp->next;

        temp->next = new_issue;
    }

    book->quantity--;

    printf("\nBook issued successfully.\n");
    printf("Issue ID   : %d\n", new_issue->issue_id);
    printf("Book ID    : %d\n", new_issue->book_id);
    printf("User ID    : %d\n", new_issue->user_id);
    printf("Issue Date : %s\n", new_issue->issue_date);
    printf("Due Date   : %s\n", new_issue->due_date);
}


/* Return Book */

void return_book(void)
{
    int book_id;
    int user_id;

    struct Issue *issue;
    struct Book *book;

    printf("\nEnter Book ID: ");
    scanf("%d", &book_id);

    printf("Enter User ID: ");
    scanf("%d", &user_id);

    issue = issue_head;

    while(issue != NULL)
    {
        if(issue->book_id == book_id &&
           issue->user_id == user_id &&
           issue->returned == 0)
        {
            break;
        }

        issue = issue->next;
    }

    if(issue == NULL)
    {
        printf("Active issue record not found.\n");
        return;
    }

    get_today(issue->return_date);

    /*
       Calculate late days
    */

    time_t due = convert_date(issue->due_date);
    time_t returned = convert_date(issue->return_date);

    double difference;
    int late_days;

    difference = difftime(returned, due);

    late_days = (int)(difference / (60 * 60 * 24));

    if(late_days < 0)
        late_days = 0;

    issue->fine = late_days * 5;

    issue->returned = 1;

    /*
       Increase book quantity
    */

    book = book_head;

    while(book != NULL)
    {
        if(book->id == book_id)
            break;

        book = book->next;
    }

    if(book != NULL)
        book->quantity++;

    printf("\nBook returned successfully.\n");
    printf("Return Date : %s\n", issue->return_date);
    printf("Late Days   : %d\n", late_days);
    printf("Fine Amount : Rs. %.2f\n", issue->fine);
}


/* List Issued Books */

void list_issued_books(void)
{
    struct Issue *issue;
    struct Book *book;
    int found = 0;

    if(issue_head == NULL)
    {
        printf("\nNo issue records available.\n");
        return;
    }

    printf("\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("IssueID BookID Title UserID UserName IssueDate DueDate ReturnDate Fine\n");
    printf("--------------------------------------------------------------------------------------------------\n");

    issue = issue_head;

    while(issue != NULL)
    {
        book = book_head;

        while(book != NULL)
        {
            if(book->id == issue->book_id)
                break;

            book = book->next;
        }

        if(book != NULL)
        {
            printf("%-7d %-6d %-15s %-6d %-12s %-11s %-11s %-11s Rs.%.2f\n",
                   issue->issue_id,
                   issue->book_id,
                   book->title,
                   issue->user_id,
                   issue->user_name,
                   issue->issue_date,
                   issue->due_date,
                   issue->return_date,
                   issue->fine);

            found = 1;
        }

        issue = issue->next;
    }

    printf("--------------------------------------------------------------------------------------------------\n");

    if(found == 0)
        printf("No records available.\n");
}
