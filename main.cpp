#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
#include <vector>

using namespace std;

//  class for grocery items
class GroceryItem {
public:
    GroceryItem(string name, float originalPrice, float discountRate)
        : name(name), originalPrice(originalPrice), discountRate(discountRate) {}

    virtual ~GroceryItem() {}

    virtual float calculateDiscountedPrice() const {
        return (1 - discountRate) * originalPrice;
    }

    string getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    float getDiscountRate() const {
        return discountRate;
    }

    virtual void print() const {
        cout << name << " per unit, $" << fixed << setprecision(2) << calculateDiscountedPrice() << " ";
    }

protected:
    string name;
    float originalPrice;
    float discountRate;
    int quantity = 0;
};

// class for fruits
class Fruit : public GroceryItem {
public:
    Fruit(string name, float originalPrice, float discountRate)
        : GroceryItem(name, originalPrice, discountRate) {}

    void print() const override {
        GroceryItem::print();
        cout << "(" << int(getDiscountRate() * 100) << "% off sale!)\n";
    }
};

// class for vegetables
class Vegetable : public GroceryItem {
public:
    Vegetable(string name, float originalPrice, float discountRate)
        : GroceryItem(name, originalPrice, discountRate) {}

    void print() const override {
        GroceryItem::print();
        cout << "(" << int(getDiscountRate() * 100) << "% off sale!)\n";
    }
};

// Function to print the welcome message
void printMessage() {
    cout << "\nWelcome to the supermarket!\n";
    cout << "We have a wide variety of groceries to purchase!\n";
}

// Function to get and validate float input
float getFloatInput() {
    float wallet;
    bool inputValidation = true;

    while (inputValidation) {
        cout << "\nEnter money to spend in US dollars and cents $";
        try {
            cin >> wallet;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Invalid Input! Please enter a number up to two decimal places.");
            }

            inputValidation = false;
        } catch (const runtime_error &e) {
            cout << e.what() << endl;
        }
    }

    return wallet;
}

// Function to calculate and display total cost
float calculateTotalCost(const vector<GroceryItem*>& cart) {
    float totalCost = 0.0;

    for (const auto& item : cart) {
        totalCost += item->calculateDiscountedPrice() * item->getQuantity();
    }

    return totalCost;
}

// Function to display items in the cart
void displayCart(const vector<GroceryItem*>& cart) {
    cout << "\nTotal Items In Cart:\n";

    for (const auto& item : cart) {
        for (int i = 0; i < item->getQuantity(); ++i) {
            cout << item->getName() << endl;
        }
    }
}

int main() {
    printMessage();
    float wallet = getFloatInput();

    // Create instances of fruits
    Fruit apple("Apple", 1.00, 0.20);
    Fruit banana("Banana", 1.50, 0.20);

    // Create instances of vegetables
    Vegetable carrot("Carrot", 1.00, 0.30);
    Vegetable broccoli("Broccoli", 1.50, 0.30);

    // Vector to store grocery items in the cart
    vector<GroceryItem*> cart;

    // Add items to the cart based on user input
    cout << "\nAre you looking at purchasing any fruit? ";
    cout << "(" << int(apple.getDiscountRate() * 100) << "% off sale!): ";
    string fruitPrompt;
    cin >> fruitPrompt;

    if (fruitPrompt == "y" || fruitPrompt == "Y" || fruitPrompt == "yes" || fruitPrompt == "Yes" || fruitPrompt == "YES") {
        cout << "Enter the amount of apples you want to purchase. Per unit, $" << fixed << setprecision(2) << float(apple.calculateDiscountedPrice()) << ": ";
        int appleQuantity;
        cin >> appleQuantity;
        apple.setQuantity(appleQuantity);
        cart.push_back(&apple);

        cout << "Enter the amount of bananas you want to purchase. Per unit, $" << fixed << setprecision(2) << float(banana.calculateDiscountedPrice()) << ": ";
        int bananaQuantity;
        cin >> bananaQuantity;
        banana.setQuantity(bananaQuantity);
        cart.push_back(&banana);
    } else if (fruitPrompt != "n" && fruitPrompt != "N" && fruitPrompt != "no" && fruitPrompt != "No" && fruitPrompt != "NO") {
        cout << "Did not understand your response, taking it as a no.\n";
    }

    cout << "\nAre you looking at purchasing any vegetables? ";
    cout << "(" << int(carrot.getDiscountRate() * 100) << "% off sale!): ";
    string vegPrompt;
    cin >> vegPrompt;

    if (vegPrompt == "y" || vegPrompt == "Y" || vegPrompt == "yes" || vegPrompt == "Yes" || vegPrompt == "YES") {
        cout << "Enter the amount of carrots you want to purchase. Per unit, $" << fixed << setprecision(2) << float(carrot.calculateDiscountedPrice()) << ": ";
        int carrotQuantity;
        cin >> carrotQuantity;
        carrot.setQuantity(carrotQuantity);
        cart.push_back(&carrot);

        cout << "Enter the amount of broccoli you want to purchase. Per unit, $" << fixed << setprecision(2) << float(broccoli.calculateDiscountedPrice()) << ": ";
        int broccoliQuantity;
        cin >> broccoliQuantity;
        broccoli.setQuantity(broccoliQuantity);
        cart.push_back(&broccoli);
    } else if (vegPrompt != "n" && vegPrompt != "N" && vegPrompt != "no" && vegPrompt != "No" && vegPrompt != "NO") {
        cout << "Did not understand your response, taking it as a no.\n";
    }

    // Calculate and display total cost
    float totalCost = calculateTotalCost(cart);
    cout << "\nTotal Cost of Items: $" << fixed << setprecision(2) << totalCost << endl;

   
    for (int i = 0; i < 50; ++i) {
        cout << "-";
    }

    // Tells the user if their purchase was successful
    if (totalCost == wallet || totalCost < wallet) {
        cout << "\n\nPurchase Successful!\n";

        // Tells the user if they have money leftover
        float balance = wallet - totalCost;
        cout << "Money Leftover: $" << fixed << setprecision(2) << balance << endl;
    }
    
    // Tells the user if their purchase failed
    if (totalCost > wallet) {
        cout << "\n\nPurchase Failed!\n";

        // Tells the user if they have money leftover
        float balance = totalCost - wallet;
        cout << "Money still owed: $" << fixed << setprecision(2) << balance << endl;
    }

   
    cout << "\n--------------------------------------------------\n";

    // Display items in the cart
    displayCart(cart);

    // Clean up memory by deleting items in the cart
    for (auto item : cart) {
        delete item;
    }

    return 0;
}
