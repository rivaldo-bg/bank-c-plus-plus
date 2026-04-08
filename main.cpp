#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

class BankAccount{
private:
    std::string accountHolder;
    std::string accountNumber;
    double balance;
    std::string username;
    std::string password;
    bool loggedIn;

public:
    //Constructor to initialize the account
    BankAccount(std::string_view holder, std::string_view number, std::string_view user, std::string_view pass):
        accountHolder(holder), accountNumber(number), balance(0.0), username(user), password(pass), loggedIn(false) {}

    //Method to deposit money into the account
    void deposit(double amount){
       if(amount <= 0){
        throw std::invalid_argument("Deposit amount must be positive!");
       }
       balance+= amount;
       std::cout<< "Deposited: " << amount << " New balance: " << balance << std::endl;
    }

    //Method to withdraw money from the account
    void withdraw(double amount){
       if(amount <= 0){
        throw std::invalid_argument("Withdrawal amount must be positive!");
       }
       if(amount > balance){
        throw std::out_of_range("Insufficient funds");
       }
       balance-=amount;
       std::cout << "Withdrew: " <<amount <<" New Balance: "<< balance << std::endl;
    }

    //Method to check the current balance
    double getBalance() const{
    return balance;
    }

    //Method to display account information
    void displayAccountInfo() const{
        std::cout << "Account Holder: " << accountHolder << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Balance: " <<balance << std::endl;
    }

    //Method to save account data to a file
    void saveToFile(const std::string&filename) const{
            std::ofstream outFile(filename);
    if(!outFile){
        throw std::ios_base::failure("Failed to open file for writing.");
    }
    outFile << accountHolder <<"\n"
            << accountNumber <<"\n"
            << balance <<"\n"
            << username <<"\n"
            << password <<"\n";
    }

    //Method to load account data from a file
    void loadFromFile(const std::string&filename){
            std::ifstream inFile(filename);
            if(!inFile){
                throw std::ios_base::failure("Failed to open file for reading");
            }
            std::getline(inFile, accountHolder);
            std::getline(inFile, accountNumber);
            inFile >> balance;
            inFile.ignore();
            std::getline(inFile, username);
            std::getline(inFile, password);
    }

    //Method to create a new account
    static BankAccount createAccount(std::string_view holder, std::string_view number, std::string_view user, std::string_view pass){
    return BankAccount(holder, number, user, pass);
    }

    //Method to authenticate user
    bool login(const std::string&user, const std::string&pass){
    if(username==user && password==pass){
        loggedIn = true;
        std::cout <<"Login successful!"<< std::endl;
        return true;
    }
    std::cerr << "Login failed: Incorrect username or password."<< std::endl;
    return false;
    }

    //Method to log out
    void logout(){
    loggedIn= false;
    std::cout << "Logged out successfully." << std::endl;
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
            std::cout << "Please try again!" << std::endl;
            }

        //Load account data
        BankAccount loadedAccount("","","","");
        loadedAccount.loadFromFile("account_data.txt");
        if(loadedAccount.login("alice","securePassword")){
            loadedAccount.displayAccountInfo();
            }
       }
    catch(const std::exception&e){
       std::cerr <<"Error: " <<e.what() << std::endl;
       }

       return 0;
}
