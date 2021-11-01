#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#define NOMINMAX
#include <windows.h>
#include <ctime>
#include <SQLAPI.h>
#include <typeinfo>
using namespace std;

class User
{
protected:
	string Email;
	string Password;
	struct tm DOR;

public:
	User();
	virtual ~User();
	static int UserID;
	string Name;
	virtual User* Register(SAConnection& conn) = 0;
	virtual User* Login(SAConnection& conn) = 0;
	virtual void profile(SAConnection& conn) = 0;
	void get_type();
};


