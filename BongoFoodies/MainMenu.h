#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "User.h"
//#include "Foodie.h"
//#include "HomeCook.h"
using namespace std;

class MainMenu
{
public:
	MainMenu();
	virtual ~MainMenu();
	void highlights();
	void browse();
	void tips();
	void login();

	bool logged_in;
	string username;
};

void main_menu();

