#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib> // for system("clear") or system("cls")
using namespace std;
#ifdef _WIN32
    const string CLEAR_CONSOLE = "cls";
#else
    const string CLEAR_CONSOLE = "clear";
#endif

class User {
private:
    string username;
    string password;
    bool isAdmin;

public:
    User(const string& username, const string& password, bool isAdmin = false)
        : username(username), password(password), isAdmin(isAdmin) {}

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    bool isAdminUser() const {
        return isAdmin;
    }
};

class Product {
private:
    string name;
    string brand;
    double price;

public:
    Product(const string& name, const string& brand, double price)
        : name(name), brand(brand), price(price) {}

    string getName() const {
        return name;
    }

    string getBrand() const {
        return brand;
    }

    double getPrice() const {
        return price;
    }
};

class Inventory {
private:
    vector<Product> products;

public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    vector<Product>& getProducts() {
        return products;
    }

    void displayProducts() const {
        cout << "Inventory:\n";
        cout << "------------------------------------------------\n";
        cout << "|   Product    |     Brand      |    Price     |\n";
        cout << "------------------------------------------------\n";
        for (const auto& product : products) {
            cout << "| " << setw(12) << left << product.getName() << " | "
                      << setw(14) << left << product.getBrand() << " | "
                      << setw(10) << fixed << setprecision(2) << right << product.getPrice() << " |\n";
        }
        cout << "------------------------------------------------\n";
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& product : products) {
                file << product.getName() << "," << product.getBrand() << "," << product.getPrice() << "\n";
            }
            file.close();
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            products.clear();
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, brand;
                double price;
                getline(ss, name, ',');
                getline(ss, brand, ',');
                ss >> price;
                products.push_back(Product(name, brand, price));
            }
            file.close();
        }
    }
};

class UserManager {
private:
    vector<User> users;

public:
    void addUser(const User& user) {
        users.push_back(user);
    }

    bool isUserExist(const string& username) const {
        for (const auto& user : users) {
            if (user.getUsername() == username) {
                return true;
            }
        }
        return false;
    }

    bool authenticateUser(const string& username, const string& password) const {
        for (const auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                return true;
            }
        }
        return false;
    }

    bool isAdminUser(const string& username) const {
        for (const auto& user : users) {
            if (user.getUsername() == username && user.isAdminUser()) {
                return true;
            }
        }
        return false;
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& user : users) {
                file << user.getUsername() << "," << user.getPassword() << "," << user.isAdminUser() << "\n";
            }
            file.close();
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            users.clear();
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string username, password;
                bool isAdmin;
                getline(ss, username, ',');
                getline(ss, password, ',');
                ss >> isAdmin;
                users.push_back(User(username, password, isAdmin));
            }
            file.close();
        }
    }
};

class ShoppingCart {
private:
    vector<Product> items;

public:
    void addItem(const Product& product) {
        items.push_back(product);
    }

    void displayItems() const {
        if (items.empty()) {
            cout << "Your cart is empty.\n";
        }
        else {
            cout << "Your Cart:\n";
            cout << "------------------------------------------------\n";
            cout << "|   Product    |     Brand      |    Price     |\n";
            cout << "------------------------------------------------\n";
            for (const auto& item : items) {
                cout << "| " << setw(12) << left << item.getName() << " | "
                          << setw(14) << left << item.getBrand() << " | "
                          << setw(10) << fixed << setprecision(2) << right << item.getPrice() << " |\n";
            }
            cout << "------------------------------------------------\n";
        }
    }
};

void clearConsole() {
    system(CLEAR_CONSOLE.c_str());
}

int main() {
    UserManager userManager;
    Inventory inventory;
    ShoppingCart cart;

    // Load users from file
    userManager.loadFromFile("users.txt");

    // Load products from file
    inventory.loadFromFile("inventory.txt");
    inventory.addProduct(Product("Smartphone", "Apple", 999.99));
    inventory.addProduct(Product("Laptop", "Dell", 1299.99));
    inventory.addProduct(Product("Tablet", "Samsung", 599.99));
    inventory.addProduct(Product("Smartwatch", "Fitbit", 199.99));
    inventory.addProduct(Product("Headphones", "Sony", 149.99));
    inventory.addProduct(Product("Camera", "Canon", 699.99));
    inventory.addProduct(Product("Printer", "HP", 299.99));
    inventory.addProduct(Product("Gaming Console", "Microsoft", 499.99));
    inventory.addProduct(Product("Wireless Earbuds", "Jabra", 129.99));
    inventory.addProduct(Product("Smart Speaker", "Amazon", 79.99));
    inventory.addProduct(Product("External Hard Drive", "Western Digital", 149.99));
    inventory.addProduct(Product("Monitor", "LG", 399.99));
    inventory.addProduct(Product("Keyboard", "Logitech", 69.99));
    inventory.addProduct(Product("Mouse", "Razer", 49.99));
    inventory.addProduct(Product("VR Headset", "Oculus", 299.99));
    inventory.addProduct(Product("Router", "TP-Link", 89.99));
    inventory.addProduct(Product("Graphics Card", "NVIDIA", 699.99));
    inventory.addProduct(Product("SSD", "Samsung", 179.99));
    inventory.addProduct(Product("Gaming Chair", "DXRacer", 249.99));
    inventory.addProduct(Product("Microphone", "Blue", 99.99));

    string username, password;
    string action;
    bool loggedIn = false;
    bool isAdmin = false;

    while (true) {
        clearConsole();
        cout << "Welcome to the Tech Shop website!\n";
        cout << "----------------------------------------\n";
        if (!loggedIn) {
            cout << "| 1. Sign up                            |\n";
            cout << "| 2. Login                              |\n";
            cout << "| 3. Exit                               |\n";
            cout << "----------------------------------------\n";
            cout << "Your choice: ";
            cin >> action;
            cout << "----------------------------------------\n";

            if (action == "1") {
                clearConsole();
                cout << "Enter a new username: ";
                cin >> username;
                cout << "Enter a new password: ";
                cin >> password;

                if (userManager.isUserExist(username)) {
                    cout << "Username already exists. Please try again.\n";
                }
                else {
                    userManager.addUser(User(username, password));
                    userManager.saveToFile("users.txt");
                    cout << "User created successfully. Please login.\n";
                }

                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
            else if (action == "2") {
                clearConsole();
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;

                if (userManager.authenticateUser(username, password)) {
                    loggedIn = true;
                    isAdmin = userManager.isAdminUser(username);
                    cout << "Login successful!\n";
                }
                else {
                    cout << "Invalid username or password. Please try again.\n";
                }

                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
            else if (action == "3") {
                clearConsole();
                cout << "Thank you for using the Tech Shop website!\n";
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n";
                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
        }
        else {
            if (isAdmin) {
                cout << "| 1. Add product to inventory           |\n";
                cout << "| 2. Display inventory                  |\n";
                cout << "| 3. Display shopping cart              |\n";
                cout << "| 4. Logout                             |\n";
                cout << "----------------------------------------\n";
                cout << "Your choice: ";
                cin >> action;
                cout << "----------------------------------------\n";

                if (action == "1") {
                    clearConsole();
                    string name, brand;
                    double price;

                    cout << "Enter the product name: ";
                    cin >> name;
                    cout << "Enter the product brand: ";
                    cin >> brand;
                    cout << "Enter the product price: ";
                    cin >> price;

                    inventory.addProduct(Product(name, brand, price));
                    inventory.saveToFile("inventory.txt");
                    cout << "Product added successfully.\n";

                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                else if (action == "2") {
                    clearConsole();
                    inventory.displayProducts();

                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                else if (action == "3") {
                    clearConsole();
                    cart.displayItems();

                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                else if (action == "4") {
                    loggedIn = false;
                }
                else {
                    cout << "Invalid choice. Please try again.\n";
                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                }
            }
            else {
                cout << "| 1. Display inventory                  |\n";
                cout << "| 2. Add product to shopping cart       |\n";
                cout << "| 3. Display shopping cart              |\n";
                cout << "| 4. Logout                             |\n";
                cout << "----------------------------------------\n";
                cout << "Your choice: ";
                cin >> action;
                cout << "----------------------------------------\n";

                if (action == "1") {
                    clearConsole();
                    inventory.displayProducts();

                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                else if (action == "2") {
    clearConsole();
    cout << "Current Inventory:\n";
    inventory.displayProducts(); // Display the inventory

    string productName;
    cout << "Enter the product name: ";
    cin >> productName;

    bool productFound = false;
    for (const auto& product : inventory.getProducts()) {
        if (product.getName() == productName) {
            cart.addItem(product);
            productFound = true;
            break;
        }
    }

    if (productFound) {
        cout << "Product added to cart.\n";
    }
    else {
        cout << "Product not found.\n";
    }

    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}


                else if (action == "3") {
                    clearConsole();
                    cart.displayItems();

                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                else if (action == "4") {
                    loggedIn = false;
                }
                else {
                    cout << "Invalid choice. Please try again.\n";
                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                }
            }
        }
    }

    return 0;
}
