#include <stdio.h>
#include <string.h>

// Structure to store book details
struct Book {
    char title[50];
    char author[50];
    char genre[30];
    int copies;
};

// Function declarations
void displayBooks(struct Book library[], int count);
void searchBook(struct Book library[], int count);
void issueBook(struct Book library[], int count);
void returnBook(struct Book library[], int count);
void recommendBook(struct Book library[], int count);

int main() {
    struct Book library[50];
    int count = 5; // Number of books in library
    int choice;

    // Initialize books
    strcpy(library[0].title, "C Programming");
    strcpy(library[0].author, "Dennis Ritchie");
    strcpy(library[0].genre, "Programming");
    library[0].copies = 3;

    strcpy(library[1].title, "The Alchemist");
    strcpy(library[1].author, "Paulo Coelho");
    strcpy(library[1].genre, "Fiction");
    library[1].copies = 2;

    strcpy(library[2].title, "Data Structures");
    strcpy(library[2].author, "Mark Weiss");
    strcpy(library[2].genre, "Education");
    library[2].copies = 4;

    strcpy(library[3].title, "Harry Potter");
    strcpy(library[3].author, "J.K. Rowling");
    strcpy(library[3].genre, "Fantasy");
    library[3].copies = 5;

    strcpy(library[4].title, "Rich Dad Poor Dad");
    strcpy(library[4].author, "Robert Kiyosaki");
    strcpy(library[4].genre, "Finance");
    library[4].copies = 3;

    // Menu-driven program
    do {
        printf("\n====== DIGITAL LIBRARY SYSTEM ======\n");
        printf("1. Display All Books\n");
        printf("2. Search Book\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Recommend Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To clear newline from input buffer

        switch(choice) {
            case 1:
                displayBooks(library, count);
                break;
            case 2:
                searchBook(library, count);
                break;
            case 3:
                issueBook(library, count);
                break;
            case 4:
                returnBook(library, count);
                break;
            case 5:
                recommendBook(library, count);
                break;
            case 6:
                printf("\nThank you for using the Digital Library!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while(choice != 6);

    return 0;
}

// Function to display all books
void displayBooks(struct Book library[], int count) {
    printf("\nAvailable Books:\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < count; i++) {
        printf("Title: %s\nAuthor: %s\nGenre: %s\nCopies: %d\n\n",
               library[i].title, library[i].author, library[i].genre, library[i].copies);
    }
}

// Function to search for a book
void searchBook(struct Book library[], int count) {
    char keyword[50];
    int found = 0;

    printf("\nEnter book title or author to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // remove newline

    for(int i = 0; i < count; i++) {
        if(strstr(library[i].title, keyword) != NULL || strstr(library[i].author, keyword) != NULL) {
            printf("\nBook Found:\nTitle: %s\nAuthor: %s\nGenre: %s\nCopies: %d\n",
                   library[i].title, library[i].author, library[i].genre, library[i].copies);
            found = 1;
        }
    }
    if(!found)
        printf("\nNo matching book found.\n");
}

// Function to issue a book
void issueBook(struct Book library[], int count) {
    char title[50];
    int found = 0;

    printf("\nEnter book title to issue: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for(int i = 0; i < count; i++) {
        if(strcmp(library[i].title, title) == 0) {
            found = 1;
            if(library[i].copies > 0) {
                library[i].copies--;
                printf("Book issued successfully!\n");
            } else {
                printf("Sorry, no copies available.\n");
            }
        }
    }
    if(!found)
        printf("Book not found in library.\n");
}

// Function to return a book and calculate fine
void returnBook(struct Book library[], int count) {
    char title[50];
    int daysLate, fine;
    int found = 0;

    printf("\nEnter book title to return: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for(int i = 0; i < count; i++) {
        if(strcmp(library[i].title, title) == 0) {
            found = 1;
            library[i].copies++;
            printf("Enter number of days late (0 if on time): ");
            scanf("%d", &daysLate);
            getchar();  // To clear newline from input buffer
            if(daysLate > 0) {
                fine = daysLate * 2;
                printf("Book returned late. Fine = Rupees %d\n", fine);
            } else {
                printf("Book returned on time. No fine.\n");
            }
        }
    }
    if(!found)
        printf("Book not found in library.\n");
}

// Function to recommend books by genre
void recommendBook(struct Book library[], int count) {
    char genre[30];
    int found = 0;

    printf("\nEnter preferred genre: ");
    fgets(genre, sizeof(genre), stdin);
    genre[strcspn(genre, "\n")] = '\0';

    printf("\nRecommended Books in '%s':\n", genre);
    for(int i = 0; i < count; i++) {
        if(strcmp(library[i].genre, genre) == 0) {
            printf(" - %s by %s\n", library[i].title, library[i].author);
            found = 1;
        }
    }
    if(!found)
        printf("No recommendations available for this genre.\n");
}
