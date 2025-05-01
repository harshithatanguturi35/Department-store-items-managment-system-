#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an item in the store
struct Item {
    int id;
    char name[50];
    float price;
    int quantity;
    struct Item* next;
};

// Function to create a new item node
struct Item* createItem(int id, const char* name, float price, int quantity) {
    struct Item* newItem = (struct Item*)malloc(sizeof(struct Item));
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->quantity = quantity;
    newItem->next = NULL;
    return newItem;
}

// Function to add an item to the linked list
void addItem(struct Item** head, int id, const char* name, float price, int quantity) {
    struct Item* newItem = createItem(id, name, price, quantity);
    newItem->next = *head;
    *head = newItem;
}

// Function to display the items in the store
void displayItems(struct Item* head) {
    if (head == NULL) {
        printf("No items available.\n");
        return;
    }
    printf("\nID\tName\t\tPrice\tQuantity\n");
    printf("-----------------------------------------\n");
    while (head != NULL) {
        printf("%d\t%s\t%.2f\t%d\n", head->id, head->name, head->price, head->quantity);
        head = head->next;
    }
}

// Function to save the items to a file
void saveItemsToFile(struct Item* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    while (head != NULL) {
        fprintf(file, "%d\t%s\t%.2f\t%d\n", head->id, head->name, head->price, head->quantity);
        head = head->next;
    }
    fclose(file);
}

// Function to load items from a file into the linked list
void loadItemsFromFile(struct Item** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    int id, quantity;
    char name[50];
    float price;
    while (fscanf(file, "%d\t%s\t%f\t%d\n", &id, name, &price, &quantity) != EOF) {
        addItem(head, id, name, price, quantity);
    }
    fclose(file);
}

// Function to delete an item from the linked list
void deleteItem(struct Item** head, int id) {
    struct Item* temp = *head;
    struct Item* prev = NULL;

    // If the item to be deleted is the head
    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        printf("Item with ID %d deleted.\n", id);
        return;
    }

    // Search for the item to delete
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If item was not found
    if (temp == NULL) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    // Unlink the node
    prev->next = temp->next;
    free(temp);
    printf("Item with ID %d deleted.\n", id);
}

// Main function
int main() {
    struct Item* head = NULL;
    int choice;
    int id, quantity;
    char name[50];
    float price;
    const char* filename = "items.txt";

    // Load items from the file
    loadItemsFromFile(&head, filename);

    do {
        printf("\nDepartment Store Management System\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Delete Item\n");
        printf("4. Save Items to File\n");
        printf("5. Load Items from File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Item ID: ");
                scanf("%d", &id);
                printf("Enter Item Name: ");
                getchar();  // Consume the newline character left by previous input
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline character at the end of name
                printf("Enter Item Price: ");
                scanf("%f", &price);
                printf("Enter Item Quantity: ");
                scanf("%d", &quantity);
                addItem(&head, id, name, price, quantity);
                printf("Item added successfully.\n");
                break;

            case 2:
                displayItems(head);
                break;

            case 3:
                printf("Enter Item ID to delete: ");
                scanf("%d", &id);
                deleteItem(&head, id);
                break;

            case 4:
                saveItemsToFile(head, filename);
                printf("Items saved to file.\n");
                break;

            case 5:
                loadItemsFromFile(&head, filename);
                printf("Items loaded from file.\n");
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
