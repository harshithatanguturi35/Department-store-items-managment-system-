#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    int id;
    char name[50];
    float price;
    int quantity;
    struct Item* next;
} Item;

Item* head = NULL;

// Function to create a new item node
Item* createItem(int id, const char* name, float price, int quantity) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->quantity = quantity;
    newItem->next = NULL;
    return newItem;
}

// Add item to the list
void addItem() {
    int id, quantity;
    float price;
    char name[50];

    printf("Enter item ID: ");
    scanf("%d", &id);
    printf("Enter item name: ");
    scanf(" %[^\n]s", name);
    printf("Enter item price: ");
    scanf("%f", &price);
    printf("Enter item quantity: ");
    scanf("%d", &quantity);

    Item* newItem = createItem(id, name, price, quantity);
    newItem->next = head;
    head = newItem;

    printf("Item added successfully!\n");
}

// Display all items
void displayItems() {
    Item* current = head;
    if (current == NULL) {
        printf("No items in the list.\n");
        return;
    }
    printf("\n--- Item List ---\n");
    while (current != NULL) {
        printf("ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
               current->id, current->name, current->price, current->quantity);
        current = current->next;
    }
}

// Search item by ID
void searchItem() {
    int id;
    printf("Enter item ID to search: ");
    scanf("%d", &id);
    Item* current = head;

    while (current != NULL) {
        if (current->id == id) {
            printf("Item Found: ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
                   current->id, current->name, current->price, current->quantity);
            return;
        }
        current = current->next;
    }
    printf("Item with ID %d not found.\n", id);
}

// Delete item by ID
void deleteItem() {
    int id;
    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    Item* current = head;
    Item* prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Item deleted successfully.\n");
}

// Main menu
int main() {
    int choice;

    do {
        printf("\nDepartment Store Item Management\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Search Item\n");
        printf("4. Delete Item\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addItem(); break;
            case 2: displayItems(); break;
            case 3: searchItem(); break;
            case 4: deleteItem(); break;
            case 5: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}