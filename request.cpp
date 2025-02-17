#include "request.h"
using namespace std;
#include<iostream>
#include<string>
Request::Request(int id,int sender, int reciever, double amount,string date,string state)
{
    this->id=id;
    this->senderRequest = sender;
    this->recieverRequest = reciever;
    this->amount = amount;
    this->date = date;
    setStatusRequest(state);
}

int Request::getID()
{
    return this->id;
}

int Request::getSender()
{
    return this->senderRequest;
}

int Request::getReciever()
{
    return this->recieverRequest;
}

double Request::getAmount()
{
    return this->amount;
}
string Request::getDate()
{
    return this->date;
}

void Request::setStatusRequest(string state)
{
    if (state == "success") {
       this->state = StatusRequest::SUCCESS;
    } else if (state == "cancel") {
       this->state = StatusRequest::CANCEL;
    } else if (state == "Loading") {
       this->state = StatusRequest::Loading;
    } else {

    }
}

string Request::getStatusRequest()
{
    switch (state) {
    case StatusRequest::SUCCESS:
        return "success";
        break;
    case StatusRequest::Loading:
        return "loading";
        break;
    case StatusRequest::CANCEL:
        return "cancel";
        break;
    default:
        break;
    }
   return "loading";
}
