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
            if (categories[i] == cat) {
                return true;
            }
        } return false;
    }
    // Helper function to read an integer with validation
    int readInteger() {
        int input;
        while (true) {
            if (cin >> input) {
                return input;
            } else {
                cout << "\nInvalid input! Please enter a number only: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    // Helper function to read a double with validation
    double readDouble() {
        double input;
        while (true) {
            if (cin >> input) {
                return input;
            } else {
                cout << "\nInvalid input! Please enter a valid price: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    // Helper function to check if a string contains only digits
    bool isDigitOnly(const string& str) {
        for (char const &c : str) {
            if (isdigit(c) == 0) return false;
        } return true;
    }
    // Helper function to check if a string contains only digits and decimal point
    bool isDecimalOnly(const string& str) {
        bool decimalPoint = false;
        for (char const &c : str) {
            if (isdigit(c) == 0) {
                if (c == '.' && !decimalPoint) {
                    decimalPoint = true;
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
    } public:
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
        // Input category
         cin.ignore();
         while (true) {
         clearScreen();
        cout << "Enter Category (Clothing, Electronics, Entertainment) or press 0 to go back: ";
        getline(cin, category);
    // Convert category to uppercase for case-insensitive comparison
    for (char& ch : category) {
        ch = toupper(ch);
    }
    // Check if the user wants to go back
    if (category == "0") {
        return;
    }
    // Check if the category is a single word
    if (category.find(' ') != string::npos) {
        cout << "\nInvalid category! Only one category is allowed per item.";
        cout <<"\n";
        pause();
        continue;
    }
    // Validate category
    if (!isValidCategory(category)) {
        cout << "\nCategory " << category << " does not exist!";
        cout <<"\n";
        pause();
        continue;
    } break; // Valid category entered
}
        // Input ID
        while (true) {
            cout << "Enter ID: ";
            cin >> id;
            if(idExists(id)) {
                cout << "\nID already exists, Make different ID!\n";
                continue;
            } if (id.empty()) {
                cout << "\nID cannot be blank!\n";
                continue;
            }bool isValidID = true;
            for (char& ch : id) {
                if (!isalnum(ch)) {
                    isValidID = false;
                    break;
                }
            } if (!isValidID) {
                cout << "\nID should contain only letters and numbers!\n";
                continue;
            } break; // Valid ID entered
        }
        // Input name
        while (true) {
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            if (name.empty()) {
                cout << "\nName cannot be blank!\n";
                continue;
            } break; // Valid name entered
        }
        // Input quantity
        while (true) {
            cout << "Enter quantity: ";
            string input;
            cin >> input;
            if (input.empty()) {
                cout << "\nQuantity cannot be blank!\n";
                continue;
            } if (!isDigitOnly(input)) {
                cout << "\nQuantity should contain only digits!\n";
                continue;
            } quantity = stoi(input);
            if (quantity <= 0) {
                cout << "\nQuantity should be a positive number!\n";
                continue;
            } break; // Valid quantity entered
        }
        // Input price
        while (true) {
            cout << "Enter price: ";
            string input;
            cin >> input;
            if (input.empty()) {
                cout << "\nPrice cannot be blank!\n";
                continue;
            } if (!isDecimalOnly(input)) {
                cout << "\nPrice should contain only digits and decimals!\n";
                continue;
            } price = stod(input);
            if (price <= 0) {
                cout << "\nPrice should be a positive number!\n";
                continue;
            } break; // Valid price entered
        }
        // Add item to the inventory
        items[itemCount++] = new Item(id, name, quantity, price, category);
        cout << "\nItem added successfully!" << endl;
    }
    // Update Item
    void UpdateItem() override {
    if (itemCount == 0) {
        cout << "No items to update!" << endl;
        return;
    } string id;
    cout << "Enter Item ID to update: ";
    cin >> id;
    // Search for item by ID
    int index = -1;
    for (int i = 0; i < itemCount; i++) {
        if (items[i]->getID() == id) {
            index = i;
            break;
        }
    } if (index == -1) {
        cout << "Item not found!" << endl;
        return;
    } int updateOption;
    while (true) {
        cout << "What do you want to update? (1 for Quantity, 2 for Price): ";
        string input;
        cin >> input;
        if (input.length() != 1 || !isdigit(input[0])) {
            cout << "\nInvalid input! Please enter a number only (1 or 2)." << endl;
            pause();
            clearScreen();
            continue;
        } updateOption = stoi(input);
        if (updateOption != 1 && updateOption != 2) {
            cout << "\nInvalid choice! Please enter a valid choice (1 or 2)." << endl;
            pause();
            clearScreen();
            continue;
        } break;
    } switch (updateOption) {
        case 1: {
            int newQuantity;
            while (true) {
                cout << "Enter new quantity: ";
                string input;
                cin >> input;
                if (input.empty()) {
                    cout << "\nQuantity cannot be blank!\n";
                    continue;
                } if (!isDigitOnly(input)) {
                    cout << "\nQuantity should contain only digits!\n";
                    continue;
                } newQuantity = stoi(input);
                if (newQuantity <= 0) {
                    cout << "\nQuantity should be a positive number!\n";
                    continue;
                } break; // Valid quantity entered
            }
            // Update and show success message
            int oldQuantity = items[index]->getQuantity();
            items[index]->setQuantity(newQuantity);
            cout << "\nQuantity of Item " << items[index]->getName() << " updated from " 
                 << oldQuantity << " to " << newQuantity << endl;
            break;
        } case 2: {
            double newPrice;
            while (true) {
                cout << "Enter new price: ";
                string input;
                cin >> input;
                if (input.empty()) {
                    cout << "\nPrice cannot be blank!\n";
                    continue;
                } if (!isDecimalOnly(input)) {
                    cout << "\nPrice should contain only digits and decimal!\n";
                    continue;
                } newPrice = stod(input);
                if (newPrice <= 0) {
                    cout << "\nPrice should be a positive number!\n";
                    continue;
                } break; // Valid price entered
            }
            // Update and show success message
            double oldPrice = items[index]->getPrice();
            items[index]->setPrice(newPrice);
            cout << "\nPrice of Item " << items[index]->getName() << " updated from " 
                 << oldPrice << " to " << newPrice << endl;
            break;
        } default:
            cout << "\nInvalid choice!" << endl;
            break;
    }
}
    // Remove Item
    void RemoveItem() override {
        if (itemCount == 0) {
            cout << "No items to remove!" << endl;
            return;
        } string id;
        cout << "Enter Item ID to remove: ";
        cin >> id;
        // Search for item by ID
        int index = -1;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getID() == id) {
                index = i;
                break;
            }
        } if (index == -1) {
            cout << "\nItem not found!" << endl;
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
         while (true) {
         clearScreen();
        cout << "Enter Category (Clothing, Electronics, Entertainment) or press 0 to go back: ";
        getline(cin, category);
          // Convert category to uppercase for case-insensitive comparison
        for (char& ch : category) {
        ch = toupper(ch);
        } if (category == "0") {
        return;
        } if (category.find(' ') != string::npos) {
        cout << "\nInvalid category! Only one category is allowed per item.";
        cout <<"\n";
        pause();
        continue;
          } if (!isValidCategory(category)) {
        cout << "\nCategory " << category << " does not exist!";
        cout <<"\n";
        pause();
        continue;
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
            } return; // Return after displaying items
        }
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
    cout << "Enter Item ID to search: ";
    cin >> id;
    for (char& ch : id) {
        ch = toupper(ch);
    }
    // Search for item by ID
    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        string itemId = items[i]->getID();
        for (char& ch : itemId) {
            ch = toupper(ch);
        } if (itemId == id) {
            // Display item details if found
            if (!found) {
                cout << "Item found!" << endl;
                cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
                cout << "---------------------------------------------------------------------" << endl;
            } cout << left << setw(10) << items[i]->getID() << setw(20) << items[i]->getName() << setw(10) << items[i]->getQuantity() << setw(10) << items[i]->getPrice() << setw(15) << items[i]->getCategory() << endl;
            found = true;
        }
    } if (!found) {
        cout << "Item not found!" << endl;
    }
}
// Sort items 
void SortItems() override {
    if (itemCount == 0) {
        cout << "No items to sort!" << endl;
        return;
    } cin.ignore();
    int sortOption;
    while (true) {
        cout << "Do you want to sort by (1) Quantity or (2) Price? ";
        string input;
        cin >> input;
        if (input.length() != 1 || !isdigit(input[0])) {
            cout << "\nInvalid input! Please enter a number only (1 or 2)." << endl;
            pause();
            clearScreen();
            continue;
        } sortOption = stoi(input);
        if (sortOption != 1 && sortOption != 2) {
            cout << "\nInvalid choice! Please enter a valid choice (1 or 2)." << endl;
            pause();
            clearScreen();
            continue;
        } break;
    } int sortOrder;
    while (true) {
        cout << "Do you want to sort in (1) Ascending or (2) Descending order? ";
        string input;
        cin >> input;
        if (input.length() != 1 || !isdigit(input[0])) {
            cout << "\nInvalid input! Please enter a number only (1 or 2)." << endl;
            pause();
            clearScreen();
            continue;
        } sortOrder = stoi(input);
        if (sortOrder != 1 && sortOrder != 2) {
            cout << "\nInvalid choice! Please enter a valid choice (1 or 2)." << endl;
            pause();
            clearScreen();
            continue;
        } break;
    } switch (sortOption) {
        case 1:
            if (sortOrder == 1) {
                // Simple bubble sort by name in ascending order
                for (int i = 0; i < itemCount - 1; i++) {
                    for (int j = 0; j < itemCount - i - 1; j++) {
                        if (items[j]->getQuantity() > items[j + 1]->getQuantity()) {
                            swap(items[j], items[j + 1]);
                        }
                    }
                }
            } else {
                // Simple bubble sort by name in descending order
                for (int i = 0; i < itemCount - 1; i++) {
                    for (int j = 0; j < itemCount - i - 1; j++) {
                        if (items[j]->getQuantity() < items[j + 1]->getQuantity()) {
                            swap(items[j], items[j + 1]);
                        }
                    }
                }
            } cout << "\nAll items sorted by quantity!" << endl;
            cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            for (int i = 0; i < itemCount; i++) {
            cout << left << setw(10) << items[i]->getID() << setw(20) << items[i]->getName() << setw(10) << items[i]->getQuantity() << setw(10) << items[i]->getPrice() << setw(15) << items[i]->getCategory() << endl;
        } break;
            case 2:
            if (sortOrder == 1) {
                // Simple bubble sort by price in ascending order
                for (int i = 0; i < itemCount - 1; i++) {
                    for (int j = 0; j < itemCount - i - 1; j++) {
                        if (items[j]->getPrice() > items[j + 1]->getPrice()) {
                            swap(items[j], items[j + 1]);
                        }
                    }
                }
            } else {
                // Simple bubble sort by price in descending order
                for (int i = 0; i < itemCount - 1; i++) {
                    for (int j = 0; j < itemCount - i - 1; j++) {
                        if (items[j]->getPrice() < items[j + 1]->getPrice()) {
                            swap(items[j], items[j + 1]);
                        }
                    }
                }
            } cout << "\nAll items sorted by price!" << endl;
            cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            for (int i = 0; i < itemCount; i++) {
            cout << left << setw(10) << items[i]->getID() << setw(20) << items[i]->getName() << setw(10) << items[i]->getQuantity() << setw(10) << items[i]->getPrice() << setw(15) << items[i]->getCategory() << endl;
        } break;
        default:
            cout << "\nInvalid choice! Please enter a valid choice (1 or 2)." << endl;
            break;
    }
}
// Display low stock items
 void DisplayLowStockItems() override {
    if (itemCount == 0) {
        cout << "No items to display!" << endl;
        return;
    } bool found = false;
      for (int i = 0; i < itemCount; i++) {
        if (items[i]->getQuantity() < 5) {
            found = true;
            break; // exit the loop as soon as we find a low stock item
        }
    } if (found) {
        cout << "Low stock items (less than 5):" << endl;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getQuantity() < 5) {
                cout << left << setw(10) << items[i]->getID() << setw(20 ) << items[i]->getName() << setw(10) << items[i]->getQuantity() << setw(10) << items[i]->getPrice() << setw(15) << items[i]->getCategory() << endl;
            }
        }
    } else {
        cout << "No low stock items found!" << endl;
    }
}
   // Show menu
    void ShowMenu() override {
    bool isValid = true;
    while (isValid) {
        clearScreen();
        cout << "\n--- Inventory Management Menu ---" << endl;
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
        string input;
        cin >> input;
        if (isDigitOnly(input)) {
            int choice = stoi(input);
            if (choice >= 1 && choice <= 9) {
                switch (choice) {
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
)" << endl;
                        break;
                }
            } else {
                cout << "\nInvalid choice! Please choose a number between 1 and 9." << endl;
                pause();
            }
        } else  {
            cout << "\nInvalid input! Please enter a number only." << endl;
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