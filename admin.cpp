#include "admin.h"
#include "User.h"
#include<iostream>
#include"FileStream.h"
using namespace std;


Admin::Admin()
{
    this->listOfUser=FileStream::read();

}

void Admin::updateProfile(int id, string username, string password,double balance)
{
    this->listOfUser[id].setUsername(username);
     this->listOfUser[id].setPassword(password);
    if(balance==0.0){
         return;
    }else{
      this->listOfUser[id].setBalance(balance);
    }

}


bool Admin::loginAdmin(string userName,string password)
{
    if(userName == "010" && password == "123")
        return true;
    else
        return false;
}

bool Admin::signup(int id,string username, string pass,double balance)
{
    if (listOfUser.find(id) != listOfUser.end())
        return false;
    User user(username, pass,balance);
    listOfUser[id] = user;
    return true;
}

int Admin::login(int id, string pass)
{
    if (listOfUser.find(id) == listOfUser.end())
        return 0;
    if (listOfUser[id].getPassword() == pass)
        return id;
    return 0;
}



unordered_map<int, User>* Admin::getListOfUsers()
{
    return &listOfUser;
}

void Admin::deleteUser(int id)
{
	listOfUser.erase(id);
}

void Admin::suspendUser(int id,bool value)
{
	listOfUser.at(id).changeSuspended(value);
}

void Admin::viewAllTransactions(stack<Transaction>history)

{
	stack<Transaction>temp = history;
	for (int i = 0; i < history.size(); i++)
	{
		history.top();
		history.pop();
	}

}


void Admin::adjustBalance(int id, double balance)
{
	listOfUser.at(id).setBalance(balance);
}

Admin::~Admin()
{

}










