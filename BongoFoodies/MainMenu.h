#pragma once
#include <stdlib.h>
#include "Foodie.h"
#include "HomeCook.h"
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
};

//extern bool logged_in;
User* login_interface(SAConnection& conn);
void main_menu();
//extern User* user_ptr;

