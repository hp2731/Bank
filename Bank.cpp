#include <bits/stdc++.h>
using namespace std;
#define MIN_BALANCE -FLT_MAX
class InsufficientFunds
{
};
class Account
{
private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    static long NextAccountNumber;
    int pin;

public:
    Account() {}
    Account(string fname, string lname, float balance, int pin);
    long getAccountNumber() { return accountNumber; }
    int getPin() { return pin; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    float getBalance() { return balance; }

    void Deposit(float amount);
    void Withdraw(float amount);
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();
    friend ofstream &operator<<(ofstream &ofs, Account &acc);
    friend ifstream &operator>>(ifstream &ifs, Account &acc);
    friend ostream &operator<<(ostream &os, Account &acc);
};
long Account::NextAccountNumber = 0;
class Bank
{
private:
    map<long, Account> accounts;

public:
    Bank();
    Account OpenAccount(string fname, string lname, float balance, int pin);
    float BalanceEnquiry(long accountNumber, int pin);
    Account Deposit(long accountNumber, float amount, int pin);
    Account Withdraw(long accountNumber, float amount, int pin);
    void Transfer(long senderAccountNumber, long receiverAccountNumber, float amount, int senderPin);
    void CloseAccount(long accountNumber, int pin);
    void ShowAllAccounts();
    ~Bank();
};
int main(void)
{
    Bank bank;
    Account account;

    int choice;
    string fname, lname;
    long accountNumber;
    long senderAccountNumber;
    long receiverAccountNumber;
    float balance;
    float amount;
    int pin;
    cout << "Banking System" << endl;
    do
    {
        cout << "\n\tSelect one option below ";
        cout << "\n\t1 Open an Account";
        cout << "\n\t2 Balance Enquiry";
        cout << "\n\t3 Deposit";
        cout << "\n\t4 Withdrawal";
        cout << "\n\t5 Transfer";
        cout << "\n\t6 Close an Account";
        cout << "\n\t7 Show All Accounts";
        cout << "\n\t8 Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter First Name: ";
            cin >> fname;
            cout << "Enter Last Name: ";
            cin >> lname;
            cout << "Enter initial Balance: ";
            cin >> balance;
            cout << "Enter pin: ";
            cin >> pin;
            account = bank.OpenAccount(fname, lname, balance, pin);
            cout << endl
                 << "Congratulations, Account is Created" << endl;
            cout << account;
            break;
        case 2:
            cout << "Enter Account Number:";
            cin >> accountNumber;
            cout << "Enter pin: ";
            cin >> pin;
            cout << endl
                 << "Your Balance is " << bank.BalanceEnquiry(accountNumber, pin) << endl;
            break;
        case 3:
            cout << "Enter Account Number:";
            cin >> accountNumber;
            cout << "Enter Balance:";
            cin >> amount;
            cout << "Enter pin: ";
            cin >> pin;
            account = bank.Deposit(accountNumber, amount, pin);
            cout << endl
                 << "Amount is Deposited" << endl;
            cout << account;
            break;
        case 4:
            cout << "Enter Account Number:";
            cin >> accountNumber;
            cout << "Enter Balance:";
            cin >> amount;
            cout << "Enter pin: ";
            cin >> pin;
            account = bank.Withdraw(accountNumber, amount, pin);
            cout << endl
                 << "Amount Withdrawn" << endl;
            cout << account;
            break;
        case 5:
            cout << "Enter sender account Number:";
            cin >> senderAccountNumber;
            cout << "Enter receiver account Number:";
            cin >> receiverAccountNumber;
            cout << "Enter Balance:";
            cin >> amount;
            cout << "Enter pin: ";
            cin >> pin;
            bank.Transfer(senderAccountNumber, receiverAccountNumber, amount, pin);
            break;
        case 6:
            cout << "Enter Account Number:";
            cin >> accountNumber;
            cout << "Enter pin: ";
            cin >> pin;
            bank.CloseAccount(accountNumber, pin);
            cout << endl
                 << "Account is Closed" << endl;
            cout << account;
        case 7:
            bank.ShowAllAccounts();
            break;
        case 8:
            break;
        default:
            cout << "\nEnter correct choice";
            exit(0);
        }
    } while (choice != 8);
}
Account::Account(string firstName, string lastName, float balance, int pin)
{
    NextAccountNumber++;
    accountNumber = NextAccountNumber;
    this->firstName = firstName;
    this->lastName = lastName;
    this->balance = balance;
    this->pin = pin;
}
void Account::Deposit(float amount)
{
    balance += amount;
}
void Account::Withdraw(float amount)
{
    if (balance - amount < MIN_BALANCE)
        throw InsufficientFunds();
    balance -= amount;
}
void Account::setLastAccountNumber(long accountNumber)
{
    NextAccountNumber = accountNumber;
}
long Account::getLastAccountNumber()
{
    return NextAccountNumber;
}
ofstream &operator<<(ofstream &ofs, Account &acc)
{
    ofs << acc.accountNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.balance << endl;
    ofs << acc.pin << endl;
    return ofs;
}
ifstream &operator>>(ifstream &ifs, Account &acc)
{
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    ifs >> acc.pin;
    return ifs;
}
ostream &operator<<(ostream &os, Account &acc)
{
    os << "First Name:" << acc.getFirstName() << endl;
    os << "Last Name:" << acc.getLastName() << endl;
    os << "Account Number:" << acc.getAccountNumber() << endl;
    os << "Balance:" << acc.getBalance() << endl;
    os << "Pin:" << acc.getPin() << endl;
    return os;
}
Bank::Bank()
{

    Account account;
    ifstream infile;
    infile.open("Bank.data");
    if (!infile)
        return;
    while (!infile.eof())
    {
        infile >> account;
        accounts.insert(pair<long, Account>(account.getAccountNumber(), account));
    }
    Account::setLastAccountNumber(account.getAccountNumber());
    infile.close();
}
Account Bank::OpenAccount(string fname, string lname, float balance, int pin)
{
    Account account(fname, lname, balance, pin);
    accounts.insert(pair<long, Account>(account.getAccountNumber(), account));
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);
    map<long, Account>::iterator itr; // writing into the Bank.data file
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
        outfile << itr->second;
    outfile.close();
    return account;
}
float Bank::BalanceEnquiry(long accountNumber, int pin)
{
    map<long, Account>::iterator account = accounts.find(accountNumber);
    if (account->second.getPin() == pin)
        return account->second.getBalance();
    return -1;
}
Account Bank::Deposit(long accountNumber, float amount, int pin)
{
    map<long, Account>::iterator account = accounts.find(accountNumber);
    if (account->second.getPin() == pin)
        account->second.Deposit(amount);
    return account->second;
}
Account Bank::Withdraw(long accountNumber, float amount, int pin)
{
    map<long, Account>::iterator account = accounts.find(accountNumber);
    if (account->second.getPin() == pin)
        account->second.Withdraw(amount);
    return account->second;
}
void Bank::Transfer(long senderAccountNumber, long receiverAccountNumber, float amount, int senderPin)
{
    map<long, Account>::iterator sender = accounts.find(senderAccountNumber);
    map<long, Account>::iterator receiver = accounts.find(receiverAccountNumber);
    if (sender->second.getPin() == senderPin)
    {
        sender->second.Withdraw(amount);
        receiver->second.Deposit(amount);
    }
    cout << "Amount transferred from " << senderAccountNumber << " to " << receiverAccountNumber << endl;
}
void Bank::CloseAccount(long accountNumber, int pin)
{
    map<long, Account>::iterator account = accounts.find(accountNumber);
    if (account->second.getPin() == pin)
    {
        accounts.erase(accountNumber);
        cout << "Account Deleted" << account->second;
    }
}
void Bank::ShowAllAccounts()
{
    map<long, Account>::iterator account;
    for (account = accounts.begin(); account != accounts.end(); account++)
        cout << "Account " << account->first << endl
             << account->second << endl;
}
Bank::~Bank()
{
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);
    map<long, Account>::iterator account;
    for (account = accounts.begin(); account != accounts.end(); account++)
        outfile << account->second;
    accounts.clear();
    outfile.close();
}