#pragma once
#include "User.h"
#include "Recipe.h"

class HomeCook :
	public User
{
public:
	HomeCook();
	virtual ~HomeCook();
	void show_recipes();
	void profile(SAConnection& conn);

	virtual HomeCook* Register(SAConnection& conn);
	virtual HomeCook* Login(SAConnection& conn);

private:
	//void upload_recipe();
	void edit_recipe();
	void orders_to_be_fulfilled();
};

