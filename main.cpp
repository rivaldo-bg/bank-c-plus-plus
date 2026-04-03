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
    string username;
    string password;
    bool loggedIn;

public:
    //Constructor to initialize the account
    BankAccount(string_view holder, string_view number, string_view user, string_view pass):
        accountHolder(holder), accountNumber(number), balance(0.0), username(user), password(pass), loggedIn(false) {}

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

    //Method to create a new account
    static BankAccount createAccount(string_view holder, string_view number, string_view user, string_view pass){
    return BankAccount(holder, number, user, pass);
    }

    //Method to authenticate user
    bool login(const string&user, const string&pass){
    if(username==user && password==pass){
        loggedIn = true;
        cout<<"Login successful!"<<endl;
        return true;
    }
    cerr << "Login failed: Incorrect username or password."<<endl;
    return false;
    }

    //Method to log out
    void logout(){
    loggedIn= false;
    cout << "Logged out successfully." <<endl;
    }

    //Method to check if the user is logged in
    bool isLoggedIn() const{
    return loggedIn;
    }
};
int main()
{
    try{
        //Create a new bank account
        BankAccount myAccount = BankAccount::createAccount("Alice Johnson", "123456789", "alice", "securePassword");

        //Attempt login
        if(myAccount.login("alice","securePassword")){
            myAccount.deposit(500);
            myAccount.saveToFile("account_data.txt");
            myAccount.displayAccountInfo();
            }

        //Log out
        myAccount.logout();

        //Attempt to log in with incorrect password
        if(!myAccount.login("alice","wrongPassword")){
            cout << "Please try again!" <<endl;
            }

        //Load account data
        BankAccount loadedAccount("","","","");
        loadedAccount.loadFromFile("account_data.txt");
        if(loadedAccount.login("alice","securePassword")){
            loadedAccount.displayAccountInfo();
            }
       }
    catch(const exception&e){
       cerr <<"Error: " <<e.what() <<endl;
       }

       return 0;
}
