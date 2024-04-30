#include "User.h"
#include <iostream>
#include <string>



using namespace std;
User::User() {
	this->username="Gust";
	this->password="1";
    this->balance = 0.0;
}

User::User(string username, string password,double balance) {
	this->username=username;
	this->password=password;
    this->balance=balance;
}

User::User(string username, string password, double balance, stack<Transaction> history) {
	this->username=username;
	this->password=password;
	this->balance=balance;
	this->history=history;
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

    return balance;
}
stack<Transaction> User::getHistory() {
	return history;
}
stack<string> User::getRequests() {
	return requests;
}

bool User::getSuspended()
{
	return suspended;
}

void User::changeSuspended(bool value)
{
	suspended = value;
}
bool User::sendMoney(int sender_id ,int reciever_id,double amount, User& reciever) {
	if (this->balance >= amount) {
		this->balance -= amount;
        Transaction sendTransac(amount, sender_id, reciever_id, "send",User::timeTransactions());
        this->history.push(sendTransac);
        this->recieveMoney(sender_id,reciever_id,amount, reciever);

        return true;
	}
    return false;
}
void User::recieveMoney(int sender_id ,int reciever_id,double amount, User& reciever) {
	reciever.balance += amount;
    Transaction recieveTransac(amount, reciever_id, sender_id, "recieve", User::timeTransactions());
    reciever. history.push(recieveTransac);
}

void User::requestMoney(double amount, User& reciever) {
	cout << "the user: " << this->getUsername() << ", is requesting: " << amount << endl;
	reciever.requests.push("a request from: " + this->getUsername() + ", for a money transaction.");
}
string User::timeTransactions()
{
    time_t t = time(0);
    char date[30];
    ctime_s(date, sizeof(date), &t);


    return date;
}
