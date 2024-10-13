// Coded by Esquillo, Christian / Inventory Management System / Midterm Project 
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

// Abstract class for inventory system
class InventorySystem {
public:
    virtual void AddItem() = 0;
    virtual void UpdateItem() = 0;
    virtual void RemoveItem() = 0;
    virtual void DisplayItemCategory() = 0;
    virtual void DisplayAllItems() = 0;
    virtual void SearchItem() = 0;
    virtual void SortItems() = 0;
    virtual void DisplayLowStockItems() = 0;
    virtual void ShowMenu() = 0;
};

// Class representing an individual item
class Item {
private:
    string ID;
    string name;
    int quantity;
    double price;
    string category;

public:
    // Constructor
    Item(string id, string n, int q, double p, string cat) : ID(id), name(n), quantity(q), price(p), category(cat) {}

    // Getters
    string getID() const { return ID; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }

    // Setters
    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }
};

// Class for managing inventory operations
class InventoryManager : public InventorySystem {
private:
    Item* items[100];  // Array to store items
    int itemCount = 0;  // Count of items
    const string categories[3] = {"CLOTHING", "ELECTRONICS", "ENTERTAINMENT"}; // Valid categories

    // Helper function to validate category
    bool isValidCategory(string cat) {
        for (int i = 0; i < 3; i++) {
            if (cat == categories[i]) {
                return true;
            }
        } return false;
    }

    // Helper function to check if a string contains only digits and no spaces
    bool isDigitOnly(const string& str) {
        for (char const &c : str) {
            if (!isdigit(c)) {
                return false;
            }
        } return true;
    }

    // Helper function to check if a string contains only digits, one decimal point, and no spaces
    bool isDecimalOnly(const string& str) {
        bool decimalPoint = false;
        for (char const &c : str) {
            if (!isdigit(c)) {
                if (c == '.' && !decimalPoint) {
                    decimalPoint = true; // Allow only one decimal point
                } else {
                    return false;
                }
            }
        } return true;
    }

    // Helper function to generate a unique item ID
    bool idExists(const string& id) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getID() == id) {
                return true;
            }
        } return false;
    }

public:
    // Function to clear the screen
    void clearScreen() {
        system("cls");
    }

    // Function to pause the program
    void pause() {
        system("pause");
    }

// Add Item
void AddItem() override {
    string id, name, category;
    int quantity;
    double price;
    bool validCategory = false, validId = false, validName = false, validQuantity = false, validPrice = false;

    // Input category
    cin.ignore();
    while (!validCategory) {
        clearScreen();
        cout << "Enter Category (Clothing, Electronics, Entertainment) or press 0 to go back: "; getline(cin, category);
        if (category.find(' ') != string::npos || category.empty()) {
            cout << "\nInvalid category! Category cannot contain spaces or be empty.\n";
            pause();
        } else {
            // Convert category to uppercase for case-insensitive comparison
            for (char& ch : category) {
                ch = toupper(ch);
            }
            // Check if the user wants to go back
            if (category == "0") {
                return;
            }
            // Validate category
            if (!isValidCategory(category)) {
                cout << "\nCategory " << category << " does not exist!";
                cout << "\n"; pause();
            } else {
                validCategory = true; // Valid category entered
            }
        }
    }

    // Input ID
    while (!validId) {
        cout << "Enter ID: "; getline(cin, id);
        if (id.empty()) {
            cout << "\nID cannot be blank!\n";
        } else if (idExists(id)) {
            cout << "\nID already exists, Make different ID!\n";
        } else {
            validId = true; // Valid ID entered
        }
    }

    // Input name
    while (!validName) {
        cout << "Enter name: "; getline(cin, name);
        if (name.empty()) {
            cout << "\nName cannot be blank!\n";
        } else {
            validName = true; // Valid name entered
        }
    }

    // Input quantity
    while (!validQuantity) {
        string input;
        cout << "Enter quantity: "; getline(cin, input);
        if (!isDigitOnly(input)) {
            cout << "\nQuantity should contain only digits and no spaces!\n";
        } else if (input.empty()) {
            cout << "\nQuantity cannot be blank!\n";
        } else {
            try {
            quantity = stoi(input);
            if (quantity <= 0) {
                cout << "\nQuantity should be a positive number!\n";
            } else {
                validQuantity = true; // Valid quantity entered
            }
        } catch (const out_of_range& e) {
                cout << "\nQuantity is out of range. Please enter a valid quantity.\n";
            }
        }
    }

    // Input price
    while (!validPrice) {
        string input;
        cout << "Enter price: "; getline(cin, input);
        if (!isDecimalOnly(input)) {
            cout << "\nPrice should contain only digits, decimal point, and no spaces!\n";
        } else if (input.empty()) {
            cout << "\nPrice cannot be blank!\n";
        } else {
            price = stod(input);
            if (price <= 0) {
                cout << "\nPrice should be a positive number!\n";
            } else {
                validPrice = true; // Valid price entered
            }
        } 
    }  

    // Add item to the inventory
    items[itemCount++] = new Item(id, name, quantity, price, category);
    cout << "\nItem added successfully!\n";
}

    // Update Item
void UpdateItem() override {
    if (itemCount == 0) {
        cout << "No items to update!\n";
        return;
    } string id;
      cout << "Enter Item ID to update: "; cin.ignore(); getline(cin, id);

    // Search for item by ID
    int index = -1;
    for (int i = 0; i < itemCount; i++) {
        if (items[i]->getID() == id) {
            index = i;
            break;
        }
    } if (index == -1) {
        cout << "Item not found!\n";
        cout << "\nReturning To Menu...\n";
        return;
    } char updateOption;
    bool validOption = true;
    while(validOption) {
        cout << "What do you want to update? (Q for Quantity, P for Price): "; cin >> updateOption; 
        updateOption = toupper(updateOption);
        if (cin.fail()) { 
            cin.clear(); cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter 'Q' for quantity or 'P' for price.\n";
            continue;
        } if (cin.peek() != '\n') {
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter 'Q' for quantity or 'P' for price.\n";
            continue;
        } if (updateOption != 'Q' && updateOption != 'P') {
            cout << "\nInvalid choice! Please enter 'Q' for quantity or 'P' for price.\n";
            continue;
        } validOption = false;
    } if (updateOption == 'Q') {
        int newQuantity;
        bool validNewQuantity = true;
            while (validNewQuantity) {
                cout << "Enter new quantity: "; cin >> newQuantity; 
                if (cin.fail()) {
                    cin.clear(); cin.ignore(10000, '\n');
                    cout << "\nInvalid input! Please enter a number.\n";
                } else if (cin.peek() != '\n') {
                    cin.ignore(10000, '\n');
                    cout << "\nQuantity should contain only digits and no spaces!\n";
              } else if (newQuantity <= 0) {
                   cout << "\nQuantity should be a positive number!\n";
             } else if (newQuantity == items[index]->getQuantity()) {
                 cout << "\nInvalid input! The quantity you entered is already the current quantity.\n";
            } else {
              validNewQuantity = false; // exit the loop if all conditions are met
        }
    }

        // Update and show success message
        int oldQuantity = items[index]->getQuantity();
        items[index]->setQuantity(newQuantity);
        cout << "\nQuantity of Item " << items[index]->getName() << " updated from " << oldQuantity << " to " << newQuantity << endl;
    } else if (updateOption == 'P') {
        double newPrice;
        bool validPrice = false;
        while (!validPrice) {
                cout << "Enter new price: "; cin >> newPrice; 
                if (cin.fail()) {
                cin.clear(); cin.ignore(10000, '\n');
                cout << "\nInvalid input! Please enter a number.\n";
        } else if (cin.peek() != '\n') {
                cin.ignore(10000, '\n');
                cout << "\nPrice should contain only digits, decimal point, and no spaces!\n";
        } else if (newPrice <= 0) {
                cout << "\nPrice should be a positive number!\n";
        } else if (newPrice == items[index]->getPrice()) {
                cout << "\nInvalid input! The price you entered is already the current price.\n";
        } else {
            validPrice = true; // Valid price entered
        }
    }
        double oldPrice = items[index]->getPrice();
        items[index]->setPrice(newPrice);
        cout << "\nPrice of Item " << items[index]->getName() << " updated from " << oldPrice << " to " << newPrice << endl;
    }
}
    // Remove Item
    void RemoveItem() override {
        if (itemCount == 0) {
            cout << "No items to remove!\n";
            return;
        } string id;
          cout << "Enter Item ID to remove: "; cin.ignore(); getline(cin, id);
          int index = -1;
          for (int i = 0; i < itemCount; i++) {
             if (items[i]->getID() == id) {
                 index = i;
                 break;
            }
        } if (index == -1) {
            cout << "Item not found!\n";
            cout << "\nReturning To Menu...\n";
            return;
        }

        // Display removal message and shift items in the array
        cout << "\nItem " << items[index]->getName() << " has been removed from the inventory." << endl;
        // Shift items to remove the deleted item
        for (int i = index; i < itemCount - 1; i++) {
            items[i] = items[i + 1];
        } itemCount--; // Reduce the item count
    }

    // Display items by category
    void DisplayItemCategory() override {
    if (itemCount == 0) {
        cout << "No items to display!" << endl;
        return;
    } string category;
    cin.ignore();
    bool validCategory = false;
    while (!validCategory) {
        clearScreen();
        cout << "Enter Category (Clothing, Electronics, Entertainment) or press 0 to go back: "; getline(cin, category);
        if (category.find(' ') != string::npos || category.empty()) {
            cout << "\nInvalid category! Category cannot contain spaces or be empty.\n"; pause();
        } else {
            // Convert category to uppercase for case-insensitive comparison
            for (char& ch : category) {
                ch = toupper(ch);
            } if (category == "0") {
                return;
            }
            // Validate category
            if (!isValidCategory(category)) {
                cout << "\nCategory " << category << " does not exist!";
                cout << "\n";
                pause();
            } else {
                validCategory = true; // Valid category entered
            }
        }
    }

    // Display items in the category
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        if (items[i]->getCategory() == category) {
            cout << left << setw(10) << items[i]->getID() << setw(20) << items[i]->getName() << setw(10) << items[i]->getPrice() << setw(10) << items[i]->getQuantity() << endl;
            found = true;
        }
    } if (!found) {
        cout << "No items found in this category!" << endl;
    } return; 
}

    // Display all items
    void DisplayAllItems() override {
        if (itemCount == 0) {
            cout << "No items to display!" << endl;
            return;
        } cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
          cout << "---------------------------------------------------------------------" << endl;
          for (int i = 0; i < itemCount; i++) {
          cout << left << setw(10) << items[i]->getID() << setw(20) << items[i]->getName() << setw(10) << items[i]->getQuantity() << setw(10) << items[i]->getPrice() << setw(15) << items[i]->getCategory() << endl;
        }
    }

    // Search item
    void SearchItem() override {
        if (itemCount == 0) {
            cout << "No items to search!" << endl;
            return;
        } string id;
          cout << "Enter Item ID to search: "; cin.ignore(); getline(cin, id);
          for (char& ch : id) {
              ch = toupper(ch);
        } bool found = false;
          for (int i = 0; i < itemCount; i++) {
            string itemId = items[i]->getID();
            for (char& ch : itemId) {
                ch = toupper(ch);
            } if (itemId == id) {
                // Display item details if found
                if (!found) {
                    cout << "Displaying Items that have same or similar ID to '" << id << "':\n";
                    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
                    cout << "---------------------------------------------------------------------" << endl;
                } cout << left << setw(10) << items[i]->getID() << setw(20) << items[i]->getName() << setw(10) << items[i]->getQuantity() << setw(10) << items[i]->getPrice() << setw(15) << items[i]->getCategory() << endl;
                  found = true;
            }
        } if (!found) {
            cout << "Item not found!\n";
            cout << "\nReturning To Menu...\n";
        }
    }

// Sort items 
void SortItems() override {
    if (itemCount == 0) {
        cout << "No items to sort" << endl;
        return;
    } int sortOption;
      char type, order;
      bool validType = true; bool validOrder = true;
        while(validType) {
        cout << "Do you want to sort by (Q) Quantity or (P) Price? "; cin >> type;
        type = toupper(type);
        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter 'Q' for quantity or 'P' for price.\n";
            continue;
        } if (cin.peek() != '\n') {
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter 'Q' for quantity or 'P' for price.\n";
            continue;
        } if (type != 'Q' && type != 'P') {
            cout << "\nInvalid input! Please enter 'Q' for quantity or 'P' for price.\n";
            continue;
        } validType = false;
    } 
    while(validOrder) {
        cout << "Do you want to sort in (A) Ascending or (D) Descending order? "; cin >> order;
        order = toupper(order);
        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter 'A' for ascending or 'D' for descending.\n";
            continue;
        } if (cin.peek() != '\n') {
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter 'A' for ascending or 'D' for descending.\n";
            continue;
        } if (order != 'A' && order != 'D') {
            cout << "\nInvalid input! Please enter 'A' for ascending or 'D' for descending.\n";
            continue;
        } validOrder = false;
    } for (int i = 0; i < itemCount - 1; ++i) {
        for (int j = 0; j < itemCount - i - 1; ++j) {
            bool exchangeCondition = false;
            if (type == 'Q') {
                exchangeCondition = (order == 'A') ? (items[j]->getQuantity() > items[j + 1]->getQuantity()) : (items[j]->getQuantity() < items[j + 1]->getQuantity());
            } else if (type == 'P') {
                exchangeCondition = (order == 'A') ? (items[j]->getPrice() > items[j + 1]->getPrice()) : (items[j]->getPrice() < items[j + 1]->getPrice());
            } if (exchangeCondition) {
              swap(items[j], items[j + 1]);
            }
        }
    } if (type == 'Q') {
        cout << "\nAll items sorted by quantity!\n";
    } else {
        cout << "\nAll items sorted by price!\n";
    }
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    for (int i = 0; i < itemCount; i++) {
    cout << left << setw(10) << items[i]->getID() << setw(20) << items[i]->getName() << setw(10) << items[i]->getQuantity() << setw(10) << items[i]->getPrice() << setw(15) << items[i]->getCategory() << endl;
    }
}


    // Display low stock items
    void DisplayLowStockItems() override {
        if (itemCount == 0) {
            cout << "No items to display!\n";
            return;
        } bool found = false;
          for (int i = 0; i < itemCount; i++) {
             if (items[i]->getQuantity() < 6) {
                found = true;
                break; // exit the loop as soon as we find a low stock item
            }
        } if (found) {
            cout << "Low stock items (quantity of 5 and below):" << endl;
            cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            for (int i = 0; i < itemCount; i++) {
                if ( items[i]->getQuantity() < 6) {
                    cout << left << setw(10) << items[i]->getID() << setw(20) << items[i]->getName() << setw(10) << items[i]->getQuantity() << setw(10) << items[i]->getPrice() << setw(15) << items[i]->getCategory() << endl;
                }
            }
        } else {
          cout << "No low stock items found!\n";
        }
    }

    // Show menu
    void ShowMenu() override {
    bool isValid = true;
    while (isValid) {
        clearScreen();
        cout << "\n--- Inventory Management Menu ---\n";
        cout << "1. Add Item\n";
        cout << "2. Update Item\n";
        cout << "3. Remove Item\n";
        cout << "4. Display Items by Category\n";
        cout << "5. Display All Items\n";
        cout << "6. Search Item\n";
        cout << "7. Sort Items\n";
        cout << "8. Display Low Stock Items\n";
        cout << "9. Exit\n";
        cout << "\nChoose an option: ";
        int input;
        cin >> input;
        if(cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number between 1 and 9.\n";
            cout << endl;
            pause();
            continue;
        } if (cin.peek() != '\n') {
            cin.ignore(10000, '\n'); 
            cout << "\nInvalid input! Please enter a number between 1 and 9 without exw characters.\n";
            cout << endl;
            pause();
            continue;
        } if (input < 1 || input > 9) {
            cout << "\nInvalid input! Please enter a number between 1 and 9.\n";
            cout << endl;
            pause();
            continue; 
        } switch (input) {
                    case 1: clearScreen(); AddItem(); pause(); break;
                    case 2: clearScreen(); UpdateItem(); pause(); break;
                    case 3: clearScreen(); RemoveItem(); pause(); break;
                    case 4: clearScreen(); DisplayItemCategory(); pause(); break;
                    case 5: clearScreen(); DisplayAllItems(); pause(); break;
                    case 6: clearScreen(); SearchItem(); pause(); break;
                    case 7: clearScreen(); SortItems(); pause(); break;
                    case 8: clearScreen(); DisplayLowStockItems(); pause(); break;
                    case 9: clearScreen(); isValid = false;
                        cout << R"(  ______      _ _   _               _____                                           _______ _                 _     __     __         _ 
 |  ____|    (_) | (_)             |  __ \                                         |__   __| |               | |    \ \   / /        | |
 | |__  __  ___| |_ _ _ __   __ _  | |__) | __ ___   __ _ _ __ __ _ _ __ ___          | |  | |__   __ _ _ __ | | __  \ \_/ /__  _   _| |
 |  __| \ \/ / | __| | '_ \ / _` | |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \         | |  | '_ \ / _` | '_ \| |/ /   \   / _ \| | | | |
 | |____ >  <| | |_| | | | | (_| | | |   | | | (_) | (_| | | | (_| | | | | | |_ _     | |  | | | | (_| | | | |   <     | | (_) | |_| |_|
 |______/_/\_\_|\__|_|_| |_|\__, | |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_(_|_)    |_|  |_| |_|\__,_|_| |_|_|\_\    |_|\___/ \__,_(_)
                             __/ |                   __/ |                                                                              
                            |___/                   |___/                                                                               
)" << endl; break;
                default:
                cout << "\nInvalid choice!\n\n";
                pause();
            }
         }
    }
};

int main() {
    InventoryManager manager;
    manager.ShowMenu();
    return 0;
}
