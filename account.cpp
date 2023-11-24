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

}
/*
Derived class from the Account class.
Additional properties: overdraftlimit.
Override the withdraw method to allow overdrafts up to the specified limit.
*/

/*
Derived class from the Account class.
Additional properties: interestRate.
Override the withdraw method to enforce a minimum balance.
*/