#pragma once
#include "User.h"
#include "Recipe.h"

class HomeCook :
	public User
{
public:
	HomeCook();
	virtual ~HomeCook();
	void profile(SAConnection& conn);

	virtual HomeCook* Register(SAConnection& conn);
	virtual HomeCook* Login(SAConnection& conn);
};

