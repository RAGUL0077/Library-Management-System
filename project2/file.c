#include <stdio.h>
#include <stdlib.h>
#include "library.h"


/* Save all data */

void save_data(void)
{
    FILE *fp;

    struct Book *book;
    struct Issue *issue;

    /*
       Save Books
    */

    fp = fopen("books.dat", "wb");

    if(fp == NULL)
    {
        printf("Unable to open books.dat\n");
        return;
    }

    book = book_head;

    while(book != NULL)
    {
        fwrite(book, sizeof(struct Book), 1, fp);

        book = book->next;
    }

    fclose(fp);


    /*
       Save Issues
    */

    fp = fopen("issues.dat", "wb");

    if(fp == NULL)
    {
        printf("Unable to open issues.dat\n");
        return;
    }

    issue = issue_head;

    while(issue != NULL)
    {
        fwrite(issue, sizeof(struct Issue), 1, fp);

        issue = issue->next;
    }

    fclose(fp);

    printf("\nData saved successfully.\n");
}


/* Load data */

void load_data(void)
{
    FILE *fp;

    struct Book book_data;
    struct Book *new_book;
    struct Book *book_temp;

    struct Issue issue_data;
    struct Issue *new_issue;
    struct Issue *issue_temp;


    /*
       Load Books
    */

    fp = fopen("books.dat", "rb");

    if(fp != NULL)
    {
        while(fread(&book_data,
                    sizeof(struct Book),
                    1,
                    fp) == 1)
        {
            new_book = malloc(sizeof(struct Book));

            if(new_book == NULL)
            {
                fclose(fp);
                return;
            }

            *new_book = book_data;
            new_book->next = NULL;

            if(book_head == NULL)
            {
                book_head = new_book;
            }
            else
            {
                book_temp = book_head;

                while(book_temp->next != NULL)
                    book_temp = book_temp->next;

                book_temp->next = new_book;
            }
        }

        fclose(fp);
    }


    /*
       Load Issues
    */

    fp = fopen("issues.dat", "rb");

    if(fp != NULL)
    {
        while(fread(&issue_data,
                    sizeof(struct Issue),
                    1,
                    fp) == 1)
        {
            new_issue = malloc(sizeof(struct Issue));

            if(new_issue == NULL)
            {
                fclose(fp);
                return;
            }

            *new_issue = issue_data;
            new_issue->next = NULL;

            if(issue_head == NULL)
            {
                issue_head = new_issue;
            }
            else
            {
                issue_temp = issue_head;

                while(issue_temp->next != NULL)
                    issue_temp = issue_temp->next;

                issue_temp->next = new_issue;
            }
        }

        fclose(fp);
    }
}
