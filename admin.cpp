#include "admin.h"
#include "User.h"
#include<iostream>
#include"FileStream.h"

using namespace std;


Admin::Admin()
{
    vector<unordered_map<int, User>> allUsers= FileStream::read();
    this->listOfUser = allUsers[0];
    this->listOfDeletedUsers = allUsers[1];
}

void Admin::updateProfile(int id, string username, string password,double balance,bool suspended)
{
    this->listOfUser[id].setUsername(username);
    this->listOfUser[id].setPassword(password);
    this->listOfUser[id].changeSuspended(suspended);
    if(balance==0.0){
        return;
    }else{
        this->adjustBalance(id,balance);
    }

}


bool Admin::loginAdmin(string userName,string password)
{
    if(userName == "01000000000" && password == "123")
        return true;
    else
        return false;
}

bool Admin::signup(int id,string username, string pass,double balance)
{
    if(!(listOfDeletedUsers.find(id)==listOfDeletedUsers.end())){
        listOfDeletedUsers.erase(id);
    }
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

unordered_map<int, User> *Admin::getListOfDeletedUsers()
{
    return &listOfDeletedUsers;
}

void Admin::deleteUser(int id)
{
    listOfDeletedUsers.insert({id,listOfUser[id]});
    listOfUser.erase(id);
}

void Admin::suspendUser(int id,bool value)
{
    listOfUser.at(id).changeSuspended(value);
}




void Admin::adjustBalance(int id, double balance)
{
    listOfUser.at(id).setBalance(balance);
}

Admin::~Admin()
{
    FileStream::write(listOfUser, listOfDeletedUsers);
}










