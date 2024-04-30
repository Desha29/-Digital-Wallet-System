#pragma once
#include <stack>
#include "Transaction.h"
#include <string>
using namespace std;
class User
{
	string username;
	string password;
	double balance;
	bool suspended;
	stack<Transaction> history;
	stack<string> requests;

public:
	User();
    User(string username, string password,double balance);
	User(string username, string password, double balance, stack<Transaction> history);
	string getUsername();
	string getPassword();
    double getBalance();
	bool getSuspended();
	void setUsername(string new_username);
	void setPassword(string new_password);
	void setBalance(double new_balance);
	void requestMoney(double amount, User& reciever);
	stack<Transaction> getHistory();
	stack<string> getRequests();
    bool sendMoney(int sender_id ,int reciever_id,double amount, User& reciever);
	void changeSuspended(bool value);
private:
    static string timeTransactions();
     void recieveMoney(int sender_id ,int reciever_id,double amount, User& reciever);

};

