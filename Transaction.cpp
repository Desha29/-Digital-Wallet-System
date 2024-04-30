#include "Transaction.h"
#include <string>
Transaction::Transaction(double amount, int sender, int reciever, string transacType,string date)
{
    this->sender = sender;
    this->reciever = reciever;
	this->amount = amount;
	this->transacType = transacType;
    this->date = date;
}

int Transaction::getSender() {
    return sender;
}

int Transaction::getReciever() {
    return reciever;
}

string Transaction::getTransacType() {
	return transacType;
}

double Transaction::getAmount() {
	return amount;
}
