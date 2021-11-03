#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#pragma once


//This is the latest we got
using namespace std;



/*Payment class and its inheritance, Order*/

class Payment
{
private:

public:
    int paid, totalAmount;
    virtual void checkPayment(double totalAmount, double paid)=0;
};

