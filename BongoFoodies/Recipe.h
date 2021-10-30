#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#define NOMINMAX
#include <windows.h>
#include <SQLAPI.h>
using namespace std;

class Recipe
{
protected:
	string title;
	string cook_name;
	string region;
	double time;
	int servings;
	vector<string> ingredients;
	string procedure;	
	double rating = 0;
	vector<string> delivery_area;
	double price = 0;

public:
	Recipe();
	virtual ~Recipe();
	static int RecipeID;

	void upload_recipe(SAConnection& conn, int cook_ID);
	//void show_recipe();
	//void show_cook_profile();
	//void order_recipe();
	//void download_recipe();
	//void give_feedback();

	friend class HomeCook;
};

		