#include <iostream>
#include <vector>
using namespace std;

// ---------------- TRANSACTION CLASS ----------------
class Transaction {
public:
    string type;
    double amount;

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }

    void display() {
        cout << type << " : " << amount << endl;
    }
};

// ---------------- ACCOUNT CLASS ----------------
class Account {
public:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

    Account(int accNo) {
        accountNumber = accNo;
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposited: " << amount << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!" << endl;
            return;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdraw", amount));
        cout << "Withdrawn: " << amount << endl;
    }

    void transfer(Account &toAccount, double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!" << endl;
            return;
        }

        balance -= amount;
        toAccount.balance += amount;

        transactions.push_back(Transaction("Transfer Sent", amount));
        toAccount.transactions.push_back(Transaction("Transfer Received", amount));

        cout << "Transferred: " << amount << endl;
    }

    void showTransactions() {
        cout << "Transaction History:\n";
        for (auto &t : transactions) {
            t.display();
        }
    }

    void displayAccount() {
        cout << "Account No: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

// ---------------- CUSTOMER CLASS ----------------
class Customer {
public:
    int customerId;
    string name;
    vector<Account> accounts;

    Customer(int id, string n) {
        customerId = id;
        name = n;
    }

    void createAccount(int accNo) {
        accounts.push_back(Account(accNo));
        cout << "Account Created Successfully!" << endl;
    }

    Account* getAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.accountNumber == accNo) {
                return &acc;
            }
        }
        return NULL;
    }

    void displayCustomer() {
        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
    }
};

// ---------------- MAIN FUNCTION ----------------
int main() {
    Customer c1(1, "Aditya");
    Customer c2(2, "Rahul");

    c1.createAccount(101);
    c2.createAccount(201);

    Account* acc1 = c1.getAccount(101);
    Account* acc2 = c2.getAccount(201);

    if (acc1 && acc2) {
        acc1->deposit(1000);
        acc1->withdraw(200);
        acc1->transfer(*acc2, 300);

        cout << "\n--- Account 1 Details ---\n";
        acc1->displayAccount();
        acc1->showTransactions();

        cout << "\n--- Account 2 Details ---\n";
        acc2->displayAccount();
        acc2->showTransactions();
    }

    return 0;
}