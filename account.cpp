/*
Author: Kusuma Murthy
KUID: 3095756
Date: 11/22/2023
Lab: Ectra Credit Lab 11
Last modified: 11/25/2023
Purpose: Design a simple banking system that utilizes inheritance and operator overloading to handle transactions between different types of bank accounts.
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Account Parent Class
/*
Base class for all types of bank accounts.
Properties: accountNumber, accountHolder, balance.
Methods:
displayDetails(): Display account details.
deposit(amount): Deposit money into the account.
withdraw(amount): Withdraw money from the account (ensure sufficient balance).
*/
class Account
{
public:
    string accountNumber;
    string accountHolder;
    double balance;

    Account(const string number, const string holder, double bal)
        : accountNumber(number), accountHolder(holder), balance(bal) {}

    void displayDetails()
    {
        cout << *this;
    }

    void deposit(double amount)
    {
        balance += amount;
    }

    virtual void withdraw(double amount)
    {
        balance -= amount;
    }

    friend ostream &operator<<(ostream &output, Account &bankAccount)
    {
        output << " Holder: " << bankAccount.accountHolder << endl;
        output << " Balance: " << bankAccount.balance << endl;
        return output;
    }
};

// Savings Account
/*
Derived class from the Account class.
Additional properties: interestRate.
Override the withdraw method to enforce a minimum balance.
*/
class SavingsAccount : public Account
{

protected:
    double interestRate;

public:
    SavingsAccount(const string number, const string holder, double bal, const double iR)
        : Account(number, holder, bal), interestRate(iR) {}

    void displayDetails()
    {
        cout << "Account Details for Savings Account (ID: " << accountNumber << "):" << endl;
        cout << *this; // gets it from the << operator in the account (parent) class
        double percentage = 0;
        percentage = interestRate * 100;
        cout << " Interest Rate: " << fixed << setprecision(2) << percentage << "%" << endl;
        cout << "" << endl;
    }

    void withdraw(double amount)
    {
        const double min_bal = 50; // you can set what the minimum value can be, for the purpsoe of this lab I chose 50
        if ((balance - amount) >= min_bal)
            balance -= amount;
        else
            cout << "Withdrawal not allowed as the requested withdrawal amount is greater than the required minimum balance" << endl;
    }

    SavingsAccount &operator+(Account &other)
    {
        double transfer = 300;
        if (other.balance >= transfer)
        {
            deposit(transfer);
            other.withdraw(transfer);
            return *this;
        }

        else
        {
            return *this;
        }
    }
};

// Current Account
/*
Derived class from the Account class.
Additional properties: overdraftlimit.
Override the withdraw method to allow overdrafts up to the specified limit.
*/
class CurrentAccount : public Account
{
protected:
    double overdraftLimit;

public:
    CurrentAccount(const string number, const string holder, double bal, double oL)
        : Account(number, holder, bal), overdraftLimit(oL) {}

    void displayDetails()
    {
        cout << "Account Details for Current Account (ID: " << accountNumber << "):" << endl;
        cout << *this; // gets it from the << operator in the account (parent) class
        cout << " Overdraft Limit: $" << overdraftLimit << endl;
        cout << "" << endl;
    }

    void withdraw(double amount)
    {
        if ((balance + overdraftLimit) >= amount)
            balance -= amount;
        else
            cout << "Withdrawal not allowed as the overdraft limit will be exceeded" << endl;
    }

    CurrentAccount &operator+(Account &other)
    {
        double transfer = 300;
        if (other.balance >= transfer)
        {
            deposit(transfer);
            other.withdraw(transfer);
            return *this;
        }

        else
        {
            return *this;
        }
    }
};

// main function
int main()
{
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdraw(1000);

    cout << "Account Details after deposit and withdrawal:" << endl; // added this because the output was formated this way
    savings.displayDetails();
    current.displayDetails();

    // Transfer 300 from savings to current
    current = current + savings;

    cout << "Account Details after transfer:" << endl; // added this because the output was formated this way
    savings.displayDetails();
    current.displayDetails();

    return 0;
}
