#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <vector>
#include<ctime>
using namespace std;

class User
{
public:
    User();
    virtual ~User();
    static int ID;
    void Register();
    void Login();

protected:

private:
    string Name;
    string Email;
    string Password;
    struct tm * DOR;
};

void login_interface();