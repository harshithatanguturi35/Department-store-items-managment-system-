#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Item {
    int id;
    string name;
    float price;
    int quantity;
    Item* next;
};

Item* head = nullptr;

// Add item
void addItem(int id, string name, float price, int quantity) {
    Item* newItem = new Item{id, name, price, quantity, head};
    head = newItem;
}

// Display all items
void displayItems() {
    Item* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id
             << ", Name: " << temp->name
             << ", Price: " << temp->price
             << ", Quantity: " << temp->quantity << endl;
        temp = temp->next;
    }
}

// Search by ID
Item* searchItem(int id) {
    Item* temp = head;
    while (temp != nullptr) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Delete item by ID
void deleteItem(int id) {
    Item *temp = head, *prev = nullptr;
    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Item not found.\n";
        return;
    }
    if (prev == nullptr)
        head = temp->next;
    else
        prev->next = temp->next;
    delete temp;
    cout << "Item deleted.\n";
}

// Save to file
void saveToFile(const string& filename) {
    ofstream file(filename);
    Item* temp = head;
    while (temp != nullptr) {
        file << temp->id << "," << temp->name << "," << temp->price << "," << temp->quantity << "\n";
        temp = temp->next;
    }
    file.close();
    cout << "Data saved to file.\n";
}

// Load from file
void loadFromFile(const string& filename) {
    ifstream file(filename);
    head = nullptr;
    int id, quantity;
    float price;
    string name, line;
    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);
        id = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        price = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        quantity = stoi(line.substr(pos3 + 1));
        addItem(id, name, price, quantity);
    }
    file.close();
    cout << "Data loaded from file.\n";
}

// Main menu
int main() {
    int choice, id, quantity;
    float price;
    string name;
    string filename = "items.txt";

    loadFromFile(filename); // Load at startup

    do {
        cout << "\n1. Add Item\n2. Display Items\n3. Search Item\n4. Delete Item\n5. Save to File\n6. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter ID, Name, Price, Quantity: ";
                cin >> id >> name >> price >> quantity;
                addItem(id, name, price, quantity);
                break;
            case 2:
                displayItems();
                break;
            case 3:
                cout << "Enter ID to search: ";
                cin >> id;
                {
                    Item* found = searchItem(id);
                    if (found)
                        cout << "Found - " << found->name << ", Price: " << found->price << ", Quantity: " << found->quantity << endl;
                    else
                        cout << "Item not found.\n";
                }
                break;
            case 4:
                cout << "Enter ID to delete: ";
                cin >> id;
                deleteItem(id);
                break;
            case 5:
                saveToFile(filename);
                break;
            case 6:
                saveToFile(filename); // Auto-save on exit
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
