#pragma once
#include "User.h"

class HomeCook :
	public User
{
public:
	HomeCook();
	virtual ~HomeCook();
	void show_recipe();

private:
	void upload_recipe();
	void edit_recipe();
	void orders_to_be_fulfilled();
};

