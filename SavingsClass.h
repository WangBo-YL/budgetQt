//Savings Class Header File

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "sqlite3.h"

class Savings {
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

    //Returns savings id as a int. Needs savings name. Tested Working************
    int getSavingsID(std::string savingsName) noexcept(false);

public:
    //Constructor
    Savings();

    //Destructor
    ~Savings();

    //Accessors
    //Returns a double for goal. Needs a savings name. Tested Working**************
    double getGoal(std::string savingsName) noexcept(false);

    //Returns a double for total. Needs a savings name. Tested Working***************
    double getTotal(std::string savingsName) noexcept(false);

    //Returns a list of savings as strings. Tested Working*************
    std::vector<std::string> getSavingsList() noexcept(false);

    //Returns vector of doubles that are transaction amounts. Needs a savings name. Tested Working********************
    std::vector<double> getSavingsTransactionsList(std::string savingsName) noexcept(false);

    //Mutators
    //Deletes a savings after setting all related transactions to sav_id = NULL. Needs a savings name. Tested Working**************
    void deleteSavings(std::string savingsName) noexcept(false);

    //Changes a savings goal. Needs savings name and new goal amount. Tested Working************
    void changeGoal(std::string savingsName, double newGoal) noexcept(false);

    //Changes a savings total. Adds a transaction to reflect a deposit or withdraw. Needs savings name and new total amount. Tested Working************
    void changeTotal(std::string savingsName, double newTotal) noexcept(false);

    //Adds a savings. Needs a name and goal. Tested Working************
    void addSavings(std::string savingsName, double goal) noexcept(false);

};//End of class
