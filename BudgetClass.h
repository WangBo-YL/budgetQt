//Budget Class Header File

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include "sqlite3.h"

class Budget {
private:
    std::string name = "Default";

    //Database calls.
    //Start a transaction in the database. Returns sqlite ok.
    int startTransaction(sqlite3* db) noexcept(false);

    //Rolls database back if transaction faild. Returns sqlite ok.
    int rollback(sqlite3* db) noexcept(false);

    //Commits changes if everything went fine. Returns sqlite ok.
    int commit(sqlite3* db) noexcept(false);

    //Runs a simple query that needs no output. returns 0 for failed or 1 for success.
    int simpleQuery(sqlite3* db, std::string query) noexcept(false);

    //Returns budget id as a int. Needs budget name. Tested Working**************
    int getBudgetID(std::string budgetName) noexcept(false);

    //Returns a vector of item id's. Needs a budget name. Tested Working**************
    std::vector<int> getItemIDList(std::string budgetName) noexcept(false);

    //Returns a id number for item. Tested Working**********
    int getItemID(std::string itemName) noexcept(false);

public:
    //Structs
    struct category {
        double total = 0;
        std::string name = "";//Name of category to add/alter.
    };

    struct item {
        double total = 0;//Current amount of line item. Default 0.
        double cap = 0;//Cap for budget line item. Default 0.
        std::string name = "";//Name of budget line item to add.
    };

    //Constructor
    Budget();

    //Destructor
    ~Budget();

    //Accessors
    //Returns double for budget total. Needs budget name. Tested Working*********
    double getBudgetTotal(std::string budgetName) noexcept(false);

    //Returns double for category total. Needs category name. Tested Working***********
    double getCategoryTotal(std::string categoryName) noexcept(false);

    //Returns double for item total. Needs item name. Tested Working******
    double getItemTotal(std::string itemName) noexcept(false);

    //Returns double for item cap. Needs item name. Tested Working******
    double getItemCap(std::string itemName) noexcept(false);

    //Returns vector of strings that are budget names. Tested Working********************
    std::vector<std::string> getBudgetList() noexcept(false);

    //Returns a list of category name strings. Needs a budget name.  Tested Working************
    std::vector<std::string> getCategoryList(std::string budgetName) noexcept(false);

    //Returns vector of item structs. Needs budget name. Tested Working****************
    std::vector<item> getItemList(std::string budgetName) noexcept(false);

    //Returns vector of doubles that are transaction amounts. Needs a budget name. Tested Working********************
    std::vector<double> getBudgetTransactionsList(std::string budgetName) noexcept(false);

    //Returns vector of doubles that are transaction amounts. Needs a item name. Tested Working********************
    std::vector<double> getItemTransactionsList(std::string itemName) noexcept(false);

    //Mutators
    //Needs a budget name, budget starting total, and vector of items. Tested Working*************
    void addBudget(std::string budgetName, double total, std::vector<item>& items) noexcept(false);

    //Needs a budget name. Tested Working**************
    void deleteBudget(std::string name) noexcept(false);

    //Needs a budget name and item struct. Tested Working*****************
    void addItem(std::string budgetName, item newItem) noexcept(false);

    //Deletes item from table and sets all related transactions to NULL item_id. Needs item name. Tested Working*****************
    void deleteItem(std::string itemName) noexcept(false);

    //Adds funds to total of a budget. Needs budget name and amount to add. Test Working***************
    void addFunds(std::string name, double amount) noexcept(false);

    //Adds a transaction. Needs a category name, item name, budget name, and amount of transaction. Tested Working***************
    void addExpense(std::string catName, std::string itemName, std::string budgetName, double amount) noexcept(false);

    //Adds a category. Needs a category name and a budget name it belongs to.
    void addCategory(std::string catName, std::string budgetName) noexcept(false);

    //Deletes a category. Needs a category name. Tested Working*************
    void deleteCategory(std::string catName) noexcept(false);

};//End of class
