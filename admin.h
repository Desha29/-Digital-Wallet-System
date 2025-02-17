#pragma once
#include<string>
#include "User.h"
#include <stack>
#include "Transaction.h"
#include<unordered_map>

class Admin
{

    unordered_map<int, User> listOfUser;
    unordered_map<int, User> listOfDeletedUsers;


public:

    Admin();
    void updateProfile(int id,string username ,string password,double balance=0.0, bool suspended=false);
    bool loginAdmin(string userName, string password);
    bool signup(int id,string username,string pass,double balance);
    int login(int id, string pass);
    unordered_map<int, User>* getListOfUsers();
    unordered_map<int, User>* getListOfDeletedUsers();
    void deleteUser(int id);
    void suspendUser(int id,bool value);
    void adjustBalance(int id, double balance);
    ~Admin();
};

