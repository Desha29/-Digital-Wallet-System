#pragma once
#include <string>
using namespace std;
class Transaction
{
	double amount;
    int sender;
    int reciever;
	string transacType;

public:
    string date;
    Transaction(double amount, int sender, int reciever, string transacType,string date);
    int getSender();
    int getReciever();
	string getTransacType();
	double getAmount();
};

