#pragma once
#include "User.h"

class Foodie :
	public User
{
public:
	Foodie();
	virtual ~Foodie();

private:
	void order_history();
};

