#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

class BankAccount{
private:
    string accountHolder;
    string accountNumber;
    double balance;

public:
    //Constructor to initialize the account
    BankAccount(const string&holder, const string&number)
    :accountHolder(holder), accountNumber(number), balance(0.0){}

    //Method to deposit money into the account
    void deposit(double amount){
       if(amount <= 0){
        throw invalid_argument("Deposit amount must be positive!");
       }
       balance+= amount;
       cout<< "Deposited: " << amount << " New balance: "<< balance <<endl;
    }

    //Method to withdraw money from the account
    void withdraw(double amount){
       if(amount <= 0){
        throw invalid_argument("Withdrawal amount must be positive!");
       }
       if(amount > balance){
        throw out_of_range("Insufficient funds");
       }
       balance-=amount;
       cout<< "Withdrew: " <<amount <<" New Balance: "<< balance <<endl;
    }

    //Method to check the current balance
    double getBalance() const{
    return balance;
    }

    //Method to display account information
    void displayAccountInfo() const{
        cout << "Account Holder: " << accountHolder <<endl;
        cout << "Account Number: " << accountNumber <<endl;
        cout << "Balance: " <<balance <<endl;
    }

    //Method to save account data to a file
    void saveToFile(const string&filename) const{
            ofstream outFile(filename);
    if(!outFile){
        throw ios_base::failure("Failed to open file for writing.");
    }
    outFile << accountHolder <<"\n"
            << accountNumber <<"\n"
            << balance <<"\n";
    }

    //Method to load account data from a file
    void loadFromFile(const string&filename){
            ifstream inFile(filename);
            if(!inFile){
                throw ios_base::failure("Failed to open file for reading");
            }
            getline(inFile, accountHolder);
            getline(inFile, accountNumber);
            inFile >> balance;
    }
};
int main()
{
    try{
        //Create a new bank account for Alice
        BankAccount myAccount("Alice Johnson", "123456789");
        myAccount.displayAccountInfo();

        //Performs some transactions
        myAccount.deposit(500);
        myAccount.withdraw(200);
        cout << "Current balance: "<< myAccount.getBalance() <<endl;

        //Attempt to withdraw more than the balance
        myAccount.withdraw(400);//This will throw an exception
       }
    catch(const exception&e){
       cerr <<"Error: " <<e.what() <<endl;
       }

       return 0;
}
