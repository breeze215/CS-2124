/*
  rec03_start.cpp
 Uvindu Salgado
  2024 Fall
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account{
    string accountName;
    int accountNumber;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account2{
    friend ostream& operator<<(ostream& os, const Account2& randomAcc2);
public:
    Account2 (const string& accNamevar, int accNumVar) : accName(accNamevar), accNum(accNumVar) {}
    //const string& getAccName() const { return accName; }
    //int getAccNum() const { return accNum; }
private:
    string accName;
    int accNum;
};

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".
class Transaction{
    friend ostream& operator<<(ostream& os, const Transaction& randomTransac);
public:
    Transaction(const string& typeT, int amountT) : type(typeT), amount(amountT) {}
private:
    string type;
    int amount;
};

class Account3{
    friend ostream& operator<<(ostream& os, const Account3& randomAcc3);
public:
    //Account3(): Account3("", 0) {}
    Account3(const string& accName, int accNumT) : PersonName(accName), accountNum(accNumT), balance(0){}
    int getAccNum() const{ return accountNum; }
    void deposit(int amount){
        transactions.emplace_back("deposit", amount);
        balance += amount;
    }
    void withdrawal(int amount){
        if(balance < amount){
            cerr << "Insufficient funds" << endl;
            return;
        }
        transactions.emplace_back("withdraw", amount);
        balance -= amount;
    }
private:
    int balance;
    int accountNum;
    string PersonName;
    vector<Transaction> transactions;
};
// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class Account4{
    friend ostream& operator<<(ostream& os, const Account4& randomAcc4);
public:
    //Account4(): Account4("", 0) {}
    Account4(const string& accNameT, int accNumT) : PersonName2(accNameT), accountNum2(accNumT), balance2(0){}
    int getAccNum2() const{ return accountNum2; }
    void deposit2(int amount){
        transactions2.emplace_back("deposit", amount);
        balance2 += amount;
    }
    void withdrawal2(int amount){
        if(balance2 < amount){
            cerr << "Insufficient funds" << endl;
            return;
        }
        transactions2.emplace_back("withdraw", amount);
        balance2 -= amount;
    }
    class Transaction{
        friend ostream& operator<<(ostream& os, const Transaction& randomTransac);
    public:
        Transaction(const string& typeT, int amountT) : type2(typeT), amount2(amountT) {}
        const string& getT2() const{return type2;}
        int getAmount2() const {return amount2;}
    private:
        string type2;
        int amount2;
    };
private:
    int balance2;
    int accountNum2;
    string PersonName2;
    vector<Transaction> transactions2;
};

// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.
class Account5{
    class Transaction;
    friend ostream& operator<<(ostream& os, const Account5& randomAcc5);
    friend ostream& operator<<(ostream& os, const Transaction& randomTransac);
public:
   // Account5(): Account5("", 0) {}
    Account5(const string& accNameT, int accNumT) : PersonName3(accNameT), accountNum3(accNumT), balance3(0), transactions3{} {}
    int getAccNum3() const{ return accountNum3; }
    void deposit3(int amount){
        transactions3.emplace_back("deposit", amount);
        balance3 += amount;
    }
    void withdrawal3(int amount){
        if(balance3 < amount){
            cerr << "Insufficient funds" << endl;
            return;
        }
        transactions3.emplace_back("withdraw", amount);
        balance3 -= amount;
    }
private:
    class Transaction{
        friend ostream& operator<<(ostream& os, const Transaction& randomTransac);
    public:
        Transaction(const string& typeT, int amountT) : type3(typeT), amount3(amountT) {}
        const string& getT3() const{return type3;}
        int getAmount3() const {return amount3;}
    private:
        string type3;
        int amount3;
    };
    int balance3;
    int accountNum3;
    string PersonName3;
    vector<Transaction> transactions3;
};

//function prototypes
//ostream& operator<<(ostream& os, const Account2& randomAcc);
//ostream& operator<<(ostream& os, const Transaction& randomTransac);
//ostream& operator<<(ostream& os, const Account3& randomAcc3);
//ostream& operator<<(ostream& os, const Account4::Transaction& randomTransac);
//ostream& operator<<(ostream& os, const Account4& randomAcc4);
//ostream& operator<<(ostream& os, const Account5::Transaction& randomTransac);
//ostream& operator<<(ostream& os, const Account5& randomAcc5);

int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";
    ifstream accStream;
    accStream.open("accounts.txt");
    if(!accStream){
        cerr << "Could not open file accounts.txt" << endl;
        exit(1);
    }
    vector<Account> accVec;
    string name;
    int num;
    while(accStream >> name >> num){
        Account tempAcc;
        tempAcc.accountName = name;
        tempAcc.accountNumber = num;
        accVec.push_back(tempAcc);
    }
    accStream.close();
    for(const Account& currAccount : accVec){
        cout << "name: " << currAccount.accountName << ", Account number " << currAccount.accountNumber << endl;
    }
    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";
    accVec.clear();
    accStream.open("accounts.txt");
    while(accStream >> name >> num){
        Account tempAcc{name, num};
        accVec.push_back(tempAcc);
    }
    accStream.close();
    for(const Account& currAccount : accVec){
        cout << "name: " << currAccount.accountName << ", Account number" << currAccount.accountNumber << endl;
    }
    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
    vector<Account2> accVec2;
    accStream.open("accounts.txt");
    while(accStream >> name >> num){
        Account2 tempAcc(name, num);
        accVec2.push_back(tempAcc);
    }
    accStream.close();
    for(const Account2& currAccount : accVec2){
        //cout << "name: " << currAccount.getAccName() << ", Account number" << currAccount.getAccNum() << endl;
    }
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for(const Account2& currAccount : accVec2){
        cout << currAccount << endl;
    }

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
    for(const Account2& currAccount : accVec2){
        cout << currAccount << endl;
    }

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
    accVec2.clear();
    accStream.open("accounts.txt");
    while(accStream >> name >> num){
        accVec2.push_back(Account2(name, num));
    }
    accStream.close();
    
    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
    accVec2.clear();
    accStream.open("accounts.txt");
    while(accStream >> name >> num){
        accVec2.emplace_back(name, num);
    }
    accStream.close();
    for(const Account2& currAccount : accVec2){
        cout << currAccount << endl;
    }
    
    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
    ifstream transacStream;
    transacStream.open("transactions.txt");
    if(!transacStream){
        cerr << "Could not open transactions.txt" << endl;
        exit(1);
    }
    vector<Account3> accounts;
    string command;
    string personName;
    int accNumber;
    int amountT;
    while(transacStream >> command){
        if(command == "Account"){
            transacStream >> personName >> accNumber;
            accounts.emplace_back(personName, accNumber);
        }
        else if(command == "Deposit"){
            transacStream >> accNumber >> amountT;
            size_t index3 = accounts.size();
            for(size_t index = 0; index < accounts.size(); index++){
                if(accounts[index].getAccNum() == accNumber){
                    index3 = index;
                    break;
                }
            }
            accounts[index3].deposit(amountT);
        }
        else{
            transacStream >> accNumber >> amountT;
            size_t index3 = accounts.size();
            for(size_t index = 0; index < accounts.size(); index++){
                if(accounts[index].getAccNum() == accNumber){
                    index3 = index;
                    break;
                }
            }
            accounts[index3].withdrawal(amountT);
        }
    }
    transacStream.close();
    for(const Account3& tempAcc : accounts){
        cout << tempAcc << endl;
    }
    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
    transacStream.open("transactions.txt");
    vector<Account4> accounts2;
    while(transacStream >> command){
        if(command == "Account"){
            transacStream >> personName >> accNumber;
            accounts2.emplace_back(personName, accNumber);
        }
        else if(command == "Deposit"){
            transacStream >> accNumber >> amountT;
            size_t index1 = accounts2.size();
            for(size_t index = 0; index < accounts2.size(); index++){
                if(accounts2[index].getAccNum2() == accNumber){
                    index1 = index;
                    break;
                }
            }
            accounts2[index1].deposit2(amountT);
        }
        else{
            transacStream >> accNumber >> amountT;
            size_t index1 = accounts2.size();
            for(size_t index = 0; index < accounts2.size(); index++){
                if(accounts2[index].getAccNum2() == accNumber){
                    index1 = index;
                    break;
                }
            }
            accounts2[index1].withdrawal2(amountT);
        }
    }
    transacStream.close();
    for(const Account4& tempAcc : accounts2){
        cout << tempAcc << endl;
    }
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";
    transacStream.open("transactions.txt");
    vector<Account5> accounts3;
    while(transacStream >> command){
        if(command == "Account"){
            transacStream >> personName >> accNumber;
            accounts3.emplace_back(personName, accNumber);
        }
        else if(command == "Deposit"){
            transacStream >> accNumber >> amountT;
            size_t index2 = accounts3.size();
            for(size_t index = 0; index < accounts3.size(); index++){
                if(accounts3[index].getAccNum3() == accNumber){
                    index2 = index;
                    break;
                }
            }
            accounts3[index2].deposit3(amountT);
        }
        else{
            transacStream >> accNumber >> amountT;
            size_t index2 = accounts3.size();
            for(size_t index = 0; index < accounts3.size(); index++){
                if(accounts3[index].getAccNum3() == accNumber){
                    index2 = index;
                    break;
                }
            }
            accounts3[index2].withdrawal3(amountT);
        }
    }
    transacStream.close();
    for(const Account5& tempAcc : accounts3){
        cout << tempAcc << endl;
    }
    
}

ostream& operator<<(ostream& os, const Account2& randomAcc){
    //os << "Name: " << randomAcc.getAccName() << ", Number: " << randomAcc.getAccNum() << endl;
    os << "Name: " << randomAcc.accName << ", Number: " << randomAcc.accNum << endl;
    return os;
}

ostream& operator<<(ostream& os, const Transaction& randomTransac){
    os << "type: " << randomTransac.type << ", amount: " << randomTransac.amount;
    return os;
}

ostream& operator<<(ostream& os, const Account3& randomAcc3){
    os << "balance: " << randomAcc3.balance << endl;
    os << "Transactions: " << endl;
    for(const Transaction& currTransac : randomAcc3.transactions){
        cout << currTransac << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const Account4::Transaction& randomTransac){
    os << "type: " << randomTransac.type2 << ", amount: " << randomTransac.amount2;
    return os;
}

ostream& operator<<(ostream& os, const Account4& randomAcc4){
    os << "balance: " << randomAcc4.balance2 << endl;
    os << "Transactions: " << endl;
    for(const Account4::Transaction& currTransac : randomAcc4.transactions2){
        cout << currTransac << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const Account5::Transaction& randomTransac){
    os << "type: " << randomTransac.type3 << ", amount: " << randomTransac.amount3;
    return os;
}

ostream& operator<<(ostream& os, const Account5& randomAcc5){
    os << "balance: " << randomAcc5.balance3 << endl;
    os << "Transactions: " << endl;
    for(const Account5::Transaction& currTransac : randomAcc5.transactions3){
        cout << currTransac << endl;
    }
    return os;
}
