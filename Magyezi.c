
#include <stdio.h>
#include <stdlib.h> // For exit()
#include <string.h> // For strcpy() and strlen()

// Define a structure Book with title, author, and price.
struct Book {
    char title[100];
    char author[100];
    float price;
};

// Function to input book details
void inputBookDetails(struct Book *book) {
    printf("Enter book title: ");
    // Read the whole line including spaces
    fgets(book->title, sizeof(book->title), stdin);
    // Remove the trailing newline character if present
    book->title[strcspn(book->title, "\n")] = 0;

    printf("Enter book author: ");
    fgets(book->author, sizeof(book->author), stdin);
    book->author[strcspn(book->author, "\n")] = 0;

    printf("Enter book price: ");
    scanf("%f", &book->price);
    // Consume the leftover newline character after scanf
    while (getchar() != '\n');
}

// Function to save book details to a file
void saveBookDetails(const struct Book *book, const char *filename) {
    FILE *file = fopen(filename, "a"); // Open in append mode
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Title: %s\n", book->title);
    fprintf(file, "Author: %s\n", book->author);
    fprintf(file, "Price: %.2f\n", book->price);
    fprintf(file, "--------------------\n"); // Separator for multiple books

    fclose(file);
    printf("Book details saved to %s\n", filename);
}

// Function to read and display saved book details
void displaySavedBookDetails(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open in read mode
    if (file == NULL) {
        perror("Error opening file for reading");
        return; // Don't exit, just indicate no file or error
    }

    printf("\n--- Saved Book Details ---\n");
    char line[256]; // Buffer to read each line
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    printf("--------------------------\n");

    fclose(file);
}

int main() {
    struct Book myBook;
    const char *filename = "book_details.txt";

    // Input book details
    inputBookDetails(&myBook);

    // Save book details to a file
    saveBookDetails(&myBook, filename);

    // Read and display the saved book details
    displaySavedBookDetails(filename);

    return 0;
}
