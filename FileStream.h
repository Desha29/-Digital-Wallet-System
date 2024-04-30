#pragma once
#include<iostream>
#include <vector>
#include "User.h"
#include<unordered_map>
using namespace std;
class FileStream
{
	static string toFile(string name);
	static string fromFile(string name);
public:
    static unordered_map<int, User> read();
    static void write(unordered_map<int, User> users);
		
};

