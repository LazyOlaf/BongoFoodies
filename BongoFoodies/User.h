#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <ctime>
using namespace std;

class User
{
public:
    User();
    virtual ~User();
    static int ID;
    string Register();
    string Login();

protected:

private:
    string Name;
    string Email;
    string Password;
    struct tm* DOR;
};

string login_interface();