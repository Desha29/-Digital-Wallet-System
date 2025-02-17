#pragma once
#include<iostream>
#include<string>
using namespace std;
enum class StatusRequest {
    SUCCESS,
    CANCEL,
    Loading
};
class Request
{
    int senderRequest;
    int recieverRequest;
    int id;
    string date;
    double amount;
    StatusRequest state;
public:
    Request(int id,int sender, int reciever, double amount, string date,string state);
    int getID();
    int getSender();
    int getReciever();
    double getAmount();
    string getDate();
    void setStatusRequest(string state);
    string getStatusRequest();

};
