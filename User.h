#pragma once
#include <stack>
#include <queue>
#include "Transaction.h"
#include <string>
#include"request.h"
#include <ctime>
using namespace std;
class User
{
	string username;
	string password;
	double balance;
    double incomes;
    double expenses;
    bool suspended=false;
	stack<Transaction> history;
    queue<Request> requests;
    queue<Request> requestsHistory;

public:
	User();
    User(string username, string password,double balance);
    User(bool suspended,string username, string password, double balance,double incomes,double expenses, stack<Transaction> history,queue<Request> requests,queue<Request> requestsHistory);
    void removeRequest(int id);
    void removeRequestHistory(int id);
	string getUsername();
	string getPassword();
    double getBalance();
    double getIncomes();
    double getExpenses();
	bool getSuspended();
	void setUsername(string new_username);
	void setPassword(string new_password);
	void setBalance(double new_balance);
    void requestMoney(int sender_id ,int reciever_id,double amount, User& reciever);
	stack<Transaction> getHistory();
    queue<Request> getRequests();
    queue<Request> getRequestsHistory();
    bool sendMoney(int sender_id ,int reciever_id,double amount, User& reciever);
	void changeSuspended(bool value);
    void changeStatus(int id,string state);

private:
    static string timeTransactions();
     void recieveMoney(int sender_id ,int reciever_id,double amount, User& reciever);

};

