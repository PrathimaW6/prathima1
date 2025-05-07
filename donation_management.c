
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CATEGORY_COUNT 3
#define NAME_LEN 100

// Define categories
const char* categories[] = { "Food", "Clothes", "Money" };

// Node structure for donor
typedef struct Donor {
    char name[NAME_LEN];
    struct Donor* next;
} Donor;

// Linked list head for each category
Donor* donorLists[CATEGORY_COUNT] = { NULL };

// Function to create a new donor node
Donor* createDonor(const char* name) {
    Donor* newDonor = (Donor*)malloc(sizeof(Donor));
    if (!newDonor) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strncpy(newDonor->name, name, NAME_LEN);
    newDonor->next = NULL;
    return newDonor;
}

// Function to add donor to a category
void addDonor(int categoryIndex, const char* name) {
    if (categoryIndex < 0 || categoryIndex >= CATEGORY_COUNT) {
        printf("Invalid category.\n");
        return;
    }

    Donor* newDonor = createDonor(name);
    newDonor->next = donorLists[categoryIndex];
    donorLists[categoryIndex] = newDonor;

    printf("Donor '%s' added to category.\n"
, name, categories[categoryIndex]);
}

// Function to display all donors in each category
void displayDonors() {
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        printf("\nCategory: %s\n", categories[i]);
        Donor* temp = donorLists[i];
        if (!temp) {
            printf("  No donors yet.\n");
        } else {
            while (temp) {
                printf("  - %s\n", temp->name);
                temp = temp->next;
            }
        }
    }
}

// Free allocated memory
void freeMemory() {
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        Donor* temp = donorLists[i];
        while (temp) {
            Donor* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
}

// Main program
int main() {
    int choice, categoryIndex;
    char name[NAME_LEN];

    do {
        printf("\n--- Donation Management System ---\n");
        printf("1. Add Donor\n");
        printf("2. Display Donors\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Select Category:\n");
                for (int i = 0; i < CATEGORY_COUNT; i++) {
                    printf("  %d. %s\n", i + 1, categories[i]);
                }
                printf("Enter category number: ");
                scanf("%d", &categoryIndex);
                getchar(); // consume newline

                if (categoryIndex < 1 || categoryIndex > CATEGORY_COUNT) {
                    printf("Invalid category selection.\n");
                    break;
                }

                printf("Enter donor name: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0'; // remove newline

                addDonor(categoryIndex - 1, name);
                break;

            case 2:
                displayDonors();
                break;

            case 3:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    freeMemory();
    return 0;
}
