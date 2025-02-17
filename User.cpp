#include "User.h"
#include <iostream>
#include <string>



using namespace std;
User::User() {
	this->username="Gust";
	this->password="1";
    this->balance = 0.0;
    this->incomes=0.0;
    this->expenses=0.0;

}

User::User(string username, string password,double balance) {
	this->username=username;
	this->password=password;
    this->balance=balance;
    this->incomes=0.0;
    this->expenses=0.0;
}

User::User(bool suspended,string username, string password, double balance,double incomes,double expenses, stack<Transaction> history,queue<Request> requests,queue<Request> requestsHistory) {
    this->suspended=suspended;
    this->username=username;
	this->password=password;
	this->balance=balance;
	this->history=history;
    this->requests=requests;
    this->requestsHistory=requestsHistory;
    this->incomes=incomes;
    this->expenses=expenses;
}



void User::removeRequest(int id)
{
    queue<Request> temp;
     while(!requests.empty()) {
        if (requests.front().getID() == id) {
             requests.pop();
            break;
        }
        else{
            temp.push(requests.front());
            requests.pop();
        }

    }
    while(!requests.empty()){
        temp.push(requests.front());
         requests.pop();

    }
    requests=temp;
}

void User::removeRequestHistory(int id)
{
    queue<Request> temp;
    while(!requestsHistory.empty()) {
        if (requestsHistory.front().getID() == id) {
            requestsHistory.pop();
            break;
        }
        else{
            temp.push(requestsHistory.front());
            requestsHistory.pop();
        }

    }
    while(!requestsHistory.empty()){
        temp.push(requestsHistory.front());
        requestsHistory.pop();

    }
    requestsHistory=temp;
}

void User::setUsername(string username) {
	this->username = username;
}
void User::setPassword(string password) {
	this->password = password;
}
void User::setBalance(double balance) {
    this->balance = balance;
}

string User::getUsername() {
	return username;
}
string User::getPassword() {
	return password;
}
double User::getBalance() {

    return  balance;
}

double User::getIncomes()
{
    return incomes;
}

double User::getExpenses()
{
    return expenses;
}
stack<Transaction> User::getHistory() {
	return history;
}
queue<Request> User::getRequests() {
    return  requests;
}

queue<Request> User::getRequestsHistory()
{
 return  requestsHistory;
}

bool User::getSuspended()
{
	return suspended;
}

void User::changeSuspended(bool value)
{
    this->suspended = value;
}

void User::changeStatus(int id,string state)
{
    queue<Request> temp;
    while(!requestsHistory.empty()) {
        if (requestsHistory.front().getID() == id) {
            requestsHistory.front().setStatusRequest(state);
            break;
        }
        else{
            temp.push(requestsHistory.front());
            requestsHistory.pop();
        }

    }
    while(!requestsHistory.empty()){
        temp.push(requestsHistory.front());
        requestsHistory.pop();

    }
    requestsHistory=temp;
}
bool User::sendMoney(int sender_id ,int reciever_id,double amount, User& reciever) {
	if (this->balance >= amount) {
		this->balance -= amount;
        Transaction sendTransac(amount, sender_id, reciever_id, "send",User::timeTransactions());
        this->history.push(sendTransac);
        this->recieveMoney(sender_id,reciever_id,amount, reciever);
        expenses+=amount;
        return true;
	}
    return false;
}
void User::recieveMoney(int sender_id ,int reciever_id,double amount, User& reciever) {
	reciever.balance += amount;
    Transaction recieveTransac(amount, reciever_id, sender_id, "recieve", User::timeTransactions());
    reciever. history.push(recieveTransac);
    reciever.incomes+=amount;
}

void User::requestMoney(int sender_id ,int reciever_id,double amount, User& reciever) {

    srand(time(0));
    int randomNumber = rand() % 999999999 + 1;

    Request request=Request(randomNumber,sender_id,reciever_id,amount,User::timeTransactions(),"loading");
    reciever.requests.push(request);
    this->requestsHistory.push(request);
}
string User::timeTransactions()
{
    time_t t = time(0);
    char date[30];
    ctime_s(date, sizeof(date), &t);


    return date;
}
